#include "ServerMgr.h"

ServerMgr::ServerMgr(String host, int port)
{
  m_host = host;
  m_httpPort = port;
  
  m_responce = "";
  
  WiFi.begin("Infrastructure", "2k3Sd1a52nb12Ds");

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void ServerMgr::sendRequest(JsonObject& json, std::function<void(void)> fn)
{
    m_responce = "";
    Serial.println("SendRequest");
    while (!client.connected())
    {
      Serial.println("connectionLoop");
        if (client.connect(m_host.c_str(), m_httpPort))
        {
          Serial.println("FormReq");
            char buffer[256];
            json.printTo(buffer, sizeof(buffer));
          
           	String data(buffer);
            String request = "POST /postEndpoint HTTP/1.1";
            request = request + "\r\n";
            request = request + "Content-Type: application/json";
            request = request + "\r\n";
            request = request + "Content-Length: " + data.length();
            request = request + "\r\n";
            request = request + "\r\n";
            request = request + data;
            request = request + "\r\n";
			      //Serial.println(request);            
			      client.print(request);

            m_callback = fn;
        }
        else
        {
          Serial.println("Failed to Connect to server");
        }
    }
}

bool ServerMgr::receivedResponce()
{
   String responce = waitForResponce();
   
   if(responce != "")
   {      
      m_responce = responce;
      m_callback();
      return true;
   }
   return false;
}

String ServerMgr::getResponceString()
{  
  return m_responce;
}

JsonObject& ServerMgr::getResponceJson()
{
  int str_len = m_responce.length() + 1; 
  char char_array[str_len];
  m_responce.toCharArray(char_array, str_len);
  
  StaticJsonBuffer<200> jsonBuffer;  
  return jsonBuffer.parseObject(char_array);
}

String ServerMgr::waitForResponce()
{
   String serverResponceString = "";
   int count = 0;
   while(client.available() && client.connected())
   {
       char c = client.read();
       //Serial.println(c);
       serverResponceString += c;

       if(c == '\r')
        serverResponceString = "";
       
       if (c == '}')
       {
          client.stop();
          break;
        }

       
   }
   
  return serverResponceString;
}
