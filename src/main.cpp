#include <Arduino.h>
#include <L298NX2.h>

#define SPEED_COEF 2

L298NX2 motor1(1, 2, 3, 4, 5, 6);
L298NX2 motor2(1, 2, 3, 4, 5, 6);

void setup() { Serial.begin(9600); }

void stop() {
  motor1.stop();
  motor2.stop();
}

void forward() {
  motor1.forward();
  motor2.forward();
}

void backward() {
  motor1.backward();
  motor2.backward();
}

void left() {
  motor1.forward();
  motor2.backward();
}

void right() {
  motor1.backward();
  motor2.forward();
}

void forwardLeft() {
  short speed = motor1.getSpeedA();

  motor1.setSpeedA(speed / SPEED_COEF);
  motor2.setSpeedA(speed / SPEED_COEF);

  motor1.forward();
  motor2.forward();

  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
}

void forwardRight() {
  short speed = motor1.getSpeedA();

  motor1.setSpeedB(speed / SPEED_COEF);
  motor2.setSpeedB(speed / SPEED_COEF);

  motor1.forward();
  motor2.forward();

  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
}

void backwardLeft() {
  short speed = motor1.getSpeedA();

  motor1.setSpeedA(speed / SPEED_COEF);
  motor2.setSpeedA(speed / SPEED_COEF);

  motor1.backward();
  motor2.backward();

  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
}

void backwardRight() {
  short speed = motor1.getSpeedA();

  motor1.setSpeedB(speed / SPEED_COEF);
  motor2.setSpeedB(speed / SPEED_COEF);

  motor1.backward();
  motor2.backward();

  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    stop();

    switch (command) {
    case 'F':
      forward();
      break;
    case 'B':
      backward();
      break;
    case 'L':
      left();
      break;
    case 'R':
      right();
      break;
    case 'G':
      forwardLeft();
      break;
    case 'I':
      forwardRight();
      break;
    case 'H':
      backwardLeft();
      break;
    case 'J':
      backwardRight();
      break;
    case '0':
      motor1.setSpeed(0);
      motor2.setSpeed(0);
      break;
    case '1':
      motor1.setSpeed(140);
      motor2.setSpeed(140);
      break;
    case '2':
      motor1.setSpeed(153);
      motor2.setSpeed(153);
      break;
    case '3':
      motor1.setSpeed(165);
      motor2.setSpeed(165);
      break;
    case '4':
      motor1.setSpeed(178);
      motor2.setSpeed(178);
      break;
    case '5':
      motor1.setSpeed(191);
      motor2.setSpeed(191);
      break;
    case '6':
      motor1.setSpeed(204);
      motor2.setSpeed(204);
    case '7':
      motor1.setSpeed(216);
      motor2.setSpeed(216);
      break;
    case '8':
      motor1.setSpeed(229);
      motor2.setSpeed(229);
      break;
    case '9':
      motor1.setSpeed(242);
      motor2.setSpeed(242);
      break;
    case 'q':
      motor1.setSpeed(255);
      motor2.setSpeed(255);
      break;
    }
  }
}