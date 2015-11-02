//---------------------------------------------------------------------
//
//							 Software License Agreement
//
// The software supplied herewith by Microchip Technology Incorporated
// (the ?Company?) for its PICmicro® Microcontroller is intended and
// supplied to you, the Company?s customer, for use solely and
// exclusively on Microchip PICmicro Microcontroller products. The
// software is owned by the Company and/or its supplier, and is
// protected under applicable copyright laws. All rights are reserved.
//  Any use in violation of the foregoing restrictions may subject the
// user to criminal sanctions under applicable laws, as well as to
// civil liability for the breach of the terms and conditions of this
// license.
//
// THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
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

#include "p33EP32MC202.h"
#include "SensoredBLDC.h"
#include "motorcontrol.h"
#include "stdlib.h"

int DesiredSpeed;
int ActualSpeed;
int SpeedError;
unsigned int Kps = 20000;					// Kp and Ks terms need to be adjusted
unsigned int Kis = 2000;					// as per the motor and load

unsigned int segundo = 1000;

unsigned char RAMBuffer[256];	//RAM area which will work as EEPROM for Master I2C device
unsigned char *RAMPtr;			//Pointer to RAM memory locations
struct FlagType Flag;

float uk=0;
float uk1=0;
float ek=0;
float ek1=0;

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
  	if (Flags.RunMotor)
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

/*********************************************************************
Function:		void __attribute__((interrupt, no_auto_psv)) _IC1Interrupt (void)

PreCondition:	The inputs of the hall effect sensors should have low pass
				filters. A simple RC network works.

Overview:		This interrupt represents Hall A ISR.
   				In Reverse, Hall reading == 3 or 4
   				In Forward, Hall reading == 2 or 5
   				and generates the next commutation sector.
				Hall A is used for Speed measurement
********************************************************************/

void __attribute__((interrupt, no_auto_psv)) _IC1Interrupt (void)
{
       //unsigned int TempTimer;
       // Se sentido = 0, os valores dos Halls são 1 ou 6;
       // Se sentido = 1, os valores dos Halls são 2 ou 5;
       
	IFS0bits.IC1IF = 0;	// Clear interrupt flag
        polecount++;
        HallValue = (unsigned int)(HALL1<<2)+(HALL2<<1)+HALL3;	// Read halls	// Read halls

	if (Flags.Direction==1)
	{
        motorcontrol(StateTableFwd[HallValue]);
	}
	if (Flags.Direction==0)
	{
        motorcontrol(StateTableRev[HallValue]);
	}
        switch(HallValue)
	{
            case 1:
            Flags.Sentido = 0;
            break;
            case 2:
            Flags.Sentido = 1;
            break;
            case 5:
            Flags.Sentido = 1;
            break;
            case 6:
            Flags.Sentido = 0;
            break;
        }
}

/*********************************************************************
Function:		void __attribute__((interrupt, no_auto_psv)) _IC2Interrupt (void)

PreCondition:	The inputs of the hall effect sensors should have
				low pass filters. A simple RC network works.

Overview:		This interrupt represents Hall B ISR.
   				Hall reading == 1 or 6
   				and generates the next commutation sector.

********************************************************************/

void __attribute__((interrupt, no_auto_psv)) _IC2Interrupt (void)
{

        IFS0bits.IC2IF = 0;	// Clear interrupt flag
        
        HallValue = (unsigned int)(HALL1<<2)+(HALL2<<1)+HALL3;	// Read halls	// Read halls
        polecount++;
        if (Flags.Direction==1)
	{
        motorcontrol(StateTableFwd[HallValue]);
	}

	if (Flags.Direction==0)
	{
        motorcontrol(StateTableRev[HallValue]);
	}
}

/*********************************************************************
Function:		void __attribute__((interrupt, no_auto_psv)) _IC7Interrupt (void)

PreCondition:	The inputs of the hall effect sensors should have
				low pass filters. A simple RC network works.

Overview:		This interrupt represents Hall C ISR.
   				and generates the next commutation sector.

********************************************************************/

void __attribute__((interrupt, no_auto_psv)) _IC3Interrupt (void)
{

       IFS2bits.IC3IF = 0;	// Clear interrupt flag

       HallValue = (unsigned int)(HALL1<<2)+(HALL2<<1)+HALL3;	// Read halls	// Read halls
       polecount++;
       if (Flags.Direction==1)
	{
        motorcontrol(StateTableFwd[HallValue]);
	}
	if (Flags.Direction==0)
	{
        motorcontrol(StateTableRev[HallValue]);
	}
}

/*********************************************************************
Function:		void __attribute__((interrupt, no_auto_psv)) _T3Interrupt (void)

PreCondition:	None.

Overview:		This interrupt a 1ms interrupt and outputs a square
				wave toggling LED4.

********************************************************************/

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt (void)
{
    
    IFS0bits.T1IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt (void)
{
    timer3value = (polecount*125);
    timer3avg = timer3value>>1;
    polecount = 0;

    //if (timer1avg==0)
    //{
    //velocidade1=0;
    //}
    //else
    //{
    //timer1avg = (int)(3515625/timer1value);
    //}

    if (Flags.Sentido==0)
    {
    velocidade = -1*timer3avg;
    //velocidade1 = -1*timer1avg;
    }
    if (Flags.Sentido==1)
    {
    velocidade = timer3avg;
    //velocidade1 = timer1avg;
    }
    RAMBuffer[30] = velocidade>>8;
    RAMBuffer[31] = velocidade&0x00FF;

    setpoint = (RAMBuffer[20]<<8)+(RAMBuffer[21]);
    //setpoint = 2000;
    //RAMBuffer[32] = velocidade1>>8;
    //RAMBuffer[33] = velocidade1&0x00FF;

    float velocidaderads = velocidade*0.10471975511966;//Velocidade 1 para metodo alternativo
    float setpointrads = setpoint*0.10471975511966;

    ek = setpointrads - velocidaderads;

    //uk = uk1 + (0.02293*ek) - (0.02201*ek1); Equação funcionando
    uk = uk1 + (0.023107314300773*ek) - (0.022561042095081*ek1);

    if (uk>0)
    {
    Flags.Direction = 1;
    }
    if (uk<0)
    {
    Flags.Direction = 0;
    }

    int mdc = abs((int)(62.5*uk));

    if (mdc>750)
        {
        mdc = 750;
        }

    MDC = 750 - mdc;

    ek1 = ek;
    uk1 = uk;

    //RAMBuffer[34] = (int)mdc>>8;
    //RAMBuffer[35] = (int)mdc&0x00FF;

    //O motor as vezes fica parado justamente em um polo magnético.
    //Para corrigir, esperamos o set point máximo para ver o que acontece
    if ((mdc>=550)&&(velocidade==0))
        {
        motorcontrol(1);
        DelayNmSec(50);
        motorcontrol(2);
        DelayNmSec(50);
        motorcontrol(3);
        DelayNmSec(50);
        }
    IFS0bits.T3IF = 0;
}
/*
Function Name: SI2C1Interrupt
Description : This is the ISR for I2C1 Slave interrupt.
Arguments	 : None
*/

void __attribute__((interrupt,no_auto_psv)) _SI2C1Interrupt(void)
{
	unsigned char Temp;	//used for dummy read

	if((I2C1STATbits.R_W == 0)&&(I2C1STATbits.D_A == 0))	//Address matched
		{
			Temp = I2C1RCV;		//dummy read
			Flag.AddrFlag = 1;	//next byte will be address
		}
	else if((I2C1STATbits.R_W == 0)&&(I2C1STATbits.D_A == 1))	//check for data
		{
			if(Flag.AddrFlag)
			{
				Flag.AddrFlag = 0;
				Flag.DataFlag = 1;	//next byte is data
				RAMPtr = RAMPtr + I2C1RCV;
			}
			else if(Flag.DataFlag)
			{
				*RAMPtr = (unsigned int)I2C1RCV;// store data into RAM
				Flag.AddrFlag = 0;//end of tx
				Flag.DataFlag = 0;
				RAMPtr = &RAMBuffer[0];	//reset the RAM pointer
			}
		}
	else if((I2C1STATbits.R_W == 1)&&(I2C1STATbits.D_A == 0))
	{
		Temp = I2C1RCV;
		I2C1TRN = *RAMPtr;	//Read data from RAM & send data to I2C master device
		I2C1CONbits.SCLREL = 1;	//Release SCL1 line
		while(I2C1STATbits.TBF);//Wait till all
		RAMPtr = &RAMBuffer[0];	//reset the RAM pointer
	}
	_SI2C1IF = 0;	//clear I2C1 Slave interrupt flag
}