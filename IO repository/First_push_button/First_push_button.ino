int LEDstate = 0;
int LEDpin = 11;
int buttonPin = 4;

int buttonNew;
int buttonOld = 1;


void setup()
{
  pinMode(LEDpin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  }

void loop()
{
  buttonNew = digitalRead(buttonPin);

  if (buttonOld == 0 & buttonNew == 1){
    if (LEDstate ==0){
      digitalWrite(LEDpin, HIGH);
      LEDstate = 1;
      }
    else{
      digitalWrite(LEDpin, LOW);
      LEDstate=0;
      }  
  }
  
  buttonOld = buttonNew;
}
