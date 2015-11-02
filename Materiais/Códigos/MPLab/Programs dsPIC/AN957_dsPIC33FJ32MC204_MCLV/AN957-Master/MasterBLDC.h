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
//	File:		SensoredBLDC.h
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

/*
Using the Fosc = Fin * (M/(N1*N2))
Where:
Fin 	= 8Mhz
M 	= PLLFBD[PLLDIV<8:0>] 	= 0x26	then M = 40  (PLLDIV + 2)
N1	= CLKDIV[PLLPRE<4:0>] 	= 0x0 	then N1 = 2  (PLLPRE + 2)
N2	= CLKDIV[PLLPOST<1:0>]	= 0x3	then N2 = 8 

CLKDIV = 0x30C0
PLLFBD = 0x0026

?	Fosc =	(8M * (40 / (8 * 2)))  = 20Mhz
?	Fcy  =	20M/2 = 10MIP
*/

//#define CLOSEDLOOP
#define FOSC  10000000			// xtal = 10.0Mhz, 120.0Mhz after PLL
#define FCY  FOSC/2				
#define MILLISEC FCY/5000		// 1 mSec delay constant
#define FPWM 39000

//Valores das constantes para os cáculos do PID
#define Td 39.37
#define Kc 80.53
#define Ti 0.025
#define Ni 20  //Varia de 8 a 20
#define Ta 0.2
#define Tt 0.1 /// Varia de 0.1 até 1
#define b 1 //Varia de 0.5 a 1
//calculo dos valores para fórmula do PID
#define bi Kc*Ta/Ti
#define ad (2*Td-Ni*Ta)/(2*Td+Ni*Ta)
#define bd (2*Kc-Ni*Td)/(2*Td+Ni*Ta)
#define a0 Ta/Tt


#define POLEPAIRS		4		// number of pole pairs
#define HALL_INDEX_R	6		// Hall sensor position index
#define HALL_INDEX_F	5		// Hall sensor position index

#define LED     LATAbits.LATA1
#define	PLED	PORTAbits.RA1
#define EN1     LATBbits.LATB15
#define EN2     LATBbits.LATB13
#define EN3     LATBbits.LATB11
#define RESET8313N LATAbits.LATA4
#define SLEEP8313N LATBbits.LATB5
#define FAULT8313N PORTBbits.RB6
#define PRESET8313N PORTAbits.RA4
#define PSLEEP8313N PORTBbits.RB5
#define HALL1	PORTBbits.RB0
#define HALL2	PORTBbits.RB1
#define HALL3	PORTBbits.RB7
#define SCL	PORTBbits.RB6

#define T1PR1 ((FCY/1000)/8)

/* Based on using the internal Fcy and Timer 3 prescaler of 256
 * Fcy/256 = 10M/256 = 39062.5 ticks/sec
 * or, 2343750 ticks = 1RPM
 * => RPM would be 2343750/T3ticks
 */
//#define SPEEDMULT	2343750
//define OFFSET 8
//#define POTMULT 4				// pot to speed ratio

//#define Kps	50					// Kp and Ks terms need to be adjusted
//#define Kis	1					// as per the motor and load 

struct MotorFlags
{
unsigned RunMotor 	:1;
unsigned Direction	:1;
unsigned Sentido	:1;
unsigned unused		:13;
};
extern struct MotorFlags Flags;

extern long double erro;
extern long double angulo;
extern int setpoint;
extern int velocidade;
extern unsigned int HallValue;
extern unsigned int timer3value;
extern unsigned int timer3avg;
extern unsigned int polecount;
extern unsigned char recebe;

extern unsigned int StateTableFwd[];
extern unsigned int StateTableRev[];

extern unsigned char RAMBuffer[256];	//RAM area which will work as EEPROM for Master I2C device

struct FlagType
{
	unsigned char AddrFlag:1;
	unsigned char DataFlag:1;
};
extern struct FlagType Flag;

