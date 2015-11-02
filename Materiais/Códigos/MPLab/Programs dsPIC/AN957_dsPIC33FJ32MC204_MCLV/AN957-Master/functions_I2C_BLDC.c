#include <stdio.h>
#include <stdlib.h>
#include <i2c.h>
#include "p33EP32MC502.h"
#include "MasterBLDC.h"
#include "functions_i2c.h"

int hmc_data[7];
int hmc_dados[7];


unsigned int read_eeprom(unsigned int register_name)
{

    unsigned int data;

    StartI2C2();
        IdleI2C2();
    MasterWriteI2C2(DEVICE_WRITE);
        IdleI2C2();
    MasterWriteI2C2(0xE1);
        IdleI2C2();
    MasterWriteI2C2(register_name);
        IdleI2C2();
    RestartI2C2(); // Initiate a RESTART command
        IdleI2C2();
    MasterWriteI2C2(DEVICE_READ); // address device w/read
        IdleI2C2();
    data = MasterReadI2C2();
    IdleI2C2();
    NotAckI2C2();
        IdleI2C2();
    StopI2C2();

    return(data);

}
void send_command(unsigned int command_byte)
{

    StartI2C2();
        IdleI2C2();
    MasterWriteI2C2(DEVICE_WRITE);
        IdleI2C2();
    MasterWriteI2C2(command_byte);
        IdleI2C2();
    RestartI2C2(); // Initiate a RESTART command
        IdleI2C2();
    MasterWriteI2C2(DEVICE_READ);
        IdleI2C2();
        hmc_data[1] = MasterReadI2C2();
        IdleI2C2();
    AckI2C2(); // Send back Acknowledge
        IdleI2C2();
        hmc_data[2] = MasterReadI2C2();
        IdleI2C2();
    AckI2C2(); // Send back Acknowledge
        IdleI2C2();
        hmc_data[3] = MasterReadI2C2();
        IdleI2C2();
    AckI2C2(); // Send back Acknowledge
        IdleI2C2();
        hmc_data[4] = MasterReadI2C2();
        IdleI2C2();
    AckI2C2(); // Send back Acknowledge
        IdleI2C2();
        hmc_data[5] = MasterReadI2C2();
        IdleI2C2();
    AckI2C2(); // Send back Acknowledge
        IdleI2C2();
        hmc_data[6] = MasterReadI2C2();
        IdleI2C2();
    NotAckI2C2(); // Send back Acknowledge
        IdleI2C2();
    StopI2C2();
    StopI2C2();
}

void send_command_pic(unsigned int who, unsigned int address, unsigned int command_byte)
{

	StartI2C2();	        //Send the Start Bit
	IdleI2C2();		//Wait to complete

	MasterWriteI2C2((who << 1) | 0);  //Sends the slave address over the I2C line.  This must happen first so the
                                             //proper slave is selected to receive data.
	IdleI2C2();	        //Wait to complete

        MasterWriteI2C2(address);  //Sends data byte over I2C line
	IdleI2C2();		//Wait to complete

	MasterWriteI2C2(command_byte);  //Sends data byte over I2C line
	IdleI2C2();		//Wait to complete

	StopI2C2();	        //Send the Stop condition
	IdleI2C2();	        //Wait to complete
}


