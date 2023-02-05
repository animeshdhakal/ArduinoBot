#include <Arduino.h>
#include <SoftwareSerial.h>

#define MOTOR1_SPEED 9
#define MOTOR1_1 8
#define MOTOR1_2 10

#define MOTOR2_SPEED 11
#define MOTOR2_1 13
#define MOTOR2_2 12

#define MOTOR3_SPEED 3
#define MOTOR3_1 4
#define MOTOR3_2 2

#define MOTOR4_SPEED 5
#define MOTOR4_1 6
#define MOTOR4_2 7

#define BLUETOOTH_RX 2
#define BLUETOOTH_TX 3

#define SPEED_COEF 2

int speed = 255;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  pinMode(MOTOR1_SPEED, OUTPUT);
  pinMode(MOTOR1_1, OUTPUT);
  pinMode(MOTOR1_2, OUTPUT);

  pinMode(MOTOR2_SPEED, OUTPUT);
  pinMode(MOTOR2_1, OUTPUT);
  pinMode(MOTOR2_2, OUTPUT);

  pinMode(MOTOR3_SPEED, OUTPUT);
  pinMode(MOTOR3_1, OUTPUT);
  pinMode(MOTOR3_2, OUTPUT);

  pinMode(MOTOR4_SPEED, OUTPUT);
  pinMode(MOTOR4_1, OUTPUT);
  pinMode(MOTOR4_2, OUTPUT);
}

void stop()
{
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, LOW);
  analogWrite(MOTOR1_SPEED, 0);

  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, LOW);
  analogWrite(MOTOR2_SPEED, 0);

  digitalWrite(MOTOR3_1, LOW);
  digitalWrite(MOTOR3_2, LOW);
  analogWrite(MOTOR3_SPEED, 0);

  digitalWrite(MOTOR4_1, LOW);
  digitalWrite(MOTOR4_2, LOW);
  analogWrite(MOTOR4_SPEED, 0);
}

void forward()
{
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, HIGH);
  analogWrite(MOTOR1_SPEED, speed);

  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, HIGH);
  analogWrite(MOTOR2_SPEED, speed);

  digitalWrite(MOTOR3_1, LOW);
  digitalWrite(MOTOR3_2, HIGH);
  analogWrite(MOTOR3_SPEED, speed);

  digitalWrite(MOTOR4_1, LOW);
  digitalWrite(MOTOR4_2, HIGH);
  analogWrite(MOTOR4_SPEED, speed);
}

void backward()
{
  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, LOW);
  analogWrite(MOTOR1_SPEED, speed);

  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW);
  analogWrite(MOTOR2_SPEED, speed);

  digitalWrite(MOTOR3_1, HIGH);
  digitalWrite(MOTOR3_2, LOW);
  analogWrite(MOTOR3_SPEED, speed);

  digitalWrite(MOTOR4_1, HIGH);
  digitalWrite(MOTOR4_2, LOW);
  analogWrite(MOTOR4_SPEED, speed);
}

void left()
{
  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW);
  analogWrite(MOTOR2_SPEED, speed);

  digitalWrite(MOTOR4_1, HIGH);
  digitalWrite(MOTOR4_2, LOW);
  analogWrite(MOTOR4_SPEED, speed);

  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, HIGH);
  analogWrite(MOTOR1_SPEED, speed);

  digitalWrite(MOTOR3_1, LOW);
  digitalWrite(MOTOR3_2, HIGH);
  analogWrite(MOTOR3_SPEED, speed);
}

void right()
{
  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, HIGH);
  analogWrite(MOTOR2_SPEED, speed);

  digitalWrite(MOTOR4_1, LOW);
  digitalWrite(MOTOR4_2, HIGH);
  analogWrite(MOTOR4_SPEED, speed);

  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, LOW);
  analogWrite(MOTOR1_SPEED, speed);

  digitalWrite(MOTOR3_1, HIGH);
  digitalWrite(MOTOR3_2, LOW);
  analogWrite(MOTOR3_SPEED, speed);
}

void forwardLeft()
{
  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, HIGH);
  analogWrite(MOTOR2_SPEED, speed / SPEED_COEF);

  digitalWrite(MOTOR4_1, LOW);
  digitalWrite(MOTOR4_2, HIGH);
  analogWrite(MOTOR4_SPEED, speed / SPEED_COEF);

  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, HIGH);
  analogWrite(MOTOR1_SPEED, speed);

  digitalWrite(MOTOR3_1, LOW);
  digitalWrite(MOTOR3_2, HIGH);
  analogWrite(MOTOR3_SPEED, speed);
}

void forwardRight()
{
  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, HIGH);
  analogWrite(MOTOR2_SPEED, speed);

  digitalWrite(MOTOR4_1, LOW);
  digitalWrite(MOTOR4_2, HIGH);
  analogWrite(MOTOR4_SPEED, speed);

  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, HIGH);
  analogWrite(MOTOR1_SPEED, speed / SPEED_COEF);

  digitalWrite(MOTOR3_1, LOW);
  digitalWrite(MOTOR3_2, HIGH);
  analogWrite(MOTOR3_SPEED, speed / SPEED_COEF);
}

void backwardLeft()
{
  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW);
  analogWrite(MOTOR2_SPEED, speed / SPEED_COEF);

  digitalWrite(MOTOR4_1, HIGH);
  digitalWrite(MOTOR4_2, LOW);
  analogWrite(MOTOR4_SPEED, speed / SPEED_COEF);

  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, LOW);
  analogWrite(MOTOR1_SPEED, speed);

  digitalWrite(MOTOR3_1, HIGH);
  digitalWrite(MOTOR3_2, LOW);
  analogWrite(MOTOR3_SPEED, speed);
}

void backwardRight()
{
  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, LOW);
  analogWrite(MOTOR1_SPEED, speed);

  digitalWrite(MOTOR3_1, HIGH);
  digitalWrite(MOTOR3_2, LOW);
  analogWrite(MOTOR3_SPEED, speed);

  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW);
  analogWrite(MOTOR2_SPEED, speed / SPEED_COEF);

  digitalWrite(MOTOR4_1, HIGH);
  digitalWrite(MOTOR4_2, LOW);
  analogWrite(MOTOR4_SPEED, speed / SPEED_COEF);
}

void loop()
{
  if (Serial.available())
  {
    char command = Serial.read();

    stop();

    switch (command)
    {
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
      speed = 100;
      break;
    case '1':
      speed = 140;
      break;
    case '2':
      speed = 153;
      break;
    case '3':
      speed = 165;
      break;
    case '4':
      speed = 178;
      break;
    case '5':
      speed = 191;
      break;
    case '6':
      speed = 204;
      break;
    case '7':
      speed = 216;
      break;
    case '8':
      speed = 229;
      break;
    case '9':
      speed = 242;
      break;
    case 'q':
      speed = 255;
      break;
    }
  }
}