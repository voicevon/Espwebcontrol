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
String JSONtxt;
boolean varOnOff=false; 
boolean varPause=false;
boolean varReset=false;
int var_total_volume = 0;
int var_total_count = 0;
int var_volume = 0;
int var_push_time = 3;
int var_sleep_time = 50;
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

void send_status(){
  String strOnOff = "OFF";
  String strPause = "Going";
  String strReset = "Reset";
  if(varOnOff) strOnOff = "ON";
  if(varPause) strPause = "Paused";
  // JSONtxt = "{\"varOnOff\":\""+LEDstatus+"\"
  //             }";  
  JSONtxt = "{\"varOnOff\":\""+strOnOff+"\","
            + "\"varPause\":\""+strPause+"\","
            + "\"var_total_volume\"" +":\"" + var_total_volume + "\","
            + "\"var_total_count\"" +":\"" + var_total_count + "\""
              +"}";
  // Serial.println(JSONtxt);
  // delay(300);
  webSocket.broadcastTXT(JSONtxt);
}

void send_setting(){
  String strOnOff = "OFF";
  String strPause = "Going";
  String strReset = "Reset";
  if(varOnOff) strOnOff = "ON";
  if(varPause) strPause = "Paused";
  JSONtxt = "{\"varOnOff\":\""+strOnOff+"\","
            + "\"varPause\":\""+strPause+"\","
            + "\"var_total_volume\"" +":\"" + var_total_volume + "\","
            + "\"var_total_count\"" +":\"" + var_total_count + "\","
            + "\"var_volume\"" +":\"" + var_volume + "\","
            + "\"var_push_time\"" +":\"" + var_push_time + "\","
            + "\"var_sleep_time\"" +":\"" + var_sleep_time + "\""
              +"}";
  webSocket.broadcastTXT(JSONtxt);
}
//====================================================================
void loop()
{
  webSocket.loop(); server.handleClient();
  //-----------------------------------------------
  if(varOnOff == false) digitalWrite(LED, LOW);
  else digitalWrite(LED, HIGH);
  //-----------------------------------------------
  send_setting();

}
