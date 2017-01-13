#include "stm32f401xe.h"
#include "core_cm4.h"
#include "cmsis_gcc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <rozne.h>
#include <lcd.h>


#define GPIOB_8_bb *((volatile unsigned long*) BITBAND_PERI(&GPIOB->ODR,8))

#define LedOn 	GPIOA->BSRR = GPIO_BSRR_BS_5; //set bit atomic
#define LedOff 	GPIOA->BSRR = GPIO_BSRR_BR_5; //reset bit atomic


int main(void)
{
	SCB->CPACR |= (0xF << 20); //Enable FPU

	delay_init();
	led_init();
	usart2_init();

	LedOn;

	LCDT_init();

	uart_sendstr("\r\n");
	uart_sendstr("INIT");

	uart_sendstr("\r\n");
//	uart_sendnum(dane);

	int q=0;

	while (1) {

		//delay_ms(50);
		//delay_ms(50);
		//LCDT_init();
		fill_rect(0,0,200,250,q);
		q++;
	}

}


void SysTick_Handler(void) {
	GPIOA->ODR ^= GPIO_ODR_ODR_5;
}
