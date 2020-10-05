int LDRpin = A0; // select the input pin for LDR
int LDRvalue = 0; // variable to store the value coming from the sensor
int PTMpin = A1;
int PTMvalue = 0;
int PTMcount = 0, PTMtotal=0, PTMavg, PTMdisplay;

int timer = 0;

bool infinite = true;

void setup() {
  Serial.begin(9600);
}

void loop() {
  LDRvalue = analogRead(LDRpin);
  PTMvalue = analogRead(PTMpin);
  PTMtotal += PTMvalue;
  timer++;
  PTMcount++;

  if (PTMcount == 3){
    PTMavg = PTMtotal / 3;
    PTMdisplay = PTMavg;
    PTMcount = 1;
    PTMtotal = 0;
    PTMtotal += PTMvalue;
  }

  Serial.print("\n\nTimer: ");
  Serial.print(timer);
  Serial.println("s");

  Serial.print("LDR value: ");
  Serial.println(LDRvalue);
  Serial.print("Potentiometer value: ");
  Serial.println(PTMdisplay); 

  delay(1000);
  
}
