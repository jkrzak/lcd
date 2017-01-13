

void  USART2_IRQHandler(void);
void  USART1_IRQHandler(void);
void usart2_init();
void usart1_init();
void uart_sendstr(volatile char *dane);
void uart_sendnum(volatile int dane) ;

void led_init();
void buttom_init();

void delay_us(uint16_t s);
void delay_ms(int s);
void TIM2_IRQHandler(void);
void delay_init();

void usart_float(double zm);
