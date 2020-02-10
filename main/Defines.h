#ifndef Defines_h
#define Defines_h

// ----- General -----
#define MY_NAME 'R'


// ----- Encoders -----
#define LEFT_ENCODER_CHA 2
#define LEFT_ENCODER_CHB 0
#define RIGHT_ENCODER_CHA 3
#define RIGHT_ENCODER_CHB 0


// ----- Joystick -----
// --- Pins ---
#define vrx A1
#define vry A0
#define swi 8
// --- Thresholds ---
#define lowThresh 470
#define highThresh 553
#define minThresh 0
#define maxThresh 1023


// ----- MPU9250 Definitions -----
// --- Addresses ---
// - I2C Address of Front MPU -
#define MPUF B1101000
// - I2C Address of Rear MPU -
#define MPUR B1101001
// - On-device Registers -
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


// ----- Motor Controller Definitions -----
// --- General ---
// - Motor Directions -
#define forwardDirection 1
#define backwardDirection -1
#define noDirection 0
// - Speed/PWM Threshold -
#define pwmThresh 0
#define pwmMax 255
// --- Pins ---
// - Left Motor -
#define enB 11
#define in3 6
#define in4 7
// - Right Motor -
#define enA 10
#define in1 4
#define in2 5


// --- TxRx ---
// - Max sizes -
#define packetMax 265 // including a null char
#define dataMax 256 // including a null char
// - Source/destination code list -
#define robotCode 'R'
#define CONSOLE_CODE 'C'
// - Type code list -
#define commandCode 'C'
#define STATUS_CODE 'S'
#define infoCode 'I' // information report; or request info, like location, speed, distance traveled, &c.
// - Command code list -
#define forwardCode 'F' // drive backward
#define backwardCode 'B' // drive forward
#define leftCode 'L' // rotate left
#define rightCode 'R' // rotate right
#define joystickCode 'J' // toggle joystick active
#define subsystemCode 'D' // communicate with a subsystem, like a sensor, to activate or to request data
// - Information code list -
#define ERROR_CODE 'E'
#define SUCCESS_CODE 'S'
#define textCode 'T'
// - Subsystem code list -
#define generalCode 'G' // no particular subsystem
#define FRONT_IMU_CODE 'F' // front IMU
#define BACK_IMU_CODE 'B' // back IMU
#define LEFT_ENCODER_CODE 'L' // left encoder
#define RIGHT_ENCODER_CODE 'R' // right encoder

#endif
