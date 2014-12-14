#include "Arduino.h"
void setup();
void loop();
#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>

#define NODEID      42
#define NETWORKID   100
#define FREQUENCY   RF69_915MHZ //Match this with the version of your Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define KEY         "thisIsEncryptKey" //has to be same 16 characters/bytes on all nodes, not more not less!
#define LED         9
#define SERIAL_BAUD 115200
#define ACK_TIME    30  // # of ms to wait for an ack

RFM69 radio;
SPIFlash flash(8, 0xEF30); //EF40 for 16mbit windbond chip
bool promiscuousMode = false; //set to 'true' to sniff all packets on the same network
void Blink(byte PIN, int DELAY_MS);

typedef struct {		
  byte          pkgType;
  unsigned long msgID; 
  byte           pkg[32];
} Payload;
Payload theData;

typedef struct {
  byte      a;
  byte      b;
  byte      c;
  byte      d;
} Package;
Package thePackage;

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(10);
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  //radio.setHighPower(); //uncomment only for RFM69HW!
  radio.encrypt(KEY);
  radio.promiscuous(promiscuousMode);
  char buff[50];
  sprintf(buff, "\nListening at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println(buff);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);

}


byte ackCount=0;
void loop() {

  if (radio.receiveDone())
  {
    Serial.print('[');Serial.print(radio.SENDERID, DEC);Serial.print("] ");
    Serial.print(" [RX_RSSI:");Serial.print(radio.readRSSI());Serial.print("]");
    if (promiscuousMode)
	{
      Serial.print("to [");Serial.print(radio.TARGETID, DEC);Serial.print("] ");
    }
	
    if (radio.DATALEN != sizeof(Payload))
      Serial.print("Invalid payload received, not matching Payload struct!");
    else
    {
      theData = *(Payload*)radio.DATA; //assume radio.DATA actually contains our struct and not something else
      Serial.print(" S=");
      Serial.print(radio.SENDERID);
      Serial.print(" T=");
      Serial.println(radio.TARGETID);
      Serial.print(" msgID=");
      Serial.print(theData.msgID);
      Serial.print(" pkgType=");
      Serial.print(theData.pkgType);
      Serial.print(" Size=");
      Serial.println(radio.DATALEN);

      Serial.println("Package Info..... ");
      thePackage = *(Package*)theData.pkg;


      Serial.print(" A=");
      Serial.print(thePackage.a);
      Serial.print(" B=");
      Serial.print(thePackage.b);
      Serial.print(" C=");
      Serial.print(thePackage.c);
      Serial.print(" D=");
      Serial.print(thePackage.d);

      if (theData.pkgType == 1) {
        // Flip outout 
        digitalWrite(6, ! digitalRead(6));
      }


    }
    
    if (radio.ACK_REQUESTED)
    {
      byte theNodeID = radio.SENDERID;
      radio.sendACK();
      Serial.print(" - ACK sent.");

      // When a node requests an ACK, respond to the ACK
      // and also send a packet requesting an ACK (every 3rd one only)
      // This way both TX/RX NODE functions are tested on 1 end at the GATEWAY
      if (ackCount++%3==0)
      {
        Serial.print(" Pinging node ");
        Serial.print(theNodeID);
        Serial.print(" - ACK...");
        delay(3); //need this when sending right after reception .. ?
        if (radio.sendWithRetry(theNodeID, "ACK TEST", 8, 0))  // 0 = only 1 attempt, no retries
          Serial.print("ok!");
        else Serial.print("nothing");
      }
    }
    
    Serial.println();
    Blink(LED,3);
  }
}

void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
