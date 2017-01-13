#include "stm32f401xe.h"
#include "core_cm4.h"
#include "cmsis_gcc.h"
#include <stdio.h>
#include "lcd.h"
#include "rozne.h"

void LCDT_sw1(int nr, char port);
void LCDT_set_pin(int nr, char port);
void LCDT_reset_pin(int nr, char port);
int LCDT_check_pin(int nr, char port);

uint8_t LCDT_read_pins();
void LCDT_set_pins(uint8_t zm);

void LCDT_reset();

void LCDT_output(int nr, char port);
void LCDT_input(int nr, char port);
void LCDT_all_output();
void LCDT_all_input();

void LCDT_write_reg(uint16_t reg);
void LCDT_write_data(uint8_t reg);
void LCDT_read_reg(uint16_t reg, uint8_t *var1, uint8_t *var2, uint8_t *var3, uint8_t *var4 );

void set_addr_window(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2);

void LCDT_init() {

	delay_us(30);
	//LCDT_sw1(LCDT_RST_pin,LCDT_RST_port); //ustawienie pinow jako output
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	__DSB();
	GPIOC->MODER &= ~GPIO_MODER_MODER1; //zerowanie
	GPIOC->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR1; //zerowanie
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR1;

	GPIOC->MODER |= GPIO_MODER_MODER1_0; //jako output
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_1; //0 - push-pull
	GPIOC->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR1; //speed low 00
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR1_0  ; //pullup
	GPIOC->BSRR = GPIO_BSRR_BS_1; //1 na start

	LCDT_sw1(LCDT_CS_pin,LCDT_CS_port);
	LCDT_sw1(LCDT_RS_pin,LCDT_RS_port);
	LCDT_sw1(LCDT_WR_pin,LCDT_WR_port);
	LCDT_sw1(LCDT_RD_pin,LCDT_RD_port);
	LCDT_sw1(LCDT_D0_pin,LCDT_D0_port);
	LCDT_sw1(LCDT_D1_pin,LCDT_D1_port);
	LCDT_sw1(LCDT_D2_pin,LCDT_D2_port);
	LCDT_sw1(LCDT_D3_pin,LCDT_D3_port);
	LCDT_sw1(LCDT_D4_pin,LCDT_D4_port);
	LCDT_sw1(LCDT_D5_pin,LCDT_D5_port);
	LCDT_sw1(LCDT_D6_pin,LCDT_D6_port);
	LCDT_sw1(LCDT_D7_pin,LCDT_D7_port);

	LCDT_all_output();

	LCDT_set_pin(LCDT_RST_pin,LCDT_RST_port);
	LCDT_set_pin(LCDT_CS_pin,LCDT_CS_port);
	LCDT_set_pin(LCDT_WR_pin,LCDT_WR_port);
	LCDT_set_pin(LCDT_RD_pin,LCDT_RD_port);
	LCDT_set_pin(LCDT_RS_pin,LCDT_RS_port);

	LCDT_reset();

	uint8_t x=0, y=0, z=0, m=0;

	delay_ms(120);

	//LCDT_read_reg(0x04,&x,&y,&z,&m);

	//LCDT_write_reg(0x01);

	//delay_ms(50);


	LCDT_write_reg(0x01); //soft reset	//st7789v
	LCDT_write_reg(0x11);	//exit sleep mode
	delay_ms(100);
	LCDT_write_reg(0x36);
	LCDT_write_data(0x80); //MADCTL memory data access control
	LCDT_write_reg(0x3A);
	LCDT_write_data(0x55); //colmod interface pixel format
	LCDT_write_reg(0xB2);	//porctrk
	LCDT_write_data(0x0C);
	LCDT_write_data(0x0C);
	LCDT_write_data(0x00);
	LCDT_write_data(0x33);
	LCDT_write_data(0x33);
	LCDT_write_reg(0xB7);	//gate control
	LCDT_write_data(0x35);
	LCDT_write_reg(0xBB);	//vcom setting
	LCDT_write_data(0x2B);
	LCDT_write_reg(0xC0);	//lcm control
	LCDT_write_data(0x04);
	LCDT_write_reg(0xC2);	//vdh and rh enable
	LCDT_write_data(0x01);
	LCDT_write_data(0xFF);
	LCDT_write_reg(0xC3);	//vrh set
	LCDT_write_data(0x11);
	LCDT_write_reg(0xC4);	//vdv set
	LCDT_write_data(0x20);
	LCDT_write_reg(0xC6);	//frame rate control in normal mode
	LCDT_write_data(0x0F);
	LCDT_write_reg(0xD0);	//power control 1
	LCDT_write_data(0xA4);
	LCDT_write_data(0xA1);
	LCDT_write_reg(0xE0);	//positive voltage gamma
	LCDT_write_data(0xD0);
	LCDT_write_data(0x00);
	LCDT_write_data(0x05);
	LCDT_write_data(0x0E);
	LCDT_write_data(0x15);
	LCDT_write_data(0x0D);
	LCDT_write_data(0x37);
	LCDT_write_data(0x43);
	LCDT_write_data(0x47);
	LCDT_write_data(0x09);
	LCDT_write_data(0x15);
	LCDT_write_data(0x12);
	LCDT_write_data(0x16);
	LCDT_write_data(0x19);
	LCDT_write_reg(0xE1);	//negative voltage gamma
	LCDT_write_data(0xD0);
	LCDT_write_data(0x00);
	LCDT_write_data(0x05);
	LCDT_write_data(0x0D);
	LCDT_write_data(0x0C);
	LCDT_write_data(0x06);
	LCDT_write_data(0x2D);
	LCDT_write_data(0x44);
	LCDT_write_data(0x40);
	LCDT_write_data(0x0E);
	LCDT_write_data(0x1C);
	LCDT_write_data(0x18);
	LCDT_write_data(0x16);
	LCDT_write_data(0x19);
	LCDT_write_reg(0x2A);	//X address set
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0xEF);
	LCDT_write_reg(0x2A);	//y address set
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x01);
	LCDT_write_data(0x3F);
	LCDT_write_reg(0x29);	//display on


	fill_rect(0,0,240,320,0x5500);

	fill_rect(20,20,120,150,0x01);

	//LCDT_read_reg(0x09,&x,&y,&z,&m);

	uart_sendstr("pocz");
	uart_sendstr("\r\n");
	uart_sendnum(x);

	uart_sendstr("\r\n");
	uart_sendnum(y);

	uart_sendstr("\r\n");
	uart_sendnum(z);

	uart_sendstr("\r\n");
	uart_sendnum(m);

	uart_sendstr("\r\n");
	uart_sendstr("konNNNNNNNN");

}

void set_addr_window(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2) {

	LCDT_write_reg(0x2A);	//set cursor
	LCDT_write_data(x1 >> 8);
	LCDT_write_data(x1 & 0xFF);
	LCDT_write_data(x2 >> 8);
	LCDT_write_data(x2 & 0xFF);

	LCDT_write_reg(0x2B);	//set cursor
	LCDT_write_data(y1 >> 8);
	LCDT_write_data(y1 & 0xFF);
	LCDT_write_data(y2 >> 8);
	LCDT_write_data(y2 & 0xFF);

	LCDT_write_reg(0x2C);	//set cursor

}

void fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, int color) {

	set_addr_window(x,x+w-1,y,y+h-1);

	LCDT_reset_pin(LCDT_CS_pin,LCDT_CS_port); //active lcd
	LCDT_set_pin(LCDT_RS_pin,LCDT_RS_port); //data
	uint8_t hi=color >> 8;
	uint8_t lo=color & 0xFF;
	//LCDT_set_pins(hi);
	for (y=h; y>0 ; y--){
		for (x=w; x>0 ; x--){
			//LCDT_write_data(color>>8);
			//LCDT_write_data(color & 0xFF);
			LCDT_set_pins(hi);
			LCDT_reset_pin(LCDT_WR_pin,LCDT_WR_port); //pulse low
			LCDT_set_pin(LCDT_WR_pin,LCDT_WR_port);
			LCDT_set_pins(lo);
			LCDT_reset_pin(LCDT_WR_pin,LCDT_WR_port); //pulse low
			LCDT_set_pin(LCDT_WR_pin,LCDT_WR_port);
		}
	}

	LCDT_set_pin(LCDT_CS_pin,LCDT_CS_port); //deactive lcd
}


void LCDT_write_reg(uint16_t reg) {

	LCDT_reset_pin(LCDT_CS_pin,LCDT_CS_port); //active lcd
	LCDT_reset_pin(LCDT_RS_pin,LCDT_RS_port); //command

	LCDT_set_pin(LCDT_RD_pin,LCDT_RD_port);

	/*LCDT_set_pins(reg>>8);
	LCDT_reset_pin(LCDT_WR_pin,LCDT_WR_port); //pulse low
	LCDT_set_pin(LCDT_WR_pin,LCDT_WR_port);*/

	LCDT_set_pins(reg & 0xFF);
	LCDT_reset_pin(LCDT_WR_pin,LCDT_WR_port); //pulse low
	LCDT_set_pin(LCDT_WR_pin,LCDT_WR_port);

	LCDT_set_pin(LCDT_CS_pin,LCDT_CS_port); //deactive lcd
	LCDT_set_pin(LCDT_RS_pin,LCDT_RS_port); //data

}

void LCDT_write_data(uint8_t reg) {
	LCDT_reset_pin(LCDT_CS_pin,LCDT_CS_port); //active lcd
	LCDT_set_pin(LCDT_RS_pin,LCDT_RS_port); //data

	/*LCDT_set_pins(reg>>8);
	LCDT_reset_pin(LCDT_WR_pin,LCDT_WR_port); //pulse low
	LCDT_set_pin(LCDT_WR_pin,LCDT_WR_port);*/

	LCDT_set_pins(reg);
	LCDT_reset_pin(LCDT_WR_pin,LCDT_WR_port); //pulse low
	LCDT_set_pin(LCDT_WR_pin,LCDT_WR_port);

	LCDT_set_pin(LCDT_CS_pin,LCDT_CS_port); //deactive lcd
}

void LCDT_read_reg(uint16_t reg, uint8_t *var1, uint8_t *var2, uint8_t *var3, uint8_t *var4 ) {

	*var1=0;
	*var2=0;
	*var3=0;
	*var4=0;

	LCDT_reset_pin(LCDT_CS_pin,LCDT_CS_port); //active lcd
	LCDT_reset_pin(LCDT_RS_pin,LCDT_RS_port); //command
	/*LCDT_set_pins(reg>>8);
	LCDT_reset_pin(LCDT_WR_pin,LCDT_WR_port); //pulse low
	LCDT_set_pin(LCDT_WR_pin,LCDT_WR_port);*/
	LCDT_set_pins(reg &0xFF);
	LCDT_reset_pin(LCDT_WR_pin,LCDT_WR_port); //pulse low
	LCDT_set_pin(LCDT_WR_pin,LCDT_WR_port);

	LCDT_all_input();
	LCDT_set_pin(LCDT_RS_pin,LCDT_RS_port); //data

	LCDT_reset_pin(LCDT_RD_pin,LCDT_RD_port);
	*var1 = LCDT_read_pins();
	LCDT_set_pin(LCDT_RD_pin,LCDT_RD_port);

	LCDT_reset_pin(LCDT_RD_pin,LCDT_RD_port);
	*var2 = LCDT_read_pins();
	LCDT_set_pin(LCDT_RD_pin,LCDT_RD_port);

	LCDT_reset_pin(LCDT_RD_pin,LCDT_RD_port);
	*var3 = LCDT_read_pins();
	LCDT_set_pin(LCDT_RD_pin,LCDT_RD_port);

	LCDT_reset_pin(LCDT_RD_pin,LCDT_RD_port);
	*var4 = LCDT_read_pins();
	LCDT_set_pin(LCDT_RD_pin,LCDT_RD_port);

	LCDT_all_output();
	LCDT_set_pin(LCDT_CS_pin,LCDT_CS_port);

}

void LCDT_reset() {
    /***************reset**********/
   // LCDT_set_pin(LCDT_CS_pin,LCDT_CS_port);
    //LCDT_set_pin(LCDT_WR_pin,LCDT_WR_port);
    //LCDT_set_pin(LCDT_RD_pin,LCDT_RD_port);

	LCDT_set_pin(LCDT_RST_pin,LCDT_RST_port);
	delay_ms(10);
    LCDT_reset_pin(LCDT_RST_pin,LCDT_RST_port);
       delay_ms(10);
    LCDT_set_pin(LCDT_RST_pin,LCDT_RST_port);
    delay_ms(100);

   /* LCDT_reset_pin(LCDT_CS_pin,LCDT_CS_port); //active lcd
    LCDT_reset_pin(LCDT_RS_pin,LCDT_RS_port); //command

    LCDT_set_pins(0x00);
    LCDT_reset_pin(LCDT_WR_pin,LCDT_WR_port); //pulse low
    LCDT_set_pin(LCDT_WR_pin,LCDT_WR_port);
    LCDT_reset_pin(LCDT_WR_pin,LCDT_WR_port); //pulse low
    LCDT_set_pin(LCDT_WR_pin,LCDT_WR_port);
    LCDT_reset_pin(LCDT_WR_pin,LCDT_WR_port); //pulse low
    LCDT_set_pin(LCDT_WR_pin,LCDT_WR_port);

    LCDT_set_pin(LCDT_CS_pin,LCDT_CS_port); //deactive lcd
    LCDT_set_pin(LCDT_RS_pin,LCDT_RS_port); //data*/
    /********************************/
}

void LCDT_sw1(int nr, char port) {

	uint32_t nr_mod, nr_ospeed, nr_otyper, nr_pupdr, nr_bssr, zermm,zermo,zermp;

	nr_mod = GPIO_MODER_MODER0_0;
	nr_otyper = GPIO_OTYPER_OT_0;
	nr_ospeed = GPIO_OSPEEDER_OSPEEDR0_1;
	nr_pupdr = GPIO_PUPDR_PUPDR0;
	nr_bssr = GPIO_BSRR_BR_0;

	nr_mod <<= (2*nr); //o 2 w prawo * nr, czyli moze byc GPIO_MODER_MODER2_0
	nr_ospeed <<= (2*nr);
	nr_otyper <<= (1*nr);
	nr_pupdr <<= (2*nr);
	nr_bssr <<= (1*nr);

	zermm = GPIO_MODER_MODER0; //11
	zermo = GPIO_OSPEEDER_OSPEEDR0; //11
	zermp = GPIO_PUPDR_PUPDR0; //11
	zermm <<= (2*nr);
	zermo <<= (2*nr);
	zermp <<= (2*nr);

	switch (port) {
					case 'A':
						RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
						__DSB();
						GPIOA->MODER &= ~zermm; //zerowanie
						GPIOA->OSPEEDR &= ~zermo; //zerowanie
						GPIOA->PUPDR &= ~zermp;

						GPIOA->MODER |= nr_mod; //jako output 01
						GPIOA->OTYPER &= ~nr_otyper; //0 - push-pull
						GPIOA->OSPEEDR |= nr_ospeed; //fast speed 10
						GPIOA->PUPDR &= ~nr_pupdr; //no pull
						GPIOA->BSRR = nr_bssr; //0 na start
						break;
					case 'B':
						RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
						__DSB();
						GPIOB->MODER &= ~zermm; //zerowanie
						GPIOB->OSPEEDR &= ~zermo; //zerowanie
						GPIOB->PUPDR &= ~zermp;

						GPIOB->MODER |= nr_mod; //jako output
						GPIOB->OTYPER &= ~nr_otyper; //0 - push-pull
						GPIOB->OSPEEDR |= nr_ospeed; //speed low 00
						GPIOB->PUPDR &= ~nr_pupdr; //no pull
						GPIOB->BSRR = nr_bssr; //0 na start
						break;
					case 'C':
						RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
						__DSB();
						GPIOC->MODER &= ~zermm; //zerowanie
						GPIOC->OSPEEDR &= ~zermo; //zerowanie
						GPIOC->PUPDR &= ~zermp;

						GPIOC->MODER |= nr_mod; //jako output
						GPIOC->OTYPER &= ~nr_otyper; //0 - push-pull
						GPIOC->OSPEEDR |= nr_ospeed; //speed low 00
						GPIOC->PUPDR &= ~nr_pupdr; //no pull
						GPIOC->BSRR = nr_bssr; //0 na start
						break;
					default:
						break;
	}
}

void LCDT_output(int nr, char port) {
	uint32_t nr_mod, nr_bssr;
	nr_mod = GPIO_MODER_MODER0_0;
	nr_bssr = GPIO_BSRR_BR_0;
	nr_mod <<= (2*nr); //o 2 w prawo * nr, czyli moze byc GPIO_MODER_MODER2_0
	nr_bssr <<= (1*nr);
	switch (port) {
					case 'A':
						GPIOA->MODER |= nr_mod; //jako output 01
						GPIOA->BSRR = nr_bssr; //0 na start
						break;
					case 'B':
						GPIOB->MODER |= nr_mod; //jako output
						GPIOB->BSRR = nr_bssr; //0 na start
						break;
					case 'C':
						GPIOC->MODER |= nr_mod; //jako output
						GPIOC->BSRR = nr_bssr; //0 na start
						break;
					default:
						break;
	}

}

void LCDT_all_output() {
	LCDT_output(LCDT_D0_pin,LCDT_D0_port); //output
	LCDT_output(LCDT_D1_pin,LCDT_D1_port);
	LCDT_output(LCDT_D2_pin,LCDT_D2_port);
	LCDT_output(LCDT_D3_pin,LCDT_D3_port);
	LCDT_output(LCDT_D4_pin,LCDT_D4_port);
	LCDT_output(LCDT_D5_pin,LCDT_D5_port);
	LCDT_output(LCDT_D6_pin,LCDT_D6_port);
	LCDT_output(LCDT_D7_pin,LCDT_D7_port);
}

void LCDT_input(int nr, char port) {
	uint32_t nr_mod, nr_bssr;
	nr_mod = GPIO_MODER_MODER0;
	nr_bssr = GPIO_BSRR_BR_0;
	nr_mod <<= (2*nr); //o 2 w prawo * nr, czyli moze byc GPIO_MODER_MODER2_0
	nr_bssr <<= (1*nr);
	switch (port) {
					case 'A':
						GPIOA->BSRR = nr_bssr; //0 przed zmiana
						GPIOA->MODER &= ~nr_mod; //jako input 00
						break;
					case 'B':
						GPIOB->BSRR = nr_bssr;
						GPIOB->MODER &= ~nr_mod; //jako input
						break;
					case 'C':
						GPIOC->BSRR = nr_bssr;
						GPIOC->MODER &= ~nr_mod; //jako input
						break;
					default:
						break;
	}
}

void LCDT_all_input() {
	LCDT_input(LCDT_D0_pin,LCDT_D0_port); //input
	LCDT_input(LCDT_D1_pin,LCDT_D1_port);
	LCDT_input(LCDT_D2_pin,LCDT_D2_port);
	LCDT_input(LCDT_D3_pin,LCDT_D3_port);
	LCDT_input(LCDT_D4_pin,LCDT_D4_port);
	LCDT_input(LCDT_D5_pin,LCDT_D5_port);
	LCDT_input(LCDT_D6_pin,LCDT_D6_port);
	LCDT_input(LCDT_D7_pin,LCDT_D7_port);
}

void LCDT_set_pin(int nr, char port) {

	uint32_t nr_bssr = GPIO_BSRR_BS_0;
	nr_bssr <<= nr;
	switch (port) {
				case 'A':
					GPIOA->BSRR = nr_bssr;
					break;
				case 'B':
					GPIOB->BSRR = nr_bssr;
					break;
				case 'C':
					GPIOC->BSRR = nr_bssr;
					break;
				default:
					break;
	}
}

void LCDT_reset_pin(int nr, char port) {

	uint32_t nr_bssr = GPIO_BSRR_BR_0;
	nr_bssr <<= nr;
	switch (port) {
				case 'A':
					GPIOA->BSRR = nr_bssr;
					break;
				case 'B':
					GPIOB->BSRR = nr_bssr;
					break;
				case 'C':
					GPIOC->BSRR = nr_bssr;
					break;
				default:
					break;
	}
}

int LCDT_check_pin(int nr, char port) {

	uint32_t nr_bssr = GPIO_IDR_IDR_0;
	int zn=0;
	nr_bssr <<= nr;
	switch (port) {
				case 'A':
					zn = (GPIOA->IDR & nr_bssr);  //GPIOA->IDR & 0x100, to by zwrocilo 4 jak bylby ustawiony idr na 1 na pinie PA2
					break;
				case 'B':
					zn = (GPIOB->IDR & nr_bssr);
					break;
				case 'C':
					zn = (GPIOC->IDR & nr_bssr);
					break;
				default:
					break;
	}
	return zn>>nr; //przesunac spowrotem aby otrzymac 1, anie jaks liczbe
}

uint8_t LCDT_read_pins() {
	uint8_t zm=0;
	zm = LCDT_check_pin(LCDT_D0_pin, LCDT_D0_port);
	zm |= LCDT_check_pin(LCDT_D1_pin, LCDT_D1_port) << 1;
	zm |= LCDT_check_pin(LCDT_D2_pin, LCDT_D2_port) << 2;
	zm |= LCDT_check_pin(LCDT_D3_pin, LCDT_D3_port) << 3;
	zm |= LCDT_check_pin(LCDT_D4_pin, LCDT_D4_port) << 4;
	zm |= LCDT_check_pin(LCDT_D5_pin, LCDT_D5_port) << 5;
	zm |= LCDT_check_pin(LCDT_D6_pin, LCDT_D6_port) << 6;
	zm |= LCDT_check_pin(LCDT_D7_pin, LCDT_D7_port) << 7;

	return zm;
}

void LCDT_set_pins(uint8_t zm) {
	//if ((zm & 0x80)!=0){ LCD_set_pin(LCD_DB7_pin,LCD_DB7_port) } else LCD_reset_pin(LCD_DB7_pin,LCD_DB7_port)
	(zm & 0x80) ? LCDT_set_pin(LCDT_D7_pin,LCDT_D7_port) : LCDT_reset_pin(LCDT_D7_pin,LCDT_D7_port);
	(zm & 0x40) ? LCDT_set_pin(LCDT_D6_pin,LCDT_D6_port) : LCDT_reset_pin(LCDT_D6_pin,LCDT_D6_port);
	(zm & 0x20) ? LCDT_set_pin(LCDT_D5_pin,LCDT_D5_port) : LCDT_reset_pin(LCDT_D5_pin,LCDT_D5_port);
	(zm & 0x10) ? LCDT_set_pin(LCDT_D4_pin,LCDT_D4_port) : LCDT_reset_pin(LCDT_D4_pin,LCDT_D4_port);
	(zm & 0x08) ? LCDT_set_pin(LCDT_D3_pin,LCDT_D3_port) : LCDT_reset_pin(LCDT_D3_pin,LCDT_D3_port);
	(zm & 0x04) ? LCDT_set_pin(LCDT_D2_pin,LCDT_D2_port) : LCDT_reset_pin(LCDT_D2_pin,LCDT_D2_port);
	(zm & 0x02) ? LCDT_set_pin(LCDT_D1_pin,LCDT_D1_port) : LCDT_reset_pin(LCDT_D1_pin,LCDT_D1_port);
	(zm & 0x01) ? LCDT_set_pin(LCDT_D0_pin,LCDT_D0_port) : LCDT_reset_pin(LCDT_D0_pin,LCDT_D0_port);
}


/*LCDT_write_reg(0xF0);
  LCDT_write_data(0x5A);
	LCDT_write_data(0x5A);
	LCDT_write_reg(0xFC);
	LCDT_write_data(0x5A);
	LCDT_write_data(0x5A);
	LCDT_write_reg(0xFD);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x10);
	LCDT_write_data(0x14);
	LCDT_write_data(0x12);
	LCDT_write_data(0x00);
	LCDT_write_data(0x04);
	LCDT_write_data(0x48);
	LCDT_write_data(0x40);
	LCDT_write_data(0x16);
	LCDT_write_data(0x16);
	LCDT_write_reg(0x35);
	LCDT_write_reg(0x36);
	LCDT_write_data(0x28);//0x68
	LCDT_write_reg(0x3A);
	LCDT_write_data(0x55);//0x55
	LCDT_write_reg(0xF2);
	LCDT_write_data(0x28);
	LCDT_write_data(0x5B);
	LCDT_write_data(0x7F);
	LCDT_write_data(0x08);
	LCDT_write_data(0x08);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x15);
	LCDT_write_data(0x48);
	LCDT_write_data(0x04);
	LCDT_write_data(0x07);
	LCDT_write_data(0x01);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x63);
	LCDT_write_data(0x08);
	LCDT_write_data(0x08);
	LCDT_write_reg(0xF7);
	LCDT_write_data(0x01);
	LCDT_write_data(0x00);
	LCDT_write_data(0x10);
	LCDT_write_data(0x00);
	LCDT_write_reg(0xF8);
	LCDT_write_data(0x33);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_reg(0xF6);
	LCDT_write_data(0x01);
	LCDT_write_data(0x01);
	LCDT_write_data(0x07);
	LCDT_write_data(0x00);
	LCDT_write_data(0x01);
	LCDT_write_data(0x0C);
	LCDT_write_data(0x03);
	LCDT_write_data(0x0C);
	LCDT_write_data(0x03);
	LCDT_write_reg(0xF5);
	LCDT_write_data(0x00);
	LCDT_write_data(0x2E);
	LCDT_write_data(0x40);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x01);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x0D);
	LCDT_write_data(0x0D);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_reg(0xF4);
	LCDT_write_data(0x07);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x22);
	LCDT_write_data(0x64);
	LCDT_write_data(0x01);
	LCDT_write_data(0x02);
	LCDT_write_data(0x2A);
	LCDT_write_data(0x4D);
	LCDT_write_data(0x06);
	LCDT_write_data(0x2A);
	LCDT_write_data(0x00);
	LCDT_write_data(0x06);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_reg(0xF3);
	LCDT_write_data(0x01);
	//GAMMA
	LCDT_write_reg(0xF9);
	LCDT_write_data(0x04);
	LCDT_write_reg(0xFA);
	LCDT_write_data(0x0A);
	LCDT_write_data(0x04);
	LCDT_write_data(0x0C);
	LCDT_write_data(0x19);
	LCDT_write_data(0x25);
	LCDT_write_data(0x33);
	LCDT_write_data(0x2D);
	LCDT_write_data(0x27);
	LCDT_write_data(0x22);
	LCDT_write_data(0x1E);
	LCDT_write_data(0x1A);
	LCDT_write_data(0x00);
	LCDT_write_reg(0xFB);
	LCDT_write_data(0x0C);
	LCDT_write_data(0x04);
	LCDT_write_data(0x19);
	LCDT_write_data(0x1E);
	LCDT_write_data(0x20);
	LCDT_write_data(0x23);
	LCDT_write_data(0x18);
	LCDT_write_data(0x3D);
	LCDT_write_data(0x25);
	LCDT_write_data(0x19);
	LCDT_write_data(0x0B);
	LCDT_write_data(0x00);

	LCDT_write_reg(0xF9);
	LCDT_write_data(0x02);
	LCDT_write_reg(0xFA);
	LCDT_write_data(0x0A);
	LCDT_write_data(0x04);
	LCDT_write_data(0x0C);
	LCDT_write_data(0x19);
	LCDT_write_data(0x25);
	LCDT_write_data(0x33);
	LCDT_write_data(0x2D);
	LCDT_write_data(0x27);
	LCDT_write_data(0x22);
	LCDT_write_data(0x1E);
	LCDT_write_data(0x1A);
	LCDT_write_data(0x00);
	LCDT_write_reg(0xFB);
	LCDT_write_data(0x0C);
	LCDT_write_data(0x04);
	LCDT_write_data(0x19);
	LCDT_write_data(0x1E);
	LCDT_write_data(0x20);
	LCDT_write_data(0x23);
	LCDT_write_data(0x18);
	LCDT_write_data(0x3D);
	LCDT_write_data(0x25);
	LCDT_write_data(0x19);
	LCDT_write_data(0x0B);
	LCDT_write_data(0x00);

	LCDT_write_reg(0xF9);
	LCDT_write_data(0x01);
	LCDT_write_reg(0xFA);
	LCDT_write_data(0x0A);
	LCDT_write_data(0x04);
	LCDT_write_data(0x0C);
	LCDT_write_data(0x19);
	LCDT_write_data(0x25);
	LCDT_write_data(0x33);
	LCDT_write_data(0x2D);
	LCDT_write_data(0x27);
	LCDT_write_data(0x22);
	LCDT_write_data(0x1E);
	LCDT_write_data(0x1A);
	LCDT_write_data(0x00);
	LCDT_write_reg(0xFB);
	LCDT_write_data(0x0C);
	LCDT_write_data(0x04);
	LCDT_write_data(0x19);
	LCDT_write_data(0x1E);
	LCDT_write_data(0x20);
	LCDT_write_data(0x23);
	LCDT_write_data(0x18);
	LCDT_write_data(0x3D);
	LCDT_write_data(0x25);
	LCDT_write_data(0x19);
	LCDT_write_data(0x0B);
	LCDT_write_data(0x00);
	LCDT_write_reg(0x11);
	 delay_ms(100);
	LCDT_write_reg(0xF0);
	LCDT_write_data(0xA5);
	LCDT_write_data(0xA5);
	LCDT_write_reg(0xFC);
	LCDT_write_data(0xA5);
	LCDT_write_data(0xA5);
	LCDT_write_reg(0x2a);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x01);//0x01
	LCDT_write_data(0x3f);//0x3f
	LCDT_write_reg(0x2b);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);
	LCDT_write_data(0x00);//0x00
	LCDT_write_data(0xef);//0xef
	LCDT_write_reg(0x29);
	LCDT_write_reg(0x2c);*/

//	LCDT_read_reg(0x09,&x,&y,&z,&m);

/*LCDT_write_reg(0xCB);
LCDT_write_data(0x39);
LCDT_write_data(0x2C);
LCDT_write_data(0x00);
LCDT_write_data(0x34);
LCDT_write_data(0x02);
LCDT_write_reg(0xCF);
LCDT_write_data(0x00);
LCDT_write_data(0xC1);
LCDT_write_data(0x30);
LCDT_write_reg(0xE8);
LCDT_write_data(0x85);
LCDT_write_data(0x00);
LCDT_write_data(0x78);
LCDT_write_reg(0xEA);
LCDT_write_data(0x00);
LCDT_write_data(0x00);
LCDT_write_reg(0xED);
LCDT_write_data(0x64);
LCDT_write_data(0x03);
LCDT_write_data(0x12);
LCDT_write_data(0x81);
LCDT_write_reg(0xF7);
LCDT_write_data(0x20);
LCDT_write_reg(0xC0);
LCDT_write_data(0x23);
LCDT_write_reg(0xC1);
LCDT_write_data(0x10);
LCDT_write_reg(0xC5);
LCDT_write_data(0x3E);
LCDT_write_data(0x28);
LCDT_write_reg(0xC7);
LCDT_write_data(0x86);
LCDT_write_reg(0x36);
LCDT_write_data(0x48);
LCDT_write_reg(0x3A);
LCDT_write_data(0x55);
LCDT_write_reg(0xB1);
LCDT_write_data(0x00);
LCDT_write_data(0x18);
LCDT_write_reg(0xB6);
LCDT_write_data(0x08);
LCDT_write_data(0x82);
LCDT_write_data(0x27);
LCDT_write_reg(0xF2);
LCDT_write_data(0x00);
LCDT_write_reg(0x2A);
LCDT_write_data(0x00);
LCDT_write_data(0x00);
LCDT_write_data(0x00);
LCDT_write_data(0xEF);
LCDT_write_reg(0x2B);
LCDT_write_data(0x00);
LCDT_write_data(0x00);
LCDT_write_data(0x01);
LCDT_write_data(0x3F);
LCDT_write_reg(0x26);
LCDT_write_data(0x01);
LCDT_write_reg(0xE0);
LCDT_write_data(0x0F);
LCDT_write_data(0x31);
LCDT_write_data(0x2B);
LCDT_write_data(0x0C);
LCDT_write_data(0x0E);
LCDT_write_data(0x08);
LCDT_write_data(0x4E);
LCDT_write_data(0xF1);
LCDT_write_data(0x37);
LCDT_write_data(0x07);
LCDT_write_data(0x10);
LCDT_write_data(0x03);
LCDT_write_data(0x0E);
LCDT_write_data(0x09);
LCDT_write_data(0x00);
LCDT_write_reg(0xE1);
LCDT_write_data(0x00);
LCDT_write_data(0x0E);
LCDT_write_data(0x14);
LCDT_write_data(0x03);
LCDT_write_data(0x11);
LCDT_write_data(0x07);
LCDT_write_data(0x31);
LCDT_write_data(0xC1);
LCDT_write_data(0x48);
LCDT_write_data(0x08);
LCDT_write_data(0x0F);
LCDT_write_data(0x0C);
LCDT_write_data(0x31);
LCDT_write_data(0x36);
LCDT_write_data(0x0F);
LCDT_write_reg(0x11);

delay_ms(100);

LCDT_write_reg(0x29);
LCDT_write_reg(0x2C);*/
