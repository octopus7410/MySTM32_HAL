#include "stm32f1xx_hal.h"

//according
#define I2CADDRESS_LCD 0x40 

//handler accordingly
#define I2C_LCD hi2c1
#define aI2C_LCD &hi2c1

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x00
#define LCD_NOBACKLIGHT 0x80

// Display address
// Number of visible lines of the display (1 or 2 or 4)
#define LCD_LINES					2
// Visible characters per line of the display
#define LCDcharacters_per 		16
// DDRAM address of first char of line 1
#define LCD_LINE1	0x00
// DDRAM address of first char of line 2
#define LCD_LINE2	0x40
// DDRAM address of first char of line 3
#define LCD_LINE3	0x14
// DDRAM address of first char of line 4
#define LCD_LINE4	0x54

void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_send_number (int number); // send number to the lcd

void lcd_send_manynumber (int number); // send number to the lcd
	
void lcd_gotoxy(uint8_t x, uint8_t y); // set string position to the lcd





