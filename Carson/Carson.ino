#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <MFRC522.h>

#include "ServerMgr.h"
#include "RFIDMgr.h"
#include "LockMgr.h"
#include "SoundMgr.h"
#include "TimerMgr.h"

ServerMgr* m_server;
RFIDMgr* m_rfid;
LockMgr* m_lock;
SoundMgr* m_sound;
TimerMgr* m_timer;

ESP8266WebServer server(80);

void doMessage()
{
  if(strcmp(server.arg(0).c_str(), "lock") == 0)
    m_lock->changeLockState(LOCK);
    
  else if(strcmp(server.arg(0).c_str(), "unlock") == 0)
    m_lock->changeLockState(UNLOCK);
    
  else if(strcmp(server.arg(0).c_str(), "pulse_unlock") == 0)
    m_lock->changeLockState(PULSE_UNLOCK);
    
  else if(strcmp(server.arg(0).c_str(), "long_pulse_unlock") == 0)
    m_lock->changeLockState(LONG_PULSE_UNLOCK);
    
  else
  {
    server.send (200, "text/html","false");
    return;
  }
  
  server.send (200, "text/html","true");
}

void setup()
{    
    Serial.begin(115200);
    delay(10);
    Serial.print("\nInitialized");

    m_timer = new TimerMgr();
    m_server = new ServerMgr("192.168.2.250", 6969);
    m_rfid = new RFIDMgr();
    m_sound = new SoundMgr();    
    m_lock = new LockMgr(D0,m_timer);
    
    m_lock->changeLockState(LOCK);

    server.on("/Message", doMessage);
    server.begin();

    InitCtrl();
}

void InitCtrl()
{
  uint8_t mac[6];
  WiFi.macAddress(mac);
  char myMacString[24];
  sprintf(myMacString, "%d.%d.%d.%d.%d.%d", mac[0], mac[1], mac[2], mac[3], mac[4], mac[4]);  
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["Type"] = "Init";
  root["CtrlID"] = myMacString;

  char myIpString[24];
  IPAddress myIp = WiFi.localIP();
  sprintf(myIpString, "%d.%d.%d.%d", myIp[0], myIp[1], myIp[2], myIp[3]);        
  root["IP"] = myIpString;
        
  m_server->sendRequest(root,initCallback);
}

void initCallback()
{
   JsonObject& responce = m_server->getResponceJson();
   const char* accessLvl = responce["AccessLvl"];


   Serial.println("Server connected");
}

void authCallback()
{
  JsonObject& responce = m_server->getResponceJson();
  const char* access = responce["Access"];
  const char* rtttl = responce["RTTTL"];  

  if(strcmp(access, "true") == 0) 
  {
    m_lock->changeLockState(PULSE_UNLOCK);
    
    if(strcmp(rtttl, "NULL") == 0)
      m_sound->playSound(GOOD);
    else    
      m_sound->playSound(GOOD, strdup(rtttl));
  }
  else
  {
    m_sound->playSound(BAD);
  }
}

void loop()
{
    //if(WiFi.status() != WL_CONNECTED)
      //m_lock->changeLockState(UNLOCK);
  
    server.handleClient();
    m_server->receivedResponce();

    m_timer->tickTimers();

    delay(250);
    if(m_rfid->cardFound())
    {
        m_sound->playSound(READ);
      
        String UserID = m_rfid->getCard();

        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();
        root["Type"] = "Auth";
        root["ID"] = UserID.toInt();

        m_server->sendRequest(root, authCallback);
    }
}
