//---------------------------------------------------------------------
//
//							 Software License Agreement
//
// The software supplied herewith by Microchip Technology Incorporated 
// (the “Company”) for its PICmicro® Microcontroller is intended and 
// supplied to you, the Company’s customer, for use solely and 
// exclusively on Microchip PICmicro Microcontroller products. The 
// software is owned by the Company and/or its supplier, and is 
// protected under applicable copyright laws. All rights are reserved. 
//  Any use in violation of the foregoing restrictions may subject the 
// user to criminal sanctions under applicable laws, as well as to 
// civil liability for the breach of the terms and conditions of this 
// license.
//
// THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES, 
// WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
// TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT, 
// IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR 
// CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
//
//---------------------------------------------------------------------
//	File:		SensoredBLDC.c
//
//	Written By:		Bill Anderson, Microchip Technology
//						
// 
// The following files should be included in the MPLAB project:
//
//		SensoredBLDC.c		-- Main source code file
//		Interrupts.c
//		Init.c
//		SensoredBLDC.h		-- Header file
//		p33FJ256MC710.gld	-- Linker script file
//				
//
//--------------------------------------------------------------------
//
// Revision History
//
// 06/30/07 -- first version 
//---------------------------------------------------------------------- 

#include "p33EP32MC202.h"
#include "SensoredBLDC.h"
/******************************************************************************/
/* Configuration bits                                                         */
/******************************************************************************/

// Select Internal FRC at POR
_FOSCSEL(FNOSC_FRC & PWMLOCK_OFF & IESO_OFF);
// Enable Clock Switching and Configure POSC in XT mode

_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);

_FPOR( ALTI2C1_ON & ALTI2C2_ON );
// ALTI2C1_ON           I2C1 mapped to ASDA1/ASCL1 pins
// ALTI2C2_ON           I2C2 mapped to ASDA2/ASCL2 pins

_FWDT(FWDTEN_OFF)

void InitADC10(void);
void DelayNmSec(unsigned int N);
void InitMCPWM(void);
void InitTMR3(void);
void InitIC(void);
void CalculateDC(void);
void ResetPowerModule(void);
void InitTMR1(void);
void lockIO(void);
void unlockIO(void);

struct MotorFlags Flags;

unsigned int HallValue;
unsigned int timer3value;
unsigned int timer3avg;
unsigned char polecount;
 
char *UartRPM,UartRPMarray[5];
int RPM, rpmBalance;

/*************************************************************
	Low side driver table is as below.  In the StateLoTableClk
	and the StateLoTableAntiClk tables, the Low side driver is
	PWM while the high side driver is either on or off.  
*************************************************************/

unsigned int StateTableFwd[] = {0x0000, 0x0210, 0x2004, 0x0204,
									0x0801, 0x0810, 0x2001, 0x0000};
unsigned int StateTableRev[] = {0x0000, 0x2001, 0x0810, 0x0801,
									0x0204, 0x2004, 0x0210, 0x0000};



int main(void)
{
	unsigned int i;

        InitPLL();

	//TRISA |= 0x0100;	// S2 as input RA8
	//TRISB |= 0x0010;	// S3 as input RB4

	// Analog pin for POT already initialized in ADC init subroutine

        /*Função para iniciar os imput captures para os sensores hall do motor
        *
        *RPI32 - RB0 - IC1 --> Hall 1
        *RPI33 - RB1 - IC2 --> Hall 2
        *RP39 - RB7 - IC3  --> Hall 3*/



	unlockIO();
	RPINR7bits.IC1R = 32;		// IC1 on RPI32 - RB0
	RPINR7bits.IC2R = 33;		// IC2 on RPI33 - RB1
	RPINR8bits.IC3R = 39;         // IC3 on RP39 - RB7
	lockIO();
 
	//InitADC10();
	InitTMR1();
	InitTMR3();
	timer3avg = 0;
	InitMCPWM();
	InitIC();
	Flags.Direction = 1;				// initialize direction CW

        InitStatusLED();
        InitOUT_5();

        LED = 1;


	//for(i=0;i<1000;i++);

	while(1)
	{

		while(S2)					// wait for start key hit
		{
			if (!S3)				// check for direction change
			{
				while (!S3)			// wait till key is released
					DelayNmSec(10);
					Flags.Direction ^= 1;
			}
			Nop();
		}
		while (!S2)					// wait till key is released
			DelayNmSec(10);
			
			// read hall position sensors on PORTD
		HallValue = (unsigned int)((PORTB >> 1) & 0x0007);
		//if (Flags.Direction)
			//OVDCON = StateTableFwd[HallValue];
		//else
			//OVDCON = StateTableRev[HallValue];
			
		PWMCON1 = 0x0777;			// enable PWM outputs
		Flags.RunMotor = 1;			// set flag
		T3CONbits.TON = 1;			// start tmr3
		polecount = 1;
		DelayNmSec(100);

		while (Flags.RunMotor)				// while motor is running
		{
			if (!S2)						// if S2 is pressed
				{
				PWMCON1 = 0x0700;			// disable PWM outputs
  				//OVDCON = 0x0000;			// overide PWM low.
				Flags.RunMotor = 0;			// reset run flag
				while (!S2)					// wait for key release
					DelayNmSec(10);
				}
			Nop();
		}
	}
}
//---------------------------------------------------------------------
// This is a generic 1ms delay routine to give a 1mS to 65.5 Seconds delay
// For N = 1 the delay is 1 mS, for N = 65535 the delay is 65,535 mS. 
// Note that FCY is used in the computation.  Please make the necessary
// Changes(PLLx4 or PLLx8 etc) to compute the right FCY as in the define
// statement above.

void DelayNmSec(unsigned int N)
{
unsigned int j;
while(N--)
 	for(j=0;j < MILLISEC;j++);
}

/*********************************************************************************** 
 * Function: lockIO
 *
 * Preconditions: None.
 *
 * Overview: This executes the necessary process to set the IOLOCK bit to lock
 * I/O mapping from being modified.
 *
 * Input: None.
 *
 * Output: None.
 *
 *****************************************************************************/
void lockIO(){

asm volatile ("mov #OSCCON,w1 \n"
				"mov #0x46, w2 \n"
				"mov #0x57, w3 \n"
				"mov.b w2,[w1] \n"
				"mov.b w3,[w1] \n"
				"bset OSCCON, #6");
}

/*****************************************************************************
 * Function: unlockIO
 *
 * Preconditions: None.
 *
 * Overview: This executes the necessary process to clear the IOLOCK bit to 
 * allow I/O mapping to be modified.
 *
 * Input: None.
 *
 * Output: None.
 *
 *****************************************************************************/
void unlockIO(){

asm volatile ("mov #OSCCON,w1 \n"
				"mov #0x46, w2 \n"
				"mov #0x57, w3 \n"
				"mov.b w2,[w1] \n"
				"mov.b w3,[w1] \n"
				"bclr OSCCON, #6");
}
