#include "WARC.h"
#include "Motor.h"
#include "Sensors.h"
#include <Arduino_JSON.h>
#include "DHTZ.h"
#include "Ldr.h"
#include "Buzzer.h"
WARC warcInstance;
Sensors sensorsInstance;
JSONVar readings;


const char *WARC::getHtmlHomePage()
{
  const char *htmlHomePage = R"HTMLHOMEPAGE(
        
        <!DOCTYPE html>
        <html>
        <head>
            <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
            <style>
                .arrows {
                    font-size: 70px;
                    color: AliceBlue;
                }
        
                .circularArrows {
                    font-size: 80px;
                    color: Cornsilk;
                }
        
                td {
                    background-color: black;
                    border-radius: 35%;
                    box-shadow: 5px 5px #888888;
                }
        
                td:active {
                    transform: translate(5px, 5px);
                    box-shadow: none;
                }
        
                .noselect {
                    -webkit-touch-callout: none;
                    -webkit-user-select: none;
                    -khtml-user-select: none;
                    -moz-user-select: none;
                    -ms-user-select: none;
                    user-select: none;
                    touch-action: manipulation;
                }

                body {
                    font-family: Arial, sans-serif;
                    display: flex;
                    flex-direction: column;
                    align-items: center;
                    background-color: white;
                }

                .container {
                    display: flex;
                    justify-content: space-between;
                    width: 100%;
                    padding: 20px;
                }

                .temp, .humid, .light, .distance {
                    flex: 1;
                    text-align: center;
                }

                .distance, .temp {
                    text-align: left;
                }

                .light, .humid {
                    text-align: right;
                }
            </style>
        </head>
        
        <body class="noselect" align="center" style="background-color:white">
            <h1 style="color: teal;text-align:center;">AGV &#128663; Web Controller</h1>
            <h2 style="color: teal;text-align:center;">Wi-Fi &#128732; Mode</h2>
            <table id="mainTable" style="width:400px;margin:auto;table-layout:fixed" CELLSPACING=10>
                <tr>
                    <td ontouchstart='onTouchStartAndEnd("5")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows">&#11017;</span></td>
                    

                </tr>
                <tr>
                    <td ontouchstart='onTouchStartAndEnd("3")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows">&#8678;</span></td>
                    
                </tr>
                <tr>
                    <td ontouchstart='onTouchStartAndEnd("7")' ontouchend='onTouchStartAndEnd("0")'><span class="arrows">&#11019;</span></td>
                    
                </tr>
                <tr>
                    <td ontouchstart='onTouchStartAndEnd("9")' ontouchend='onTouchStartAndEnd("0")'><span class="circularArrows">&#8634;</span></td>
                    <td style="background-color:white;box-shadow:none">
                        <h2 style="color: DarkMagenta;text-align:center;">Via &#128640; IDektep</h2>
                    </td>
                    <td ontouchstart='onTouchStartAndEnd("10")' ontouchend='onTouchStartAndEnd("0")'><span class="circularArrows">&#8635;</span></td>
                </tr>
            </table>
            <div class="container">
                <div class="distance","temp">
                    <h2 style="color: DarkMagenta;text-align:center;">Distance: <span id="displayText"></span></h2>
                    <h2 style="color: DarkMagenta;text-align:center;">Temp: <span id="tempDisplayText">--</span>&deg;C</h2>
                </div>
                <div class="light","humid">
                    <h2 style="color: DarkMagenta;text-align:center;">Light: <span id="LightdisplayText"></span></h2>
                    <h2 style="color: DarkMagenta;text-align:center;">Humidity: <span id="humidDisplayText">--</span>%</h2> 
                </div>
            </div>          
            <script>
                // Get current sensor readings when the page loads  
                window.addEventListener('load', getReadings);
                window.addEventListener('load', getReadingsLight);
                window.addEventListener('load', getReadingsDHT);

                var webSocketUrl = "ws:\/\/" + window.location.hostname + "/ws";
                var websocket;
        
                function initWebSocket() {
                    websocket = new WebSocket(webSocketUrl);
                    websocket.onopen = function (event) { };
                    websocket.onclose = function (event) {setTimeout(initWebSocket, 2000);};
                    websocket.onmessage = function (event) { };
                }
        
                function onTouchStartAndEnd(value) {
                    websocket.send(value);
                }
        
                window.onload = initWebSocket;
                document.getElementById("mainTable").addEventListener("touchend", function (event) {
                    event.preventDefault()
                });
                
                function getReadings(){
                  var xhr = new XMLHttpRequest();
                  var textElement = document.getElementById('displayText');


                  xhr.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                      const myObj = JSON.parse(this.responseText);
                      textElement.textContent = myObj.distance;
                    }
                  }; 
                  xhr.open("GET", "/readings", true);
                  xhr.send();
                }
                setInterval(getReadings, 500);

                function getReadingsLight(){
                  var Lightxhr = new XMLHttpRequest();
                  var LighttextElement = document.getElementById('LightdisplayText');

                  Lightxhr.onreadystatechange = function(){
                    if (Lightxhr.readyState == 4 && Lightxhr.status == 200) {
                      const myLightObj = JSON.parse(Lightxhr.responseText);
                      LighttextElement.textContent = myLightObj.light;
                    }
                  };
                  Lightxhr.open("GET", "/Lightreadings", true);
                  Lightxhr.send();
                
                }
                setInterval(getReadingsLight, 1000);

                function getReadingsDHT(){
                  var xhr = new XMLHttpRequest();
                  var tempTextElement = document.getElementById('tempDisplayText');
                  var humidTextElement = document.getElementById('humidDisplayText')

                  xhr.onreadystatechange = function(){
                    if (this.readyState == 4 && this.status == 200) {
                      const myDHTObj = JSON.parse(this.responseText);
                      tempTextElement.textContent = myDHTObj.temp;
                      humidTextElement.textContent = myDHTObj.humid;
                    }
                  };
                  xhr.open("GET", "/DHTreadings", true);
                  xhr.send();
                  
                
                }
                setInterval(getReadingsDHT, 1000);
        
            </script>
        </body>    
        </html>
    )HTMLHOMEPAGE";
  return htmlHomePage;
}

void WARC::handleRoot(AsyncWebServerRequest *request)
{
  request->send_P(200, "text/html", warcInstance.getHtmlHomePage());
}

void WARC::handleReadSensor(AsyncWebServerRequest *request)
{
  long distance = Sensors::ultraGetDistance();
  String json = "{\"distance\":" + String(distance) + "}";
  request->send(200, "application/json", json);
}

void WARC::handleReadDHT(AsyncWebServerRequest *request)
{
  long temp =  DHTZ::DHTZReadTemp();
  long humid = DHTZ::DHTZReadHumid();
  String dht_json = "{\"temp\":" + String(temp) + ",\"humid\":" + String(humid) +"}" ;
  request->send(200, "application/json", dht_json);
}

void WARC::handleReadLight(AsyncWebServerRequest *request)
{
  int light =  LDR::LdrMeasure();
  String json_light = "{\"light\":" + String(light) + "}" ;
  request->send(200, "application/json", json_light);
}

void WARC::handleNotFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not Found");
}

void WARC::onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
  case WS_EVT_CONNECT:
    Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
    break;
  case WS_EVT_DISCONNECT:
    Serial.printf("WebSocket client #%u disconnected from %s\n", client->id(), client->remoteIP().toString().c_str());
    WARC::processCarMovement(0);
    break;
  case WS_EVT_DATA:
    AwsFrameInfo *info;
    info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
    {
      std::string myData = "";
      myData.assign((char *)data, len).c_str();
      Serial.println(atoi(myData.c_str()));
      WARC::processCarMovement(atoi(myData.c_str()));
    }
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  default:
    break;
  }
}

void WARC::processCarMovement(int inputValue) {
  switch (inputValue) {
    case UP:
      Motor::forward();
      break;
    case DOWN:
      Motor::backward();
      break;
    case LEFT:
      Motor::slide_left();
      break;
    case RIGHT:
      Motor::slide_right();
      break;
    case UP_LEFT:
      Motor::slide_left_front();
      break;
    case UP_RIGHT:
      Motor::slide_right_front();
      break;
    case DOWN_LEFT:
      Motor::slide_left_back();
      break;
    case DOWN_RIGHT:
      Motor::slide_right_back();
      break;
    case TURN_LEFT:
      Motor::turn_left();
      break;
    case TURN_RIGHT:
      Motor::turn_right();
      break;
    case STOP:
      Motor::stop();
      break;
    case ON_BUZZER:
      Motor::OnBuzzer();
      break;
    case OFF_BUZZER:
      Motor::OffBuzzer();
      break;
    default:
      Motor::stop();
      break;
  }
}

