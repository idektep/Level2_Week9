#include "LDR.h"
#include "LCD.h"    
#include <Arduino.h>

#define LDR_Pin 34

int Ldr_input = 0;
int light_alarm_val = 400;
float ldr;
LCD lcd_s;


void LDR::LdrInit()
{
    pinMode(LDR_Pin, INPUT);

}

int LDR::LdrMeasure()
{
    Ldr_input = analogRead(LDR_Pin);
    ldr = map(Ldr_input, 0, 4095, 0, 500);
    // Serial.print("Light :");
    // Serial.println(ldr);

    if (isnan(ldr)) {
      Serial.println(F("Failed to read from LDR sensor!"));
      return 0;
    }
    
    return ldr;
}

void LDR::LdrAdjustAlarm(int light_alarm)
{
    light_alarm_val = light_alarm;
}


void LDR::LdrAlarmCheck()
{
    if (ldr >= light_alarm_val)
    {
        lcd_s.LcdShowLight();
    }
    else
    {
        lcd_s.LcdNoLight();
    }
}

