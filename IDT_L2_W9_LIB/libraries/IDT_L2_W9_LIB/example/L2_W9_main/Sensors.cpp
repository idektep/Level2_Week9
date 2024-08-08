#include "Sensors.h"
#include "Motor.h"
#include <Arduino.h>

#define TrigPin 5
#define EchoPin 35

long duration, distance;

int colision_distance_v = 0;

void Sensors::ultraInit()
{
    pinMode(TrigPin, OUTPUT);
    pinMode(EchoPin, INPUT);
}

long Sensors::ultraMicrosecondsToCentimeters(long microseconds)
{
    return abs(microseconds / 29 / 2);
}

void Sensors::ultraAdjustDistance(int colision_distance)
{
    colision_distance_v = colision_distance;
}

void Sensors::ultraCheckDistance()
{
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    duration = pulseIn(EchoPin, HIGH);
    distance = ultraMicrosecondsToCentimeters(duration);
    Serial.print("distance :");
    Serial.println(distance);
    ultraCollisionCheck();
}

void Sensors::ultraCollisionCheck()
{
    if (distance <= colision_distance_v && distance > 0)
    {
        Motor::stop();
        Motor::ledBlink(40);
        delay(40);
        Motor::backward();
        delay(200);
        Motor::stop();
        Motor::ledBlink(40);
        delay(40);
    }
}

long Sensors::ultraGetDistance()
{
    return distance;
}
