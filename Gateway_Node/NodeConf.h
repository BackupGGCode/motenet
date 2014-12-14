// !!!!  DEVICE CONFIGURATION SETTINGS  !!!!
#ifndef NodeConf_h
#define NodeConf_h

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include <Arduino.h>
#endif

/*---------------------------------------------
|
|	Node Configuration Settings
|	
*/

#define NODEID      99
#define NETWORKID   100
#define TARGETID    42
#define TARGETID_2  1
#define FREQUENCY   RF69_915MHZ //Match this with the version of your Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define KEY         "thisIsEncryptKey" //has to be same 16 characters/bytes on all nodes, not more not less!
#define LED         9
#define SERIAL_BAUD 115200
#define ACK_TIME    30  // # of ms to wait for an ack
#define WAIT_TIME   1000
//#define TRANSMITPERIOD 10000 // 10 Seconds
//#define TRANSMITPERIOD 120000 // 2 min
//#define TRANSMITPERIOD 300000 // 5 min
#define TRANSMITPERIOD 600000 // 10 min
#define GET_SPKL_STATUS 35000 

#endif