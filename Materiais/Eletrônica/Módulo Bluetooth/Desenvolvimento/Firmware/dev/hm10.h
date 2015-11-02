#include "iob.h"
#include "uart.h"

#include <avr/io.h>
#include <util/delay.h>
#include <string.h> 

/**
 *  Prototipagem
 */

int hm10_init(void);
int hm10_start(void);

void hm10_off(void);
void hm10_on(void);

int hm10_check_connection(void);
int hm10_cmd_check(char *msg, char n);

void hm10_cmd_write(char *s);
