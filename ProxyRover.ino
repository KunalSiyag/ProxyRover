#ifndef Robojax_L298N_DC_motor_H
#define Robojax_L298N_DC_motor_H
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <MQUnifiedsensor.h>
class Robojax_L298N_DC_motor
{
public:
    //Arduino board single motor
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA);
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, boolean debug);	
	//ESP32 single motor
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, int CHA);
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, int CHA, boolean debug);		
	//Arduino dual motor- ESP
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA,int IN3,int IN4,int ENB);	
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA,int IN3,int IN4,int ENB, boolean debug);	
	//ESP32 dual motor
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, int CHA, int IN3, int IN4,int ENB, int CHB);	
    Robojax_L298N_DC_motor(int IN1,int IN2,int ENA, int CHA, int IN3, int IN4,int ENB, int CHB, boolean debug);		
    void rotate(int motor, int value, int dir);
   void begin();
   void brake(int motor);
   void demo(int motor);
private:
   void printDebug1(int motor, int p1, int v1, int p2, int v2, int dir, int speed);
   void printDebug2(int motor1, int p1, int v1, int p2, int v2, int dir1, int speed1, int motor2, int p3, int v3, int p4, int v4, int dir2, int speed2) ;
   void printDebug3(int motor, int p1, int v1, int p2, int v2, int dir, int speed, int duty);
   void printDebug4(int motor1, int p1, int v1, int p2, int v2, int dir1, int speed1, int duty1, int motor2, int p3, int v3, int p4, int v4, int dir2, int speed2, int duty2) ;
   int _in1, _in2, _enA, _in3, _in4,  _enB, _pwmBit, _chA, _chB;
   boolean _debug = false;
   boolean _dual;
   int _resulotion =12;
   int _frequency = 5000;
   int _bits = pow(2,_resulotion);
   int toPWM(int v);   
};
#endif

// motor 1 settings
#define CHA 0
#define ENA 19 // this pin must be PWM enabled pin if Arduino board is used
#define IN1 18
#define IN2 5

// motor 2 settings
#define IN3 17
#define IN4 16
#define ENB 4// this pin must be PWM enabled pin if Arduino board is used
#define CHB 1
const int CCW = 2; // do not change
const int CW  = 1; // do not change
#define motor1 1 // do not change
#define motor2 2 // do not change
Robojax_L298N_DC_motor motor(IN1, IN2, ENA, CHA, IN3, IN4, ENB, CHB, true);

int       motor1Direction = CW;//default direction of rotation
int       motor1Speed = 40;// variable holding the light output vlaue (initial value) 40 means 40%
const int motor1MinimumSpeed=20;
const int motor1MaximumSpeed=100;
int       motor1StopState=HIGH;//Stope state of motor (HIGH means STOP) and LOW means Start

int       motor2Direction = CW;//default direction of rotation
int       motor2Speed = 60;// variable holding the light output vlaue (initial value) 40 means 40%
const int motor2MinimumSpeed=20;
const int motor2MaximumSpeed=100;
int       motor2StopState=HIGH;//Stope state of motor (HIGH means STOP) and LOW means Start


const char *ssid = "Skyguy";
const char *password = "TheForce";

WebServer server(80);

const int led = 13; // unused
// #define DHTPIN 14   // Pin connected to DHT sensor
// #define DHTTYPE DHT22  
// DHT dht(DHTPIN, DHTTYPE);

// MQ sensor settings
#define METHANE_SENSOR_AOUT 32  // Analog pin connected to MQ Methane sensor
#define CO_SENSOR_AOUT 34       // Analog pin connected to MQ Carbon Monoxide sensor
#define MQ_SENSOR_RL 10.0       // Load resistance value for MQ sensors

const int MQ4 = 4;
const int MQ7 = 7; 
MQUnifiedsensor methaneSensor("MQ-4", METHANE_SENSOR_AOUT, MQ_SENSOR_RL, MQ4);
MQUnifiedsensor coSensor("MQ-7", CO_SENSOR_AOUT, MQ_SENSOR_RL, MQ7);


// float Temperature = 0.0;
// float Humidity = 0.0;
float Methane = 0.0;
float CarbonMonoxide = 0.0;


void handleRoot() {
  String HTML_page = "<!DOCTYPE html>\n";
HTML_page += "<html lang='en'>\n";
HTML_page += "<head>\n";
HTML_page += "<meta charset='UTF-8'>\n";
HTML_page += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
HTML_page += "<title>Rover</title>\n";
HTML_page += "<style>\n";
HTML_page += " * {";
HTML_page += "box-sizing: border-box;";
HTML_page += "text-align: center;";
HTML_page += "font-size: medium;";
HTML_page += "font-weight: bold;";
HTML_page += "}";
HTML_page += ".App {";
HTML_page += "display: flex;";
HTML_page += "margin-top: 100px;";
HTML_page += "border: 10px solid black;";
HTML_page += "height: 80vh;";
HTML_page += "align-items: center;";
HTML_page += "justify-content: center;";
HTML_page += "border-radius: 40px;";
HTML_page += "}";
HTML_page += ".Sensor {";
HTML_page += "flex: 1;";
HTML_page += "text-align: left;";
HTML_page += "padding-left: 20px;";
HTML_page += "}";
HTML_page += ".Controls {";
HTML_page += "flex: 1;";
HTML_page += "display: flex;";
HTML_page += "flex-direction: column;";
HTML_page += "align-items: center;";
HTML_page += "padding: 20px;";
HTML_page += "}";
HTML_page += ".button {";
HTML_page += "all: unset;";
HTML_page += "width: 100px;";
HTML_page += "height: 30px;";
HTML_page += "font-size: 16px;";
HTML_page += "background: transparent;";
HTML_page += "border: none;";
HTML_page += "position: relative;";
HTML_page += "color: #f0f0f0;";
HTML_page += "cursor: pointer;";
HTML_page += "z-index: 1;";
HTML_page += "padding: 10px 20px;";
HTML_page += "align-items: center;";
HTML_page += "justify-content: center;";
HTML_page += "white-space: nowrap;";
HTML_page += "user-select: none;";
HTML_page += "-webkit-user-select: none;";
HTML_page += "touch-action: manipulation;";
HTML_page += "margin: 10px;";
HTML_page += "}";
HTML_page += ".button::after,";
HTML_page += ".button::before {";
HTML_page += "content: '';";
HTML_page += "position: absolute;";
HTML_page += "bottom: 0;";
HTML_page += "right: 0;";
HTML_page += "z-index: -99999;";
HTML_page += "transition: all .4s;";
HTML_page += "}";
HTML_page += ".button::before {";
HTML_page += "transform: translate(0%, 0%);";
HTML_page += "width: 100%;";
HTML_page += "height: 100%;";
HTML_page += "background: #28282d;";
HTML_page += "border-radius: 10px;";
HTML_page += "}";
HTML_page += ".button::after {";
HTML_page += "transform: translate(10px, 10px);";
HTML_page += "width: 35px;";
HTML_page += "height: 35px;";
HTML_page += "background: #ffffff15;";
HTML_page += "backdrop-filter: blur(5px);";
HTML_page += "-webkit-backdrop-filter: blur(5px);";
HTML_page += "border-radius: 50px;";
HTML_page += "}";
HTML_page += ".button:hover::before {";
HTML_page += "transform: translate(5%, 20%);";
HTML_page += "width: 110%;";
HTML_page += "height: 110%;";
HTML_page += "}";
HTML_page += ".button:hover::after {";
HTML_page += "border-radius: 10px;";
HTML_page += "transform: translate(0, 0);";
HTML_page += "width: 100%;";
HTML_page += "height: 100%;";
HTML_page += "}";
HTML_page += ".button:active::after {";
HTML_page += "transition: 0s;";
HTML_page += "transform: translate(0, 5%);";
HTML_page += "}";
HTML_page += "h1 {";
HTML_page += "color: #333333;";
HTML_page += "font-family: 'Bitter', serif;";
HTML_page += "font-size: 40px;";
HTML_page += "font-weight: normal;";
HTML_page += "line-height: 54px;";
HTML_page += "margin: 0 0 14px;";
HTML_page += "}";
HTML_page += ".motor1, .motor2 {";
HTML_page += "background-color: rgb(255, 255, 255);";
HTML_page += "border: 2px solid black;";
HTML_page += "border-radius: 10px;";
HTML_page += "width: 600px;";
HTML_page += "height: 370px;";
HTML_page += "margin: 10px;";
HTML_page += "padding: 10px;";
HTML_page += "text-align: center;";
HTML_page += "}";
HTML_page += ".rangeValue1, .rangeValue2 {";
HTML_page += "position: relative;";
HTML_page += "display: block;";
HTML_page += "text-align: center;";
HTML_page += "font-size: 6em;";
HTML_page += "color: #999;";
HTML_page += "font-weight: 400;";
HTML_page += "}";
HTML_page += ".range {";
HTML_page += "width: 400px;";
HTML_page += "height: 15px;";
HTML_page += "-webkit-appearance: none;";
HTML_page += "background: #111;";
HTML_page += "outline: none;";
HTML_page += "border-radius: 15px;";
HTML_page += "overflow: hidden;";
HTML_page += "box-shadow: inset 0 0 5px rgba(0, 0, 0, 1);";
HTML_page += "}";
HTML_page += ".range::-webkit-slider-thumb {";
HTML_page += "-webkit-appearance: none;";
HTML_page += "width: 15px;";
HTML_page += "height: 15px;";
HTML_page += "border-radius: 50%;";
HTML_page += "background: #1a2102;";
HTML_page += "cursor: pointer;";
HTML_page += "border: 4px solid #333;";
HTML_page += "box-shadow: -407px 0 0 400px #9e03c4;";
HTML_page += "}";
HTML_page += "</style>\n";
HTML_page += "</head>\n";
HTML_page += "<body>\n";
HTML_page += "<div class='App'>\n";
HTML_page += "<div class='Sensor'>\n";
// HTML_page += "<div class='dht'>\n";
// // HTML_page += "<h1>Temperature: " + String(Temperature) + "°C</h1>\n";
// // HTML_page += "<h1>Humidity: " + String(Humidity) + "%</h1>\n";
// HTML_page += "</div>\n";
// HTML_page += "<br/>\n";
HTML_page += "<div class='MQ'>\n";
HTML_page += "<h1>Methane Level: " + String(Methane) + " ppm</h1>\n";
HTML_page += "<h1>Carbon Monoxide: " + String(CarbonMonoxide) + " ppm</h1>\n";
HTML_page += "</div>\n";
HTML_page += "</div>\n";
HTML_page += "<div class='Controls'>\n";
HTML_page += "<div class='motor1'>\n";
HTML_page += "<div class='Header'>\n";
HTML_page += "<h1>MOTOR 1 CONTROLS</h1>\n";
HTML_page += "<div>\n";
HTML_page += "<span class='rangeValue1'>" + String(motor1Speed) + "</span>\n";
HTML_page += "<input class='range' type='range' value='" + String(motor1Speed) + "' min='0' max='255' oninput='rangeSlide(this.value, \"rangeValue1\", \"do1\")'>\n";
HTML_page += "<a class='button' id='do1' href='/speed?do1=" + String(motor1Speed) + "'>Speed</a>\n";
HTML_page += "</div>\n";
HTML_page += "</div>\n";
HTML_page += "<div class='Footer'>\n";
HTML_page += "<h1>Direction</h1>\n";
HTML_page += "<a class='button' id='dir1CW' href='/direction?dir=m1CW'>Clockwise</a>";
HTML_page += "<a class='button' id='dir1CCW' href='/direction?dir=m1CCW'>Anti-Clockwise</a>";
HTML_page += "<a class='button' id='StartStop1Start' href='/stop?do=m1Start'>Start</a>";
HTML_page += "<a class='button' id='StartStop1Stop' href='/stop?do=m1Stop'>Stop</a>";
HTML_page += "</div>\n";
HTML_page += "</div>\n";
HTML_page += "<div class='motor2'>\n";
HTML_page += "<div class='Header'>\n";
HTML_page += "<h1>MOTOR 2 CONTROLS</h1>\n";
HTML_page += "<div>\n";
HTML_page += "<span class='rangeValue2'>" + String(motor2Speed) + "</span>\n";
HTML_page += "<input class='range' type='range' value='" + String(motor2Speed) + "' min='0' max='255' oninput='rangeSlide(this.value, \"rangeValue2\", \"do2\")'>\n";
HTML_page += "<a class='button' id='do2' href='/speed?do2=" + String(motor2Speed) + "'>Speed</a>\n";
HTML_page += "</div>\n";
HTML_page += "</div>\n";
HTML_page += "<div class='Footer'>\n";
HTML_page += "<h1>Direction</h1>\n";
HTML_page += "<a class='button' id='dir2CW' href='/direction?dir=m2CW'>Clockwise</a>";
HTML_page += "<a class='button' id='dir2CCW' href='/direction?dir=m2CCW'>Anti-Clockwise</a>";
HTML_page += "<a class='button' id='StartStop2Start' href='/stop?do=m2Start'>Start</a>";
HTML_page += "<a class='button' id='StartStop2Stop' href='/stop?do=m2Stop'>Stop</a>";
HTML_page += "</a>\n";
HTML_page += "</div>\n";
HTML_page += "</div>\n";
HTML_page += "</div>\n";
HTML_page += "</div>\n";
HTML_page += "</div>\n";
HTML_page += "<script type='text/javascript'>\n";
HTML_page += "function rangeSlide(value, id, linkId) {\n";
HTML_page += "document.getElementsByClassname(id)[0].textContent = value;\n";
HTML_page += "var link = document.getElementsByClassName(linkId)[0];\n";
HTML_page += "link.href = '/speed?' + linkId + '=' + value;\n";
HTML_page += "}\n";
HTML_page += "</script>\n";
HTML_page += "</body>\n";
HTML_page += "</html>\n";


  server.send(200, "text/html", HTML_page);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found";
  message += "URI: ";
  message += server.uri();
  message += "Method: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "Arguments: ";
  message += server.args();
  message += "";

  for (uint8_t i = 0; i < server.args(); i++) 
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "";
  }

  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  Serial.begin(115200);
  motor.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  if (MDNS.begin("robojaxESP32")) {
    Serial.print("MDNS responder started at http://");
    Serial.println("robojaxESP32");
  }

  server.on("/", handleRoot);
  server.on("/speed", HTTP_GET, handleMotorSpeed);  
  server.on("/direction", HTTP_GET, handleMotorDirection); 
  server.on("/stop", HTTP_GET, handleMotorBrake);     
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started"); 
}

void loop(void) {
  server.handleClient();


  if(motor1StopState ==HIGH)
  {
    motor.brake(motor1);  
    
  }else{
     motor.rotate(motor1, motor1Speed, motor1Direction);//run motor1 at motor1Speed% speed in motor1Direction 
  }
  
  if(motor2StopState ==HIGH)
  {
    motor.brake(motor2);  
    
  }else{
     motor.rotate(motor2, motor2Speed, motor2Direction);//run motor2 at motor2Speed% speed in motor2Direction 
  }
  // float temperature = dht.readTemperature();
  // float humidity = dht.readHumidity();

  // Read methane and carbon monoxide levels from MQ sensors
  float methaneLevel = methaneSensor.readSensor();
  float carbonMonoxide = coSensor.readSensor();

  // Update the sensor data variables
  // Temperature = temperature;
  // Humidity = humidity;
  Methane = methaneLevel;
  CarbonMonoxide = carbonMonoxide;
  delay(100);  
}
void handleMotorSpeed() {
    motor1Speed = server.arg("do1").toInt();
      if(motor1Speed < motor1MinimumSpeed){ motor1Speed = motor1MinimumSpeed; }
      if(motor1Speed > motor1MaximumSpeed){ motor1Speed =motor1MaximumSpeed; }
    
    motor2Speed =server.arg("do2").toInt();
      if(motor2Speed < motor2MinimumSpeed){ motor2Speed = motor2MinimumSpeed; }
      if(motor2Speed > motor2MaximumSpeed){ motor2Speed =motor2MaximumSpeed; } 

  handleRoot();
}


void handleMotorDirection() {
  if(server.arg("dir") == "m1CW")
  {
    motor1Direction = CW;

  }else if(server.arg("dir") == "m1CCW")
  {
    motor1Direction =CCW;

  }else if(server.arg("dir") == "m2CW")
  {
    motor2Direction =CW;

  }else{
    motor2Direction =CCW;   

  }

  handleRoot();
}

void handleMotorBrake() {
  if(server.arg("do") == "m1Start")
  {  
      motor1StopState=LOW;
  }else if(server.arg("do") == "m1Stop")
  {  
      motor1StopState=HIGH;
  }else if(server.arg("do") == "m2Start")
  {  
      motor2StopState=LOW;
  }else{
      motor2StopState=HIGH;    
  }
  handleRoot();
}
 