
# Home Automation System

Internet of Things. Home Automation project to control the ESP8266 module using Google Assistant Services configured using IFTTT. Adafruit.io serving as dashboard.

![App Screenshot](https://i.ytimg.com/vi/1RkOMxuPvMw/maxresdefault.jpg)
## To configure a new ESP8266-01 using arduino-IDE and arduino-uno


1. Download the latest version of arduino-IDE from "https://www.arduino.cc/en/Main/Software"
2. Connect arduino-uno to system,
3. Now make sure there is no other code running on the arduino, Navigate to "File->Examples->01.Basics->BareMinimum" then upload this to the arduino-uno board
4. Open the preferences window from the Arduino IDE. Go to "File > Preferences"
5. Enter "http://arduino.esp8266.com/stable/package_esp8266com_index.json" into Additional Board Manager URLs field and click the “OK” button
6. Open boards manager. Go to Tools > Board > Boards Manager…
7. select the ESP8266 board menu and install “ESP8266 platform”
8. Choose your ESP8266 board from Tools > Board > Generic ESP8266 Module
9. Get your code ready check https://github.com/SatyamOzaR/Home-Automation-using-ESP8266-01/blob/main/blynk_temp/blynk_temp.ino to see code structure







![App Screenshot](https://raw.githubusercontent.com/SatyamOzaR/Home-Automation-using-ESP8266-01/main/blynk_temp/cheatsheet.jpeg)


## Circuit Diagram

![App Screenshot](https://iotcircuithub.com/wp-content/uploads/2021/12/Circuit-NodeMCU-Project-Relay-2-Buttons-P1-1536x864.jpg?ezimgfmt=ng:webp/ngcb1)
## Required Components
1. ESP8266 NodeMCU
2. 2-channel 5V SPDT Relay Module
3. Pushbuttons
## Step-by-step Process

- Clone old template for Blynk IoT Project.
- Add NodeMCU in the Blynk IoT App, set up Mobile Dashboard.
- Code for the NodeMCU Project.
- Connect IFTTT with Blynk to control relay with Google Assistant
- Syntax for the Blynk Webhooks URL in IFTTT to update Datastreams values.
## Blynk-IOT

```What is Blynk IoT platform?```

Blynk is a low-code IoT software platform for connecting devices to the cloud, building mobile apps to remotely control and monitor them, and managing thousands of users and deployed products. It’s a PaaS (Platform-as-a-Service) that helps businesses and individuals seamlessly progress from a prototype of a connected product to its commercial launch and further growth.

All Blynk plans include native mobile apps, in addition to all of the other typical IoT infrastructure. With over 400 hardware models support, customers can connect any device to the Internet and use a suite of software products to run commercial projects.
## Blynk IOT CLoud Setup

Here are some related projects

![App Screenshot](https://iotcircuithub.com/wp-content/uploads/2021/12/IFTTT-Blynk-Google-Assistant-p19.jpg?ezimgfmt=ng:webp/ngcb1)

For this project, you have to create 2 Datastreams using V1 and V2 virtual pins to control 2 relays.

Please refer to the following article for the Blynk IoT Cloud account setup.

[Getting started with New Blynk 2.0 IoT platform](https://iotcircuithub.com/blynk-iot-platform-setup-esp8266-esp32/)



## Google Assistant

When it comes to IoT with voice control, an important question to ask is: Does it support natural language? With Google Assistant and the Actions on Google developer platform, you define the various capabilities, or “traits,” of your device and the Assistant automatically handles all the different phrases that users can say to control it. In other words, Google gives you natural language understanding out of the box.

For example, you define that your device can turn on/off and dim lights; then, Google handles phrases like “Ok Google, turn on all my lights” and “Hey Google, dim the living room a little bit.” Google abstracts away the NLU and sends a structured JSON request to your webhook.
## Program NodeMCU with Arduino IDE

The steps to program the NodeMCU using Arduino IDE.

1. Update the Preferences –> Aditional boards Manager URLs: https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
2. Then install the ESP8266 board from the Board manager or Click Here to download the ESP8266 board.
3. Install all the required libraries in Arduino IDE:
- Install the Blynk library from Include Library or Click Here to down

![App Screenshot](https://iotcircuithub.com/wp-content/uploads/2021/10/blynk.png?ezimgfmt=ng:webp/ngcb1)

Go to Sketch -> Include Libraries -> Manage Libraries in Arduino IDE.

When you try to install the Blynk library, it may ask you to install all the dependencies. Then Click on Install All.


Use the below code for reference:

```bash
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

````


## Result

![App Screenshot](https://content.instructables.com/FYJ/FNY5/KQ9HJQOJ/FYJFNY5KQ9HJQOJ.jpg?auto=webp&fit=bounds&frame=1&height=1024&width=1024auto=webp&frame=1&height=150)