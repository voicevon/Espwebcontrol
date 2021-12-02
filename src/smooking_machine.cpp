#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "Your_SSID";
const char* password = "Your_Password";

const int led_output = 2;

// HTML web page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
  <head>
    <title>ESP Web Server</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body { font-family: Times New Roman; text-align: center; margin:0px auto; padding-top: 30px;}
      .button {
        padding: 10px 20px;
        font-size: 24px;
        text-align: center;
        outline: none;
        color: #fff;
        background-color: #ff0522;
        border: none;
        border-radius: 5px;
        cursor: pointer;
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
        -webkit-tap-highlight-color: rgba(0,0,0,0);
      }  
      .button:hover {background-color: #ff0522 }
      .button:active {
        background-color: #1fe036;
        transform: translateY(2px);
      }
    </style>
  </head>
  <body>
    <h1>ESP Momentary Switch Web Server</h1>
    <button class="button" onmousedown="toggleCheckbox('ON');" ontouchstart="toggleCheckbox('ON');" onmouseup="toggleCheckbox('OFF');" ontouchend="toggleCheckbox('OFF');">Momentary Switch: Press to Turn ON</button>
   <script>
   function toggleCheckbox(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/" + x, true);
     xhr.send();
   }
  </script>
  </body>
</html>)rawliteral";


AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  pinMode(led_output, OUTPUT);
  digitalWrite(led_output, LOW);
  
  // Send web page to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Receive an HTTP GET request
  server.on("/ON", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(led_output, HIGH);
    request->send(200, "text/plain", "OK");
  });

  // Receive an HTTP GET request
  server.on("/OFF", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(led_output, LOW);
    request->send(200, "text/plain", "OK");
  });
  
  
  server.begin();
}

void loop() {
 
}