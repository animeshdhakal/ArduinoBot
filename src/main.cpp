#include <Arduino.h>
#include <BluetoothSerial.h>
#include <L298NX2.h>

#define MOTOR1_SPEED 2
#define MOTOR1_1 5
#define MOTOR1_2 4

#define MOTOR2_SPEED 21
#define MOTOR2_1 18
#define MOTOR2_2 19

#define MOTOR3_SPEED 25
#define MOTOR3_1 26
#define MOTOR3_2 27

#define MOTOR4_SPEED 13
#define MOTOR4_1 12
#define MOTOR4_2 14

L298NX2 motors1(MOTOR1_SPEED, MOTOR1_1, MOTOR1_2, MOTOR2_SPEED, MOTOR2_1, MOTOR2_2);
L298NX2 motors2(MOTOR3_SPEED, MOTOR3_1, MOTOR3_2, MOTOR4_SPEED, MOTOR4_1, MOTOR4_2);

BluetoothSerial SerialBT;

void setup() {
    Serial.begin(115200);

    motors1.setSpeed(255);
    motors2.setSpeed(255);

    SerialBT.begin("ValmikiCOT");
}

void loop() {
    if (SerialBT.available()) {
        char command = SerialBT.read();

        motors1.stop();
        motors2.stop();

        switch (command) {
        case 'F':
            motors1.forward();
            motors2.forward();
            break;
        case 'B':
            motors1.backward();
            motors2.backward();
            break;
        case 'L':
            motors1.forwardB();
            motors1.backwardA();
            motors2.forwardB();
            motors2.backwardA();
            break;
        case 'R':
            motors1.forwardA();
            motors1.backwardB();
            motors2.forwardA();
            motors2.backwardB();
            break;
        case '0':
            motors1.setSpeed(127);
            motors2.setSpeed(127);
            break;
        case '1':
            motors1.setSpeed(140);
            motors2.setSpeed(140);
            break;
        case '2':
            motors1.setSpeed(153);
            motors2.setSpeed(153);
            break;
        case '3':
            motors1.setSpeed(165);
            motors2.setSpeed(165);
            break;
        case '4':
            motors1.setSpeed(178);
            motors2.setSpeed(178);
            break;
        case '5':
            motors1.setSpeed(191);
            motors2.setSpeed(191);
            break;
        case '6':
            motors1.setSpeed(204);
            motors2.setSpeed(204);
        case '7':
            motors1.setSpeed(216);
            motors2.setSpeed(216);
            break;
        case '8':
            motors1.setSpeed(229);
            motors2.setSpeed(229);
            break;
        case '9':
            motors1.setSpeed(242);
            motors2.setSpeed(242);
            break;
        case 'q':
            motors1.setSpeed(255);
            motors2.setSpeed(255);
            break;
        }
    }
}