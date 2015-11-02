/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;                                                                     
;                     Software License Agreement                      
;                                                                     
;     ©2007 Microchip Technology Inc
;     Mirochip Technology Inc. ("Microchip") licenses this software to 
;     you solely for the use with Microchip Products. The software is
;     owned by Microchip and is protected under applicable copyright
;     laws. All rights reserved.
;
;     SOFTWARE IS PROVIDED "AS IS." MICROCHIP EXPRESSLY DISCLAIMS ANY
;     WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT
;     LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
;     PARTICULAR PURPOSE, OR NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP
;     BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL
;     DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF
;     PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
;     BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
;     ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS.
;     
;                                                                
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;	Filename:			    main.c            
;	Date:				    February 21, 2007          
;	File Version:		  	1.0                             
;	Assembled using:		MPLAB IDE 7.51.00.0               
; 	Author:		  	    	Martin Bowman              
;	Company:			    Microchip Technology, Inc.
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "p33Fxxxx.h"
#include "i2c.h"

_FGS(GSS_OFF & GWRP_OFF);
_FOSCSEL(FNOSC_PRI & IESO_OFF & TEMP_OFF);
_FOSC(FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMD_HS);
_FWDT(FWDTEN_OFF);


void InitPorts(void);

unsigned char ControlByte;		//Control Byte
unsigned char HighAdd;			//High Address byte
unsigned char LowAdd, HighAdd;	//Low and High Address byte
unsigned char Data;				//Data Byte
unsigned char Length;			//Length of Bytes to Read
unsigned char PageString[64];	//Array to hold page data to/from EPROM


/*********************************************************************
* Function:        main()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Main function loop.  Called on startup by init code
*
* Note:			None
********************************************************************/
int main (void)
{
	unsigned int n;		//Counter

	InitPorts();		//Initialise the IO Ports
	InitI2C();			//Initialise the I2C(1) Peripheral

	ControlByte = 0xA0;
	LowAdd = 0x00;	
	HighAdd = 0x5A;
	Data = 0xAA;
	Length = 0x01;

	for(n = 0; n < PAGESIZE; n++)
	{
		PageString[n] = n;
	}

	while(1)
	{
		LATAbits.LATA0 = 1;
		//LDByteWriteI2C(ControlByte, LowAdd, Data);	
		HDByteWriteI2C(ControlByte, HighAdd, LowAdd, Data);
		//HDPageWriteI2C(ControlByte, HighAdd, LowAdd, PageString);
		//LDByteReadI2C(ControlByte, LowAdd, &Data, 1);
		//HDByteReadI2C(ControlByte, HighAdd, LowAdd, &Data, 1);
		//HDSequentialReadI2C(ControlByte, HighAdd, LowAdd, PageString, PAGESIZE);

		Nop();
		LATAbits.LATA0 = 0;
		
	}	
}


/*********************************************************************
* Function:        InitPorts()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Initialises the IO ports
*
* Note:			None
********************************************************************/
void InitPorts(void)
{
	TRISA = 0x0000;
	TRISB = 0x0000;
	TRISC = 0x0000;
	TRISD = 0x0000;
	TRISE = 0x0000;
	TRISF = 0x0000;
	TRISG = 0x0000;

	TRISGbits.TRISG2 = 1;
	TRISGbits.TRISG3 = 1;
}
