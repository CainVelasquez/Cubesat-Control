/******************************************************************************
HMC6343_basics.ino
Simple example for using the HMC6343 3-axis compass library.
Jordan McConnell @ SparkFun Electronics
17 July 2014
https://github.com/sparkfun/HMC6343_Breakout
This example declares an SFE_HMC6343 object called compass. The object/sensor
is initialized and if the initialization fails, the sensor could not
be found and read from successfully.
Each time through the loop, heading values (heading, pitch, and roll) and
accelerometer values (accelX, accelY, accelZ) are read from the sensor. They
are then printed to the Serial Monitor at 115200 baud. The raw sensor values
are printed as well as scaled values in readable units (degrees and g forces).
The HMC6343 breakout board needs to be powered with 3.3V and uses I2C to talk
to the microcontroller. If you're using a 5V microcontroller board, such as
the standard Arduino UNO, you'll need a Logic Level Converter for the I2C lines,
such as SparkFun's BOB-12009.
Developed/Tested with:
Arduino Uno
Arduino IDE 1.0.5 & 1.5.2
Requires:
SFE_HMC6343_Library
This code is beerware.
Distributed as-is; no warranty is given.
******************************************************************************/
// Libraries for I2C and the HMC6343 sensor
#include <Wire.h>
#include "SFE_HMC6343.h"
SFE_HMC6343 compass; // Declare the sensor object

int setpointvelocidade = 0;
int setpoint = 30;
int setpointzero = 0;
int setpointnovareferencia = 0;
float setpointrad;//3.141592653589793;
float anguloatual;
char recebe;
float uk = 0;
float uk1 = 0;
float uk2 = 0;
float ek = 0;
float ek1 = 0;
float ek2 = 0;

void setup()
{
// Start serial communication at 115200 baud
Serial.begin(9600);
// Give the HMC6343 a half second to wake up
delay(500);
// Initialize the HMC6343 and verify its physical presence
  if (!compass.init())
  {
  Serial.println("Sensor Initialization Failed\n\r"); // Report failure, is the sensor wiring correct?
  }

}
void loop()
{
// Read, calculate, and print the heading, pitch, and roll from the sensor
compass.readHeading();
//printHeadingData();

///Mudança de variaveis para evitar singularidade

  setpointnovareferencia = (compass.heading/10.0) - setpoint;
  if (setpointnovareferencia >=180)
  {
    setpointnovareferencia = setpointnovareferencia-360;
  }

  Serial.println(setpointnovareferencia);
  
  anguloatual =  (((setpointnovareferencia)*3.141592653589793)/180);                                     //(((compass.heading/10.0)*3.141592653589793)/180);
  setpointrad = ((setpointzero*3.141592653589793)/180);                    //((setpoint*3.141592653589793)/180);
  
  ek = setpointrad - anguloatual; 

  //uk = uk1 + 189.95*ek - 169.2075*ek1; //PI do angelo

  uk = 150*ek + 75*ek1;// Proporcional 
  
  //uk = 1.6498*uk1 - 0.6498*uk2 + 52.418*ek + 0.08911*ek1 - 52.051*ek2; //PID 
  
  // uk = uk1 + 0.023107314300773*ek - 0.022561042095081*ek1; //Equação de PI que não funciona ek muito baixo;
   
  //uk = 1.932*uk1 - 0.9316*uk2 + 127.5*ek - 254.6*ek1 + 127.1*ek2; //Uma nova esperaça
  
  //uk = -1.422*uk1 + 264.2*ek + 29.36*ek1 + 0.2367*ek2; //Uma nova esperaça 2
  
  
  //Serial.println(uk,3);
  //Serial.println(uk1,3);
  //Serial.println(uk2,3);
  Serial.println(ek,3);
  //Serial.println(ek1,3);
  //Serial.println(ek2,3);
  //Serial.println();
  
  setpointvelocidade = -1*((uk*30)/3.141592653589793); //Mudar o sentido de rotação do conjunto.
  
  Serial.println(setpointvelocidade);
  Serial.println();

  enviaI2C(64,20,((setpointvelocidade>>8)));
  enviaI2C(64,21,(setpointvelocidade&0x00FF));     
    
  //enviaI2C(64,20,-7);
  //enviaI2C(64,21,208);     
  //recebe = recebeI2C(64,0);
  //Serial.println(recebe);
  //Serial.println();
  enviaI2C(64,0,1);
    
  uk2 = uk1;
  ek2 = ek1;
  uk1 = uk;
  ek1 = ek;

delay(10); // Minimum delay of 200ms (HMC6343 has 5Hz sensor reads/calculations)
}
// Print both the raw values of the compass heading, pitch, and roll
// as well as calculate and print the compass values in degrees
// Sample Output:
// Heading Data (Raw value, in degrees):
// Heading: 3249 324.90°
void printHeadingData()
{
Serial.println("Heading Data (Raw value, in degrees):");
Serial.print("Heading: ");
//Serial.print(compass.heading); Serial.print(" "); // Print raw heading value
Serial.print((float) compass.heading/10.0);/*Serial.write(176)*/;Serial.println(); // Print heading in degrees
}

void enviaI2C(byte who, byte adress, byte data)
{
Wire.beginTransmission(who);
Wire.write(adress);        
Wire.write(data);        
Wire.endTransmission();   
}
char recebeI2C(int who, int adress)
{
  int x;
  
  Wire.beginTransmission(who); // transmit to device #4
  Wire.write(adress);
  Wire.endTransmission();
  
  Wire.requestFrom(who,1);    // request 6 bytes from slave device #2
  while (Wire.available())   // slave may send less than requested
  {
    x = Wire.read(); // receive a byte as character
    //Serial.println(d);         // print the character
  }
  Wire.endTransmission();
  return x;
}
