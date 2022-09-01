#include <rtttl.h>
#include <Servo.h>
#define IR1 2
#define IR2 3


#define a 9
#define b 8
#define c 4
#define d 6
#define e 7
#define f 10
#define g 12

#define led1 A1
#define led2 A2
#define led3 A3
#define led4 A4
#define LDR A5

#define temp A0
#define buzzer 5
//*********************************************************


Servo motor;

bool isCarDetected(int IR);

void motorUP(int from, int to);

void motorDOWN(int from, int to);

void keepGateOpen(int IRIn,int IROut);

void attention (int buzzing);

void lightsON_OFF (bool ON_OFF);

bool lightOff = true;

void Print (int vacant);

short vacant = 1;

void welcome();

//***********************************************************

void setup()
{
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  
  motor.attach(11);
  motor.write(90);

  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(e,OUTPUT);
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
  /*char *song = "TakeOnMe:d=4,o=4,b=160:8d5,8p,8b,8p,8p,8e5,8g#5,8g#5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8d5,8e5,8p,8d5,8p";
  Rtttl player;
  player.begin(buzzer);
  player.play(song, 0);*/
}

//*************************************************************

void loop() {
 
  
      //Remote Control System
      

    if (Serial.available())
    {
      char data = Serial.read();
      switch (data)
      {
        case 'l' : lightsON_OFF(1); lightOff = false; break;
        case 'd' : lightsON_OFF(0); lightOff = true; break;
        case 'o' : motorDOWN(90,40);break; //Open the gate
        case 'c' : motorUP(40,90);break; //Close the gate
        case 'b' : tone(buzzer,1500,500);break;
        default : break;
      }
      Serial.print("Input: ");Serial.println(data);
    }
    delay(10);



//**************************
  
  
     //Smart Gate System


    if (vacant == 0 && isCarDetected(IR1))
    attention(buzzer);
     
    bool going = false; bool gateOpen = false;
    if (isCarDetected(IR1) && vacant > 0)
      {motorDOWN(90,40);
       //welcome();
       vacant--;
       going = true;
       gateOpen = true;}
    else if (isCarDetected(IR2))
      {motorDOWN(90,40);
       vacant++;
       going = true;
       gateOpen = true;}
     
 
    Print(vacant);
     
    if (going)  
    keepGateOpen(IR1,IR2);
    if (gateOpen)
    motorUP(40,90);

//***************************

    
    
    //Fire Alarm System



    float reading = analogRead(temp);
    float Temperature = reading * 5.0 / 1023;
    Temperature = Temperature / 0.01;

    if (Temperature > 85)
    {
      tone(buzzer,1000,500);
      lightsON_OFF(1);
      delay(500);
      lightsON_OFF(0);
      delay(500);
    }
    else
    {
      digitalWrite(buzzer,LOW);
    }
    
//****************************


     //Smart Lighting System
     


     int ldrReading = analogRead(LDR);
     int ldrMaping = map(ldrReading,0,1023,0,255);
     if (ldrMaping > 90 && !lightOff)
     {lightsON_OFF(1); lightOff = true;}
     else if (ldrMaping <= 90 && lightOff)
     {lightsON_OFF(0); lightOff = false;}

//*************************


Serial.print("ldrMaping: ");Serial.println(ldrMaping);    
Serial.print("Vacant: ");Serial.println(vacant);
Serial.print("Temperature: ");Serial.println(Temperature);     
}

//**************************************************************



//Functions


bool isCarDetected(int IR)
{
  int IRreading = digitalRead(IR);
  if (IRreading == LOW)
  return true;
  else
  return false;
}



void motorUP(int from, int to)
{
  for (int i = from; i <= to; i+=5)
  {
    motor.write(i);
    delay(10);
  }
}



void motorDOWN(int from, int to)
{
  for (int i = from; i >= to; i-=5)
  {
    motor.write(i);
    delay(10);
  }
}



void keepGateOpen(int IRIn,int IROut)    
    {
    for (int i = 1; i <= 27;i++) //27 came out imperically
      {
      while (isCarDetected(IRIn))
      continue;
      delay(25);
      while (isCarDetected(IROut))
      continue;
      delay(25);
      }
    }

void welcome()
{
  int melody[3] = {262, 196, 196};
  int noteDurations[3] = {4, 8, 8};
  for (int note = 0; note < 3; note++)
  {
    int noteDuration = 1000 / noteDurations[note];
    tone(buzzer, melody[note], noteDuration);

    int pauseBetweenNotes = 1.3 * noteDuration;
    delay(pauseBetweenNotes);

    noTone(buzzer);
  }
}

void attention (int buzzing)
  {for (int i = 1; i <= 2; i++)
    {
     Print(10);//Which will get all LEDs OFF
     tone(buzzing,1500,500);
     delay(500);
     Print(0);
     delay(500);
     }
  } 



void lightsON_OFF (bool ON_OFF)
{
  if (ON_OFF == 1)
  {digitalWrite(led1,HIGH);
   digitalWrite(led2,HIGH);
   digitalWrite(led3,HIGH);
   digitalWrite(led4,HIGH);}
  else 
   {digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);}
}



void Print (int vacant)
{
  if (vacant == 0)
  {
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,LOW);
  }
  else if (vacant == 1)
  { digitalWrite(a,LOW);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
  }
  else if (vacant == 2)
  {
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,LOW);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,LOW);
    digitalWrite(g,HIGH);
  }
  else if (vacant == 3)
  {
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,HIGH);
  }
  else if (vacant == 4)
  {
    digitalWrite(a,LOW);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  }
  else if (vacant == 5)
  {
    digitalWrite(a,HIGH);
    digitalWrite(b,LOW);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  }
  else if (vacant == 6)
  {
    digitalWrite(a,HIGH);
    digitalWrite(b,LOW);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  }
  else if (vacant == 7)
  {
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
  }
  else if (vacant == 8)
  {
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  }
  else if (vacant == 9)
  {
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  }
  else //All LEDs OFF
  {
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
  }
}
