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

#include "p33EP32MC502.h"
#include "MasterBLDC.h"
#include "functions_i2c.h"

#include <stdio.h>
#include <stdlib.h>
#include <i2c.h>
#include <libq.h>
#include <pps.h>
#include <uart.h>
#include <string.h>

/******************************************************************************/
/* Configuration bits                                                         */
/******************************************************************************/

// Select Internal FRC at POR
_FOSCSEL(FNOSC_PRI & PWMLOCK_OFF & IESO_OFF);
// Enable Clock Switching and Configure POSC in XT mode

_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);

_FPOR(ALTI2C1_ON & ALTI2C2_ON);
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
void I2C2_PICs(void);
void I2C1_IMU(void);
void UART1_Bluetooth(void);

struct MotorFlags Flags;

unsigned int HallValue;
unsigned int timer3value;
unsigned int timer3avg;
unsigned int polecount = 0;
unsigned int dado, dado1, ADCValue;
unsigned int maquinaestados = 0;
unsigned int controle = 1;
unsigned char serialchar;

char buffer[16];
char Txdata[] = {'M', 'i', 'c', 'r', 'o', 'c', 'h', 'i', 'p', ' ', 'I', 'C', 'D', '2', '\n', '\r'};
char Novalinha[] = {'\n', '\r'};

int main(void) {
    unsigned int i;

    TRISB = 0b0000000000000000; //Configura o PORTB;
    TRISA = 0b0000000000000000; //Configura o PORTA;

    InitADC0();

    PPSOutput(OUT_FN_PPS_U1TX, OUT_PIN_PPS_RP43); // Maps RP43 to UART TX
    PPSInput(IN_FN_PPS_U1RX, IN_PIN_PPS_RP42); // Maps RP42 to UART RX

    LED = 0;

    UART1_Bluetooth();

    DelayNmSec(5000); //Delay de 10s

    //InitTMR1();
    InitTMR3();
    //timer3avg = 0;
    //InitIC();
    InitStatusLED();
    InitOUT_5();

    for (i = 0; i < 256; i++) {
        RAMBuffer[i] = i; //Initlize RAMBuffer with some value
        //in case MasterI2C device wants to read
        //before it writes to it.
    }

    I2C2_PICs();
    //I2C1_IMU();

    LED = 1;

    while (1) {
        /*
         Interação para aplicativo
         */
        serialchar = recebe;

        if (serialchar == 'l') {
            LED = 1;
            controle = 1;
            T3CONbits.TON = 1;
        }
        if (serialchar == 'd') {
            LED = 0;
            controle = 0;
            T3CONbits.TON = 0;
        }


        if (serialchar == 'e') {
            if (velocidade>-5000) {
                velocidade = velocidade - 200;
                send_command_pic(64, 20, (velocidade >> 8));
                send_command_pic(64, 21, (velocidade & 0x00FF));
            }
        }
        if (serialchar == 'w') {
            velocidade = velocidade;
        }
        if (serialchar == 'q') {
            if (velocidade < 5000) {
                velocidade = velocidade + 200;
                send_command_pic(64, 20, (velocidade >> 8));
                send_command_pic(64, 21, (velocidade & 0x00FF));
            }
        }
        /*
        sprintf(buffer, "Velocidade:%i", velocidade);
        for (i = 0; i <= (strlen(buffer) + 1); i++) {
            while (BusyUART1());
            putcUART1(buffer[i]);
        }
        while (BusyUART1());
        putcUART1(Novalinha[0]);
        while (BusyUART1());
        putcUART1(Novalinha[1]);*/
        /*
         * Visualização da Serial para testar sistemas de controle
         */
        if (controle) {
            sprintf(buffer, "Angulo Z:%.2f", (double) angulo);
            for (i = 0; i <= (strlen(buffer) + 1); i++) {
                while (BusyUART1());
                putcUART1(buffer[i]);
            }
            while (BusyUART1());
            putcUART1(Novalinha[0]);
            while (BusyUART1());
            putcUART1(Novalinha[1]);

            sprintf(buffer, "Velocidade:%d", velocidade);
            for (i = 0; i <= (strlen(buffer) + 1); i++) {
                while (BusyUART1());
                putcUART1(buffer[i]);
            }
            while (BusyUART1());
            putcUART1(Novalinha[0]);
            while (BusyUART1());
            putcUART1(Novalinha[1]);

            sprintf(buffer, "Erro:%.4f", (double) erro);
            for (i = 0; i <= (strlen(buffer) + 1); i++) {
                while (BusyUART1());
                putcUART1(buffer[i]);
            }
            while (BusyUART1());
            putcUART1(Novalinha[0]);
            while (BusyUART1());
            putcUART1(Novalinha[1]);
        }
    }
}
//---------------------------------------------------------------------
// This is a generic 1ms delay routine to give a 1mS to 65.5 Seconds delay
// For N = 1 the delay is 1 mS, for N = 65535 the delay is 65,535 mS. 
// Note that FCY is used in the computation.  Please make the necessary
// Changes(PLLx4 or PLLx8 etc) to compute the right FCY as in the define
// statement above.

void DelayNmSec(unsigned int N) {
    unsigned int j;
    while (N--)
        for (j = 0; j < MILLISEC; j++);
}