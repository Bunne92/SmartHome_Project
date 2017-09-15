  

#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <stdlib.h>
#include <stdio.h>

 boolean connectUDP();
 boolean connectWifi();
 
// wifi connection variables
const char* ssid = "COMHEM_cf3149";
const char* password = "btn2qty2";
boolean wifiConnected = false;

// UDP variables
unsigned int localPort = 8888;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char ReplyBuffer[2]; // a string to send back
int buttonstate = LOW; 
  
void setup() {
  // Initialise Serial connection
  Serial.begin(115200);
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  // only proceed if wifi connection successful
  if(wifiConnected)
  {
     udpConnected = connectUDP();
  }
}
void loop() {
  // check if the WiFi and UDP connections were successful
  if(wifiConnected)
  {
    memset(ReplyBuffer,0,2);
    int i = analogRead(A0), y;
    delay(100);
    y = map(i, 30, 1024, 0, 1024); 
    Serial.print(i);
    Serial.print("\n");
    itoa(i,ReplyBuffer,10);
    Serial.print(ReplyBuffer); 
    if(udpConnected)
    {
      
        IPAddress remote(192,168,0,21);
        UDP.beginPacket(remote, localPort);
        UDP.write("1 ");
        UDP.write(ReplyBuffer);
        UDP.endPacket();
        delay(1000);
      //} 
    }
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
