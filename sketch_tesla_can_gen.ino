// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13
// sergey, 2018

#include <SPI.h>
#include "mcp_can.h"
#define DEBUG_MODE 1

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;

char num = 0;
int index = 0;



MCP_CAN CAN(SPI_CS_PIN);  // Set CS pin

void setup() {
  Serial.begin(115200);

START_INIT:

  if (CAN_OK ==
     // CAN.begin(CAN_500KBPS, MCP_8MHz))  // init can bus : baudrate = 500k
     CAN.begin(CAN_125KBPS, MCP_8MHz))  // init can bus : baudrate = 500k

  {
    Serial.println("CAN BUS Shield init ok!");
  } else {
    Serial.println("CAN BUS Shield init fail");
    Serial.println("Init CAN BUS Shield again");
    delay(100);
    goto START_INIT;
  }
}

void loop() {
  unsigned char len = 0;
  //unsigned char buf[8];


  //send RPM message
  unsigned char RPM[8] = {0x31, 0xFF,0x2D,0x7F,0xA3,0x14,0x0E,0xA8};
  CAN.sendMsgBuf(0x105, 0, 8, RPM);
  delay(50);

  //send speed message
  unsigned char speed1[8] = {0x84, 0x19, 0x40, 0x31, 0x00, 0xF2, 0x20, 0x78};
  unsigned char speed2[8] = {0x84, 0x28, 0xC0, 0x31, 0x5A, 0x52, 0x2D, 0xCE};

  if (random(2) == 0)  CAN.sendMsgBuf(0x256, 0, 8, speed1);
    else  CAN.sendMsgBuf(0x256, 0, 8, speed2);
  delay(50);

  //inventor temp state
  unsigned char inv[8] = {50, 50, 50, 50, 50, 50, 50, 50};

  CAN.sendMsgBuf(0x306, 0, 8, inv);

  //battery temp state
  unsigned char bms1[8] = {0x66, 0x97, 0xF8, 0xA6, 0xF2, 0x4D, 0x28, 0x01};
  unsigned char bms2[6] = {0x5C, 0x99, 0x9F, 0x83, 0x3C, 0x07};

 if (random(2) == 0)  CAN.sendMsgBuf(0x102, 0, 8, bms1);
    else  CAN.sendMsgBuf(0x102, 0, 6, bms2);
  delay(50);

  //battery state of change
   unsigned char bsc[3] = {0x82, 0xDF, 0x0D};
   CAN.sendMsgBuf(0x302, 0, 3, bsc);
   delay(50);

   //estimated energy
   unsigned char ee[8] = {0xFC, 0x9A, 0xEA, 0x69, 0xA9, 0x00, 0xA0, 0x00};
   CAN.sendMsgBuf(0x382, 0, 3, ee);
   delay(50);

  //Battery Lifetime Energy Stats
  unsigned char bles[8] = {0x25, 0xAE, 0x86, 0x00 , 0x07, 0xDC, 0x8F, 0x00};
  CAN.sendMsgBuf(0x3D2, 0, 8, bles);
    delay(50);

  //gear 
   unsigned char gear[6] = {0x5A, 0x44, 0x75, 0x44, 0x8E, 0xFC};
  CAN.sendMsgBuf(0x116, 0, 6, gear);
    delay(50);

  //odo 
   unsigned char odo[4] = {0x3C, 0x27, 0x2C, 0x01};
  CAN.sendMsgBuf(0x562, 0, 4, odo);
    delay(50);

    

  //and generate the load of random messages
  num = random(10000); //now we test with 2 byte data
  unsigned char stmp[8] = {'H', 'e', 00 , 01 , 02, ' ', 's', 'e'};
  // send generated message
  CAN.sendMsgBuf(num, 0, 8, stmp);
  delay(50);
  index = random(8);
  stmp[index]++;
  if (stmp[index] > 255) stmp[index] = 0;


  
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
