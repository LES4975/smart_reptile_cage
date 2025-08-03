
#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_

#include "main.h"
#include "i2c.h"
#include "bsp.h"

#define I2C_LCD_ADDRESS (0x27<<1) //0010 0111 << 1 (LCD의 slave address)
#define BACKLIGHT_ON		0x08

#define DISPLAY_ON			0x0C
#define DISPLAY_OFF			0x08
#define CLEAR_DISPLAY		0x01 // 2ms delay가 필요한 녀석
#define RETURN_HOME			0x02

uint8_t lcd_command(uint8_t command);
void lcd_data(uint8_t data);
void i2c_lcd_init();
void lcd_string(char *str);
void move_cursor(uint8_t row, uint8_t col);

void TempHum_to_string(uint8_t t0, uint8_t t1, uint8_t h0, char* buffer_t, char* buffer_h);
void print_string_to_LCD(char* buffer_t, char* buffer_h);

#endif /* INC_I2C_LCD_H_ */
