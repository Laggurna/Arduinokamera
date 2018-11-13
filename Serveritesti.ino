#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "OnePlus2";
const char* password = "testi123";

ESP8266WebServer server(80);

String webPage = "";

int gpio0_pin = 0; // D3 pin in our wifi-module connected to Arduino D3.


void setup(void){
  webPage += "<h1>Ultimaattinen halytysjarjestelma</h1><p>Halytys <a href=\"socket1On\"><button>PAALLE</button></a>&nbsp;<a href=\"socket1Off\"><button>POIS</button></a></p>";
 
  
  // preparing GPIOs
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, LOW);
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, HIGH);
    delay(1000);
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, LOW);
    delay(1000); 
  });
  server.begin();
  Serial.println("HTTP serveri kaynnissa");
}
 
void loop(void){
  server.handleClient();
} 
