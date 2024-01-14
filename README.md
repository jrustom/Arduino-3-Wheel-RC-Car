# Arduino-3-Wheel-RC-Car
This repository includes all files that are part of the 2023 Winter term project for the Physics for Engineers class at John Abbott College in Montreal, Canada.

For this term, our challenge was to create a three-wheeled car that would be tested in two different ways. The first would be a timed lap of a small track and the second would be the maximum distance achieved from launching off a ramp.

I led a team of three other students; developing the codebase and electrical circuitry while they worked on the manufacturing of the chassis of the car. After some careful consideration, our team decided that wireless control would offer the best accuracy while allowing for the free movement of the car (as opposed to having to follow it with physical wires). More specifically, we deployed two NRF24L01 tranceiver modules, one for the controller and one on the car, to allow for wireless communication of data. We also used two joysticks, one for each driving wheel of the car, to allow for higher precision and control in turns.

