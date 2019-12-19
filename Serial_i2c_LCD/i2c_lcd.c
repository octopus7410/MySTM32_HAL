/**
  ******************************************************************************
	*	Author             : YueHeng Li
  * File Name          : i2c_lcd.c
  * Description        : This file provides code for the configuration
  *                      of fayalab Serial LCD Adapter.
  ******************************************************************************
  * This file can support All Serial LCD 
	* But to achieve the effect you must confirm and change the pin configuration or change the program
	* PCF8574 address
	* A0 -> 0
	* A1 -> 0
	* A2 -> 0
	*
	* 000 -> 0
	* PCF8574 address is (S/A)100(A2)(A1)(A0)so tis one PCF8574 address is 01000000=0x40 
	* you can change is in i2c_lcd.h
  * and you can found data in: http://www.ti.com/lit/ds/symlink/pcf8574.pdf
	*
	* WH1602B to PCF8574 PIN configuration
	*
	*Vss
	*Vcc
	*RS  --->P6
	*R/W --->P5
	*En  --->P4
	*DB0
	*DB1
	*DB2
	*DB3
	*DB4 --->P0
	*DB5 --->P1
	*DB6 --->P2
	*DB7 --->P3
	*LED+
	*LED- -->P7
  *
  ******************************************************************************
  */
	
#include "i2c-lcd.h"
#include "stdio.h"
extern I2C_HandleTypeDef I2C_LCD; 


/**
  ******************************************************************************
  * @brief	Set LCD cmd.
  * @param	LCD cmd
  * @retval	None
  ******************************************************************************
  */
void lcd_send_cmd (char cmd)
{
  uint8_t data_u, data_l;
	uint8_t data_t[4];
	data_u = ((cmd&0xf0)>>4);
	data_t[0] = data_u|0x10;  //en=1, rs=0
	data_t[1] = data_u|0x00;  //en=0, rs=0
	data_l = (cmd&0x0f);
	data_t[2] = data_l|0x10;  //en=1, rs=0
	data_t[3] = data_l|0x00;  //en=0, rs=0
	HAL_I2C_Master_Transmit (aI2C_LCD, I2CADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}



/**
  ******************************************************************************
  * @brief	Set LCD data.
  * @param	LCD data
  * @retval	None
  ******************************************************************************
  */
void lcd_send_data (char data)
{
	uint8_t data_u, data_l;
	uint8_t data_t[4];
	data_u = ((data&0xf0)>>4);
	data_t[0] = data_u|0x50;  //en=1, rs=1
	data_t[1] = data_u|0x40;  //en=0, rs=1
	data_l = (data&0x0f);
	data_t[2] = data_l|0x50;  //en=1, rs=1
	data_t[3] = data_l|0x40;  //en=0, rs=1
	HAL_I2C_Master_Transmit (aI2C_LCD, I2CADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}



/**
  ******************************************************************************
  * @brief	clear LCD.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd_clear (void)
{
	lcd_send_cmd (0x01);
}



/**
  ******************************************************************************
  * @brief	initial the LCD.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void lcd_init (void)
{
	// 4 bit initialisation
  for(int i=0;i<3;i++)
	{	
		lcd_send_cmd (0x03);
		HAL_Delay(50);  
	}
	lcd_send_cmd (0x02); 
	HAL_Delay(100);
	lcd_send_cmd (0x28);
	HAL_Delay(1);
	lcd_send_cmd (0x0c);
	HAL_Delay(1);
	lcd_send_cmd (0x80);
	HAL_Delay(1);
	lcd_send_cmd (0x01);
	HAL_Delay(1);
}



/**
  ******************************************************************************
  * @brief	show the string to LCD.
  * @param	lcd string
  * @retval	None
  ******************************************************************************
  */
void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}
/**
  ******************************************************************************
  * @brief	show the number to LCD.
  * @param	lcd number
  * @retval	None
  ******************************************************************************
  */
void lcd_send_number (int number)
{
	lcd_send_data(number+48);
}
/**
  ******************************************************************************
  * @brief	show the number to LCD.
  * @param	lcd number
  * @retval	None
  ******************************************************************************
  */

void lcd_send_manynumber (int number)
{
	char s[64];
	sprintf(s,"%d",number);
	lcd_send_string(s);
}

/**
  ******************************************************************************
  * @brief	Set LCD position.
  * @param	LCD column
  * @param	LCD row
  * @retval	None
  ******************************************************************************
  */

void lcd_gotoxy(uint8_t x, uint8_t y)
{
#if LCD_LINES == 1 
	lcd_send_cmd(LCD_SETDDRAMADDR |(LCD_LINE1 + x));
#elif LCD_LINES == 2
	if (y == 0)
		lcd_send_cmd(LCD_SETDDRAMADDR | (LCD_LINE1 + x));
	else
		lcd_send_cmd(LCD_SETDDRAMADDR | (LCD_LINE2 + x));
#elif LCD_LINES == 4
	if (y == 0)
		lcd_send_cmd(LCD_SETDDRAMADDR | (LCD_LINE1 + x));
	else if (y == 1)
		lcd_send_cmd(LCD_SETDDRAMADDR | (LCD_LINE2 + x));
	else if (y == 2)
		lcd_send_cmd(LCD_SETDDRAMADDR | (LCD_LINE3 + x));
	else
		lcd_send_cmd(LCD_SETDDRAMADDR | (LCD_LINE4 + x));
#endif
}



