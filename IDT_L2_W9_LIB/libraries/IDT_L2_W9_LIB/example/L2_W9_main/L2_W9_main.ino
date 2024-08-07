// ####################################################################################
// ###################### IDEKTEP LEVEL 2 Source Code #################################
// ####################################################################################

#include <Arduino.h>
#include <WifiConfig.h>
#include <WARC.h>
#include <Motor.h>
#include <Sensors.h>
#include <BUZZER.h>
#include <LDR.h>
#include <LCD.h>
#include <DHTZ.h>


WifiConfig wifi;
WARC warc;
Motor motor_main;
Sensors ultra_main;
DHTZ dht_main;
BUZZER buzzer_main;
LDR ldr_main;
LCD lcd_main;

const char *ssid = "ESP32_AGV";
const char *password = "00000000";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void setup()
{
  // ##################################################################################
  // ############################# SERIAL INITTIALIZE #################################
  Serial.begin(115200);

  // ##################################################################################
  // ############################# WIFI INITTIALIZE ###################################
  wifi.wifiInit(ssid, password);

  // ##################################################################################
  // ############################# WEB SERVER INITTIALIZE #############################
  server.on("/", HTTP_GET, warc.handleRoot);
  server.on("/readings", HTTP_GET, warc.handleReadSensor);
  server.on("/Lightreadings", HTTP_GET, warc.handleReadLight);
  server.on("/DHTreadings", HTTP_GET, warc.handleReadDHT);
  server.onNotFound(warc.handleNotFound);
  server.addHandler(&ws);
  ws.onEvent(warc.onWebSocketEvent);
  server.begin();
  Serial.println("HTTP server started");

  // ##################################################################################
  // ############################# MOTOR INITTIALIZE ##################################
  motor_main.motorInit();
  motor_main.adjectMotorSpeed(255, 255, 255, 255); // Please adject value of motor_main speed in range 120-255 <------- EDIT ME
  

  // ##################################################################################
  // ############################# ULTRASONIC SENSOR INITTIALIZE ######################
  ultra_main.ultraInit();
  ultra_main.ultraAdjustDistance(5); // Please adject value of ultra_mainsonic distance to AdjustDistance <---------- EDIT ME


  // ##################################################################################
  // ############################# BUZZER INITTIALIZE #################################
  buzzer_main.BuzzerInit();

  // ##################################################################################
  // ############################# LDR INITTIALIZE ####################################
  ldr_main.LdrInit();
  ldr_main.LdrAdjustAlarm(400); // Please adject value of Ldr alarm to AdjustAlarm <---------- EDIT ME

  // ##################################################################################
  // ############################# DHT INITTIALIZE ####################################
  dht_main.DHTZInit();
  dht_main.DHTZAdjustAlarm(30); // Please adject value of Temparature alarm to AdjustAlarm <---------- EDIT ME

  // ##################################################################################
  // ###################### LIQUIDCRYSTAL DISPLAY INITTIALIZE #########################
  lcd_main.LcdInit();

}

void loop()
{
  ultra_main.ultraCheckDistance();
  ldr_main.LdrMeasure();
  ldr_main.LdrAlarmCheck();
  lcd_main.LcdDisplayDHT();
}