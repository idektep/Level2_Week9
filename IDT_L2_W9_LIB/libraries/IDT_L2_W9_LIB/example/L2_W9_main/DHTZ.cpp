#include "DHTZ.h"
#include "BUZZER.h"
#include <Arduino.h>

long t,h;
int Temp_alarm_val = 35;
BUZZER buzzer_d;

DHT dht(DHTPIN, DHTTYPE);

void DHTZ::DHTZInit()
{
    dht.begin();
}

long DHTZ::DHTZReadTemp()
{
    long t = dht.readTemperature();
    // Serial.print("Temp :");
    // Serial.println(t);

    if (isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return 0;
    }
    
    return t;
}

long DHTZ::DHTZReadHumid()
{
    long h = dht.readHumidity();
    // Serial.print("Humi :");
    // Serial.println(h);

    if (isnan(h)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return 0;
    }

    return h;
}

void DHTZ::DHTZAdjustAlarm(int temp_alarm)
{
    Temp_alarm_val = temp_alarm;
}

void DHTZ::DHTZAlarmCheck()
{

    if (t >= Temp_alarm_val)
    {
        // buzzer_d.Alarm_Beep();
        delay(100);
    }
}