/*
  Analog Input
 Demonstrates analog input by reading an analog sensor (TMP36)on analog pin 0 
 the value obtained by analogRead(). 
 
 The circuit:
 * thermometer TMP 36 (pin 2 – center)  attached to analog input 0
 * thermometer TMP 36 (pin 3) to ground
 * thermometer TMP 36 (pin 1) to +5V
 
 Created by Avi Braun based on the analogread example by David Cuartielles
 This example code is in the public domain.
 */

const int sensorPin = A0;    // select the input pin for the thermometer
int sensorValue = 0;  // variable to store the value coming from the sensor
float sensorVoltage; // variable to store the camculated volatge
float sensorTemp; // variable to store the camculated temperature
float aref_voltage=5000; // the default analog reference voltage of Arduino is ~5000mV 
const int LEDPin=11; // // select the output pin for the LED
int ThresholdT=0;// the thresh hold temperature for activating the LED
char incomingByte;

void setup() {
  pinMode(LEDPin, OUTPUT);      // sets the digital pin as output
  Serial.begin(9600); // initiate a serial connection between PC and the Arduino board
  analogReference(DEFAULT);// set the analog reference to default value

}

void loop() {
 if (Serial.available() > 0) {   // something came across serial
    ThresholdT = 0;         // throw away previous integerValue
    while(1) {            // force into a loop until 'n' is received
      incomingByte = Serial.read();
      if (incomingByte == '\n') break;   // exit the while(1), we're done receiving
      if (incomingByte == -1) continue;  // if no characters are in the buffer read() returns -1
      ThresholdT *= 10;  // shift left 1 decimal place
      // convert ASCII to integer, add, and shift left 1 decimal place
      ThresholdT = ((incomingByte - 48) + ThresholdT);
    }
    Serial.println(ThresholdT);   // Do something with the value
  }
  
  
  Serial.print("Threshold:");
  Serial.print(ThresholdT);
 
  sensorValue = analogRead(sensorPin);
  
  // print the read value:
  Serial.print(" Read Value:");
  Serial.print(sensorValue);

  sensorVoltage=sensorValue*(aref_voltage/1023);
  Serial.print(";  voltage[mV]:");
  Serial.print(sensorVoltage);

  float sensorTemp =25+(sensorVoltage-750)*.1 ;//TMP36; 750mV@25C; dV/dT=+10mV/C; range:-40 to +125C
  Serial.print(";  Temperature[C]:");
  Serial.print(sensorTemp);

  if (sensorTemp>ThresholdT){
    digitalWrite(LEDPin,HIGH);
    Serial.println(" LED ON");

  }
  else{          
    digitalWrite(LEDPin,LOW);
    Serial.println(" LED OFF");
    
  }
  delay(1000);// wait one second

}


