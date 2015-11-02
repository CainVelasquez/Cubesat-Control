/**
 * hm10 module comunicacao
 */

#include "hm10.h"

int hm10_init(void){

	/* Ativa modulo */
	hm10_on();
  
	_delay_ms(1000); 

    /*	
	uint8_t i;
	for(i=0;i<250; i++){
		//uart_put("AT"); 
		uart_putchar('A');
		uart_putchar('T');
		//uart_put("AT"); 
		_delay_ms(400);
	}

	return(1);
    */

	/* Reseta config para padrão */
	uart_put("AT+RENEW");
   	_delay_ms(300);

  	/**
 	 * -> AT+NAME[para1] 
	 * 	<- OK+Set[para1] 
	 * para1 : Nome do dispositivo
	 * 	max length is 12.
   	*/
	uart_put("AT+NAMEPanicoG");
	_delay_ms(400);

  	/**
 	 *-> AT+ROLE[para1]
	 * 	  <- OK+Set[para1]
 	 * para1 : Tipo de interface
	 * 	0: Peripheral
	 * 	1: Central
   	*/
	uart_put("AT+ROLE0");
	_delay_ms(300);

	/**
   	* -> AT+MODE[para1]
	*     <- OK+Set[para1]
	* para1 : Configura 
   	* 	0: Peripheral
   	* 	1: Central
  	*/
 	uart_put("AT+MODE1");
	_delay_ms(300);

 	 /**
   	* When module is powered on, only respond the AT Command, don’t do 
   	* nothing
   	* -> AT+IMME[para1]
   	*  <- OK+ Set[para1]
   	*  para1: Configura
   	*    0: Inicializa normalmente
   	*    1: Só recebe comandos AT
   	*/
	uart_put("AT+IMME1");
	_delay_ms(300);

	/**
	 * Coloca o modulo em modo sleep
	 */
	uart_put("AT+SLEEP");
	_delay_ms(300);

	return(1);
}

/**
 * Inicializa Bluetooth
 */
int hm10_start(void){

  hm10_cmd_write("AT+START");
  return 1;
}

/**
 *  Limpa uart buffer
 */

/**
 *  Checa conexao serial com o modulo
 */
int hm10_check_connection(void){

  /* checa conexão */
  hm10_cmd_write("AT");
  if (hm10_cmd_check("OK",2)) ;
    return 0; // Erro

   return 1;   // Ok
}

/**
 *  Checa se dispositivo está emparelhado
 */
int hm10_check_emparelhamento(void){
  return 0;
}

/**
 * Coloca modo em sleep mode.
 */
void hm10_off(void){

	/* Configura saída para 0 */
	PORTD &= ~(0<<PIN_HM10_RST);		
}

/**
 *  Ativa modulo
 */
void hm10_on(void){

	/*Configura saída para 1 */
	PORTD |= (1<<PIN_HM10_RST);
	
    _delay_ms(200);

	/* send via uart mais de 80 caracteres */
	uint8_t i;
	//for(i=0; i<100 i++); 
		                    uart_put("ATATATATATATATATATATATATATATATATAAATATATTATATATATATTATATATATTATATATATTATATATTATATATATTATATTATATTATTATATATTATATATATATTATATATATTATATATA");
	_delay_ms(300);
	uart_put("AT+START");
	_delay_ms(300);

}


/**
 *  Checa se comando foi bem sucedido
 */
int hm10_cmd_check(char *msg, char n){
 
  /* variável auxiliar */
  char s[16];
  
  /* busca dado na serial */
  uart_get(s, n);

  /* Compara string */ 
  if(!strcasecmp(s,msg)) 
    return 1;

  /* ok */
  return 0;
}

/**
 *  Escreve comando no modulo
 */
void hm10_cmd_write(char *s){
  uart_put(s);
}
