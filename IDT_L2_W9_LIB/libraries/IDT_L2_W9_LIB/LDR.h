#ifndef LDR_H
#define LDR_H

class LDR
{
    
public:

    void LdrInit();
    static int LdrMeasure();
    void LdrAdjustAlarm(int light_alarm);
    void LdrAlarmCheck();
    
};
#endif