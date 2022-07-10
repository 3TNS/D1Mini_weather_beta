#include <Arduino.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#define BLYNK_TEMPLATE_ID "Your blynk template id" //Fill in from Blynk dashboard
#define BLYNK_DEVICE_NAME "Your blynk device name" //Fill in from Blynk dashboard
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>


char auth[] = "Your Blynk aurh token"; //Fill in from Blynk dashboard
char ssid[] = "ssid";  //Enter your WIFI Name
char pass[] = "password";  //Enter your WIFI Password

#define DHTPIN 2          // Digital pin 4
#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity on DHT22
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature on DHT22
}

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}