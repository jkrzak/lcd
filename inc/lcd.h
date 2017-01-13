
#define LCDT_RST_port    'C'	//reset to stan niski
#define LCDT_RST_pin 	 1

#define LCDT_CS_port	 'B'	//chip select
#define LCDT_CS_pin		 0

#define LCDT_RS_port	 'A'	//command/data; 1 - display data or parameter
#define LCDT_RS_pin		 4		// 0 - command

#define LCDT_WR_port	'A'		//lcd write
#define LCDT_WR_pin		1

#define LCDT_RD_port	'A'		//lcd read
#define LCDT_RD_pin		0

#define LCDT_D0_port	'A'
#define LCDT_D0_pin		9

#define LCDT_D1_port	'C'
#define LCDT_D1_pin		7

#define LCDT_D2_port	'A'
#define LCDT_D2_pin		10

#define LCDT_D3_port	'B'
#define LCDT_D3_pin		3

#define LCDT_D4_port	'B'
#define LCDT_D4_pin		5

#define LCDT_D5_port	'B'
#define LCDT_D5_pin		4

#define LCDT_D6_port	'B'
#define LCDT_D6_pin		10

#define LCDT_D7_port	'A'
#define LCDT_D7_pin		8

void LCDT_init();
void fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, int color);

//void LCDT_cmd(uint8_t cmd);
//void LCDT_data(uint8_t cmd);
//char LCDT_read();

//void LCDT_data_reg(uint32_t reg, uint32_t cmd);

