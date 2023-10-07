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


const char *ssid = "POCO X3";
const char *password = "chamooda";

WebServer server(80);

const int led = 13; // unused
#define DHTPIN 14   // Pin connected to DHT sensor
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);

// MQ sensor settings
#define METHANE_SENSOR_AOUT 36  // Analog pin connected to MQ Methane sensor
#define CO_SENSOR_AOUT 35       // Analog pin connected to MQ Carbon Monoxide sensor
#define MQ_SENSOR_RL 10.0       // Load resistance value for MQ sensors

MQUnifiedsensor methaneSensor("MQ-4", METHANE_SENSOR_AOUT, MQ_SENSOR_RL, MQ4);
MQUnifiedsensor coSensor("MQ-7", CO_SENSOR_AOUT, MQ_SENSOR_RL, MQ7);


float Temperature = 0.0;
float Humidity = 0.0;
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
  HTML_page += " * {
            box-sizing: border-box;
            text-align: center;
            font-size: medium;
            font-weight: bold;
        }
        .App {
            display: flex;
            margin-top: 100px;
            border: 10px solid black;
            height: 80vh;
            align-items: center;
            justify-content: center;
            border-radius: 40px;
        }
        .Sensor {
            flex: 1;
            text-align: left;
            padding-left: 20px;
        }
        .Controls {
            flex: 1;
            display: flex;
            flex-direction: column;
            align-items: center;
            padding: 20px;
        }
        .button {
            all: unset;
            width: 100px;
            height: 30px;
            font-size: 16px;
            background: transparent;
            border: none;
            position: relative;
            color: #f0f0f0;
            cursor: pointer;
            z-index: 1;
            padding: 10px 20px;
            align-items: center;
            justify-content: center;
            white-space: nowrap;
            user-select: none;
            -webkit-user-select: none;
            touch-action: manipulation;
            margin: 10px;
        }
        .button::after,
        .button::before {
            content: '';
            position: absolute;
            bottom: 0;
            right: 0;
            z-index: -99999;
            transition: all .4s;
        }
        .button::before {
            transform: translate(0%, 0%);
            width: 100%;
            height: 100%;
            background: #28282d;
            border-radius: 10px;
        }
       .button::after {
            transform: translate(10px, 10px);
            width: 35px;
            height: 35px;
            background: #ffffff15;
            backdrop-filter: blur(5px);
            -webkit-backdrop-filter: blur(5px);
            border-radius: 50px;
        }
        .button:hover::before {
            transform: translate(5%, 20%);
            width: 110%;
            height: 110%;
        }
        .button:hover::after {
            border-radius: 10px;
            transform: translate(0, 0);
            width: 100%;
            height: 100%;
        }
        .button:active::after {
            transition: 0s;
            transform: translate(0, 5%);
        }
        h1 {
            color: #333333;
            font-family: 'Bitter', serif;
            font-size: 40px;
            font-weight: normal;
            line-height: 54px;
            margin: 0 0 14px;
        }
        .motor1, .motor2 {
            background-color: rgb(255, 255, 255);
            border: 2px solid black;
            border-radius: 10px;
            width: 600px;
            height: 370px;
            margin: 10px;
            padding: 10px;
            text-align: center;
        }
        #rangeValue1, #rangeValue2 {
            position: relative;
            display: block;
            text-align: center;
            font-size: 6em;
            color: #999;
            font-weight: 400;
        }
        .range {
            width: 400px;
            height: 15px;
            -webkit-appearance: none;
            background: #111;
            outline: none;
            border-radius: 15px;
            overflow: hidden;
            box-shadow: inset 0 0 5px rgba(0, 0, 0, 1);
        }
        .range::-webkit-slider-thumb {
            -webkit-appearance: none;
            width: 15px;
            height: 15px;
            border-radius: 50%;
            background: #1a2102;
            cursor: pointer;
            border: 4px solid #333;
            box-shadow: -407px 0 0 400px #9e03c4;
        }";
  HTML_page += "</style>\n";
  HTML_page += "</head>\n";
  HTML_page += "<body>\n";
  HTML_page += "<div class='App'>\n";
  HTML_page += "<div class='Sensor'>
            <div class='dht'>
                <h1>Temperature: " + String(Temperature) + "°C</h1>
                <h1>Humidity: "+ String(Humidity)+"%</h1>
            </div>
        <br/>
            <div class='MQ'>
                <h1>Methane Level: "+String(Methane)+"</h1>
                <h1>Carbon Monoxide: " +String(CarbonMonoxide)+"</h1>
            </div>
        </div>";
  HTML_page += "<div class = 'Controls">      
  HTML_page += "<div class='motor1'>\n";
  HTML_page += "<div class='Header'>\n";
  HTML_page += "<h1>MOTOR 1 CONTROLS</h1>\n";
  HTML_page += "<div>\n";
  HTML_page += "<span id='rangeValue1'>" + String(motor1Speed) + "</span>\n";
  HTML_page += "<input class='range' type='range' value='" + String(motor1Speed) + "' min='0' max='255' oninput='rangeSlide(this.value, \"rangeValue1\", \"do1\")'>\n";
  HTML_page += "<a class='button' id='do1' href='/speed?do1=" + String(motor1Speed) + "'>Speed</a>\n";
  HTML_page += "</div>\n";
  HTML_page += "</div>\n";
  HTML_page += "<div class='Footer'>\n";
  HTML_page += "<h1>Direction</h1>\n";
  HTML_page += "<a class='button' id='dir1' onclick='toggleDirection(\"dir1\")' href='/direction?dir=" + (motor1Direction == CW ? "m1CCW" : "m1CW") + "'>" + (motor1Direction == CW ? "Clockwise" : "Counter-Clockwise") + "</a>\n";
  HTML_page += "<a class='button' id='StartStop1' onclick='toggleStartStop(\"StartStop1\")' href='/stop?do=" + (motor1StopState == HIGH ? "m1Start" : "m1Stop") + "'>" + (motor1StopState == HIGH ? "Start" : "Stop") + "</a>\n";
  HTML_page += "</div>\n";
  HTML_page += "</div>\n";
  HTML_page += "<div class='motor2'>\n";
  HTML_page += "<div class='Header'>\n";
  HTML_page += "<h1>MOTOR 2 CONTROLS</h1>\n";
  HTML_page += "<div>\n";
  HTML_page += "<span id='rangeValue2'>" + String(motor2Speed) + "</span>\n";
  HTML_page += "<input class='range' type='range' value='" + String(motor2Speed) + "' min='0' max='255' oninput='rangeSlide(this.value, \"rangeValue2\", \"do2\")'>\n";
  HTML_page += "<a class='button' id='do2' href='/speed?do2=" + String(motor2Speed) + "'>Speed</a>\n";
  HTML_page += "</div>\n";
  HTML_page += "</div>\n";
  HTML_page += "<div class='Footer'>\n";
  HTML_page += "<h1>Direction</h1>\n";
  HTML_page += "<a class='button' id='dir2' onclick='toggleDirection(\"dir2\")' href='/direction?dir=" + (motor2Direction == CW ? "m2CCW" : "m2CW") + "'>" + (motor2Direction == CW ? "Clockwise" : "Counter-Clockwise") + "</a>\n";
  HTML_page += "<a class='button' id='StartStop2' onclick='toggleStartStop(\"StartStop2\")' href='/stop?do=" + (motor2StopState == HIGH ? "m2Start" : "m2Stop") + "'>" + (motor2StopState == HIGH ? "Start" : "Stop") + "</a>\n";
  HTML_page += "</div>\n";
  HTML_page += "</div>\n";
  HTML_page += "</div>\n";
  HTML_page += "</div>\n";
  HTML_page += "<script type='text/javascript'>\n";
  HTML_page += "function rangeSlide(value, id, linkId) {\n";
  HTML_page += "document.getElementById(id).textContent = value;\n";
  HTML_page += "var link = document.getElementById(linkId);\n";
  HTML_page += "link.href = '/speed?' + linkId + '=' + value;\n";
  HTML_page += "}\n";
  HTML_page += " function toggleDirection(buttonId) {
            var button = document.getElementById(buttonId);
            if (button.innerHTML === "Clockwise") {
                button.innerHTML = "Anti-Clockwise";
                if (buttonId === "dir1") {
                    button.setAttribute('href', '/direction?dir=m1CCW');
                } else if (buttonId === "dir2") {
                    button.setAttribute('href', '/direction?dir=m2CCW');
                }
            } else {
                button.innerHTML = "Clockwise";
                if (buttonId === "dir1") {
                    button.setAttribute('href', '/direction?dir=m1CW');
                } else if (buttonId === "dir2") {
                    button.setAttribute('href', '/direction?dir=m2CW');
                }
            }
        }
        function toggleStartStop(buttonId) {
            var button = document.getElementById(buttonId);
            if (button.innerHTML === "Start") {
                button.innerHTML = "Stop";
                if (buttonId === "StartStop1") {
                    button.setAttribute('href', '/stop?do=m1Stop');
                } else if (buttonId === "StartStop2") {
                    button.setAttribute('href', '/stop?do=m2Stop');
                }
            } else {
                button.innerHTML = "Start";
                if (buttonId === "StartStop1") {
                    button.setAttribute('href', '/stop?do=m1Start');
                } else if (buttonId === "StartStop2") {
                    button.setAttribute('href', '/stop?do=m2Start');
                }
            }
          }";
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
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read methane and carbon monoxide levels from MQ sensors
  float methaneLevel = methaneSensor.readSensor();
  float carbonMonoxide = coSensor.readSensor();

  // Update the sensor data variables
  Temperature = temperature;
  Humidity = humidity;
  Methane = methaneLevel;
  CarbonMonoxide = carbonMonoxide;
  delay(100);  
}
void handleMotorSpeed() {
    motor1Speed = server.arg("do1");
      if(motor1Speed < motor1MinimumSpeed){ motor1Speed = motor1MinimumSpeed; }
      if(motor1Speed > motor1MaximumSpeed){ motor1Speed =motor1MaximumSpeed; }
    
    motor2Speed =server.arg("do2");
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
 