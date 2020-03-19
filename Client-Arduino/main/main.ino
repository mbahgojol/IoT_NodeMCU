#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
#include <Arduino.h>
#include <string.h>
#define SendKey 0  //Button to send data Flash BTN on NodeMCU

//Server connect to WiFi Network
const char *ssid = "kambing";  //Enter your wifi SSID
const char *password = "zxcasd4919";  //Enter your wifi Password

char host[] = "192.168.43.33";
const int socketPort = 3000;

SocketIoClient socket;

const int led = 5; //GPI05

void setup() 
{
  pinMode(led,OUTPUT);
  
  Serial.begin(115200);
  pinMode(SendKey,INPUT_PULLUP);  //Btn to send data
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //Connect to wifi
 
  // Wait for connection  
  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup 'on' listen events
  socket.on("connect", socket_Connected);
  socket.on("event", event);
  socket.on("send", sendDariWeb);
  socket.begin(host, socketPort);     
}

void loop() 
{
  socket.loop();
}

void ledKedip(){
  digitalWrite(led,HIGH);
  delay(5000);
  digitalWrite(led,LOW);
  delay(5000);
}

void sendDariWeb(const char *payload, size_t length)
{
  Serial.printf("got message: %s\n", payload);
  if(String((char*)payload) == "1"){
    socket.emit("join","Menyala");
    Serial.println("Menyala");
    digitalWrite(led,HIGH);
  }else if(String((char*)payload) == "0"){
    socket.emit("join","Mati");
    Serial.println("Mati");
    digitalWrite(led,LOW);
  }
}

void event(const char *payload, size_t length)
{
  Serial.printf("got message: %s\n", payload);
}

void socket_Connected(const char * payload, size_t length) {
  Serial.println("Socket.IO Connected!");
}
