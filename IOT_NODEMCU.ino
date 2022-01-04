#include <ESP8266WiFi.h>
#include <DHT.h>
#define LEDPIN D4
#define LEDPIN_BLUE D5
#define DHTTYPE DHT11
#define GASPIN A0
const int DHTPin= D1;
const char *ssid =  "TP-Link_D1D8";
const char *pass =  "322Furkan786"; 
DHT dht(DHTPin, DHTTYPE);
const char * host = "192.168.1.101";
const uint16_t port = 1200;
WiFiClient client;
static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];  
float gas_value;



void setup(){
  Serial.begin(9600);
  dht.begin();
  WiFi.begin(ssid, pass);
  pinMode(LEDPIN,OUTPUT);
  pinMode(LEDPIN_BLUE,OUTPUT);
  while(WiFi.status() != WL_CONNECTED){
    delay(200);
    Serial.print("Wifi bağlantısı bekleniyor ...\n");
    
    }
  Serial.println("Connected as ");
  Serial.println(WiFi.localIP());
}

void loop(){
 
  gas_value = analogRead(GASPIN);
  digitalWrite(LEDPIN,LOW);
  digitalWrite(LEDPIN_BLUE,LOW);
  
  if(dht.readTemperature() > 26 && gas_value < 548){
    Serial.print("Temperature = ");
    Serial.print(dht.readTemperature());Serial.print(" Warning ! turn off natural gas\n");
    Serial.print("Humidity = ");
    Serial.print(dht.readHumidity());Serial.print(" %\n");
    Serial.print("Gas = ");
    Serial.print(gas_value);Serial.print("\n");
    digitalWrite(LEDPIN,HIGH);
    if (!client.connect(host, port)) {

        Serial.println("Connection to host failed");

        delay(200);
        return;
    }
    
    Serial.println("Connected to server successful!");
    client.print(dht.readTemperature());
    Serial.println("Disconnecting...");
    client.stop();
    delay(750);
    
    }
    else if(gas_value > 555 && dht.readTemperature() < 26){
     Serial.print("Temperature = ");
     Serial.print(dht.readTemperature());Serial.print("\n");
     Serial.print("Humidity = ");
     Serial.print(dht.readHumidity());Serial.print(" %\n");
     Serial.print("Gas = ");
     Serial.print(gas_value);Serial.print(" Warning ! There is a gas leak here\n");
     digitalWrite(LEDPIN,HIGH);
     if (!client.connect(host, port)) {

        Serial.println("Connection to host failed");

        delay(200);
        return;
    }
    
    Serial.println("Connected to server successful!");
    client.print("Gas");
    Serial.println("Disconnecting...");
    client.stop();
    delay(750);
    
      }
    else if(gas_value > 555 && dht.readTemperature() > 26){
      Serial.print("Temperature = ");
      Serial.print(dht.readTemperature());Serial.print(" Warning ! turn off natural gas\n");
      Serial.print("Humidity = ");
      Serial.print(dht.readHumidity());Serial.print(" %\n");
      Serial.print("Gas = ");
      Serial.print(gas_value);Serial.print(" Warning ! There is a gas leak here\n");
      digitalWrite(LEDPIN,HIGH);
      if (!client.connect(host, port)) {

        Serial.println("Connection to host failed");

        delay(200);
        return;
    }
    
    Serial.println("Connected to server successful!");
    client.print("Gas");
    
    Serial.println("Disconnecting...");
    client.stop();
      delay(750);
      
      }
    else if(dht.readTemperature() <= 20){
      Serial.print("Temperature = ");
      Serial.print(dht.readTemperature());Serial.print(" Warning ! turn on natural gas\n");
      Serial.print("Humidity = ");
      Serial.print(dht.readHumidity());Serial.print(" %\n");
      Serial.print("Gas = ");
      Serial.print(gas_value);Serial.print("\n");
      digitalWrite(LEDPIN_BLUE,HIGH);
      if (!client.connect(host, port)) {

        Serial.println("Connection to host failed");

        delay(200);
        return;
    }
    
      Serial.println("Connected to server successful!");
      client.print(dht.readTemperature());
      Serial.println("Disconnecting...");
      client.stop();
      delay(750);

    }
  else{
    Serial.print("Temperature = ");
    Serial.println(dht.readTemperature());
    Serial.print("Humidity = ");
    Serial.print(dht.readHumidity());Serial.print(" %\n");
    Serial.print("Gas = ");
    Serial.print(gas_value);Serial.print("\n");
    delay(750);
      } 
  
}
