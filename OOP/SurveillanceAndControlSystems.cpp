#include <notes.h>
#include <rtttl.h>
#include "pitches.h"
#include "SurveillanceAndControlSystems.h"
#include "FireAlarmSystem.h"
#include "LightingSystem.h"
#include "Arduino.h"
#include <Servo.h>


SurveillanceAndControlSystems::SurveillanceAndControlSystems()
{
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  
  motor.attach(11);
  motor.write(90);

  pinMode(a,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(E,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);

  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(LDR,INPUT);
  
  pinMode(temp,INPUT);
  pinMode(buzzer,OUTPUT);

  Serial.begin(9600);
  char *song = "TakeOnMe:d=4,o=4,b=160:8d5,8p,8b,8p,8p,8e5,8g#5,8g#5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8d5,8e5,8p,8d5,8p";
  Rtttl player;
  player.begin(buzzer);
  player.play(song, 0);
}






bool SurveillanceAndControlSystems::isCarEntering()
{
  int IRreading = digitalRead(IR1);
  if (IRreading == LOW)
  return true;
  else
  return false;
}


bool SurveillanceAndControlSystems::isCarExiting()
{
  int IRreading = digitalRead(IR2);
  if (IRreading == LOW)
  return true;
  else
  return false;
}

bool SurveillanceAndControlSystems::isThereAnyEmptySlot(short v)
{
  if (v > 0)
  return true;
  else
  return false;
}





void SurveillanceAndControlSystems::openGate()
{
  for (int i = 90; i >= 40; i-=5)
  {
    motor.write(i);
    delay(10);
  }
}


void SurveillanceAndControlSystems::closeGate()
{
  for (int i = 40; i <= 90; i+=5)
  {
    motor.write(i);
    delay(10);
  }
}


void SurveillanceAndControlSystems::keepGateOpen()    
    {
    for (int i = 1; i <= 27;i++) //27 came out imperically
      {  
      SurveillanceAndControlSystems control;  
      while (control.isCarEntering())
      continue;
      delay(25);
      while (control.isCarExiting())
      continue;
      delay(25);
      }
    }


void SurveillanceAndControlSystems::welcome()
{
  int melody[3] = {NOTE_C4, NOTE_G3, NOTE_G3};
  //NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
  int noteDurations[3] = {4, 8, 8};
  //4, 8, 8, 4, 4, 4, 4, 4
  for (int note = 0; note < 3; note++)
  {
    int noteDuration = 1000 / noteDurations[note];
    tone(buzzer, melody[note], noteDuration);

    int pauseBetweenNotes = 1.3 * noteDuration;
    delay(pauseBetweenNotes);

    noTone(buzzer);
  }
}

void SurveillanceAndControlSystems::controlTheSystem()
{
      LightingSystem lightSystem;

      char input = Serial.read();
      switch (input)
      {
        case 'l' : lightSystem.controlLightsON();break;
        case 'd' : lightSystem.controlLightsOFF();break;
        case 'o' : openGate();break;
        case 'c' : closeGate();break;
        case 'b' : tone(buzzer,1500,500);break;
        default : break;
      }
      Serial.print("Input: ");Serial.println(input);
}



void SurveillanceAndControlSystems::Print(short e)
{
  if (e == 0)
  {
    digitalWrite(a,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(E,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,LOW);
  }
  else if (e == 1)
  { digitalWrite(a,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(E,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
  }
  else if (e == 2)
  {
    digitalWrite(a,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,LOW);
    digitalWrite(d,HIGH);
    digitalWrite(E,HIGH);
    digitalWrite(f,LOW);
    digitalWrite(g,HIGH);
  }
  else if (e == 3)
  {
    digitalWrite(a,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(E,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,HIGH);
  }
  else if (e == 4)
  {
    digitalWrite(a,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(E,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  }
  else if (e == 5)
  {
    digitalWrite(a,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(C,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(E,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  }
  else if (e == 6)
  {
    digitalWrite(a,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(C,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(E,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  }
  else if (e == 7)
  {
    digitalWrite(a,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(E,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
  }
  else if (e == 8)
  {
    digitalWrite(a,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(E,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  }
  else if (e == 9)
  {
    digitalWrite(a,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(E,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  }
  else //All LEDs OFF
  {
    digitalWrite(a,LOW);
    digitalWrite(B,LOW);
    digitalWrite(C,LOW);
    digitalWrite(d,LOW);
    digitalWrite(E,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
  }
}
