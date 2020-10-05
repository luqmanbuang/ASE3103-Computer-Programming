int sensorPin = A0; // select the input pin for LDR
float sensorValue = 0; // variable to store the value coming from the sensor
int timer, i,n;
float maximum = 0, minimum = 1023, total, average, voltage;
float memory[10] = {5.00};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //sets serial port for communication  
}

void loop() {

  sensorValue = analogRead(sensorPin); // read the value from the sensor
  voltage = (sensorValue/1023)*5; 

  maximum = max(voltage,maximum);
  minimum = min(voltage, minimum);
  timer++;
  i++;

  memory[0] = voltage;
  for (i =8; i>-1; i--){
    memory[i+1] = memory[i];
    Serial.print("memory[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.println(memory[i]);
  }

  for(n = 0; n<10; n++){
    total += memory[n];
  }
  average = total / 10;

//  Serial.print("----------------\n");
//
//  Serial.print("Timer: ");
//  Serial.print(timer);
//  Serial.print("s\n\n");
//
//  Serial.print("Current Value: ");
//  Serial.println(voltage); //prints the values coming from the sensor on the screen
//  Serial.print("v");
//    
//  Serial.print("Maximum value: ");
//  Serial.print(maximum);
//  Serial.print("v");
//  
//  Serial.print("\nMinimum value: ");
//  Serial.print(minimum);
//  Serial.print("v");
//
//  Serial.print("\n\n10s average: ");
//  Serial.print(average);
//   Serial.print("v");
//
//  Serial.print("\n----------------\n\n");
  delay(1000);
  total = 0;

  

}
