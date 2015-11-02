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
#include "motorcontrol.h"

#include "pps.h"
#include<uart.h>
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

void InitOUT_5(void);
void InitStatusLED(void);
void InitADC0(void);
void DelayNmSec(unsigned int N);
void InitMCPWM(void);
void InitTMR3(void);
void InitIC(void);
void InitTMR1(void);
void motorcontrol (int state);

struct MotorFlags Flags;

int setpoint;
int velocidade;
unsigned int HallValue;
unsigned int timer3value;
unsigned int timer3avg;
unsigned int polecount = 0;
unsigned int dado, dado1, ADCValue;
unsigned int maquinaestados = 0;
unsigned int controleteste = 0;
 
char *UartRPM,UartRPMarray[5];
int RPM, rpmBalance,i;



/*************************************************************
 A tablea de acionamento segue a seguinte ordem:
 * Acionamento proporcionado através do DRV8313

State	OUTPUT1	OUTPUT2	OUTPUT3	HALLA	HALLB	HALLC	# Hall	Direto	Reverso
6	Float	High	Low	0	1	0	2	1	4
1	High	Float	Low	1	1	0	6	2	5
2	High	Low	Float	1	0	0	4	3	6
3	Float	Low	High	1	0	1	5	4	1
4	Low	Float	High	0	0	1	1	5	2
5	Low	High	Float	0	1	1	3	6	3
*
*************************************************************/

unsigned int StateTableFwd[] = {0, 5, 1, 6, 3, 4, 2, 0};
unsigned int StateTableRev[] = {0, 2, 4, 3, 6, 1, 5, 0};

int main(void)
{
	unsigned int i;

        // Configure PLL prescaler, PLL postscaler, PLL divisor
        PLLFBD=46; // M=48
        CLKDIVbits.PLLPOST=0; // N2=2
        CLKDIVbits.PLLPRE=0; // N1=2
        // Initiate Clock Switch to Primary Oscillator with PLL (NOSC=0b011)
        __builtin_write_OSCCONH(0x03);
        __builtin_write_OSCCONL(OSCCON | 0x01);
        // Wait for Clock switch to occur
        while (OSCCONbits.COSC!= 0b011);
        //  Wait for PLL to lock
        while (OSCCONbits.LOCK!= 1);

        TRISB=0b0000000000000000;		 	  	 //Configura o PORTB;
	TRISA=0b0000000000000000;		 	  	 //Configura o PORTA;

	// Analog pin for POT already initialized in ADC init subroutine

        /*Função para iniciar os imput captures para os sensores hall do motor
        *
        *RPI32 - RB0 - IC1 --> Hall 1
        *RPI33 - RB1 - IC2 --> Hall 2
        *RP39 - RB7 - IC3  --> Hall 3*/

        PPSInput(IN_FN_PPS_IC1, IN_PIN_PPS_RPI32); // Maps IC1 input to RPI32 pin
        PPSInput(IN_FN_PPS_IC2, IN_PIN_PPS_RPI33); // Maps IC2 input to RPI33 pin
        PPSInput(IN_FN_PPS_IC3, IN_PIN_PPS_RP39); // Maps IC3 input to R39 pin

	InitADC0();
	InitTMR1();
	InitTMR3();
	timer3avg = 0;
	InitMCPWM();
        Flags.RunMotor = 1;
	InitIC();
        InitStatusLED();
        InitOUT_5();

        for(i = 0;i<256;i++)
	{
		RAMBuffer[i] = i;	//Initlize RAMBuffer with some value
							//in case MasterI2C device wants to read
							//before it writes to it.
	}

        I2C1_PICs();
	Flags.Direction = 1;				// initialize direction CW
        RESET8313N = 0;
        SLEEP8313N = 0;
        MDC = 300; //Valores variam de PTPER a 0; - 0 = 100%
        

        while(1)
	{
         maquinaestados = RAMBuffer[0];
         if (FAULT8313N)
         {
           maquinaestados = 0;  
         }
         maquinaestados = 3;

            switch (maquinaestados)
            {
            case 0://Estado 0 --> Modo Falha/Desligado
                SLEEP8313N = 0;
                RESET8313N = 0;
                LED = 1;
            break;
            case 1://Estado 1 --> Modo Modo automático
                SLEEP8313N = 1;
                RESET8313N = 1;
                LED = 0;
                //calculasetpoint(RAMBuffer[20]);
                setpoint = 2000;
            break;
            case 2://Estado 1 --> Modo Modo Manual
                SLEEP8313N = 1;
                RESET8313N = 1;
                Flags.Direction = RAMBuffer[15];
                MDC = RAMBuffer[16]<<8+RAMBuffer[17];
            break;
            case 3:
                SLEEP8313N = 1;
                RESET8313N = 1;
                LED = 1;
                for (i=0;i<=10;i++)
                    {
                    DelayNmSec(10000); //Delay de 10s
                    }
                if (LED == 1)
                LED = 0;
                else
                LED = 1;
                switch(controleteste)
                {
                    case 0:
                setpoint = 0;
                controleteste = 2;
                    break;
                    case 1:
                setpoint = 2000;
                controleteste = 2;
                    break;
                    case 2:
                setpoint = 6000;
                controleteste = 3;
                    break;
                    case 3:
                setpoint = 2000;
                controleteste = 4;
                    break;
                case 4:
                setpoint = 0;
                controleteste = 5;
                    break;
                    case 5:
                setpoint = -2000;
                controleteste = 6;
                    break;
                    case 6:
                setpoint = -6000;
                controleteste = 7;
                    break;
                    case 7:
                setpoint = -2000;
                controleteste = 8;
                    break;
                    case 8:
                setpoint = 0;
                controleteste = 1;
                    break;
                }
            break; 
            }    
            
           
            //Atualiza Endereços de memória
            RAMBuffer[10] = PLED;
            RAMBuffer[11] = PRESET8313N;
            RAMBuffer[12] = PSLEEP8313N;
            RAMBuffer[13] = FAULT8313N;
            RAMBuffer[14] = Flags.RunMotor;
            RAMBuffer[15] = Flags.Direction;
            RAMBuffer[18] = MDC>>8;
            RAMBuffer[19] = MDC&0x00FF;

        //DelayNmSec(100);                 // Sample for 100 us
        //AD1CON1bits.SAMP = 0;         // Start the conversion
        //while (!AD1CON1bits.DONE);    // Wait for the conversion to complete
        ///AD1CON1bits.DONE = 0;         // Clear conversion done status bit
        //ADCValue = ADC1BUF0;          // Read the ADC conversion result

        //RAMBuffer[10] = ADCValue>>8;;
        //RAMBuffer[11] = ADCValue&0x00FF;

        

        //RAMBuffer[32] = timer3avg*60*234575;

		/*while(S2)					// wait for start key hit
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
		}*/
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