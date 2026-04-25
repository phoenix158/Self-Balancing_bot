#include <Wire.h>
#include <MPU6050.h>
#include <PID_v1.h>

MPU6050 mpu;

// PID variables
double setpoint = 0;   // Target angle (upright)
double input, output;
double Kp = 20, Ki = 5, Kd = 1;  // Tune these!
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

// Motor pins
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define ENA 5
#define ENB 6

void setup() {
  Wire.begin();
  mpu.initialize();
  Serial.begin(9600);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(10);
  myPID.SetOutputLimits(-255, 255);
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Calculate tilt angle
  input = atan2(ay, az) * 180 / PI;

  myPID.Compute();
  driveMotors(output);
}

void driveMotors(double speed) {
  int spd = abs(speed);
  spd = constrain(spd, 0, 255);

  if (speed > 0) {
    // Forward
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  } else {
    // Backward
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  }

  analogWrite(ENA, spd);
  analogWrite(ENB, spd);
}