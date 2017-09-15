
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <stdlib.h>
#include <stdio.h>

boolean connectUDP();
boolean connectWifi();
 
// wifi connection variables
const char* ssid = "ASUS";
const char* password = "bajskorv";
boolean wifiConnected = false;
int value = 0, y = 0; 

// UDP variables
unsigned int localPort = 8888;
WiFiUDP UDP;
boolean udpConnected = false;
IPAddress remote(192,168,1,60);
char ReplyBuffer[10]; // a string to send back


  
void setup() {
  Serial.begin(115200);
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  // only proceed if wifi connection successful
  if(wifiConnected){
     udpConnected = connectUDP();
  }
}
void loop() {
  // check if UDP connections were successful

    if(udpConnected){
      y = 40; 
      itoa(y,ReplyBuffer,10);
      delay(450); 
      UDP.beginPacket(remote, localPort);
      UDP.write("2 ");
      UDP.write(ReplyBuffer);
      UDP.endPacket();
        delay(100); 
      } 
  }


// connect to UDP – returns true if successful or false if not
 boolean connectUDP()
 {
    boolean state = false;

    Serial.println("");
    Serial.println("Connecting to UDP");

    if(UDP.begin(localPort) == 1)
    {
      Serial.println("Connection successful");
      state = true;
    }
    else
    {
      Serial.println("Connection failed");
    }

    return state;
}

    
// connect to wifi – returns true if successful or false if not
 boolean connectWifi()
 {
    boolean state = true;
    int i = 0;
    WiFi.begin(ssid, password);
    Serial.println("");
    Serial.println("Connecting to WiFi");

    // Wait for connection
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
      if (i > 10)
      {
        state = false;
        break;
      }
      i++;
    }
    if (state)
    {
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    }
    else 
    {
      Serial.println("");
      Serial.println("Connection failed.");
    }
    return state;
}
