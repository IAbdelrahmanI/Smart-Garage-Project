#pragma once



class LightingSystem
{
    private:
       bool controlledOff = true;
       int sensor;
       int ldrmapping;
    public:
       LightingSystem();
       void turnLightsON();
       void turnLightsOFF();
       bool isItDark();
       void getLDRmapping();
       void controlLightsON();
       void controlLightsOFF();
       void forceLightsON();
       void forceLightsOFF();
};
