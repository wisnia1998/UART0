//main
#include "MKL25Z4.h"                    // Device header
#include "UART_0.h"
#include "leds.h"

int main(){
	ledsInitialize();
	UART_init(9600);
	int i = 0;
	uint16_t j = 0;
	char a = 0;	
	for(i = 0; i < 100000; i++){};	
	//while(!(UART0_S1 & UART_S1_TDRE_MASK)){}
	print_word("Press 'g' for green led \n\rPress 'r' for red led \n\r");
	FPTB -> PTOR |= (1UL << 18);

	while(1){
		a = recive();
		if( 'r' == a)
		{
			print_num(j);
			print_char('r');
			FPTB -> PTOR |= (1UL << 18);			
		}
		if( 'g' == a)
		{
			j=j+7;
			print_char('g');
			FPTB -> PTOR |= (1UL << 19);
		}
	};
	
	
}
