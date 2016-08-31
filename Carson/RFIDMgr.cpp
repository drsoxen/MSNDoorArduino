#include "RFIDMgr.h"

#define RST_PIN  15
#define SS_PIN  2

MFRC522 mfrc522(SS_PIN, D1);

RFIDMgr::RFIDMgr()
{
  SPI.begin();
  mfrc522.PCD_Init();  
}

bool RFIDMgr::cardFound()
{
  SPI.begin();
  mfrc522.PCD_Init(); 
  return mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();
}

String RFIDMgr::getCard()
{
  String UserID = "";
  UserID += String(mfrc522.uid.uidByte[0], DEC);
  UserID += String(mfrc522.uid.uidByte[1], DEC);
  UserID += String(mfrc522.uid.uidByte[2], DEC);
  UserID += String(mfrc522.uid.uidByte[3], DEC);
  UserID += String(mfrc522.uid.uidByte[4], DEC);        
  
  mfrc522.PICC_HaltA();

  return UserID;
}
