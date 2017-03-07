/*
  Analog Input
  Demonstrates analog input by reading an analog sensor (TMP36)on analog pin 0
  the value obtained by analogRead().
  The LED is turned on /off/dim according to the read temperature

  The circuit:
   thermometer TMP 36 (pin 2 – center)  attached to analog input 0
   thermometer TMP 36 (pin 3) to ground
   thermometer TMP 36 (pin 1) to +5V

  Created by Avi Braun based on the analogread example by David Cuartielles
  This example code is in the public domain.
*/

const int sensorPin = A0;    // select the input pin for the thermometer
int sensorValue = 0;  // variable to store the value coming from the sensor
float sensorVoltage; // variable to store the camculated volatge
float sensorTemp; // variable to store the camculated temperature
float aref_voltage = 5000; // the default analog reference voltage of Arduino is ~5000mV
const int LEDPinRed = 11; // // select the output pin for the redLED
const int LEDPinBlue = 10; // // select the output pin for the blue LED

unsigned long previousMillis = 0;        // will store last time Temperature was updated

const long interval_m = 500;           // interval at which to take mesurement (milliseconds)

void setup() {
  pinMode(LEDPinRed, OUTPUT);      // sets the digital pin as output
  pinMode(LEDPinBlue, OUTPUT);      // sets the digital pin as output

  Serial.begin(9600); // initiate a serial connection between PC and the Arduino board
  analogReference(DEFAULT);// set the analog reference to default value

}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval_m) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    sensorValue = analogRead(sensorPin);
    // print the read value:
    Serial.print(currentMillis);
    Serial.print("Read Value:");
    Serial.print(sensorValue);

    sensorVoltage = sensorValue * (aref_voltage / 1023);
    Serial.print(";  voltage[mV]:");
    Serial.print(sensorVoltage);

    sensorTemp = 25 + (sensorVoltage - 750) * .1 ; //TMP36; 750mV@25C; dV/dT=+10mV/C; range:-40 to +125C
    Serial.print(";  Temperature[C]:");
    Serial.println(sensorTemp);
  

    int colour=map(sensorTemp,22,28,0,150);
    Serial.print(colour);
    analogWrite(LEDPinBlue, 100+colour);
    analogWrite(LEDPinRed, 255-colour);
  }
//  
//  if (sensorTemp < 19.5) {
//    analogWrite(LEDPinRed, 255);
//    analogWrite(LEDPinBlue, 0);
//    //        Serial.print("HIGH");
//  }
//  else {
//    analogWrite(LEDPinRed, 0);
//    analogWrite(LEDPinBlue, 255);
//
//    //        Serial.print("LOW");
//  }
  //  delay(1000);// wait one second

}


