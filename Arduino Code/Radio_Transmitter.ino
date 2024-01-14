#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CNS

const byte address[6] = {"00001"};

struct S_y_value{
  int left;
  int right;
};
S_y_value y_value;

int y_pin_right = A0;
int y_pin_left = A1;

void setup() {
  radio.begin();
  radio.openWritingPipe(address); // 00001
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}

void loop() {
  //Collect joystick data
  y_value.right = analogRead(y_pin_right);
  y_value.left = analogRead(y_pin_left);
  //Transmit joystick data
  radio.write(&y_value, sizeof(y_value));

}
