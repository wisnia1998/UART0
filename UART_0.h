#include "MKL25Z4.h"                    // Device header

static char number[] = {
	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9'
};

void UART_init(uint32_t baud_rate);
void print_char(uint8_t data);
void print_word(const uint8_t *str);
void print_num(uint16_t value);
uint8_t recive();

static uint8_t len_of_num(uint16_t num);
