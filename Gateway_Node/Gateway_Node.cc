#include <RFM69.h>
#include <SPI.h>
#include <NodeMsg.h>
#include <NodeConf.h>


//int TRANSMITPERIOD = 3000; //transmit a packet to gateway so often (in ms)
byte sendSize=0;
long lastPeriod = -1;
byte zoneCycle = 0;
boolean requestACK = false;
RFM69 radio;

void Blink(byte PIN, int DELAY_MS);
void txSetZone(byte zoneNum);
void txGetZoneStatus();
void rxZoneStatus();

void setup() {
  Serial.begin(SERIAL_BAUD);
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  //radio.setHighPower(); //uncomment only for RFM69HW!
  radio.encrypt(KEY);
  char buff[50];
  sprintf(buff, "\nTransmitting at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println(buff);
}

void loop() {

  //check for any received packets
  if (radio.receiveDone()) {
    Serial.print('[');Serial.print(radio.SENDERID, DEC);Serial.print("] ");
    //for (byte i = 0; i < radio.DATALEN; i++)
    //  Serial.print((char)radio.DATA[i]);
    Serial.print("   [RX_RSSI:");Serial.print(radio.readRSSI());Serial.print("]");

    if (radio.ACK_REQUESTED)
    {
      radio.sendACK();
      Serial.print(" - ACK sent");
      delay(10);
    }
    Blink(LED,5);
    Serial.println();

    theData = *(Payload*)radio.DATA;
    // Process received Data
    switch(theData.pkgType) {
      case spklZone:
        switch(theData.msgMethod) {
          /* Gateway cannot receive these messages
          case SET:
            Serial.println("--- Executing Sprinkle Zone SET Method \n");
            setZone();
            break;
          */
          case STATUS:
            Serial.println("\n--- Process Zone status response... \n");
            // return the zone status to the requestor....
            rxZoneStatus();
            break;
          default:
            Serial.println(" Method is not supported ... "); 
        }
        break;  
      default:
        Serial.println(" No Function defined... ");
    }
  }

  /*---------------------------------------------------------------------
  |
  |
  |
  */

  if (millis() % GET_SPKL_STATUS == 0) { // Defined NodeConf.h
    // Send node Request Message
    txGetZoneStatus();
  }

  // 
  int currPeriod = millis()/TRANSMITPERIOD;

  if (currPeriod != lastPeriod) {
    //fill in the struct with new values
    theData.msgID = millis();
    //theData.pkgType = 10;

    txSetZone(zoneCycle);

    Serial.print("Sending struct (");
    Serial.print(sizeof(theData));
    Serial.print(" bytes) ... ");
    

    if (radio.sendWithRetry(TARGETID, (const void*)(&theData), sizeof(theData)))
      Serial.print(" ok!");
    else Serial.print(" nothing...");
    

    Serial.println();
    Blink(LED,3);
    lastPeriod=currPeriod;
    if (zoneCycle == 10) {
      // Reset zone cycle
      zoneCycle = 0;
    } else {
      zoneCycle++;
    }
  }
}


void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}

void txSetZone(byte zoneNum) {
  /*------------------------------------------------
  | Send zone command to sprinkler node. 
  | Set state of zone package and send via readio
  |
  | !!Hard code values for testing. 
  | Pass serial structure in future...
  */
  theData.pkgType = spklZone;
  theData.msgMethod = SET;
  spklZonePkg.zoneNumber = zoneNum;
  spklZonePkg.zoneState = 1;
  spklZonePkg.zoneCycleTime = min5;
  spklZonePkg.activeCycleTime = 0;
  spklZonePkg.percentComplete = 0;

  memcpy(theData.pkg, &spklZonePkg, sizeof(spklZonePkg));

}


void txGetZoneStatus() {
  // Send request to get zone status
  Serial.print("\nGet Zone Status :: ");
  theData.msgID = millis();
  theData.pkgType = spklZone;
  theData.msgMethod = STATUS;
  if (radio.sendWithRetry(TARGETID, (const void*)(&theData), sizeof(theData)))
    Serial.println(" ok!");
  else Serial.println(" nothing...");
}


void rxZoneStatus() {
  // Receive Zone status data
  
  spklZonePkg = *(_spklZone*)theData.pkg; // Cast package as zone structure
  Serial.print(" zoneNumber =");
  Serial.println(spklZonePkg.zoneNumber);
  Serial.print(" dataDirection =");
  Serial.println(spklZonePkg.dataDirection);
  Serial.print(" zoneState =");
  Serial.println(spklZonePkg.zoneState);
  Serial.print(" totalSprinkleTime =");
  Serial.println(spklZonePkg.zoneCycleTime);
  Serial.print(" activeSprinkleTime =");
  Serial.println(spklZonePkg.activeCycleTime);
  Serial.print(" percentComplete =");
  Serial.println(spklZonePkg.percentComplete);
  Serial.print(" pauseTime =");
  Serial.println(spklZonePkg.pauseTime);

}

// Add code to send only structure
// this is a new ling
