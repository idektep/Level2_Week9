#ifndef BUZZER_H
#define BUZZER_H

class BUZZER
{
private:
    bool alarm_state = 0;
    unsigned long previousMillis_b = 0;

public:
    void BuzzerInit();
    void Beep(bool x);
    void Alarm_Beep();
};
#endif