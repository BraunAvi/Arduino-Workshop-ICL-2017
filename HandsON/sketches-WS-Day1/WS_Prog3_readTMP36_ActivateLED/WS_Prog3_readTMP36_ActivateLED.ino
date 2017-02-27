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
float sensorVoltage; // variable to store the calculated volatge
float sensorTemp; // variable to store the calculated temperature
float aref_voltage=5000; // the default analog reference voltage of Arduino is ~5000mV 
const int LEDPin=11; // // select the output pin for the LED (if used)
void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(LEDPin, OUTPUT);      // sets the digital pin as output
  Serial.begin(9600); // initiate a serial connection between PC and the Arduino board
  analogReference(DEFAULT);// set the analog reference to default value
}

void loop() {
  sensorValue = analogRead(sensorPin);    
  // print the read value:
  Serial.print("Read Value:");
  Serial.print(sensorValue);

//  sensorVoltage=sensorValue*(aref_voltage/1023);
  sensorVoltage=map(sensorValue,0,1023,0,aref_voltage);
  Serial.print(";  voltage[mV]:");
  Serial.print(sensorVoltage);

  float sensorTemp =25+(sensorVoltage-750)*.1 ;//TMP36; 750mV@25C; dV/dT=+10mV/C; range:-40 to +125C
  Serial.print(";  Temperature[C]:");
  Serial.println(sensorTemp);

  delay(1000);// wait one second

  if (sensorTemp>20){
    digitalWrite(LEDPin,HIGH);
  }
  else{          
    digitalWrite(LEDPin,LOW);
  }

}

