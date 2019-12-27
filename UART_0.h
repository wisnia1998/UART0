#include "MKL25Z4.h"                    // Device header


void UART_init(uint32_t baud_rate);
void print_char(uint8_t data);
void print_word(const uint8_t *str);
uint8_t recive();
