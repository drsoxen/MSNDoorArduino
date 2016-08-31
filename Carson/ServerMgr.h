#ifndef SERVER_MGR
#define SERVER_MGR

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

class ServerMgr
{
public:
	ServerMgr(String host, int port);
	void sendRequest(JsonObject& json, std::function<void(void)> fn);
	bool receivedResponce();
  
  JsonObject& getResponceJson(); 
  String getResponceString();

  WiFiClient client;
  String m_host;
  int m_httpPort;

private:
   String waitForResponce();

   std::function<void(void)> m_callback;
   String m_responce;
};

#endif
