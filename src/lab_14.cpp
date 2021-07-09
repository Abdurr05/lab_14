/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Abdurrahman/Documents/labs/lab_14/src/lab_14.ino"
#include "oled-wing-adafruit.h"
#include "MQTT.h"
#include <blynk.h>
void setup();
void loop();
#line 4 "c:/Users/Abdurrahman/Documents/labs/lab_14/src/lab_14.ino"
OledWingAdafruit display;
SYSTEM_THREAD(ENABLED);

bool pressedA = false;
void callback(char* topic, byte* payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.printf("%s",p);
  Serial.println();
  if(p[0] == '1'){
    digitalWrite(D7, HIGH);
  }
  if(p[0] == '0'){
    digitalWrite(D7, LOW);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(p);
  display.display();
}
BLYNK_WRITE(V1) {
  String text = param.asStr();
  client.publish("ksa",text);
}

// setup() runs once, when the device is first turned on.
void setup() {
  display.setup();
	display.clearDisplay();
	display.display();

  pinMode(D7,OUTPUT);
  Serial.begin(9600);

  Blynk.begin("ctbHP9eZLnUvmjXzqngyAKc3NjZdJKd1", IPAddress(167, 172, 234, 162), 9090);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  display.loop();
  Blynk.run();
  if (client.isConnected()) {
    client.loop();
  } else {
    client.connect(System.deviceID());
  }
  client.subscribe("ksa");
    if(display.pressedA()){
    client.publish("ksa","pressed A");
 
  }
  if(display.pressedB()){
    client.publish("ksa","pressed B");
 
  }
  if(display.pressedC()){
    client.publish("ksa","pressed C");
 
  }

  // The core of your code will likely live here.

}