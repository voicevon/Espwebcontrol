//==================================
//ESP32 WebSocket Server: Toggle LED
//by: Ulas Dikme
// https://akuzechie.blogspot.com/2020/12/esp32-websocket-server.html
//==================================
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
//-----------------------------------------------
const char* ssid = "FuckGFW";
const char* password = "refuckgfw";
//-----------------------------------------------
#define LED 2
//-----------------------------------------------
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
//-----------------------------------------------
boolean varOnOff=false; String JSONtxt;
int var_total_volume = 0;
int var_total_count = 0;
//-----------------------------------------------
#include "html_page.h"
#include "web_functions.h"
//====================================================================
void setup()
{
  Serial.begin(115200); pinMode(LED, OUTPUT);
  //-----------------------------------------------
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){Serial.print("."); delay(500);}
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  //-----------------------------------------------
  server.on("/", webpage);
  //-----------------------------------------------
  server.begin(); webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}
//====================================================================
void loop()
{
  webSocket.loop(); server.handleClient();
  //-----------------------------------------------
  if(varOnOff == false) digitalWrite(LED, LOW);
  else digitalWrite(LED, HIGH);
  var_total_volume ++;
  //-----------------------------------------------
  String strOnOff = "OFF";
  if(varOnOff == true) strOnOff = "ON";
  // JSONtxt = "{\"varOnOff\":\""+LEDstatus+"\"
  //             }";  
  JSONtxt = "{\"varOnOff\":\""+strOnOff+"\","
            + "\"var_total_volume\"" +":" + var_total_volume
              +"}";
  webSocket.broadcastTXT(JSONtxt);
}
