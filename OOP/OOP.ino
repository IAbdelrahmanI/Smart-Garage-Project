#include "FireAlarmSystem.h"
#include "LightingSystem.h"
#include "SurveillanceAndControlSystems.h"
#include <Servo.h>
//********************************************************

short vacant = 1;
FireAlarmSystem alarmSystem;
LightingSystem lightSystem;
SurveillanceAndControlSystems control;

//********************************************************
void setup()
{
}
//********************************************************
void loop() {
  
      //Remote Control System
      

    if (Serial.available())
    control.controlTheSystem();
    delay(10);


//**************************
  
     //Smart Gate System


    if (!control.isThereAnyEmptySlot(vacant) && control.isCarEntering())
    alarmSystem.attention();
     
    bool going = false; bool gateOpen = false;
    if (control.isCarEntering() && vacant > 0)
      {control.openGate(); control.welcome(); vacant--;going = true; gateOpen = true;}
      
    else if (control.isCarExiting())
      {control.openGate(); vacant++;going = true; gateOpen = true;}

    control.Print(vacant);
     
    if (going)  
    control.keepGateOpen();
    if (gateOpen)
    control.closeGate();

//****************************
      
    //Fire Alarm System


    if (alarmSystem.isThereFire())
    alarmSystem.makeAlarm();
    else
    alarmSystem.noSound();
    
//****************************

     //Smart Lighting System
     

    if (lightSystem.isItDark())
    lightSystem.turnLightsON();
    else
    lightSystem.turnLightsOFF();

//****************************


Serial.print("ldrMaping: ");
lightSystem.getLDRmapping();    
Serial.print("Vacant: ");Serial.println(vacant);
Serial.print("Temperature: ");
alarmSystem.getTemperature();
}
