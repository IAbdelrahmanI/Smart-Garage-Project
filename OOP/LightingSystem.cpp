#include "LightingSystem.h"
#include "Arduino.h"

#define led1 A1
#define led2 A2
#define led3 A3
#define led4 A4
#define LDR A5

LightingSystem::LightingSystem(): sensor(LDR)
{
  
}


void LightingSystem::turnLightsON()
{
    if (!controlledOff)
    {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    controlledOff = true;
    }
}

void LightingSystem::turnLightsOFF()
{
    if (controlledOff)
    {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    controlledOff = false;
    }
}


bool LightingSystem::isItDark()
{
    int ldrReading = analogRead(sensor);
    int ldrMapping = map(ldrReading,0,1023,0,255);
    ldrmapping = ldrMapping;
    if (ldrMapping > 90)
    return true;
    else
    return false;
}


void LightingSystem::getLDRmapping()
{
  Serial.println(ldrmapping);
}





void LightingSystem::controlLightsON()
{
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    controlledOff = false;
}
void LightingSystem::controlLightsOFF()
{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    controlledOff = true;
}

void LightingSystem::forceLightsON()
{
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    controlledOff = false;
}
void LightingSystem::forceLightsOFF()
{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    //no need to return "controlledOff" variable to true condtion again
}
