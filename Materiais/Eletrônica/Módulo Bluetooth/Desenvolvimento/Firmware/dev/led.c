/**
 *  Lida com os Leds
 *
 */

#include "led.h"

void led_erro(void){
   
}

void led_battery_low(void){

}

void led_battery_ok(void){

}

void led_conexao_ok(void){

}

void led_conexao_erro(void){

}

void led_enable(void){
    output_high(PORTB, PIN_LEDR);
    output_high(PORTB, PIN_LEDG);
    output_high(PORTB, PIN_LEDB);
}

void led_disable(void){
    output_low(PORTB, PIN_LEDR);
    output_low(PORTB, PIN_LEDG);
    output_low(PORTB, PIN_LEDB);
}

/**
 *  Pisca leds
 */
void led_blink(void)
{
    output_low(PORTB, PIN_LEDR);
    output_low(PORTB, PIN_LEDG);
    output_low(PORTB, PIN_LEDB);

    _delay_ms(500);
   
    //output_high(PORTB, PIN_LEDR);
    //output_high(PORTB, PIN_LEDG);
    output_high(PORTB, PIN_LEDB);

    _delay_ms(500);
}


