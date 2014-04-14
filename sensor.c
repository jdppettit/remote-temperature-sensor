#include <Adafruit_BMP085_U.h>

#include <power.h>
#include <sleep.h>
#include <wdt.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11 
#define DHTPIN1 7
#define DHTTYPE1 DHT22

#define ONE_WIRE_BUS 4

const int Xbee_wake = 9;

DHT dht(DHTPIN, DHTTYPE);
DHT dht1(DHTPIN1, DHTTYPE1);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

volatile int f_wdt=0;

void setup() {
  Serial.begin(9600);
  wakeXbee();
  dht.begin();
  Serial.println("Initialising...");
  delay(100); //Allow for serial print to complete.
  
  Serial.println("Initialisation complete.");
  delay(100); //Allow for serial print to complete.
  
   if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
 
  delay(10000);
 
}

void loop() {
 
  delay(5000);
  
  float h = dht.readHumidity();
  float h1 = dht1.readHumidity();
  
  sensors.requestTemperatures();
  
  if (isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print(h);
    Serial.print(";");
  }
    delay(1000);
    Serial.print(sensors.getTempFByIndex(0));
   
    Serial.print(";");
    Serial.print(sensors.getTempFByIndex(1));
    Serial.print(";");
    
    Serial.print(h1);
    Serial.print(";");
    
    sensors_event_t event;
  bmp.getEvent(&event);
  
  if (event.pressure)
  {
   
    Serial.print(event.pressure);
    Serial.println("");
  }
  else
  {
    Serial.print("Sensor error");
    Serial.println("");
  }
    
    delay(2000);
    
  
}

void wakeXbee() {
    pinMode(Xbee_wake,OUTPUT);
    digitalWrite(Xbee_wake, LOW);
}

void sleepXbee() {
    pinMode(Xbee_wake, INPUT);
    digitalWrite(Xbee_wake, HIGH);
}

