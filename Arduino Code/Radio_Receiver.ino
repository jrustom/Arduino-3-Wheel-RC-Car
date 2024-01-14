#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CNS
const byte address[6] = {"00001"};

//Define pin numbers
int EnableA = 9;
int dir_1 = 3;
int dir_2 = 4;
int EnableB = 10;
int dir_3 = 5;
int dir_4 = 6;
int left_light = 19;
int right_light = 18;

struct S_y_value{
  int left;
  int right;
};
S_y_value y_value;

void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(EnableA, OUTPUT);
  pinMode(EnableB, OUTPUT);
  pinMode(dir_1, OUTPUT);
  pinMode(dir_2, OUTPUT);
  pinMode(dir_3, OUTPUT);
  pinMode(dir_4, OUTPUT);
  pinMode(left_light, OUTPUT);
  pinMode(right_light, OUTPUT);
}

void loop() {
  if (radio.available()){
  //Get joystick data from controller
   radio.read(&y_value, sizeof(y_value));
   /*Joystick transmits values between 0 and 1023. In this case,
   values between (0,480) result in forward movement, values
   between (480,520) result in no movement and values between
   (520,1023) result in backward movement
   */
   if (y_value.right < 480){
    digitalWrite(dir_1, HIGH);
    digitalWrite(dir_2, LOW);
    analogWrite(EnableA, map(y_value.right, 480, 0, 60, 255));
   }
   else if (y_value.right > 520){
    digitalWrite(dir_1, LOW);
    digitalWrite(dir_2, HIGH);
    analogWrite(EnableA, map(y_value.right, 520, 1023, 60, 255));
   }
   else{
    digitalWrite(dir_1, LOW);
    digitalWrite(dir_2, LOW);
   } 

   if (y_value.left < 480){
    digitalWrite(dir_3, HIGH);
    digitalWrite(dir_4, LOW);
    analogWrite(EnableB, map(y_value.left, 480, 0, 60, 255));
   }
   else if (y_value.left > 520){
    digitalWrite(dir_3, LOW);
    digitalWrite(dir_4, HIGH);
    analogWrite(EnableB, map(y_value.left, 520, 1023, 60, 255));
   }
   else{
    digitalWrite(dir_3, LOW);
    digitalWrite(dir_4, LOW);
  }

  //Make sure right motor is not rotating backwards, but faster than left motor (with margin of 20)
  if (y_value.right < 520 && y_value.right < y_value.left - 20){
    digitalWrite(left_light, HIGH);
    digitalWrite(right_light, LOW);
  }
  else if (y_value.left < 520 && y_value.left < y_value.right - 20){
    digitalWrite(left_light, LOW);
    digitalWrite(right_light, HIGH);
  }
  else{
    digitalWrite(left_light, LOW);
    digitalWrite(right_light, LOW);
  }
 }
}
