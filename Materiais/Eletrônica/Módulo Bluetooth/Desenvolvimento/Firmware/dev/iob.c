#include "iob.h"

/* Funcoes de uso geral */


/**
 * Inicializa I/O configurando direcao
 * TODO: Verificar pull-up 
 *  Não esta funcionando a chamada de função
 *  parece algum erro de copilacao
 *
 * LEDs e Serial
 */

inline void io_init(void)
{
    // LED 	   : Output
    set_output(DDRB,PIN_LEDR);
    set_output(DDRB,PIN_LEDG);
    set_output(DDRB,PIN_LEDB);

    // Botao
    // PD2 (PCINT0 pin) is now an input
    // PD2 is now an input with pull-up enabled
	// #TODO: Revisar PD2
    DDRD &= ~(1 << DDD2);      // Clear the PD2 pin
    PORTD |= (1 << PORTD2);    // turn On the Pull-up

    // uart Tx : Output
    set_output(DDRD,PIN_TX);

}

int io_botao(void){
	
}
