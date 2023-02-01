#include <Arduino.h>
#include <SoftwareSerial.h>

#define MOTOR1_SPEED 5
#define MOTOR1_1 6
#define MOTOR1_2 7

#define MOTOR2_SPEED 10
#define MOTOR2_1 9
#define MOTOR2_2 8

#define BLUETOOTH_RX 2
#define BLUETOOTH_TX 3

#define SPEED_COEF 3

SoftwareSerial BTSerial(BLUETOOTH_RX, BLUETOOTH_TX);

int speed = 255;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  BTSerial.begin(9600);
  Serial.begin(115200);

  pinMode(MOTOR1_SPEED, OUTPUT);
  pinMode(MOTOR1_1, OUTPUT);
  pinMode(MOTOR1_2, OUTPUT);

  pinMode(MOTOR2_SPEED, OUTPUT);
  pinMode(MOTOR2_1, OUTPUT);
  pinMode(MOTOR2_2, OUTPUT);
}

void stop()
{
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, LOW);
  analogWrite(MOTOR1_SPEED, 0);

  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, LOW);
  analogWrite(MOTOR2_SPEED, 0);
}

void forward()
{
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, HIGH);
  analogWrite(MOTOR1_SPEED, speed);

  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, HIGH);
  analogWrite(MOTOR2_SPEED, speed);
}

void backward()
{
  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, LOW);
  analogWrite(MOTOR1_SPEED, speed);

  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW);
  analogWrite(MOTOR2_SPEED, speed);
}

void left()
{
  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, LOW);
  analogWrite(MOTOR1_SPEED, speed);

  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, HIGH);
  analogWrite(MOTOR2_SPEED, speed);
}

void right()
{
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, HIGH);
  analogWrite(MOTOR1_SPEED, speed);

  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW);
  analogWrite(MOTOR2_SPEED, speed);
}

void forwardLeft()
{
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, HIGH);
  analogWrite(MOTOR1_SPEED, speed);

  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, HIGH);
  analogWrite(MOTOR2_SPEED, speed / SPEED_COEF);
}

void forwardRight()
{
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, HIGH);
  analogWrite(MOTOR1_SPEED, speed / SPEED_COEF);

  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, HIGH);
  analogWrite(MOTOR2_SPEED, speed);
}

void backwardLeft()
{
  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, LOW);
  analogWrite(MOTOR1_SPEED, speed);

  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW);
  analogWrite(MOTOR2_SPEED, speed / SPEED_COEF);
}

void backwardRight()
{
  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, LOW);
  analogWrite(MOTOR1_SPEED, speed / SPEED_COEF);

  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW);
  analogWrite(MOTOR2_SPEED, speed);
}

void loop()
{
  if (BTSerial.available())
  {
    char command = BTSerial.read();

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