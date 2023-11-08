#include <Servo.h> 
#include <ArduinoJson.h>
#include <DHT.h>
Servo myServo;
const int mq7Pin = A0;
const int mq4Pin = A1;
const int servoPin = A5;
const int DHTPIN = A2;
float newT =0.0;
float newH =0.0;

#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);
void setup() {

  Serial.begin(115200);
  dht.begin();  
  myServo.attach(servoPin);

  pinMode(mq7Pin, INPUT);
  pinMode(mq4Pin, INPUT);
}

void loop() {
    newT = dht.readTemperature();
    newH = dht.readHumidity();
  int mq7Value = analogRead(mq7Pin);
  int mq4Value = analogRead(mq4Pin);

  DynamicJsonDocument doc(256);
  doc["mq7"] = mq7Value;
  doc["mq4"] = mq4Value;
  doc["Temp"] = newT;
  doc["Humid"] = newH;

  // Control servo
  int pos;
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  // Send JSON over serial
  serializeJson(doc, Serial);

  delay(1000);
}