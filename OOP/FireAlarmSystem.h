#pragma once
#define temp A0
#define buzzer 5

class FireAlarmSystem
{
    private:
       int sound = buzzer;
       float temperature;
    public:
       FireAlarmSystem();
       bool isThereFire();
       void makeAlarm();
       void noSound();
       void attention();
       void getTemperature();
};
