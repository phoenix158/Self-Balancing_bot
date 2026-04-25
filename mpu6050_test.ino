#include "Wire.h"
#include "I2Cdev.h" // You need the I2Cdev library installed as well
#include "MPU6050.h"

// Force the address to 0x68 explicitly
MPU6050 mpu(0x68); 

void setup() {
  Wire.begin();
  Serial.begin(9600);

  Serial.println("Testing MPU6050 connection...");
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful!");
  } else {
    Serial.println("MPU6050 connection failed.");
  }
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Print just the X-axis for now to keep it clean
  Serial.print("Accel X: "); Serial.print(ax);
  Serial.print(" | Gyro X: "); Serial.println(gx);
  
  delay(200);
}