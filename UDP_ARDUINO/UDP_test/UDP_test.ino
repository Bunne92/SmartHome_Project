  

#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

 boolean connectUDP();
 boolean connectWifi();
 
// wifi connection variables
const char* ssid = "Molk";
const char* password = "Molk0901";
boolean wifiConnected = false;



// UDP variables
unsigned int localPort = 80;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char ReplyBuffer[] = "GAY SENSOR ACTIVATED 100% GAY"; // a string to send back

int buttonstate = LOW; 
  
void setup() {
  // Initialise Serial connection
  Serial.begin(115200);
  pinMode(2, OUTPUT); 
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
    if(udpConnected)
    {
      buttonstate = digitalRead(2);
      if(buttonstate == HIGH){
       IPAddress remote(192,168,153,156);
      // if there’s data available, read a packet
       int packetSize = UDP.parsePacket();
      
        UDP.beginPacket(remote, localPort);
        UDP.write(ReplyBuffer);
        UDP.endPacket();
        delay(10);
      } 
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
