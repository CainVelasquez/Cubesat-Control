/**
 * @file main.c
 *
 * Firmeware Botão de Panico André
 *
 * Rafael Corsi / corsiferrao@gmail.com
 * Arnaldo Viana
 *
 * Resumo:
 * 	Software de interface com o Modulo HM10
 *
 * ROADMAP :
 *            IO        - ok
 *            INT       - ok
 *            Powersave - ok
 *            Serial    - n
 *            HM10      - n
 *            LEDs      - n
 *            Verificar - n
 *
 * Copilar
 * make hex
 *
 * Gravar com o make
 * make flashwrite
 *
 * Gravação:
 * sudo avrdude -c usbasp -p m328p -P /dev/ttyusb0 -e -U flash:w:panico.hex
 *
 * lfuse = 0xFF
 *
 *
 * avrdude -p 328p -u -U lfuse:w:0xff:m 
 *
 * Revisões:
 * 	18.4.14 : Arquivo criado
 */

/**
 *	Includes
 */

#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "iob.h"
#include "led.h"
#include "hm10.h"
#include "uart.h"


/**
 *	Defines
 */

/* tipo de variaveis */


/* system */
#define F_CPU		16000000 //4mhz
#define __avr_atmega328p__

/* serial */

#define BAUD 		9600

/**
 * Variáveis Globais
 */


/**
 *	Prototipo
*/


/**
 * Funcoes locais
 */

void var_init(void){

}

/**
* pg. 66
* Low level interrupts on INT0/INT1 are detected asynchronously. This implies
* that these interrupts can be used for waking the part also from sleep modes
* other than Idle mode.The I/O clock is halted in all sleep modes except Idle
* mode.
*
* No prototipo 1 a interrupcao está no pino PD7 que é PCINT23
*
* do datasheet: The pin change interrupt PCI2 will trigger if any enabled
* PCINT[23:16] pin toggles ... The PCMSK2, PCMSK1 and PCMSK0
* Registers control which pins contribute to the pin change interrupts. Pin 
* change interrupts on PCINT23...0 are detected asynchronously
*/
void int_enable(void){
  EICRA |= (1 << ISC00);    // set INT to trigger on Low logic
  EIMSK |= (1 << INT0);     // Turns on INT
}

/**
* pg. 66
* Low level interrupts on INT0/INT1 are detected asynchronously. This implies
* that these interrupts can be used for waking the part also from sleep modes
* other than Idle mode. The I/O clock is halted in all sleep modes except
* Idle  mode.
*
* TODO: revisar com o master
*/
void int_disable(void){
  EIMSK &= ~(1 << INT0);    // Turns off INT
}

/**
* pg. 34
* When the SM2..0 bits are written to 010, the SLEEP instruction makes the MC
* U e nter Power-down mode. In this mode, the External Oscillator is stopped,
* while the external interrupts, the Two-wire Serial Interface address watch,
* and the Watchdog continue operating (if enabled). Only an External Reset, a
* Watchdog Reset, a Brown-out Reset,  a Two-wire Serial Interface address
* ch interrupt, or an external level interrupt  on INT0 or INT1, can wake up
* the MCU. This sleep mode basically halts all generated  clocks, allowing op
* eration of asynchronous mod-ules only.
*/
void pwr_init(void){
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

/**
*	main
*/
int main(void){
	// Inicializa IOs
    io_init();

    // Inicializa variáveis globais
	var_init();

	// Habilita interrupcao
	int_enable();

	// Configura modo sleep
	pwr_init();

    // configura watchdog
    //wdt_enable(WDTO_1S);

    // Serial
    uart_init(); 

    // hm10
    hm10_init();

    hm10_start();

    //hm10_off();

    // Habilita interrupcoes globais
    sei();

    // loop sleep
    while(1){
	
    }

}

/**
* INT0 interruption
* TODO: depende do pino
*
* Detectado aperto de botão
* ativar bluetooth
*
*/


ISR(INT0_vect){

  // desativar interrupcao
  cli();

  led_blink();
  led_disable();

  uart_putchar(0xFC);

  //hm10_on();

  //hm10_init();

  //hm10_on();
  //hm10_start();
  
  // ativar interrupcao
  sei();
}


ISR(PCINT2_vect){

  // Status da inicialização
  uint8_t hm10_status;
  uint8_t hm10_cnt;

  // HM10 não inicializado
  hm10_status = 0;

  // Zera hm10 status
  hm10_cnt = 0;

  // desativar interrupcao
  cli();

  led_blink();

  // HM10 energiza
  //hm10_on();

  /*
  uint8_t i;
  char dado[] = {0x01, 0xFF, 0x00};
  char dado2[] = {0xFF, 0x01, 0x00};
  for(i=0;i<100;i++){
  	//uart_put(0x00);
	//uart_put(0xFF);
	uart_put("Uv");
 }
 */

  //led_blink();

  // serial
  //hm10_init();


  /*
  // inicialização do modulo
  while(!hm10_status){

    // delay
    _delay_ms(500);

    // checa conexao
    //  0 erro
    //  1 ok
    hm10_status = hm10_check_connection();

    // incrementa contador
    hm10_cnt++;
  }

  // Inicializa modulo hm10
  hm10_init();

  // Checa confirmação de incialização
  //hm10_status;

  // incrementa contador
  //hm10_cnt++;

  // habilita comunicação
  hm10_start();

  // Espera dado
  //hm10_read();

  */
  // Entra em sleep mode
  //hm10_off();

  // ativar interrupcao
  sei();
}


/**
 *	END
 */
