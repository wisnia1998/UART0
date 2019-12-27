#include "UART_0.h"
#define BUS_CLOCK 20971520

void UART_init(uint32_t baud_rate){
	uint32_t divisor;
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);//
	//connect UART to pins for PTE22, PTE23
	PORTA -> PCR[1] |= PORT_PCR_MUX(2);//
	PORTA -> PCR[2] |= PORT_PCR_MUX(2);//
	// ensure tx and rx are disabled before configuration
	UART0->C2 &= ~(UARTLP_C2_TE_MASK | UARTLP_C2_RE_MASK);
	
	UART0 -> C4 |= UART0_C4_OSR(0b1111);//próbkowanie nadmiarowe   16
	UART0 -> BDH |= UART0_BDH_SBR(0b0);					//
	UART0 -> BDL |= UART0_BDL_SBR(0b10001000);	//9600 b/s   136
	// Set baud rate to 9600 baud^
	/*divisor = BUS_CLOCK/(baud_rate * 16);
	UART0->BDH = UART_BDH_SBR(divisor>>8);
	UART0->BDL = UART_BDL_SBR(divisor);*/
	
	// No parity, 8 bits, two stop bits, other settings;
	UART0->C1 = UART0->S2 = UART0->C3 = 0;
	UART0 ->BDH |= UART0_BDH_SBNS_MASK;//bit stopu
	//Enable transmitter and receiver
	UART0->C2 = UART_C2_TE_MASK | UART_C2_RE_MASK;
}

void print_char(uint8_t data){
	while(!(UART0_S1 & UART_S1_TDRE_MASK)){}
	UART0 -> D = data; 
}

void print_word(const uint8_t *str)
{
    while(*str != '\0')
    {
			 while(!(UART0_S1 & UART_S1_TDRE_MASK)){}
        print_char(*str++);
    }
}

static uint8_t len_of_num(uint16_t num){
	if (num >= 10000) { return 5;}
	if (num >= 1000) { return 4;}
	if (num >= 100) { return 3;}
	if (num >= 10) { return 2;}
	return 1;
}

void print_num(uint16_t value){
	static uint8_t len = 1;
	char num_to_print[5];
	len = len_of_num(value);
	for(uint8_t i = 0; i < len; i++){
		num_to_print[i] = value%10;
		value = value/10;
	}
	for(uint8_t i = 0; i < len; i++){
		print_char(number[num_to_print[len - i - 1]]);
	}		
}

uint8_t recive(){
	while(!(UART0->S1 & UART0_S1_RDRF_MASK));
	return UART0 -> D;
}
