#include <dht.h>

#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <stdlib.h>
#include <stdio.h>

dht DHT;
boolean connectUDP();
boolean connectWifi();

// wifi connection variables
const char* ssid = "TN_24GHz_ABB15F";
const char* password = "2AE679EC96";
boolean wifiConnected = false;

const int DHTpin = 5;
int temp;
int celsius = 0;
int humidity = 0;

//int value = 0, y = 0; 

// UDP variables
unsigned int localPort = 8888;
WiFiUDP UDP;
boolean udpConnected = false;
IPAddress remote(192,168,10,209);
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


    
    //Serial.print(celsius);
    Serial.print("\n");
    delay(100);

    temp = DHT.read11(DHTpin);

    celsius = DHT.temperature;
    humidity = DHT.humidity;
    delay(2000);
    Serial.print("Tempeartur:");
    Serial.print(celsius);
    Serial.print("C");
    Serial.print("\t|\t");
    Serial.print("Luftfuktighet:");
    Serial.print(humidity);
    Serial.print("%\n");
    
    if(udpConnected)
    {   

      
      //itoa(celsius, ReplyBuffer, 10);
      
      /*for(int i = 0; i <= 10; i++){
        value += analogRead(A0);
        delay(10); 
      }
      value = value/10;
      y = map(value, 10, 700, 0, 1024); 
      value = 0; 
      itoa(y,ReplyBuffer,10);*/
      
      UDP.beginPacket(remote, localPort);
      UDP.write("1 ");
      UDP.write(ReplyBuffer);
      UDP.endPacket();
        delay(100); 
      } 
  }

  

//----------------------------------------FUNCTIONS--------------------------------------------

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
    WiFi.begin(ssid);
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
