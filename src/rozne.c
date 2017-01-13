#include "stm32f401xe.h"
#include "core_cm4.h"
#include "cmsis_gcc.h"
#include <stdio.h>
#include <string.h>
#include "rozne.h"

uint8_t dane;
void  USART2_IRQHandler(void) {
	if ( USART2->SR & USART_SR_RXNE){
		USART2->SR &= ~USART_SR_RXNE; //kasowanie flagi
		dane = USART2->DR;
		USART2->DR = dane;
	}
}

void  USART1_IRQHandler(void) {
	if ( USART1->SR & USART_SR_RXNE){
		USART1->SR &= ~USART_SR_RXNE; //kasowanie flagi
		dane = USART1->DR;
		USART2->DR = dane;
	}
}

void usart2_init() {
	/*
	 * PA2 - USART2_TX
	 * PA3 - USART2_RX
	 */
	 /*  1320 = 10 1 00 10 1000 RX
		Moder = 10
		OTYPER = 1
		OSPEEDR = 00
		PUPDR = 10
	 */
	/*
	    1032 = 10 0 00 00 1000 TX
		Moder = 10
		OTYPER = 0
		OSPEEDR = 00
		PUPDR = 00
	 */
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN | RCC_AHB1ENR_GPIOAEN; //wlczenie usart2 i gpioa
	__DSB();

	GPIOA->MODER |= GPIO_MODER_MODER2_1;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_2;
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR2;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR2;
	GPIOA->AFR[0] |= 0x700; //funkcja alternatywna AF7 dla PA2

	GPIOA->MODER |= GPIO_MODER_MODER3_1;
	GPIOA->OTYPER |= GPIO_OTYPER_OT_3;
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR3;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR3_1;
	GPIOA->AFR[0] |= 0x7000; //funkcja alternatywna AF7 dla PA3

	USART2->BRR = 16000000/9600; //freq/baude
	USART2->CR1 = USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_TE | USART_CR1_RE; //| USART_CR1_TXEIE;

	NVIC_EnableIRQ(USART2_IRQn); //wlaczenie przerwan

}

void usart1_init() {
	/*
	 * PB6 - USART2_TX
	 * PB7 - USART2_RX
	 */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; //rejestr clock enable, bit GPIOB wlaczenie
	__DSB();
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; //wlczenie usart2
	__DSB();

	GPIOB->MODER |= GPIO_MODER_MODER6_1;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_6;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR6;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6;
	GPIOB->AFR[0] |= 0x7000000; //funkcja alternatywna AF7 dla PA2

	GPIOB->MODER |= GPIO_MODER_MODER7_1;
	GPIOB->OTYPER |= GPIO_OTYPER_OT_7;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR7;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR7_1;
	GPIOB->AFR[0] |= 0x70000000; //funkcja alternatywna AF7 dla PA3

	USART1->BRR = 16000000/9600; //freq/baude
	USART1->CR1 = USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_TE | USART_CR1_RE; //| USART_CR1_TXEIE;

	NVIC_EnableIRQ(USART1_IRQn); //wlaczenie przerwan

}

void uart_sendstr(volatile char *dane) {

	while (*dane) {
		while ( !(USART2->SR & 0x00000040));
		USART2->DR = (*dane & (uint16_t)0x01FF);
		*(dane++);
	}
}

void uart_sendnum(volatile int dane) {

	while ( !(USART2->SR & 0x00000040));
	char buf[15]="";
	//itoa(dane,buf,16); //lub to nizej (jak dwojka to 1-0 liczba, normalna liczba to dac 10
	siprintf(buf, "0x%x", dane); //lekka wersja sprintf
	uart_sendstr(buf);


}

void usart_float(double zm) {
	char buf[15]="";
	sprintf(buf, "%f", zm);
	uart_sendstr(buf);
	/*float fNum = 1.2345; //nie sprawdzane ktore wydajniejsze
	int wholeNum = fNum;//wouldn't hurt to cast it to avoid warning
	float kl = fNum - wholeNum;
	int decimalNum = (int) (kl * 10000.0);
	char wholeNumStr[10]="";
	char decNumStr[5]="";
	char decPtStr[1] = ".";
	char numStr[17]="";
	itoa(wholeNum, wholeNumStr,10);
	itoa(decimalNum, decNumStr,10);
	strcpy(numStr, wholeNumStr);
	strcat(numStr, decPtStr);
	strcat(numStr, decNumStr);
	uart_sendstr(numStr);*/
}

/***************************************************************************/


void led_init() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //rejestr clock enable, bit GPIOA wlaczenie
	__DSB(); //blad w errata, czeka na zakonczenie operacji na pamieci
	GPIOA->MODER &= ~GPIO_MODER_MODER5; // wyczyszczenie bitw (ustawienie zer) a potem ustwienie odpowiednich
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR5; //wyczyszczenie

	GPIOA->MODER |= GPIO_MODER_MODER5_0; //jako output pin5 01
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_5; //0 to push-pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_1; //szybkosc, zbocze - high=10
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR5; //no pull-up, pull-down
}

void buttom_init() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; //rejestr clock enable, bit GPIOC wlaczenie
	__DSB();
	GPIOC->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR13; //zerowanie
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR13; //zerowanie

	GPIOC->MODER &= ~GPIO_MODER_MODER13; //jako input pin13, 00
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_1; //szybkosc, zbocze - high=10 bez znaczenia
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_13; //0 - push-pull
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR13_1; // pull-down
}

/***************************************************************************/


volatile uint8_t flag=0;

void delay_us(uint16_t s) { //max s=4000
	TIM2->CNT =0;
	TIM2->ARR = (s*16); //auto-reload, zlicza do tej wartosci od 0, 16 bo 1us to 16 taktow (16MHz ma ustawione proc)
	TIM2->CR1 |= TIM_CR1_CEN; //wlaczenie timera, zaczyna liczyc
	flag=1;
	while(flag);
}

void delay_ms(int s) { //1000=1s
	int i;
	for (i=0; i<s; ++i){
		delay_us(1000);
	}
}

void TIM2_IRQHandler(void) {
	TIM2->SR = ~TIM_SR_UIF; //reset flagi
	flag=0;
}

void delay_init() {
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //wlczenie taktowania? timera
	__DSB();
	TIM2->CR1 |= TIM_CR1_OPM; //one pulse mode, resetuje CEN, dziala tylko raz do przerwania
	TIM2->PSC |= 0; //preskaler = 0
	TIM2->DIER |=TIM_DIER_UIE; //wlaczenie przerwania timera
	NVIC_EnableIRQ(TIM2_IRQn); //wlczenie przerwan
}

/***************************************************************************/

