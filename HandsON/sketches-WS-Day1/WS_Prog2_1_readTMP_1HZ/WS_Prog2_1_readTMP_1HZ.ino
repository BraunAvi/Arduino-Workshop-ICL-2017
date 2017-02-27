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

const int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
float sensorVoltage; // variable to store the camculated volatge
float sensorTemp; // variable to store the camculated temperature
float aref_voltage=5000; // the default analog reference voltage of Arduino is ~5000mV 
unsigned long time; // variable to store the time in miliseconds
#define LOG_INTERVAL 1000 // how many ms between sensor readings (reduce to take more/faster data)

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600); // initiate a serial connection between PC and the Arduino board
  analogReference(DEFAULT);// set the analog reference to default value
}

void loop() {
  delay((LOG_INTERVAL) - (millis() % LOG_INTERVAL));
  
  Serial.print("Time: ");
  time = millis();
  //prints time since program started
  Serial.print(time);
  
  sensorValue = analogRead(sensorPin);    
  // print the read value:
  Serial.print("; Read Value:");
  Serial.print(sensorValue);
  
  sensorVoltage=sensorValue*(aref_voltage/1023);
  Serial.print(";  voltage[mV]:");
  Serial.print(sensorVoltage);
  
  float sensorTemp =25+(sensorVoltage-750)*0.1 ;//TMP36; 750mV@25C; dV/dT=+10mV/C; range:-40 to +125C
  Serial.print(";  Temperature[C]:");
  Serial.println(sensorTemp);
     
}
