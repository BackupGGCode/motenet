// NodeMsg.h
// Node message types

#ifndef NodeMsg_h
#define NodeMsg_h

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include <Arduino.h>
#endif

#define MAX_PKG_SIZE 32 // Package size in payload

/*---------------------------------------------
|
|	!! PKG Types !!
|	Structure written to pkg[] array...
|
*/

typedef enum {
	// Endpoint ping
	pingMsg			= 0,	// System Ping
	// Sprinkler Zone Control types
	spklZone 	= 10, 	// Zone Control
	spklProg 	= 11, 	// Program Control	
	spklSys 	= 12, 	// Sprinkler System Control
	// Test Message
	testMsg			= 255	// Test messagte 
} NodeMsgType;

// Message Wrapper
typedef struct {		
  byte           pkgType;
  unsigned long  msgID; 
  byte           pkg[MAX_PKG_SIZE];  // 32 bytes
} Payload;
Payload theData;


/*---------------------------------------------
|
|	!! PKG Definitions !!
|	Sensor specific message structures
|
*/

typedef struct {
  byte      a;
  byte      b;
  byte      c;
  byte      d;
} _testMsg;
_testMsg testMsgPkg;


typedef struct {
	//Pkg for spklZoneCtrl 	= 10, 	// Zone Control
	byte 	zoneNumber;					// {1}
	byte 	zoneOperation;				// {1} Get, Post like operations
	byte	dataDirection; 				// {1} Send or receive 
	byte	zoneState;					// {1} {0=OFF, 1=ON, 2=PAUSED}
	int		totalSprinkleTime;			// {2} total number of seconds to sprinkle
	int		activeSprinkleTime; 		// {2} Actuve number of seconds for node
	byte	percentComplete;			// {1} Active tiv
	int 	pauseTime;					// {2} Ammount of time paused... (If in Pause Mode, otherwise 0)
} _spklZone;
_spklZone spklZonePkg;

typedef struct {
	// Sprinkler program control 
} _spklProg;
_spklProg spklProgPkg;

typedef struct {
  byte      a;
  byte      b;
  byte      c;
  byte      d;
} _spklSys;
_spklSys spklSysPkg;


#endif