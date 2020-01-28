#include <Wire.h>
#include <MPU9250.h>

#define MPU1 B1101000 // I2C address of 1st MPU9250 sensor
#define MPU2 B1101001 // I2C address of 2nd MPU9250 sensor
#define ACCEL_X_H 0x3B
#define ACCEL_X_L 0x3C
#define ACCEL_Y_H 0x3D
#define ACCEL_Y_L 0x3E
#define ACCEL_Z_H 0x3F
#define ACCEL_Z_L 0x40
#define TEMP_H 0x41
#define TEMP_L 0x42
#define GYRO_X_H 0x43
#define GYRO_X_L 0x44
#define GYRO_Y_H 0x45
#define GYRO_Y_L 0x46
#define GYRO_Z_H 0x47
#define GYRO_Z_L 0x48

MPU9250 IMU(Wire,MPU2);

void setup() {
  Serial.begin(9600);
  Serial.println("-----Starting-----");
  int status;
  status = IMU.begin();
  if(status < 0){
    Serial.println("Start-up error...");
    while(true){}
  }
  
}

void loop() {
  // read the sensor
  IMU.readSensor();
  // display the data
//  Serial.print("AccelX: ");
//  Serial.print(IMU.getAccelX_mss(),6);
//  Serial.print("  ");
//  Serial.print("AccelY: ");  
//  Serial.print(IMU.getAccelY_mss(),6);
//  Serial.print("  ");
//  Serial.print("AccelZ: ");  
//  Serial.println(IMU.getAccelZ_mss(),6);
  
  Serial.print("GyroX: ");
  Serial.print(IMU.getGyroX_rads(),6);
  Serial.print("  ");
  Serial.print("GyroY: ");  
  Serial.print(IMU.getGyroY_rads(),6);
  Serial.print("  ");
  Serial.print("GyroZ: ");  
  Serial.println(IMU.getGyroZ_rads(),6);

//  Serial.print("MagX: ");  
//  Serial.print(IMU.getMagX_uT(),6);
//  Serial.print("  ");  
//  Serial.print("MagY: ");
//  Serial.print(IMU.getMagY_uT(),6);
//  Serial.print("  ");
//  Serial.print("MagZ: ");  
//  Serial.println(IMU.getMagZ_uT(),6);
//  
//  Serial.print("Temperature in C: ");
//  Serial.println(IMU.getTemperature_C(),6);
//  Serial.println();
  delay(100);
} 
