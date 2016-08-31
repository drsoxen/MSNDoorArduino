#ifndef RFID_MGR
#define RFID_MGR

#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

class RFIDMgr
{
public:
	RFIDMgr();
	bool cardFound();
	String getCard();
 
};

#endif
