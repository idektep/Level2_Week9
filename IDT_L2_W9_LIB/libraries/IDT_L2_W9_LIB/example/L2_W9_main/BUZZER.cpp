#include "BUZZER.h"
#include <Arduino.h>

#define Buzzer_Pin 18

void BUZZER::BuzzerInit()
{
    pinMode(Buzzer_Pin, OUTPUT);
    digitalWrite(Buzzer_Pin, LOW);
}

void BUZZER::Beep(bool x)
{
    if (x==1)
    {
        digitalWrite(Buzzer_Pin, HIGH);
        delay(500);
    }
    else
    {
        digitalWrite(Buzzer_Pin, LOW);
    }
}

void BUZZER::Alarm_Beep()
{
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis_b >= 500)
    {
        previousMillis_b = currentMillis;
        if (alarm_state == 0)
        {
            alarm_state = 1;
        }
        else
        {
            alarm_state = 0;
        }
        digitalWrite(Buzzer_Pin, alarm_state);
    }
}
