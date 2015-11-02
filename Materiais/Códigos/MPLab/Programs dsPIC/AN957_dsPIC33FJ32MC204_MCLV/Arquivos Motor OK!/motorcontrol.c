#include <stdio.h>
#include <stdlib.h>
#include "p33EP32MC202.h"
#include "SensoredBLDC.h"
#include "motorcontrol.h"

int state;

void motorcontrol (int state)
{
 switch(state){
        case 0:
        EN1 = 0;
        IOCON1bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON1bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        EN2 =0;
        IOCON2bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON2bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        EN3 =0;
        IOCON3bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON3bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        break;
        case 1:
        EN1 = 0;
        IOCON1bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON1bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        EN2 =1;
        IOCON2bits.OVRENH = 0;  //Turn overide off for high pin - PWM Enabled
        EN3 =1;
        IOCON3bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON3bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        break;
        case 2:
        EN1 =1;
        IOCON1bits.OVRENH = 0;  //Turn overide off for high pin - PWM Enabled
        EN2 =0;
        IOCON2bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON2bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        EN3 =1;
        IOCON3bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON3bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        break;
        case 3:
        EN1 =1;
        IOCON1bits.OVRENH = 0;  //Turn overide off for high pin - PWM Enabled
        EN2 =1;
        IOCON2bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON2bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        EN3 =0;
        IOCON3bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON3bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        break;
        case 4:
        EN1 =0;
        IOCON1bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON1bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        EN2 =1;
        IOCON2bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON2bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        EN3 =1;
        IOCON3bits.OVRENH = 0;  //Turn overide off for high pin - PWM Enabled
        break;
        case 5:
        EN1 =1;
        IOCON1bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON1bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        EN2 =0;
        IOCON2bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON2bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        EN3 =1;
        IOCON3bits.OVRENH = 0;  //Turn overide off for high pin - PWM Enabled
        break;
        case 6:
        EN1 =1;
        IOCON1bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON1bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        EN2 =1;
        IOCON2bits.OVRENH = 0;  //Turn overide off for high pin - PWM Enabled
        EN3 =0;
        IOCON3bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON3bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        break;
        case 7:
        EN1 = 0;
        IOCON1bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON1bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        EN2 =0;
        IOCON2bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON2bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        EN3 =0;
        IOCON3bits.OVRENH = 1;  //Turn overide ON for high pin - PWM OFF
        IOCON3bits.OVRDAT1 = 1; // PWM High Pin override output is off = 0;
        break;
    }
}
