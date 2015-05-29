/*
    3-26-08
    Nathan Seidle
    nathan@sparkfun.com
    Copyright Spark Fun Electronics© 2008
    
    Software I2C control
    PIC 16F88
    
    Reading and writing to HMC6343
    
    This is a internally tilt compensated compass.
*/
#define Clock_8MHz
#define Baud_9600

#include "c:\Global\Code\C\16F88.h"  // device dependent interrupt definitions

#pragma origin 4

#define STATUS_LED PORTB.3

#define SCL     PORTA.1
#define SDA     PORTA.0 

#define WRITE_sda() TRISA = TRISA & 0b.1111.1110 //SDA must be output when writing
#define READ_sda()  TRISA = TRISA | 0b.0000.0001 //SDA must be input when reading - don't forget the resistor on SDA!!

#define I2C_DELAY   10

#define ACK     1
#define NO_ACK  0

#define DEVICE_WRITE    0x32 //Default HMC6343 I2C address - write
#define DEVICE_READ     0x33 //Default HMC6343 I2C address - read

void boot_up(void);

void send_command(uns8 command_byte);
uns8 read_eeprom(uns8 register_name);
void write_register(uns8 register_name, uns8 register_value);

void i2c_ack_polling(uns8 device_address);
void i2c_start(void);
void i2c_stop(void);
uns8 i2c_read_byte(void); //No ACK
uns8 i2c_read_bytes(void); //9th bit ACK
bit i2c_send_byte(uns8 out_byte);

void delay_ms(uns16 x);
void delay_us(uns16 x);
uns8 bin2Hex(char x);
void printf(const char *nate, int16 my_byte);

uns8 hmc_data[6];

void main(void)
{
    uns8 choice;
    
    boot_up(); //Init ports and settings
        
    STATUS_LED = 0;

    printf("\nHMC6343 Testing:\n\n\r", 0);

    delay_ms(100);
    
    uns8 response;

    response = read_eeprom(0x00); //Who am I
    printf("\n\rWho am I (should be 0x32): %h\n\r", response);

    while(1)
    {
        STATUS_LED ^= 1;

        /*if(RCIF)
        {
            choice = RCREG;
            if(choice == 'x') break;
        }*/
        
        send_command(0x50); //Post heading data to hmc_data array
        
        printf("head=%d ", hmc_data[0]);
        printf("%d ", hmc_data[1]);
        printf("pitch=%d ", hmc_data[2]);
        printf("%d ", hmc_data[3]);
        printf("roll=%d ", hmc_data[4]);
        printf("%d ", hmc_data[5]);

        printf("\n", 0);
        
        delay_ms(200);
    }

    while(1);

}//End Main

void boot_up(void)
{
    //Setup Ports
    ANSEL = 0b.0000.0000; //Turn off A/D

    PORTA = 0b.0000.0000;
    TRISA = 0b.0000.0000;  //0 = Output, 1 = Input

    //Output PB7, PB6, PB4 - Input PB1
    PORTB = 0b.1100.0000;
    TRISB = 0b.0000.0110;   //0 = Output, 1 = Input RX on RB2

    //OPREG = 0b.1111.1111; //Enable pull-ups

    //Setup the hardware UART module
    //=============================================================
    SPBRG = 51; //8MHz for 9600 inital communication baud rate
    //SPBRG = 129; //20MHz for 9600 inital communication baud rate

    TXSTA = 0b.0010.0100; //8-bit asych mode, high speed uart enabled
    RCSTA = 0b.1001.0000; //Serial port enable, 8-bit asych continous receive mode
    //=============================================================
}

//Gets bulk data for the four different post types (Accel, Mag, Heading, Tilt)
void send_command(uns8 command_byte)
{
    uns8 in_byte, i;
    
    i2c_ack_polling(DEVICE_WRITE);

    i2c_start();
    i2c_send_byte(DEVICE_WRITE); 
    i2c_send_byte(command_byte); //Send command
    //i2c_stop();

    i2c_start(); //Repeat start (SR)
    i2c_send_byte(DEVICE_READ); //Now ask the IC to report on the last command
    for(i = 0 ; i < 6 ; i++)
    {
        in_byte = i2c_read_bytes();
        hmc_data[i] = in_byte; //Read in 6 data bytes
    }
    i2c_stop();
    i2c_stop();
}

//Reads a register
uns8 read_eeprom(uns8 register_name)
{
    uns8 in_byte;
    
    i2c_ack_polling(DEVICE_WRITE);

    i2c_start();
    i2c_send_byte(DEVICE_WRITE); 
    i2c_send_byte(0xE1); //Read from EEPROM
    i2c_send_byte(register_name); //Write register address   
    //i2c_stop();

    i2c_start(); //Repeat start (SR)
    i2c_send_byte(DEVICE_READ); //Now ask the IC to report on the last command
    in_byte = i2c_read_byte();
    i2c_stop();

    return(in_byte);
}

//Write to a register
void write_register(uns8 register_name, uns8 register_value)
{
    i2c_ack_polling(DEVICE_WRITE);

    i2c_start();
    i2c_send_byte(DEVICE_WRITE); 
    i2c_send_byte(register_name); //Write register address
    i2c_send_byte(register_value); //Write data
    i2c_stop();

    //Return nothing
}

//Software I2C Routines
//====================================
void i2c_ack_polling(uns8 device_address)
{
    while(1)
    {
        i2c_start();
        if (i2c_send_byte(device_address) == ACK) break;
    }
    i2c_stop();
}

void i2c_start(void)
{
    WRITE_sda();
    SDA = 1;
    delay_us(I2C_DELAY);

    SCL = 1;
    delay_us(I2C_DELAY);

    SDA = 0;
    delay_us(I2C_DELAY);
}

//The I2C Clock has a minimum of 2us high time and 2us low time
void i2c_stop(void)
{
    SCL = 0;
    delay_us(I2C_DELAY);

    WRITE_sda();
    
    SDA = 0;
    delay_us(I2C_DELAY);

    SCL = 1;
    delay_us(I2C_DELAY);

    SDA = 1;
    delay_us(I2C_DELAY);
}

//The I2C Clock has a minimum of 2us high time and 2us low time
//8MHz = 0.5us per instruction
uns8 i2c_read_byte(void)
{
    int j, in_byte;

    SCL = 0;

    READ_sda();

    for(j = 0 ; j < 8 ; j++)
    {
        SCL = 0;
        delay_us(I2C_DELAY);

        SCL = 1;
        delay_us(I2C_DELAY);

        in_byte = rl(in_byte);
        in_byte.0 = SDA;
    }

    //Send 9th bit acknowledge
/*
    For single byte reads, there is NMAK or no master acknowledge
    SCL = 0;
    WRITE_sda();
    SDA = 0;
    delay_us(I2C_DELAY);
    SCL = 1;

    delay_us(I2C_DELAY);
    SCL = 0;

    delay_us(I2C_DELAY);
    SDA = 1;
    while(1);
*/
    return(in_byte);
}

//The I2C Clock has a minimum of 2us high time and 2us low time
//8MHz = 0.5us per instruction
uns8 i2c_read_bytes(void)
{
    int j, in_byte;

    SCL = 0;

    READ_sda();

    for(j = 0 ; j < 8 ; j++)
    {
        SCL = 0;
        delay_us(I2C_DELAY);

        SCL = 1;
        delay_us(I2C_DELAY);

        in_byte = rl(in_byte);
        in_byte.0 = SDA;
    }

    //Send 9th bit acknowledge
    SCL = 0;
    WRITE_sda();
    SDA = 0;
    delay_us(I2C_DELAY);
    SCL = 1;

    delay_us(I2C_DELAY);
    SCL = 0;

    delay_us(I2C_DELAY);
    SDA = 1;

    return(in_byte);
}

//The I2C Clock has a minimum of 2us high time and 2us low time
//8MHz = 500ns per instruction
bit i2c_send_byte(uns8 out_byte)
{
    uns8 i;

    WRITE_sda();

    for(i = 0 ; i < 8 ; i++)
    {
        SCL = 0;
        delay_us(I2C_DELAY);

        out_byte = rl(out_byte);
        SDA = Carry;
        delay_us(5);

        SCL = 1;
        delay_us(I2C_DELAY);
    }

    //Read ack
    SCL = 0;
    delay_us(I2C_DELAY);

    READ_sda();

    SCL = 1;
    delay_us(I2C_DELAY);

    //Wait for IC to acknowledge
    for(i = 0 ; i < 255 ; i++)
        if(SDA == 0) break;

    SCL = 0;
    delay_us(I2C_DELAY);

    if (i == 255) return(NO_ACK);
    
    return(ACK);
}
//====================================

//General short delay
void delay_ms(uns16 x)
{
    //Clocks out at 1006us per 1ms
    uns8 y, z;
    for ( ; x > 0 ; x--)
        for ( y = 0 ; y < 4 ; y++)
            for ( z = 0 ; z < 69 ; z++);
}

//Really short delay
void delay_us(uns16 x)
{
    //Calling with 1us returns 7.5us
    //Calling with 10us returns 48
    //Calling with 1000us returns 4.5ms
    while(--x); 
}

//Sends nate to the Transmit Register
void putc(uns8 nate)
{
    while(TXIF == 0);
    TXREG = nate;
}

uns8 getc(void)
{
    while(RCIF == 0);
    return (RCREG);
}    

uns8 scanc(void)
{
    uns16 counter = 0;
    
    //CREN = 0;
    //CREN = 1;
    
    RCIF = 0;
    while(RCIF == 0)
    {
        counter++;
        if(counter == 1000) return 0;
    }
    
    return (RCREG);
}   

//Returns ASCII Decimal and Hex values
uns8 bin2Hex(char x)
{
   skip(x);
   #pragma return[16] = "0123456789ABCDEF"
}

//Prints a string including variables
void printf(const char *nate, int16 my_byte)
{
    uns8 i, k, m, temp;
    uns8 high_byte = 0, low_byte = 0;
    uns8 y, z;
    
    uns8 decimal_output[5];
    
    for(i = 0 ; ; i++)
    {
        k = nate[i];

        if (k == '\0') 
            break;

        else if (k == '%') //Print var
        {
            i++;
            k = nate[i];

            if (k == '\0') 
                break;
            else if (k == '\\') //Print special characters
            {
                i++;
                k = nate[i];
                
                putc(k);
            } //End Special Characters
            else if (k == 'b') //Print Binary
            {
                for( m = 0 ; m < 8 ; m++ )
                {
                    if (my_byte.7 == 1) putc('1');
                    if (my_byte.7 == 0) putc('0');
                    if (m == 3) putc(' ');
                    
                    my_byte = my_byte << 1;
                }
            } //End Binary               
            else if (k == 'd') //Print Decimal
            {
                //Print negative sign and take 2's compliment
                
                if(my_byte < 0)
                {
                    putc('-');
                    my_byte *= -1;
                }
                
                if (my_byte == 0)
                    putc('0');
                else
                {
                    //Divide number by a series of 10s
                    for(m = 4 ; my_byte > 0 ; m--)
                    {
                        temp = my_byte % (uns16)10;
                        decimal_output[m] = temp;
                        my_byte = my_byte / (uns16)10;               
                    }
                
                    for(m++ ; m < 5 ; m++)
                        putc(bin2Hex(decimal_output[m]));
                }
    
            } //End Decimal
            else if (k == 'h') //Print Hex
            {
                //New trick 3-15-04
                putc('0');
                putc('x');
                
                if(my_byte > 0x00FF)
                {
                    putc(bin2Hex(my_byte.high8 >> 4));
                    putc(bin2Hex(my_byte.high8 & 0b.0000.1111));
                }

                putc(bin2Hex(my_byte.low8 >> 4));
                putc(bin2Hex(my_byte.low8 & 0b.0000.1111));

                /*high_byte.3 = my_byte.7;
                high_byte.2 = my_byte.6;
                high_byte.1 = my_byte.5;
                high_byte.0 = my_byte.4;
            
                low_byte.3 = my_byte.3;
                low_byte.2 = my_byte.2;
                low_byte.1 = my_byte.1;
                low_byte.0 = my_byte.0;
        
                putc('0');
                putc('x');
            
                putc(bin2Hex(high_byte));
                putc(bin2Hex(low_byte));*/
            } //End Hex
            else if (k == 'f') //Print Float
            {
                putc('!');
            } //End Float
            else if (k == 'u') //Print Direct Character
            {
                //All ascii characters below 20 are special and screwy characters
                //if(my_byte > 20) 
                    putc(my_byte);
            } //End Direct
                        
        } //End Special Chars           

        else
            putc(k);
    }    
}