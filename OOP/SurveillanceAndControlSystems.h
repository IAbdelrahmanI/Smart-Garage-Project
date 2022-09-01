#pragma once
#include <Servo.h>
#include "FireAlarmSystem.h"
#include "LightingSystem.h"

#define IR1 2
#define IR2 3


#define a 9
#define B 8
#define C 4
#define d 6
#define E 7
#define f 10
#define g 12

#define led1 A1
#define led2 A2
#define led3 A3
#define led4 A4
#define LDR A5

#define temp A0
#define buzzer 5


class SurveillanceAndControlSystems
{
    private:
       Servo motor;
       short enter;
    public:
       SurveillanceAndControlSystems();
       bool isCarEntering();
       bool isCarExiting();
       bool isThereAnyEmptySlot(short v);
       void openGate();
       void closeGate();
       void keepGateOpen();
       void controlTheSystem();
       void Print(short e);
       void welcome();
};   
