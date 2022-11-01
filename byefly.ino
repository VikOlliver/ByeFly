/*
byefly - Code to thrash two servos around in a pseudo-random manner with manual override.

The concept is that one servo is attached to another at 90 degrees, and the free servo arm has a flexible steel wire on it. At the end of the wire is a tassle of some kind. The servo assemby is attached to a support in the middle of the table, and waves the tassle around scaring off the flies. 

Push the joystick button and it switches to manual mode.

Placed in the public domain in 2022 by Vik Olliver of the Masterton Fab Lab.

 Parts required:
 2 servo motors on pins 8 & 9
 optional joystick on A0 A1, with button wired to A2
 
 */

// include the servo library
#include <Servo.h>

#define SWITCH_PIN A2

Servo xServo;  // create servo objects
Servo yServo;

int xAngle;   // variable to hold the angle for the servo motor
int yAngle;

void setup() {
  xServo.attach(9); // attaches the servo on pin 9 to the servo object
  yServo.attach(8);
  pinMode(SWITCH_PIN,INPUT);
  Serial.begin(9600); // open a serial connection to your computer
}

void randomLoop() {
  int i=0;
    int j=0;
    while (digitalRead(SWITCH_PIN)==0) {
          xAngle=abs(180-i);
          yAngle=abs(180-j);
          // set the servo positions
          xServo.write(xAngle);
          yServo.write(yAngle);
        // wait for the servo to get there
          delay(60);
          j+=7;
          if (j>360) j-=360;
          i+=17;
          if (i>360) i-=360;
    }
}

void manualLoop() {
  while (digitalRead(SWITCH_PIN)==0) {
  xAngle = map(analogRead(A0), 0, 1023, 0, 179);
  yAngle = map(analogRead(A1), 0, 1023, 0, 179);
  // set the servo positions
  xServo.write(xAngle);
  yServo.write(yAngle);
  // wait for the servo to get there
  delay(15);
  }
}

void loop() {
  randomLoop();
  while (digitalRead(SWITCH_PIN)==1);
  manualLoop();
  while (digitalRead(SWITCH_PIN)==1);
}
