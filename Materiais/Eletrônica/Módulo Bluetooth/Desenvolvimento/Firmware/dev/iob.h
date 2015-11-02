/* Includes */
#include <avr/io.h>

/* Prototipo */
void io_init(void);

/* IOs */

#define PIN_LEDR	    PB0 // REVISAR COM O MASTER !!!
#define PIN_LEDG	    PB2
#define PIN_LEDB 	    PB1
#define PIN_TX 		    PD1
#define PIN_RX		    PD0
#define PIN_HM10_RST	PD3
#define PIN_HM10_STA	PD7
#define PIN_Botao	    PD2

/* Macros */
#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)


