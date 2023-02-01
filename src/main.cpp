#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // RX, TX

#define MOTOR1_SPEED 5
#define MOTOR1_1 6
#define MOTOR1_2 7

#define MOTOR2_SPEED 10
#define MOTOR2_1 9
#define MOTOR2_2 8

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  BTSerial.begin(9600);
  Serial.begin(115200);

  pinMode(MOTOR1_SPEED, OUTPUT);
  pinMode(MOTOR1_1, OUTPUT);
  pinMode(MOTOR1_2, OUTPUT);

  pinMode(MOTOR2_SPEED, OUTPUT);
  pinMode(MOTOR2_1, OUTPUT);
  pinMode(MOTOR2_2, OUTPUT);

  analogWrite(MOTOR1_SPEED, 100);
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, HIGH);

  analogWrite(MOTOR2_SPEED, 100);
  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, HIGH);

}

void changeSpeed(int pin, int speed){
  analogWrite(pin, speed);
}

void stop(){
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, LOW);
  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, LOW);
}

void forward(){
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, HIGH);
  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, HIGH);
}

void backward(){
  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, LOW);
  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW);
}

void left(){
  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, LOW);
  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, HIGH);
}

void right(){
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, HIGH);
  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW);
}

void forwardLeft(){
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, LOW);
  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, HIGH);
}

void forwardRight(){
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, HIGH);
  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, LOW);
}

void backwardLeft(){
  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, LOW);
  digitalWrite(MOTOR2_1, LOW);
  digitalWrite(MOTOR2_2, LOW);
}

void backwardRight(){
  digitalWrite(MOTOR1_1, LOW);
  digitalWrite(MOTOR1_2, LOW);
  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW);
}

void changeSpeed(int speed){
  changeSpeed(MOTOR1_SPEED, speed);
  changeSpeed(MOTOR2_SPEED, speed);
}

void loop() {
  if (BTSerial.available()) {
      char command = BTSerial.read();

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
          changeSpeed(100);
          break;
        case '1':
          changeSpeed(140);
          break;
        case '2':
          changeSpeed(153);
          break;
        case '3':
          changeSpeed(165);
          break;
        case '4':
          changeSpeed(178);
          break;
        case '5':
          changeSpeed(191);
          break;
        case '6':
          changeSpeed(204);
          break;
        case '7':
          changeSpeed(216);
          break;
        case '8':
          changeSpeed(229);
          break;
        case '9':
          changeSpeed(242);
          break;
        case 'q':
          changeSpeed(255);
          break;
      }   
  }
}