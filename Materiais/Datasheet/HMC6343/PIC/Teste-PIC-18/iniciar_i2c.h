#include<p18f4550.h>
#include<delays.h>

//Função criada para inicar o I2C como 

void iniciar_i2c(unsigned char master_ou_slave, unsigned char endereco, unsigned char frequencia)
{
	
	
	OpenI2C(SLAVE_7, SLEW_OFF);// Initialize I2C module
	    SSPADD = 0x02; //400kHz Baud clock(9) @16MHz
	                //100kHz Baud clock(39) @16MHz

}

