/*
 * Rafael Corsi - corsiferrao@gmail.com 
 * Programa de debug para projeto de botao de panico
 * 	- André
 * 29.3.14
 * Teste em Arduino Uno com protoboard

	comandos
    AT  (Test command)
    AT+BAUD   (Query/Set Baud rate)
    AT+CHK   (Query/Set parity)
    AT+STOP   (Query/Set stop bit)
    AT+UART   (Query/Set uart rate,parity, stop bit)
    AT+PIO   (Query/Set PIO pins status Long command)
    AT+PIO   (Query/Set a PIO pin sttus Short command)
    AT+NAME   (Query/Set device friendly name)
    AT+PIN   (Query/Set device password code)
    AT+DEFAULT   (Reset device settings)
    AT+RESTART   (Restart device)
    AT+ROLE   (Query/Set device mode, Master or Slave)
    AT+CLEAR   (Clear remote device address if has)
    AT+CONLAST   (Try to connect last connect succeed device)
    AT+VERSION   (Show software version information)
    AT+HELP   (Show help information)
    AT+RADD   (Query remote device address)
    AT+LADD   (Query self address)
    AT+IMME   (Query/Set Whether the device boot immediately)
    AT+WORK   (if device not working, start work, use with AT+IMME command)
    AT+TCON   (Query/Set Try to connect remote times)
    AT+TYPE   (Query/Set device work type, transceiver mode or remote mode)
    AT+START   (Switch remote control mode to transceiver mode)
    AT+BUFF   (Query/Set How to use buffer data, Duing mode switching time)
    AT+FILT   (Query/Set device filter when device searching) A
    T+COD   (Query/Set Class of Device. eg: phone, headset etc.)

*/


int i =0;
int ndata;
int dado[20];

//SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{
	Serial.begin(9600);
}

void loop()
{
  delay(5000);
 
  Serial.write("AT+RENEW"); // Reset all settings.
  delay(300);

  // -> AT+NAME[para1] 
  // 	<- OK+Set[para1] 
  // para1 : Nome do dispositivo
  //	max length is 12.
  Serial.write("AT+NAMEPanico2");
  delay(400);

  // -> AT+ROLE[para1]
  //    <- OK+Set[para1]
  // para1 : Tipo de interface
  // 	0: Peripheral
  // 	1: Central
  Serial.write("AT+ROLE0");
  delay(300);

   // -> AT+MODE[para1]
  //    <- OK+Set[para1]
  // para1 : Configura 
  // 	0: Peripheral
  // 	1: Central
  Serial.write("AT+MODE1");
  delay(300);

  Serial.write("AT+IMME1");
  delay(300);

  Serial.write("AT+START");
  delay(300);

  while(1){
	Serial.write("TEST");
	delay(400); 	
  };
}

void plota(int atraso)
{
  delay(atraso);
  ndata =  Serial.available();
  //Serial.println(ndata, DEC);
  //Serial.print('\n');
  if(ndata)
  	while(ndata){
		Serial.write(Serial.read());
  		ndata =  Serial.available();
 	}
  //	Serial.print("---");
  //Serial.print('\n');
}

