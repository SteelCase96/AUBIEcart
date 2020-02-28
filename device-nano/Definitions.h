#ifndef Definitions_h
#define Definitions_h

// ----- General -----
#define MY_NAME 'C'
#define COMMAND_BUF_MAX_SIZE 256

// --- TxRx ---
// - Control Characters - 
#define SOH char(1) // start of heading character
#define STX char(2) // start of text character
#define ETX char(3) // end of text character
#define EOT char(4) // end of transmission character
#define ENQ char(5) // enquiry character
#define ACK char(6) // acknowledge character
#define US  char(31) // unit separator character
// - Max sizes -
#define MAX_PACKET_SIZE 256 // including a null char
#define MAX_PAYLOAD_SIZE 247 // including a null char 
// - Source/destination code list -
#define ROBOT_CODE 'R'
#define CONSOLE_CODE 'C'
// - Type code list -
//#define commandCode 'C'
#define COMMAND_CODE 'C'
#define STATUS_CODE 'S'
#define ESTABLISH_CONNECTION_CODE 'E'
#define infoCode 'I' // information report; or request info, like location, speed, distance traveled, &c. !!! - change
// - Command code list -
#define DRIVE_FORWARD_CMD 'F' // drive backward
#define DRIVE_BACKWARD_CMD 'B' // drive forward !!! - change
#define TURN_LEFT_CMD 'L' // rotate left !!! - change
#define TURN_RIGHT_CMD 'R' // rotate right !!! - change
#define ACTIVATE_JOYSTICK_CMD 'J' // toggle joystick active !!! - change
#define COMMAND_SEQUENCE_CMD 'C'
#define SUBSYSTEM_CMD 'D' // communicate with a subsystem, like a sensor, to activate or to request data
// - Information code list -
#define ERROR_CODE 'E'
#define SUCCESS_CODE 'S'
#define textCode 'T' !!! - change
// - Subsystem code list -
#define generalCode 'G' // no particular subsystem !!! - change
#define TURN_CONTROLLER 'T'
#define DRIVE_CONTROLLER 'D'
#define FRONT_IMU_CODE 'F' // front IMU
#define BACK_IMU_CODE 'B' // back IMU
#define LEFT_ENCODER_CODE 'L' // left encoder
#define RIGHT_ENCODER_CODE 'R' // right encoder

#endif
