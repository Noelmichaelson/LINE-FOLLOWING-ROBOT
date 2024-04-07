//https://www.youtube.com/watch?v=5jh-5HGvC-I
#define IR_SENSOR_RIGHT 7
#define IR_SENSOR_LEFT 8
#define MOTOR_SPEED 180

#define trigPin 11
#define echoPin 12
#define LED_PIN 13



//Right motor
int enableRightMotor = 10;
int rightMotorPin1 = 3;
int rightMotorPin2 = 2;

//Left motor
int enableLeftMotor = 9;
int leftMotorPin1 = 5;
int leftMotorPin2 = 4;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_PIN, OUTPUT);


  //The problem with TT gear motors is that, at very low pwm value it does not even rotate.
  //If we increase the PWM value then it rotates faster and our robot is not controlled in that speed and goes out of line.
  //For that we need to increase the frequency of analogWrite.
  //Below line is important to change the frequency of PWM signal on pin D5 and D6
  //Because of this, motor runs in controlled manner (lower speed) at high PWM value.
  //This sets frequecny as 7812.5 hz.
  TCCR0B = TCCR0B & B11111000 | B00000010;

  // put your setup code here, to run once:
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  rotateMotor(0, 0);
}


void loop() {

  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  if (distance < 20) {
    rotateMotor(0, 0);
  } else {
    int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
    int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

    //If none of the sensors detects black line, then go straight
    if (rightIRSensorValue == LOW && leftIRSensorValue == LOW) {
      rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
    }
    //If right sensor detects black line, then turn right
    else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW) {
      rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
    }
    //If left sensor detects black line, then turn left
    else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH) {
      rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
    }
    //If both the sensors detect black line, then stop
    else if (rightIRSensorValue == HIGH && leftIRSensorValue == HIGH) {
      rotateMotor(0, 0);
    }
    //If anything not defined above happens, stop the both wheels
  }
}
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {

  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } else if (rightMotorSpeed > 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else if (leftMotorSpeed > 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  } else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }

  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}
