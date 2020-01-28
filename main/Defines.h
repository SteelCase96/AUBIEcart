#ifndef Defines_h
#define Defines_h


// --- General ---

#define myName 'R'
// - Motor Directions -
#define forwardDirection 1
#define backwardDirection -1
#define noDirection 0
// - Speed/PWM Threshold -
#define pwmThresh 0
#define pwmMax 255
// - Joystick Thresholds -
#define lowThresh 470
#define highThresh 553
#define minThresh 0
#define maxThresh 1023


// ----- MPU9250 Definitions -----
// --- Register Addresses ---
#define ACCEL_X_H 0x3B
#define ACCEL_X_L 0x3C
#define ACCEL_Y_H 0x3D
#define ACCEL_Y_L 0x3E
#define ACCEL_Z_H 0x3F
#define ACCEL_Z_L 0x40
#define GYRO_X_H 0x43
#define GYRO_X_L 0x44
#define GYRO_Y_H 0x45
#define GYRO_Y_L 0x46
#define GYRO_Z_H 0x47
#define GYRO_Z_L 0x48
// --- I2C Address of Front MPU ---
#define MPUF B1101000
// --- I2C Address of Rear MPU ---
#define MPUR B1101001

// ----- Motor Controller Definitions -----
// --- Pin Definitions ---
// - Left Motor -
#define enB 10
#define in3 6
#define in4 7
// - Right Motor -
#define enA 9
#define in1 4
#define in2 5

// --- TxRx ---
// Max sizes
#define packetMax 265
#define dataMax 256

// Source/destination code list
#define robotCode 'R'
#define consoleCode 'C'

// Type code list
#define commandCode 'C'
#define infoCode 'I' // request info, like location, speed, distance traveled, &c.

// Command code list
#define forwardCode 'F' // drive backward
#define backwardCode 'B' // drive forward
#define leftCode 'L' // rotate left
#define rightCode 'R' // rotate right
#define joystickCode 'J' // toggle joystick active
#define subsystemCode 'D' // communicate with a subsystem, like a sensor, to activate or to request data

// Subsystem code list
#define frontIMUcode 'F' // front IMU
#define backIMUcode 'B' // back IMU
#define leftEncoderCode 'L' // left encoder
#define rightEncoderCode 'R' // right encoder

// Information code list
#define errorCode 'E'
#define successCode 'S'


#endif
