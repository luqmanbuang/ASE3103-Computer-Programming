#include <Servo.h>

int gateState = 0;
int servoPin = 2;
int buttonPin = 3;

int buttonNew;
int buttonOld = 1;

Servo servo;void setup() {
  servo.attach(servoPin);
  servo.write(0); // initialize the angle as 0 degrees

  pinMode(3, INPUT);
  pinMode(3, INPUT_PULLUP);
  
  Serial.begin(9600);
  delay(2000); // give 2 second delay after setup

}

void loop()
{
  buttonNew = digitalRead(buttonPin);

  if (buttonOld == 0 & buttonNew == 1){
    if (gateState == 0){
      servo.write(90);
      gateState = 90;
      }
    else{
      servo.write(0);
      gateState = 0;
      }
  }
  if (gateState == 0){
    Serial.println("Gate is closed");
  }
  else{
    Serial.println("Gate is open");
  }
  buttonOld = buttonNew;
}
