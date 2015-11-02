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
//	File:		Init.c
//
//						
// 
// The following files should be included in the MPLAB project:
//
//		SensoredBLDC.c		-- Main source code file
//		Interrupts.c
//		Init.c
//		SensoredBLDC.h		-- Header file
//		p33EP32MC202.gld	-- Linker script file
//				
//
//--------------------------------------------------------------------

#include "p33EP32MC502.h"
#include "MasterBLDC.h"
#include "functions_i2c.h"

#include<uart.h>
#include<i2c.h>
#include<pps.h>

#define USE_AND_OR
#define BRG_VAL 118

extern unsigned char RAMBuffer[256];	//RAM area which will work as EEPROM for Master I2C device
extern unsigned char *RAMPtr;

/*******************************************************************
		Below is the code required to setup the ADC registers for :
		1. 1 channel conversion (in this case AN8)
		2. PWM trigger starts conversion
		3. Pot is connected to CH0 and AN8
		4. Manual Stop Sampling and start converting
		5. Manual check of Conversion complete 
																
*********************************************************************/
void InitADC0(void)
{
       /* Set port configuration */
        ANSELA = ANSELB = 0x0000;
        //ANSELAbits.ANSA0 = 1;             // Ensure AN0/RA0 is analog
        //TRISAbits.TRISA0 = 1;               // Ensure AN0/RA0 is input

        /* Initialize and enable ADC module,  Automatic Sample and Manual Conversion */

        //AD1CON1 = 0x0004;
        /* No channel scan for CH0+, Use MUX A,
	   SMPI = 1 per interrupt, Vref = AVdd/AVss */
        //AD1CON2 = 0x0000;
        /* Set Samples and bit conversion time */
        //AD1CON3 = 0x000F;
        //AD1CON4 = 0x0000;
        /* channel select AN0 */
        //AD1CHS0 = 0x0000;
        //AD1CHS123 = 0x0000;
        //AD1CSSH = 0x0000;
        //AD1CSSL = 0x0000;


 	/* set channel scanning here, auto sampling and convert,
 	   with default read-format mode */
	//AD1CON1 = 0x006C;
	/* select 10-bit, 1 channel ADC operation */
	//AD1CON1bits.AD12B = 0;

	//IFS0bits.AD1IF = 0;
	//IEC0bits.AD1IE = 1;
	//AD1CON1bits.ADON = 1;
        //DelayNmSec(20);
}

/********************************************************************
InitMCPWM, intializes the PWM as follows:
1. FPWM = 39000 hz
2. Independant PWMs
3. Control outputs using OVDCON
4. Set Duty Cycle with the ADC value read from pot
5. Set ADC to be triggered by PWM special trigger
*********************************************************************/

void InitMCPWM(void)
{

    //PTCON2bits.PCLKDIV = 0b010; //PWM input clock prescaled by 1:4
    //Period = 120 MHz / (PTPER * Prescaler)
    //Period = 120 MHz / (40kHz * 4) = 750
    //PTPER = 750;
    //IOCON1bits.PMOD = 01; //Set PWM to Redundant Mode
    //IOCON2bits.PMOD = 01; //Set PWM to Redundant Mode
    //IOCON3bits.PMOD = 01; //Set PWM to Redundant Mode

    //DTR1 = DTR2 = DTR3 = 0;
    //ALTDTR1 = ALTDTR2 = ALTDTR3 = 0;

    //IOCON1bits.PENH = 1;//PWM1 module controls PWM1H pin
    //IOCON1bits.PENL = 0;//GPIO module controls PWM1L pin
    //IOCON2bits.PENH = 1;//PWM1 module controls PWM2H pin
    //IOCON2bits.PENL = 0;//GPIO module controls PWM2L pin
    //IOCON3bits.PENH = 1;//PWM1 module controls PWM3H pin
    //IOCON3bits.PENL = 0;//GPIO module controls PWM3L pin

    //IOCON1bits.POLH = 1;
    //IOCON2bits.POLH = 1;
    //IOCON3bits.POLH = 1;

    //PWMCON1bits.MDCS = 1; //MDC register provides duty cycle information
    //PWMCON2bits.MDCS = 1;
    //PWMCON3bits.MDCS = 1;

    //MDC = 100; // Sets master duty cycle at 10%

    //PTCONbits.PTEN = 1;	 
}
/*********************************************************************
  Function:        void InitICandCN(void)

  Overview:        Configure Hall sensor inputs, one change notification and 
                   two input captures. on IC7 the actual capture value is used
                   for further period calculation

  Note:            None.
********************************************************************/

void InitIC(void)
{
	/*Função para iniciar os imput captures para os sensores hall do motor
        *
        *RPI32 - RB0 - IC1 --> Hall 1
        *RPI33 - RB1 - IC2 --> Hall 2
        *RP39 - RB7 - IC3  --> Hall 3*/

	//TRISBbits.TRISB0= 1;	// Ensure that hall connections are inputs
        //TRISBbits.TRISB1= 1;
        //TRISBbits.TRISB7= 1;
	
	//IC1CON1 = 0x0001; //T3CLK is the clock source of the ICx
        //IC1CON2 = 0x0000;
        //IC2CON1 = 0x0001;//T3CLK is the clock source of the ICx
        //IC2CON2 = 0x0000;
        //IC3CON1 = 0x0001;//T3CLK is the clock source of the ICx
        //IC3CON2 = 0x0000;
	
	//IFS0bits.IC1IF = 0;	// Clear interrupt flag
	//IFS0bits.IC2IF = 0;
	//IFS2bits.IC3IF = 0;

	//IEC0bits.IC1IE = 1;	// Enable interrupt
	//IEC0bits.IC2IE = 1;
	//IEC2bits.IC3IE = 1;

        //IPC0bits.IC1IP = 1; // Set module interrupt priority as 1
        //IPC1bits.IC2IP = 1; // Set module interrupt priority as 1
        //IPC9bits.IC3IP = 1; // Set module interrupt priority as 1
}

/************************************************************************
Tmr3 is used to determine the rotor speed so it is set to count using Tcy/256

*************************************************************************/

void InitTMR3(void)
{
	// MIPs / (Scale * Hz interrupt)
	// For this design, 60 MIPs
	// 5MIP/(64 * 5) = 15625, => PR1 = 15625 for 5Hz interrupt

        T3CON = 0x8020;			// internal Tcy/64 clock
	TMR3 = 0;
	PR3 = 15625;
        //T3CONbits.TON = 1;
        IFS0bits.T3IF = 0;
	IEC0bits.T3IE = 1;
}

void InitTMR1(void)
{
	// MIPs / (Scale * Hz interrupt)
	// For this design, 5 MIPs
	// 5 MIPs/(8 * 1000) = 625, => PR1 = 625 for 1000Hz interrupt

	T1CON = 0x8010;			// internal Tcy/8 clock
	TMR1 = 0;
	PR1 = 625;
	T1CONbits.TON = 1;		// turn on timer 1 
	IFS0bits.T1IF = 0;
	IEC0bits.T1IE = 1;
}
/*
 *Função para configuração do Status LED
 *Pino RA1 - OutPut
 */
void InitStatusLED(void)
{
    TRISAbits.TRISA1 = 0;
}
/*
 *Função para configurar 5 portas para outputs
 * para controle do driver de acinamento do motor
 *
 *OBS:não pode ser configurada junto com o CAN!
 *
 *RB15 - EN1 - PWM1 --> Fase 1 Motor
 *RB13 - EN2 - PWM2 --> Fase 2 Motor
 *RB11 - EN3 - PWM3 --> Fase 3 Motor
 *RA4  - RESET8313N --> Reset do driver motor
 *RB5  - SLEEP8313N --> SLEEP do driver motor
 *
 */
void InitOUT_5(void)
{
    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB11 = 0;
    TRISAbits.TRISA4 = 0;
    TRISBbits.TRISB5 = 0;

}
void I2C2_PICs(void)
{
    /* Baud rate is set for 100 kHz */

  //int config2 = 118;

  /* Configure I2C for 7 bit address mode */

  //int config1 = (I2C2_ON);/*& I2C2_IDLE_CON & I2C2_CLK_REL &
            // I2C2_IPMI_DIS & I2C2_7BIT_ADD &
             //I2C2_SLW_EN & I2C2_SM_EN & I2C2_STR_EN);*/

  //OpenI2C2(config1,config2);

     /*
     PBCLK = 120 Mhz
     Fsck = 1 Mhz
     *  BRG_VAL 	(((1/FSCK-Delay)*PBCLK)-2)
     * BRG = 118
     */
    //CNPUBbits.CNPUB5 = 1;
    //CNPUBbits.CNPUB6 = 1;

    I2C2CON = 0x8000;	//Enable I2C1 module
    //I2C2CON = 0x9040;	//Enable I2C1 module, enable clock stretching

    //I2C2ADD = 0x60;			// 7-bit I2C slave address must be initialised here.
    //I2C2MSK = 0;

    I2C2BRG = 30;

    //_SI2C2IF=0;
    RAMPtr = &RAMBuffer[0];	//set the RAM pointer and points to beginning of RAMBuffer
    Flag.AddrFlag = 0;	//Initlize AddFlag
    Flag.DataFlag = 0;	//Initlize DataFlag
    //_SI2C2IE = 1;
}
void I2C1_IMU(void)
{

	//I2C1CON = 0x8000;	//Enable I2C1 module
	//I2C1ADD = 0x40;			// 7-bit I2C slave address must be initialised here.
        //I2C1MSK = 0;
        //I2C1BRG = 30;

	//_SI2C2IF=0;
	//_SI2C1IE = 0;

}
void UART1_Bluetooth (void)
{
    /* Configure UART1 module to transmit 8 bit data with one stopbit. Also Enable loopback mode  */
    // configure U1MODE
    U1MODEbits.UARTEN = 0; // Bit15 TX, RX DISABLED, ENABLE at end of func

    //U1MODEbits.notimplemented;// Bit14
    U1MODEbits.USIDL = 0; // Bit13 Continue in Idle
    U1MODEbits.IREN = 0; // Bit12 No IR translation
    U1MODEbits.RTSMD = 0; // Bit11 Simplex Mode

    //U1MODEbits.notimplemented;// Bit10
    U1MODEbits.UEN = 0; // Bits8,9 TX,RX enabled, CTS,RTS not
    U1MODEbits.WAKE = 0; // Bit7 No Wake up (since we don't sleep here)
    U1MODEbits.LPBACK = 0; // Bit6 No Loop Back
    U1MODEbits.ABAUD = 0; // Bit5 No Autobaud (would require sending '55')
    U1MODEbits.BRGH = 0; // Bit3 16 clocks per bit period
    U1MODEbits.PDSEL = 0; // Bits1,2 8bit, No Parity
    U1MODEbits.STSEL = 0; // Bit0 One Stop Bit

    // Load a value into Baud Rate Generator.  Example is for 9600.
    // See section 19.3.1 of datasheet.
    // U1BRG = (Fcy/(16*BaudRate))-1
    // U1BRG = (5M/(16*9600))-1
    // U1BRG = 32,55
    U1BRG = 32; // 10Mhz osc, 9600 Baud

    // Load all values in for U1STA SFR
    U1STAbits.UTXISEL1 = 0; //Bit15 Int when Char is transferred (1/2 config!)
    U1STAbits.UTXINV = 0; //Bit14 N/A, IRDA config
    U1STAbits.UTXISEL0 = 0; //Bit13 Other half of Bit15

    //U1STAbits.notimplemented = 0;//Bit12
    U1STAbits.UTXBRK = 0; //Bit11 Disabled
    U1STAbits.UTXEN = 0; //Bit10 TX pins controlled by periph
    U1STAbits.UTXBF = 0; //Bit9 *Read Only Bit*
    U1STAbits.TRMT = 0; //Bit8 *Read Only bit*
    U1STAbits.URXISEL = 0; //Bits6,7 Int. on character recieved
    U1STAbits.ADDEN = 0; //Bit5 Address Detect Disabled
    U1STAbits.RIDLE = 0; //Bit4 *Read Only Bit*
    U1STAbits.PERR = 0; //Bit3 *Read Only Bit*
    U1STAbits.FERR = 0; //Bit2 *Read Only Bit*
    U1STAbits.OERR = 0; //Bit1 *Read Only Bit*
    U1STAbits.URXDA = 0; //Bit0 *Read Only Bit*
    //IPC7 = 0x4400; // Mid Range Interrupt Priority level, no urgent reason
    IFS0bits.U1TXIF = 0; // Clear the Transmit Interrupt Flag
    IEC0bits.U1TXIE = 1; // Dis//Enable Transmit Interrupts
    IFS0bits.U1RXIF = 0; // Clear the Recieve Interrupt Flag
    IEC0bits.U1RXIE = 1; // Enable Recieve Interrupts
    U1MODEbits.UARTEN = 1; // And turn the peripheral on
    U1STAbits.UTXEN = 1;

    TRISBbits.TRISB10 = 1; //U1RX as input
    TRISBbits.TRISB11 = 0; //U1TX as output

}