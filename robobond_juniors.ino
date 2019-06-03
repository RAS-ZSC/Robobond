#include <Servo.h>
#define S1 12
#define S2 11
#define S3 10
#define motorPin1 6
#define motorPin2 7
#define motorPin3 4
#define motorPin4 5
int Speed = 230;
int angle2;
int ln = 0;
#define frequency 10
Servo servo2;
boolean line_follower_enabled = false;
char recieved_data;
void setup() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  servo2.attach(8,500,1500);
  stopAll();
  Serial1.begin(9600);
  Serial.begin(9600);
}
void loop() {
  if (Serial1.available() > 0) {
    recieved_data = Serial1.read();
    Serial1.println(recieved_data);
    switch (recieved_data) {
      case 'F':
        //forward
        motors(Speed, 0, Speed, 0); //90% pwm
        delay(frequency);
        break;
      case 'B':
        //back
        motors(0, Speed, 0, Speed);
        delay(frequency);
        break;
      case 'L':
        //left
        motors(Speed, 0, 0, Speed);
        delay(frequency);
        break;
      case 'R':
        //right
        motors(0, Speed, Speed, 0);
        delay(frequency);
        break;
      case 'S':
        //stop
        motors(0, 0, 0, 0);
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

      case 'P':
        angle2 = Serial1.parseInt();
        servo2.write(angle2);
        break;
      case 'N':
          if(ln == 1){ln = 0;}
          else{ln = 1;}
          break;
       
    }
  }
  Serial.print(digitalRead(S1)); // Med
  Serial.print(digitalRead(S2)); // L
  Serial.println(digitalRead(S3)); // R
  if(ln == 1){LineFollower();}
}

void stopAll() {
  motors(0, 0, 0, 0);
}

void LineFollower() {

    digitalWrite(motorPin1, digitalRead(S2));
    digitalWrite(motorPin2, !digitalRead(S2));
    digitalWrite(motorPin3, digitalRead(S3));
    digitalWrite(motorPin4, !digitalRead(S3));
}
void motors(int pinA, int pinB, int pinC, int pinD) {
  analogWrite(motorPin1, pinA);
  analogWrite(motorPin2, pinB);
  analogWrite(motorPin3, pinC);
  analogWrite(motorPin4, pinD);
}
