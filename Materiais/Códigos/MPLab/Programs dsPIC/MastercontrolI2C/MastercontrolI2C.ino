
#include <Wire.h>
#include "SFE_HMC6343.h"
SFE_HMC6343 compass; // Declare the sensor object

void enviaI2C(byte who, byte adress, byte data);
char recebeI2C(byte who, byte adress);


void setup() 
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);
  delay(500);
  // Initialize the HMC6343 and verify its physical presence
  if (!compass.init())
  {
  Serial.println("Sensor Initialization Failed\n\r"); // Report failure, is the sensor wiring correct?
  }
}

void loop() {
  // Assumes a string in from the serial port like so:
  // s ledNumber, brightness \n
  // for example: "s5,200\n":
  
  int sentido, velocidade = 0;
  byte enderecomemoria = 0;
  byte enderecoi2c = 0;
  byte valor = 0;
  byte recebe, recebe2 = 0;

  if (Serial.find("s")) {
    
    //enderecoi2c = Serial.parseInt();// parses numeric characters after the comma
    enderecomemoria = Serial.parseInt(); // parses numeric characters before the comma
    valor = Serial.parseInt();// parses numeric characters after the comma
    
    // print the results back to the sender:
    //Serial.print("Endereco I2C: " );
    //Serial.print(enderecoi2c);
    Serial.print("Endereco Memoria: " );
    Serial.print(enderecomemoria);
    Serial.print(" Valor: ");
    Serial.print(valor);
    Serial.println(" ");
    enviaI2C(64,enderecomemoria,valor);    
    recebe = recebeI2C(64,enderecomemoria);
    Serial.println(recebe);
    
    enviaI2C(64,20,7);
    recebe = recebeI2C(64,20);
    Serial.println(recebe);
    enviaI2C(64,21,208);
    recebe = recebeI2C(64,21); 
   Serial.println(recebe);   
  
    Wire.endTransmission();
    
   }
   
  
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
  return x;
}
void printHeadingData()
{
Serial.println("Heading Data (Raw value, in degrees):");
Serial.print("Heading: ");
Serial.print(compass.heading); Serial.print(" "); // Print raw heading value
Serial.print((float) compass.heading/10.0);/*Serial.write(176)*/;Serial.println(); // Print heading in degrees
Serial.print("Pitch: ");
Serial.print(compass.pitch); Serial.print(" ");
Serial.print((float) compass.pitch/10.0);//Serial.write(176);Serial.println();
Serial.print("Roll: ");
Serial.print(compass.roll); Serial.print(" ");
Serial.print((float) compass.roll/10.0);//Serial.write(176);Serial.println();
Serial.println();
Serial.println();
}
