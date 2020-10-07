#include <Servo.h>
Servo myservo;  // create servo object to control a servo

#include "pitches.h"

#define buzzer 12
#define pot A1

const int a = 2;  //For displaying segment "a"
const int b = 3;  //For displaying segment "b"
const int c = 4;  //For displaying segment "c"
const int d = 5;  //For displaying segment "d"
const int e = 6;  //For displaying segment "e"
const int f = 7;  //For displaying segment "f"
const int g = 8;  //For displaying segment "g"

bool bPress = false;
const int IncbuttonPin = 9;
const int DecbuttonPin = 10;

// Changing of variables:
int buttonPushCounter = 0;      // counter for the number of button presses
int IncbuttonState = 0;         // current state of the button
int lastIncbuttonState = 0;     // previous state of the button
int DecbuttonState = 0;         // current state of the button
int lastDecbuttonState = 0;     // previous state of the button

//notes in the melody:
int melody[] = 
{
  NOTE_D5, NOTE_CS5, NOTE_B4, NOTE_FS4,
  NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_G4,
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_CS5, NOTE_D5, NOTE_A4,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_CS4,
  0,  
  NOTE_D5, NOTE_CS5, NOTE_B4, NOTE_FS4,
  NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_G4,
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_CS5, NOTE_D5, NOTE_A4,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_CS4, 
};

// note durations: 4 = quarter note, 8 = eighth note, etc
int noteDurations[] = 
{
  2, 2, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 2,
  8,
  2, 2, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 2,  
};


int value; //buzzer
int frequency; //buzzer

int angle = 90;    // initial angle  for servo
int angleStep = 5;


void setup() 
{
  // put your setup code here, to run once:
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G

  pinMode(IncbuttonPin, INPUT_PULLUP );
  pinMode(DecbuttonPin, INPUT_PULLUP );
  Serial.begin(9600);
  
  displayDigit(buttonPushCounter);


  Serial.begin(9600); //setup serial
  myservo.attach(11);  //attaches the servo on pin 11 to the servo object
  pinMode(13,INPUT_PULLUP);
  Serial.println("Dhanie's Assignment (LED, Buzzer, Servo) ");
}

void loop() 
{
   IncbuttonState = digitalRead(IncbuttonPin);
   DecbuttonState = digitalRead(DecbuttonPin);

   checkIncButtonPress();
   checkDecButtonPress();
  
  if( bPress )
  {  bPress = false;
     turnOff();
     displayDigit(buttonPushCounter);
  }

   /*
  for(int i=0;i<10;i++)
 {
   displayDigit(i);
   delay(1000);
   turnOff();
 }
 */
    while(digitalRead(13) == LOW)
    { angle = angle + angleStep;  //change the angle for next time through the loop

    if (angle <= 0 || angle >= 180) 
    { 
      angleStep = -angleStep;  //reverse the direction of the moving at the ends of the angle }
    }
      
    myservo.write(angle); //moving the servo to the desired angle
    Serial.print("Moved to: ");
    Serial.print(angle);   // print the angle
    Serial.println(" degrees");    
    delay(100); // waits for the servo to get there
    }

  
    value = analogRead(pot);
    frequency = map(value, 0, 1023, 30, 900);
    tone(buzzer, frequency);

    pinMode (buzzer, OUTPUT); //buzzer
    pinMode (pot, INPUT); //buzzer
    for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) 
    {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(12, melody[thisNote],noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(12); //stop the tone playing:
    }
  
}

void checkIncButtonPress()
{
   // comparing the IncbuttonState to its previous state
  if (IncbuttonState != lastIncbuttonState) 
  {
    // if the state has changed, increment the counter
    if (IncbuttonState == LOW) 
      {
      // if the current state is HIGH then the button went from off to on:
      bPress = true;
      buttonPushCounter++;
      if( buttonPushCounter > 9) buttonPushCounter =0 ;
      Serial.println("Number increased!");
      } 
      
      else 
        {
          // if the current state is LOW then the button went from on to off:
          // Serial.println("Number remained.");
        }
         // Delay a little bit to avoid bouncing
          delay(50);
  }
  //save the current state as the last state, for next time through the loop
  lastIncbuttonState = IncbuttonState;

}
void checkDecButtonPress()
{
   // compare the IncbuttonState to its previous state
  if (DecbuttonState != lastDecbuttonState) 
  {
    // if the state has changed, increment the counter
    if (DecbuttonState == LOW) 
      {
      // if the current state is HIGH then the button went from off to on:
      bPress = true;
      buttonPushCounter--;
      if( buttonPushCounter < 0) buttonPushCounter =9 ;
      Serial.println("Number decreased!");
      } 
   
      else 
      {
      // if the current state is LOW then the button went from on to off:
     // Serial.println("Number remained.");
      }
      // Delay a little bit to avoid bouncing
      delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastDecbuttonState = DecbuttonState;

}  

void displayDigit(int digit)
{
 // To display segment a,
 if(digit!=1 && digit != 4)
 digitalWrite(a,HIGH);

 // To display segment b,
 if(digit != 5 && digit != 6)
 digitalWrite(b,HIGH);

 // To display segment c,
 if(digit !=2)
 digitalWrite(c,HIGH);

 // To display segment d,
 if(digit != 1 && digit !=4 && digit !=7)
 digitalWrite(d,HIGH);

 // To display segment e, 
 if(digit == 2 || digit ==6 || digit == 8 || digit==0)
 digitalWrite(e,HIGH);

 // To display segment f,
 if(digit != 1 && digit !=2 && digit!=3 && digit !=7)
 digitalWrite(f,HIGH);

 // To display segment g,
 if (digit!=0 && digit!=1 && digit !=7)
 digitalWrite(g,HIGH);

}
void turnOff()
{
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
  digitalWrite(e,LOW);
  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
}
