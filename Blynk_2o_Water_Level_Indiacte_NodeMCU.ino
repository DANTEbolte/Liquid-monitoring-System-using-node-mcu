
 *  For NodeMCU:
 *  https://arduino.esp8266.com/stable/package_esp8266com_index.json
 *  
 *  *********************************************************************************/


/* Fill-in your Template ID (only if using Blynk.Cloud) */

#define BLYNK_TEMPLATE_ID "TMPLHYmfbonE"
#define BLYNK_DEVICE_NAME "ESP8266"
#define BLYNK_AUTH_TOKEN "xpS6cfxCZzR4eD3yF4yYjFvv5nBU8CYP"



#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define trig D5   // Trig pin
#define echo D6  // Echo Pin 
// Comment this out to disable prints and save space

char ssid[] = "SSD 5g";  // type your wifi name
char pass[] = "sahil2002";  // type your wifi password
int tankdepth =8 ;   // Change  according to your tank depth


BlynkTimer timer;


char auth[] = BLYNK_AUTH_TOKEN;
void PGM()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
  Serial.println(cm);
  long level= tankdepth-cm;
  if (level<0)
  level=0;
  level = map(level,0,tankdepth-4,0,100);
  Blynk.virtualWrite(V0, level);
  Blynk.virtualWrite(V1,"Tank Water LeveL");
  Blynk.virtualWrite(V2,"     in %");
}

 
void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10L, PGM);
  pinMode(D4,OUTPUT);
  digitalWrite(D4,HIGH);
  
}

void loop()
{
 
  Blynk.run();
  timer.run();
  }
