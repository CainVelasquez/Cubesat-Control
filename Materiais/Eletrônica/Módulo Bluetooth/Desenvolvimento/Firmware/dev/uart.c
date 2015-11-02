#include <avr/io.h>
#include <iob.h> 
#include "uart.h"

/* system */
#define F_CPU		1000000L //12Mhz

/* serial */
#define BAUD 		9600
#include <util/setbaud.h>

/* http://www.cs.mun.ca/~rod/Winter2007/4723/notes/serial/serial.html */
void uart_init(void) {

    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    
#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00) ; /* 8-bit data , no parity, one stop bit*/ 
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */    
}

/**
 *  Escreve um vetor na serial
 */
void uart_put(char *s){
      while (*s)
   	   uart_putchar(*s++);
}

/**
 *  Le um vetor da serial
 *  TODO: Verificar
 */
void uart_get(char *s, char n){
	int i;
	for(i=0; i<=n; i++){
		*s = uart_getchar(s);
    s++;
  }
}

/**
 * Funcoes internas
 */

/**
 *  Escreve um char na serial
 */
void uart_putchar(char c) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

/**
 *  Le um char da serial
 */
char uart_getchar(char *stream) {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}
