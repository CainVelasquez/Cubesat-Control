/* 
 * File:   functions_i2c.h
 * Author: felipe
 *
 * Created on 21 de Outubro de 2015, 22:05
 */

#ifndef FUNCTIONS_I2C_H
#define	FUNCTIONS_I2C_H

#ifdef	__cplusplus
extern "C" {
#endif


#define DEVICE_WRITE    0x32 //Default HMC6343 I2C address - write
#define DEVICE_READ     0x33 //Default HMC6343 I2C address - read

extern int hmc_data[7];
extern int hmc_dados[7];
extern long double angulo;

unsigned int read_eeprom(unsigned int register_name);
void send_command(unsigned int command_byte);
void send_command_pic(unsigned int who, unsigned int address, unsigned int command_byte);


#ifdef	__cplusplus
}
#endif

#endif	/* FUNCTIONS_I2C_H */

