//---------------------------------------------------------------------
//
//							 Software License Agreement
//
// The software supplied herewith by Microchip Technology Incorporated 
// (the �Company�) for its PICmicro� Microcontroller is intended and 
// supplied to you, the Company�s customer, for use solely and 
// exclusively on Microchip PICmicro Microcontroller products. The 
// software is owned by the Company and/or its supplier, and is 
// protected under applicable copyright laws. All rights are reserved. 
//  Any use in violation of the foregoing restrictions may subject the 
// user to criminal sanctions under applicable laws, as well as to 
// civil liability for the breach of the terms and conditions of this 
// license.
//
// THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES, 
// WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
// TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT, 
// IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR 
// CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
//
//---------------------------------------------------------------------
//	File:		Interrupts.c
//
//						
// 
// The following files should be included in the MPLAB project:
//
//		SensoredBLDC.c		-- Main source code file
//		Interrupts.c
//		Init.c
//		SensoredBLDC.h		-- Header file
//		p33FJ32MC204.gld	-- Linker script file
//				
//
//---------------------------------------------------------------------- 

#include "p33EP32MC502.h"
#include "MasterBLDC.h"
#include "functions_i2c.h"

#include <uart.h>
#include <math.h>

unsigned int Kps = 20000;					// Kp and Ks terms need to be adjusted
unsigned int Kis = 2000;					// as per the motor and load

unsigned int segundo = 1000;

unsigned char RAMBuffer[256];	//RAM area which will work as EEPROM for Master I2C device
unsigned char *RAMPtr;			//Pointer to RAM memory locations
struct FlagType Flag;

long double uk=0;
long double uk1=0;
long double uk2=0;
long double ek=0;
long double ek1=0;
long double ek2=0;
long double erro;

long double angulo;
long double angulonovo;
long double conv;
int velocidade = 0;
int setpoint = 180;
int setpoint180 = 180;
unsigned char recebe;


/*********************************************************************
Function:		void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt (void)

Overview:		For Open loop, the ADC interrupt loads the PDCx 
				registers with thedemand pot value.  This is only 
				done when the motor is running.
				For Closed loop, the ADC interrupt saves into 
				DesiredSpeed the demand pot value.  This is only 
				done when the motor is running.

*********************************************************************/

/*void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt (void)
{
  	/*if (Flags.RunMotor)
    #ifdef CLOSEDLOOP					// For closed loop, save
		DesiredSpeed = ADC1BUF0 * POTMULT;	// value for speed control
    #else
	{									// For open loop control,
		P1DC1 =  (ADC1BUF0 >> 1);			// get value,
		P1DC2 = P1DC1;					// and load all three PWM
		P1DC3 = P1DC1;					// duty cycles
	}
	#endif


	// reset ADC interrupt flag
	IFS0bits.AD1IF = 0;
}*/

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt (void)
{
    if (segundo--==0)
    {
        //segundo = 1000;
        //if (LED==1)
            //LED=0;
       // else
           // LED=1;
    }
    IFS0bits.T1IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt (void)
{

    send_command(0x50);

    hmc_dados[1] = (hmc_data[1]<<8)+ hmc_data[2];
    hmc_dados[2] = (hmc_data[3]<<8)+ hmc_data[4];
    hmc_dados[3] = (hmc_data[5]<<8)+ hmc_data[6];
    angulo = (long double)hmc_dados[1]/10.0;

    if ((angulo>=(setpoint-4))&&(angulo<=setpoint+4))
      LED=0;
      else
      LED=1;
    
    //Transforma��o coordenadas
    //Transforma��o de coordenadas para evitar singularidade

    /*conv = 180.0 - setpoint;
    angulonovo = angulo + conv;
    if (angulonovo>360)
    {
        angulo = angulonovo-360.0;
    }
    else if (angulonovo<0)
    {
        angulo = angulonovo+360.0;
    }
    else
    {
        angulo = angulonovo;
    }*/
    ///Fun��es para realizar os c�lculos sem transforma��o de coordenadas;
    long double angulorad = angulo*0.01745329252;
    long double setpointrad = setpoint*0.01745329252;
    ///Fun��es com transforma��o das coodenadas;
    //float angulorad = angulo*0.01745329252;
    //float setpointrad = setpoint180*0.01745329252;

    ek = setpointrad - angulorad;

    //uk = -620*ek; //P funcionando
    //uk = uk1 - 16.24*ek + 26.46*ek1 - 10.77*ek2; PID ganho muito baixo
    uk = uk1 - 239.1*ek + 389.7*ek1 - 158.6*ek2; //PID sintonizado

    velocidade = (int)(uk*9.5492965855);

    if (velocidade > 5500)
    {
        velocidade = -5500;
    }
    if (velocidade < -5500)
    {
        velocidade = 5500;
    }

    send_command_pic(64,20,(velocidade>>8));
    send_command_pic(64,21,(velocidade&0x00FF));
    //send_command_pic(64,0,1);

    ek2 = ek1;
    uk2 = uk1;
    ek1 = ek;
    uk1 = uk;
    erro = ek;

    IFS0bits.T3IF = 0;
}
/*
Function Name: SI2C1Interrupt
Description : This is the ISR for I2C2 Slave interrupt.
Arguments	 : None
*/

void __attribute__((interrupt,no_auto_psv)) _SI2C2Interrupt(void)
{
	unsigned char Temp;	//used for dummy read

	if((I2C2STATbits.R_W == 0)&&(I2C2STATbits.D_A == 0))	//Address matched
		{
			Temp = I2C2RCV;		//dummy read
			Flag.AddrFlag = 1;	//next byte will be address
		}
	else if((I2C2STATbits.R_W == 0)&&(I2C2STATbits.D_A == 1))	//check for data
		{
			if(Flag.AddrFlag)
			{
				Flag.AddrFlag = 0;
				Flag.DataFlag = 1;	//next byte is data
				RAMPtr = RAMPtr + I2C2RCV;
			}
			else if(Flag.DataFlag)
			{
				*RAMPtr = (unsigned int)I2C2RCV;// store data into RAM
				Flag.AddrFlag = 0;//end of tx
				Flag.DataFlag = 0;
				RAMPtr = &RAMBuffer[0];	//reset the RAM pointer
			}
		}
	else if((I2C2STATbits.R_W == 1)&&(I2C2STATbits.D_A == 0))
	{
		Temp = I2C2RCV;
		I2C2TRN = *RAMPtr;	//Read data from RAM & send data to I2C master device
		I2C2CONbits.SCLREL = 1;	//Release SCL1 line
		while(I2C2STATbits.TBF);//Wait till all
		RAMPtr = &RAMBuffer[0];	//reset the RAM pointer
	}
	_SI2C2IF = 0;	//clear I2C1 Slave interrupt flag
}
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    /* Check for receive errors */
    /* Must clear the overrun error to keep UART receiving */
    if (U1STAbits.OERR == 1) {
        U1STAbits.OERR = 0;
    }
    /* Get the data */
    if (U1STAbits.URXDA == 1) {
        recebe = U1RXREG;
    }
    IFS0bits.U1RXIF = 0;
}

/******************************************************************************
 * Function:   void __attribute__ ((interrupt, no_auto_psv)) _U1TXInterrupt(void)
 *
 * PreCondition: UART Module must be Initialized with transmit interrupt enabled.
 *
 * Input:        None
 *
 * Output:       None
 *
 * Side Effects: None
 *
 * Overview:     UART transmit interrupt service routine called whenever a data
 *               is sent from UART Tx buffer
 *****************************************************************************/
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
    IFS0bits.U1TXIF = 0;
}
