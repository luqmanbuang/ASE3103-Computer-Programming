/* LDR related variables */
int ldrPin = A5; // LDR digital input pin
float ldrValue = 0; // variable to store the value coming from the sensor
int timer;
float memory[5] = {}; // initialize array, stored as a global variable
float ldrAverage(int); // prototype function

/* 7seg related variables */
int g = 9, f = 10, a = 11, b = 12, e = 5, d = 6, c = 7, dp = 8;
int q;
void display(int); // prototype function

/* LED and button related variables */
int ledPin = 2; // led digital input pin
int buttonPin = 4; // button digital input pin
int buttonNew;
int buttonOld = 1;
bool ledState = false;

/* Potentiometer and buzzer related variables */
int buzzerPin = 3; // buzzer digital input pin
int potPin = A0; // potentiometer digital input pin

int buzzerFreq = 1000;

/*Variables used to calculate time intervals replacing delay() by using millis() function*/
unsigned long currentMillis = 0;
unsigned long blinkMillis = 0;
unsigned long sirenMillis = 0;
unsigned long slwMillis = 0;

/*Prototype functions of outputs requiting time intervals*/ 
void blink(bool, int); // prototype function
void siren(int); // prototype function
void serialLockdownWarning(int); // prototype function

void setup() {
  Serial.begin(9600); //sets serial port for communication

  /*Declare pins used for the 7sed display*/
  pinMode(g, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(dp, OUTPUT);

  /*Declare pins used for the LED*/
  pinMode(ledPin, OUTPUT);

  /*Declare pins used for the button*/
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);


}

void loop() {
  /*Feature one: Reads the ldr value and displays the value on the serial monitor*/
  serialOutput(ldrPin);

  /*Feature two: Risplay the average readings onto the 7seg display*/
  display(9);
  delay(1000);

  /*Feature three: If the average value is less than 3 volts, it will go into countdown mode*/
  if (ldrValue < 3.0 && timer > 4) {
    /*Counts down from 5 to 0, during countdown, the voltage average is still monitored every second*/
    for (q = 9; q > 0; q--) {
      display(q); // displays the 5 second countdown
      blink(false, 1000);
      Serial.print("WARNING, COUNTDOWN ACTIVATED! ");
      Serial.print(q);
      Serial.println("s LEFT UNTIL SYSTEM LOCKDOWN");
      serialOutput(ldrPin);
      delay(1000);
      /*If voltage average increases above 3.0v, the system exits countdown mode*/
      if (ldrValue > 3.0) {
        Serial.println("COUNTDOWN MODE EXITED");
        goto recover; // goto command is used to redirect to the end of the loop
      }
    }
    /*Feature four: If voltage average continues below 3.0v after 5 second countdown, goes into lockdown mode. Voltage average is still monitored every second.
      Lockdown mode is an infinite loop, breaks when voltage average is more than 3.0v and reset button is pushed*/

    /*starts real-time counter*/
    StartMillis = millis();
    blinkMillis = millis();
    sirenMillis = millis();
    slwMillis = millis();
    while (true) {
      currentMillis = millis(); //starts realtime count of while loop

      serialLockdownWarning(1000);
      siren(250);
      blink(true, 250);

      /*Condition to exit lockdown mode: Average voltage more than 3.0v and reset button is pressed */
      buttonNew = digitalRead(buttonPin);
      if (buttonOld == 0 && buttonNew == 1 && ldrAverage(ldrPin) > 3.0 ) {
        digitalWrite(ledPin, LOW); //resets red LED (warning light)
        noTone(buzzerPin); // silents the buzzer        
        Serial.print("\n");
        goto recover; // goto command is used to redirect to the end of the loop
      }
      buttonOld = buttonNew;
    }
  }
recover:; // goto recover; command is redirected here to the end of the loop
}

/*VVVVVV Functions Below VVVVVV*/

// ldrAverage(): function which return the 5 second average of the ldr voltage
float ldrAverage(int pin) {
  float Total, Average, Value, Voltage;
  int i, n; 
  
  float potVAL = (analogRead(A0) / 1023.0) * 5.0; // reads the Voltage input from the potentiometer. This reading is used to add artificial values into LDR reading. 
  
  Value = analogRead(pin); // reads the value from the LDR sensor
  Voltage = ( (Value / 1023) * 5 ) + int(potVAL) ; // converts LDR analog data into voltage, plus potentiometer reading. U
  
  //Serial.println(int(potVAL));
  Serial.print("Current voltage: ");
  Serial.print(Voltage);
  Serial.println("v");

  /*The voltage is stored into a 5-second memory */
  memory[0] = Voltage; //In each iteration the voltage is stored in the first array (memory[0])
  for (i = 3; i > -1; i--) {
    memory[i + 1] = memory[i]; //The oldest memory is replaced, and the memory is cascaded backwards
  }

  Total = 0; // resets Total so that it can recompute everytime function is called
  for (n = 0; n < 5; n++) {
    Total += memory[n]; //computes the sum of the voltages in the memory array
    //    Serial.print("memory[");
    //    Serial.print(n);
    //    Serial.print("]: ");
    //    Serial.println(memory[n]);
  }
  return Average = Total / 5.0; // returns the 5 sec voltage average
}

// display(): Function outputs single digit argument to the 7seg display
void display(int num = -1) {
  if (num == 0){
    digitalWrite(g, 0);
    digitalWrite(f, 1);
    digitalWrite(a, 1);
    digitalWrite(b, 1);
    digitalWrite(e, 1);
    digitalWrite(d, 1);
    digitalWrite(c, 1);
  } else if (num == 1) {
    digitalWrite(g, 0);
    digitalWrite(f, 1);
    digitalWrite(a, 0);
    digitalWrite(b, 0);
    digitalWrite(e, 1);
    digitalWrite(d, 0);
    digitalWrite(c, 0);
  } else if (num == 2) {
    digitalWrite(g, 1);
    digitalWrite(f, 0);
    digitalWrite(a, 1);
    digitalWrite(b, 1);
    digitalWrite(e, 1);
    digitalWrite(d, 1);
    digitalWrite(c, 0);
  } else if (num == 3) {
    digitalWrite(g, 1);
    digitalWrite(f, 0);
    digitalWrite(a, 1);
    digitalWrite(b, 1);
    digitalWrite(e, 0);
    digitalWrite(d, 1);
    digitalWrite(c, 1);
  } else if (num == 4) {
    digitalWrite(g, 1);
    digitalWrite(f, 1);
    digitalWrite(a, 0);
    digitalWrite(b, 1);
    digitalWrite(e, 0);
    digitalWrite(d, 0);
    digitalWrite(c, 1);
  } else if (num == 5) {
    digitalWrite(g, 1);
    digitalWrite(f, 1);
    digitalWrite(a, 1);
    digitalWrite(b, 0);
    digitalWrite(e, 0);
    digitalWrite(d, 1);
    digitalWrite(c, 1);
  } else if (num == 6) {
    digitalWrite(g, 1);
    digitalWrite(f, 1);
    digitalWrite(a, 1);
    digitalWrite(b, 0);
    digitalWrite(e, 1);
    digitalWrite(d, 1);
    digitalWrite(c, 1);
  } else if (num == 7) {
    digitalWrite(g, 0);
    digitalWrite(f, 0);
    digitalWrite(a, 1);
    digitalWrite(b, 1);
    digitalWrite(e, 0);
    digitalWrite(d, 0);
    digitalWrite(c, 1);
  } else if (num == 8) {
    digitalWrite(g, 1);
    digitalWrite(f, 1);
    digitalWrite(a, 1);
    digitalWrite(b, 1);
    digitalWrite(e, 1);
    digitalWrite(d, 1);
    digitalWrite(c, 1);
  } else if (num == 9) {
    digitalWrite(g, 1);
    digitalWrite(f, 1);
    digitalWrite(a, 1);
    digitalWrite(b, 1);
    digitalWrite(e, 0);
    digitalWrite(d, 0);
    digitalWrite(c, 1);
  } else {
    digitalWrite(g, 0);
    digitalWrite(f, 1);
    digitalWrite(a, 0);
    digitalWrite(b, 0);
    digitalWrite(e, 1);
    digitalWrite(d, 1);
    digitalWrite(c, 0);
  }
}

//serialOutput(int): This function reduces code repetition in the loop.
float serialOutput(int z) {
  timer++; // counts the time in seconds
  Serial.print("Timer: ");
  Serial.print(timer);
  Serial.println("s");

  /*Feature one: reads the ldr value and displays the value on the serial monitor*/
  ldrValue = ldrAverage(z); //calls ldrAverage() function and stores it into a variable called ldrValue
  Serial.print("5 sec average: ");
  Serial.print(ldrValue);
  Serial.println("v\n");
  return ldrValue; // ldrValue is returned
}

void siren(int timer = 1000) {
  if (currentMillis - sirenMillis >= timer) {
    if (buzzerFreq == 1000) {
      buzzerFreq = 2000;
    }
    else {
      buzzerFreq = 1000;
    }
    tone(buzzerPin, buzzerFreq);
    sirenMillis = currentMillis;
  }
}

void blink(boolean follow = false, int timer = 1000) {
  if (follow) {
    if (currentMillis - blinkMillis >= timer) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);  //Change the state of the LED
      blinkMillis = currentMillis;
    }
  }
  else {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);  //Change the state of the LED
  }
}

void serialLockdownWarning(int timer = 1000 ) {
  if (currentMillis - slwMillis >= timer) {
    display(-1); //Displays 'L' signifying system is in lockdown mode
    Serial.println("WARNING, SYSTEM LOCKDOWN ACTIVATED!\nTO RESET: ENSURE PROPER LIGHTING AND PRESS RESET BUTTON");
    serialOutput(ldrPin);
    slwMillis = currentMillis;
  }
}
