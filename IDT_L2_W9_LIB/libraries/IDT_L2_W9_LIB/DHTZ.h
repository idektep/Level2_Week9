#ifndef DHTZ_H
#define DHTZ_H

#include <DHT.h>

#define DHTPIN 23
#define DHTTYPE DHT22

class DHTZ
{
public:
    void DHTZInit();
    static long DHTZReadTemp();
    static long DHTZReadHumid();
    void DHTZAdjustAlarm(int temp_alarm);
    void DHTZAlarmCheck();
};
#endif
