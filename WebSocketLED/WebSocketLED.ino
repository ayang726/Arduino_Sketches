/*
   WebSocketClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>

#include <WebSocketsClient.h>
#include <DataHandler.h>

// #include <Hash.h>


WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
//////////////////////SETUP CODE///////////////////////////

#define WIFICONNECTION_TIMEOUT 60000
#define MESSAGE_INTERVAL 100
#define HEARTBEAT_INTERVAL 30000
#define RECONNECT_INTERVAL 2000

#define USE_SERIAL Serial

#define SSID "HOME2GEXT"
#define password "feast5884charge"
#define user "User"
#define authKey "kEy"
#define host "10.0.0.195"
#define port 3000


uint64_t messageTimestamp = 0;
uint64_t heartbeatTimestamp = 0;
bool isConnected = false;

//////////////////////TEST CODE/////////////////////////////
const int STATUSPIN = 2;

const int LEDPIN = 16;
const int BUTTONPIN = 17;

int buttonState = 0;

///////////////////////////////////////////////////


void setup() {
    ////////////////////////TESTCODE: SETUP FOR LED PINS///////////////////////
    pinMode(LEDPIN, OUTPUT);
    pinMode(BUTTONPIN, INPUT_PULLUP);
    digitalWrite(LEDPIN, LOW);
    ///////////////////////////////////////////////////////////////////////////

    pinMode(STATUSPIN, OUTPUT);

    setupForWifiAndWebSockets();

}

void loop() {
    //////////////////////LOOP FOR LED DETECTION///////////////// 
    buttonState = digitalRead(BUTTONPIN);
    if(buttonState == LOW) {
        digitalWrite(LEDPIN, HIGH);
    } else {
        digitalWrite(LEDPIN, LOW);
    }
    
    SocketData dataHandler = SocketData("ledLit", !buttonState);

    webSocket.loop();

    if (isConnected) {

        uint64_t now = millis();

        if (now - messageTimestamp > MESSAGE_INTERVAL) {
        messageTimestamp = now;
        // example socket.io message with type "messageType" and JSON payload
        // webSocket.sendTXT("42[\"messageType\",{\"greeting\":\"hello\"}]");

        // USE_SERIAL.println("Sending Starting Binary data");
        // USE_SERIAL.println(dataHandler.parsedString);
        webSocket.sendTXT(dataHandler.parsedString);
        }
        
        if ((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
        heartbeatTimestamp = now;
        // socket.io heartbeat message
        webSocket.sendTXT("2");
        toggleStatusLight();
        }
    }
    delay(200);
}

////////////////////////////--FUNCTIONS--//////////////////////////////////////

void hexdump(const void *mem, uint32_t len, uint8_t cols = 16) {
  const uint8_t* src = (const uint8_t*) mem;
  USE_SERIAL.printf("\n[HEXDUMP] Address: 0x%08X len: 0x%X (%d)", (ptrdiff_t)src, len, len);
  for (uint32_t i = 0; i < len; i++) {
    if (i % cols == 0) {
      USE_SERIAL.printf("\n[0x%08X] 0x%08X: ", (ptrdiff_t)src, i);
    }
    USE_SERIAL.printf("%02X ", *src);
    src++;
  }
  USE_SERIAL.printf("\n");
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {


  switch (type) {
    case WStype_DISCONNECTED:
      USE_SERIAL.printf("[WSc] Disconnected!\n");
      isConnected = false;
      break;
    case WStype_CONNECTED:
      {
        USE_SERIAL.printf("[WSc] Connected to url: %s\n",  payload);
        isConnected = true;

        // send message to server when Connected
        // socket.io upgrade confirmation message (required)
        webSocket.sendTXT("5");

        // USE_SERIAL.println("Receiving Message");
        webSocket.sendTXT("42[\"message\",\"Is anyone out there?\"]");
        
      }
      break;
    case WStype_TEXT:
      USE_SERIAL.printf("[WSc] get text: %s\n", payload);

      // send message to server
      // webSocket.sendTXT("message here");
      break;
    case WStype_BIN:
      USE_SERIAL.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
  }

}

void setupForWifiAndWebSockets() {
    

    USE_SERIAL.begin(115200);

    //Serial.setDebugOutput(true);
    USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    USE_SERIAL.print("Connecting to WIFI at ");
    USE_SERIAL.println(SSID);
    
    // ///////////////// Use WiFi Framework///////////////////
    // WiFi.begin(SSID,password);
    // while (WiFi.status() != WL_CONNECTED) {
    //   delay(500);
    //   USE_SERIAL.print(".");
    // }

    /////////////////////Use WiFiMulti Framework//////////////

    uint64_t now = millis();
    WiFiMulti.addAP(SSID, password);
    while (WiFiMulti.run() != WL_CONNECTED) {
        if (millis() - now > WIFICONNECTION_TIMEOUT) {
            USE_SERIAL.println();
            USE_SERIAL.println("-------------");
            USE_SERIAL.println("Restarting myself....");
            USE_SERIAL.println("-------------");
            esp_restart();
        }
        USE_SERIAL.print(".");
        toggleStatusLight();
        delay(500);
    }
    
    USE_SERIAL.println();
    USE_SERIAL.println("Connected!");
    toggleStatusLight(20, 10);
    // USE_SERIAL.print("My IP address: ");
    // USE_SERIAL.println(WiFi.localIP());
    

    // server address, port and URL
    webSocket.beginSocketIO(host, port);

    // event handler
    webSocket.onEvent(webSocketEvent);

    // use HTTP Basic Authorization this is optional remove if not needed
    // webSocket.setAuthorization(user, authKey);

    // try ever 5000 again if connection has failed
    webSocket.setReconnectInterval(RECONNECT_INTERVAL);
    
}

void lightIndicator_ConnectedToWifi() {
    // pinMode(STATUSPIN, OUTPUT); // already set in the setup function
    for(int i = 0; i < 10; i++)
    {
        digitalWrite(STATUSPIN, LOW);
        delay(100);
        digitalWrite(STATUSPIN, HIGH);
        delay(100);
    }
}
void toggleStatusLight() {
    // must have
    // pinMode(STATUSPIN, OUTPUT);
    //somewhere in code
    digitalWrite(STATUSPIN, !digitalRead(STATUSPIN));
}

void toggleStatusLight(int times, int Hertz) {
    int frequency = 1/double(Hertz)*1000;
    USE_SERIAL.println(frequency);
    for(int i = 0; i < times; i++)
    {
        digitalWrite(STATUSPIN, LOW);
        delay(frequency);
        digitalWrite(STATUSPIN, HIGH);
        delay(frequency);
    }
}