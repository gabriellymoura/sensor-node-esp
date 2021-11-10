
#include <WiFi.h>
#include <PubSubClient.h>

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char* ssid = "RPiUema";
const char* password = "1234567890";
const char* mqtt_server = "192.168.50.5";

// Initializes the espClient
WiFiClient espClient;
PubSubClient MQTT(espClient);

//temperatura
int DS18B20 = 23; 
OneWire ourWire(DS18B20);
DallasTemperature sensors(&ourWire);

//umidade
const int AirValue = 4095;   //you need to replace this value with Value_1
const int WaterValue = 900;  //you need to replace this value with Value_2
const int SensorPin = 26;

//auxiliares
int soilMoistureValue = 0;
int soilmoisturepercent=0;
float t;
char data[80];
char arrayT[4];
char arrayU[4];

long now = millis();
long lastMeasure = 0;

void setup() {
  Serial.begin(115200);
  initWiFi();
  initMQTT();
}

void loop() { 
  verificaConexaoWIFIMQTT();
  MQTT.loop();
    
  sensors.requestTemperatures(); //temp
  dtostrf(sensors.getTempCByIndex(0), 4, 2, arrayT); 
    
  soilMoistureValue = analogRead(SensorPin); //umidade
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);

  if(soilmoisturepercent > 100){
   // MQTT.publish("/esp32/temperature", arrayT);
    Serial.print("temperatureTemp: ");
    Serial.print(arrayT);
    Serial.println("*C ");
    //MQTT.publish("/esp32/humidity", "100");
    Serial.print("Umidade: ");
    Serial.println("100 %");  

    String Readings = "{ \"temperature\": \"" + String(sensors.getTempCByIndex(0)) + "\", \"humidity\" : \"" + String(100) + "\"}";
    Readings.toCharArray(data, (Readings.length() + 1));
    MQTT.publish("PV/ESP32/05", data);
    
  }
  else if(soilmoisturepercent <0){ 
    //MQTT.publish("/esp32/temperature", arrayT);
    Serial.print("temperatureTemp: ");
    Serial.print(arrayT);
    Serial.println("*C ");
       
    //MQTT.publish("/esp32/humidity", "0");
    Serial.print("Umidade: ");
    Serial.println("0 %");

    String Readings = "{ \"temperature\": \"" + String(sensors.getTempCByIndex(0)) + "\", \"humidity\" : \"" + String(0) + "\"}";
    Readings.toCharArray(data, (Readings.length() + 1));
    MQTT.publish("PV/ESP32/05", data);
    
  }
  else if(soilmoisturepercent >=0 && soilmoisturepercent <= 100){
    //MQTT.publish("/esp32/temperature", arrayT);
    Serial.print("temperatureTemp: ");
    Serial.print(arrayT);
    Serial.println("*C ");
    
    dtostrf(soilmoisturepercent, 4, 2, arrayU); 
    //MQTT.publish("/esp32/humidity",arrayU);
    Serial.print("Umidade: ");
    Serial.print(arrayU);
    Serial.println("%");

    String Readings = "{ \"temperature\": \"" + String(sensors.getTempCByIndex(0)) + "\", \"humidity\" : \"" + String(soilmoisturepercent) + "\"}";
    Readings.toCharArray(data, (Readings.length() + 1));
    MQTT.publish("PV/ESP32/05", data);
    
  } 
  // Publishes new temperature and humidity every 1 hour (3600000 ms)
  delay(3600000);

//  delay(10000);
}
