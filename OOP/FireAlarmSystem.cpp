#include "FireAlarmSystem.h"
#include "LightingSystem.h"
#include "SurveillanceAndControlSystems.h"
#include "Arduino.h"

#define temp A0
#define buzzer 5

FireAlarmSystem::FireAlarmSystem()
{

}



bool FireAlarmSystem::isThereFire()
{
    float reading = analogRead(temp);
    float Temperature = reading * 5.0 / 1023;
    Temperature = Temperature / 0.01;
    temperature = Temperature;
    if (Temperature > 85)
    return true;
    else 
    return false;
}



void FireAlarmSystem::makeAlarm()
{
    LightingSystem objSystem;
    tone(buzzer,1000,500);
    objSystem.forceLightsON();
    delay(500);
    objSystem.forceLightsOFF();
    delay(500);
}

void FireAlarmSystem::noSound()
{
    digitalWrite(buzzer,LOW);
}



void FireAlarmSystem::attention()
{
    for (int i = 1; i <= 2; i++)
    {
     SurveillanceAndControlSystems printer;   
     printer.Print(10);//Which will get all LEDs OFF
     tone(sound,1500,500);
     delay(500);
     printer.Print(0);
     delay(500);
     }
}

void FireAlarmSystem::getTemperature()
{
  Serial.println(temperature);
}
