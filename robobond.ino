#include <Servo.h>
#define SERVO1_MIN 500
#define SERVO1_MAX 2500 //1500
#define SERVO2_MIN 500
#define SERVO2_MAX 2500
#define motorPin1 3
#define motorPin2 5
#define motorPin3 6
#define motorPin4 9
#define frequency 10
#define SERVO1_PIN 10
#define SERVO2_PIN 11
#define EN_PIN 2
#define EN_PIN2 4
int Speed = 230;

int angle = 0, angle2 = 0;
char recieved_data;
Servo servo1; //s3003
Servo servo2; //sg06
uint8_t x = 0;
void setup() {
  Serial.begin(9600);
  pinMode(motorPin1, 1);
  pinMode(motorPin2, 1);
  pinMode(motorPin3, 1);
  pinMode(motorPin4, 1);
  servo1.attach(SERVO1_PIN, SERVO1_MIN, SERVO1_MAX); //s3003
  servo2.attach(SERVO2_PIN, SERVO2_MIN, SERVO2_MAX); //MG90S
  digitalWrite(EN_PIN, 1);
  digitalWrite(EN_PIN2, 1);

}
void loop() {
  if (Serial.available() > 0) {
    recieved_data = Serial.read();
    Serial.println(recieved_data);
    switch (recieved_data) {
      case 'F':
        //forward
        motors(Speed, 0, Speed / 2, 0); //90% pwm
        delay(frequency);
        break;
      case 'B':
        //back
        motors(0, Speed, 0, Speed / 2);
        delay(frequency);
        break;
      case 'L':
        //left
        motors(0, Speed, Speed / 2, 0);
        delay(frequency);
        break;
      case 'R':
        //right
        motors(Speed, 0, 0, Speed / 2);
        delay(frequency);
        break;
      case 'S':
        //stop
        motors(0, 0, 0, 0);
        delay(frequency);
        break;
      case 'U':
        //servo up
        angle += 30;
        if (angle > 180)
          angle = 180;
        servo1.write(angle);
        delay(frequency);
        break;
      case 'D':
        //servo down
        angle -= 30;
        if (angle < 0)
          angle = 0;
        servo1.write(angle);
        delay(frequency);
        break;
      case 'H':
        //gripper hold
        angle2 += 30;
        if (angle2 > 180)
          angle2 = 180;
        servo2.write(angle);
        delay(frequency);
        break;
      case 'K'://ml2et4 7rof tany
        //gripper release
        angle -= 30;
        if (angle2 < 0)
          angle2 = 0;
        servo2.write(angle);
        delay(frequency);
        break;
      case '1':
        Speed = 80;
        break;
      case '2':
        Speed = 130;
        break;
      case '3':
        Speed = 170;
        break;
      case '4':
        Speed = 230;
        break;
      case 'Z':
        angle = Serial.parseInt();
        servo1.write(angle);
        break;
      case 'P':
        angle2 = Serial.parseInt();
        servo2.write(angle2);
        break;
    }
  }
}
void motors(int pinA, int pinB, int pinC, int pinD) {
  analogWrite(motorPin1, pinA);
  analogWrite(motorPin2, pinB);
  analogWrite(motorPin3, pinC);
  analogWrite(motorPin4, pinD);
}
void stopAll() {
  motors(0, 0, 0, 0);
}
