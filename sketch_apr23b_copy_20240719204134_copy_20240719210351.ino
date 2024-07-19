#include <OneWire.h>
#include <DallasTemperature.h>

// Constants
const int pResistor = A0;   // Photoresistor pin to Arduino analog A1 pin
const int buzzer= 7;        // Buzzer pin to Arduino pin 7
const int gasSensor= A1;    // Gas sensor MQ-2 signal pin to Arduino analog A0 pin
const int hLight= 8;        // Helmet light to Arduino pin 4
const int redLed=9;         // Red led pin to Arduino pin 5

/* Temp sensor DS18B20 to Arduino pin 2 */
#define ONE_WIRE_BUS 11
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

/* Change values if you want */
////////////////////
int dTemp = 60;  // Default temperature
int dGas = 500;    // Default Air value (0-1023)
int bValue= 10;   // Brightness value (0-1023)
///////////////////

//Variables
int gasValue;
int lightValue;
int tempValue;

void setup(void)
{
  Serial.begin(9600); // Initialize serial communication
  pinMode(buzzer,OUTPUT);
  pinMode(hLight,OUTPUT);
  pinMode(redLed, OUTPUT);
  sensors.begin();
  delay(10000);//mq-2 warmup delay (60sec)
}

void loop(void)
{ 
  // Read and store values to additional variables 
  gasValue   = analogRead(gasSensor);
  lightValue = analogRead(pResistor);
  sensors.requestTemperatures();  
  tempValue  = sensors.getTempCByIndex(0); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  
  // Print sensor values to Serial Monitor
  Serial.print("Gas Value: ");  
  Serial.print(gasValue);  
  Serial.print(" | Light Value: ");
  Serial.print(lightValue);
  Serial.print(" | Temp Value: ");
  Serial.println(tempValue);
  
  // Dangerous gas if
  // Rest of your gasValue and tempValue checks go here

  // Room/area light - brightness
  if (lightValue > bValue){
    digitalWrite(hLight, LOW);
  }
  else{
    digitalWrite(hLight, HIGH);
  }
}
