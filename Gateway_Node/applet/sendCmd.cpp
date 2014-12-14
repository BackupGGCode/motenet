#include "Arduino.h"
void setup();
void loop();
#include <RFM69.h>
#include <SPI.h>
#include <NodeMsg.h>
#include <NodeConf.h>


//int TRANSMITPERIOD = 3000; //transmit a packet to gateway so often (in ms)
byte sendSize=0;
boolean requestACK = false;
RFM69 radio;
void Blink(byte PIN, int DELAY_MS);


void setup() {
  Serial.begin(SERIAL_BAUD);
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  //radio.setHighPower(); //uncomment only for RFM69HW!
  radio.encrypt(KEY);
  char buff[50];
  sprintf(buff, "\nTransmitting at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println(buff);
}


long lastPeriod = -1;
void loop() {

  //check for any received packets
  if (radio.receiveDone()) {
    Serial.print('[');Serial.print(radio.SENDERID, DEC);Serial.print("] ");
    for (byte i = 0; i < radio.DATALEN; i++)
      Serial.print((char)radio.DATA[i]);
    Serial.print("   [RX_RSSI:");Serial.print(radio.readRSSI());Serial.print("]");

    if (radio.ACK_REQUESTED)
    {
      radio.sendACK();
      Serial.print(" - ACK sent");
      delay(10);
    }
    Blink(LED,5);
    Serial.println();
  }

  // 
  int currPeriod = millis()/TRANSMITPERIOD;
  //Serial.print("lastPeriod: ");
  //Serial.print(lastPeriod);
  //Serial.print(" currPeriod: ");
  //Serial.println(currPeriod);  

  if (currPeriod != lastPeriod) {
    //fill in the struct with new values
    theData.msgID = millis();
    theData.pkgType = 1;
    //theData.count = currPeriod;
    
    thePackage.a = 9;
    thePackage.b = 19;
    thePackage.c = 29;
    thePackage.d = 39;

    //theData.pkg = (const void*)(&thePackage);
    memcpy(theData.pkg, &thePackage, sizeof(thePackage));

    Serial.print("Sending struct (");
    Serial.print(sizeof(theData));
    Serial.print(" bytes) ... ");
    
    /* TEST - Delete 
    if (currPeriod % 2) { 
    if (radio.sendWithRetry(TARGETID, (const void*)(&theData), sizeof(theData)))
      Serial.print(" ok!");
    else Serial.print(" nothing...");
    } else {
    if (radio.sendWithRetry(TARGETID_2, (const void*)(&theData), sizeof(theData)))
      Serial.print(" ok!");
    else Serial.print(" nothing...");
    }
    */


    if (radio.sendWithRetry(TARGETID, (const void*)(&theData), sizeof(theData)))
      Serial.print(" ok!");
    else Serial.print(" nothing...");
    

    Serial.println();
    Blink(LED,3);
    lastPeriod=currPeriod;
  }
}


void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
