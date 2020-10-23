int ledPin = 13;
char input;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.read();
    Serial.print(input);
    
    // single quotes '' are for char, double quotes are for str ""
    if (input == '1') {
      digitalWrite(ledPin, HIGH);
    }
    else if (input == '0') {
      digitalWrite(ledPin, LOW);
    }
  }
}
