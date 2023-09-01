#define BLYNK_TEMPLATE_ID "TMPLxfuzxcq8"
#define BLYNK_DEVICE_NAME "FullRelayConnectivity"
#define BLYNK_AUTH_TOKEN "XlbLZeu-dsQWL890ibRah
UW4Winp56e4"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Nawaz";
char pass[] = "Nawaz@2002";
#include "DHT.h"
#define DHTPIN D0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define trig D7
#define echo D8
int MagneticSwitch = D4;
int Buzzer = D3;
int SensorData = 0;
int SensorValue;
int depth =20, pinValue;
long cms, t, cm;
BlynkTimer timer;
void waterlevel()
{
 digitalWrite(trig, LOW);
 delayMicroseconds(2);
 digitalWrite(trig, HIGH);
 delayMicroseconds(10);
 digitalWrite(trig, LOW);
 t = pulseIn(echo, HIGH);
 cm = t / 29 / 2;
 Serial.println(cm);
 cms=cm;
 long level= depth-cm;
 if (level<0)
 level=0;
 level = map(level,0,depth-3,0,100);
 Blynk.virtualWrite(V4, level);
}
BLYNK_WRITE(V0)
{
 int value = param.asInt();
 Serial.println(value);
 if(value == 1)
 {
 digitalWrite(D1, LOW);
 Serial.println("LED ON");
 }
 if(value == 0)
 {
 digitalWrite(D1, HIGH);
 Serial.println("LED OFF");
 }
}
void setup()
{
 Serial.begin(115200);
 Blynk.begin(auth, ssid, pass);
 pinMode(D1,OUTPUT);
 pinMode(D2,OUTPUT);
 pinMode(D5,OUTPUT);
 pinMode(D6,OUTPUT);
 pinMode(Buzzer,OUTPUT);
 pinMode(MagneticSwitch,
INPUT_PULLUP);
 pinMode(trig, OUTPUT);
 pinMode(echo, INPUT);
 Serial.println("DHT11 Test!");
 dht.begin();

 timer.setInterval(10L, waterlevel);
}
void loop()
{
 // Magnetic Switch Logic
 SensorValue = digitalRead(MagneticSwitch);
 if(SensorValue == 1)
 {
 digitalWrite(Buzzer, HIGH);
 }
 else
 {
 digitalWrite(Buzzer, LOW);
 }
 // Temperature Sensor Logic
 delay(1000);
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 float f = dht.readTemperature(true);
if(isnan(h) || isnan(t) || isnan(f))
 {
 Serial.println("Failed to read
DHT sensor");
 return;
 }
 Serial.print("Humidity: ");
 Serial.println(h);
 Serial.print("Temperature: ");
 Serial.print(t);
 Serial.println("'C");
 Serial.print("Temperature: ");
 Serial.print(f);
 Serial.println("'F");
if(t>30.00)
 {
 digitalWrite(D2, LOW);
 Serial.println("Fan ON");
 }
 else
 {
 digitalWrite(D2, HIGH);
 Serial.println("Fan OFF");
 }
 Blynk.run();
 timer.run();
}
