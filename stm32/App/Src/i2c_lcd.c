#include "i2c_lcd.h"

void force_i2c_reset(I2C_HandleTypeDef *hi2c1)
{
	// I2C 버스 강제 초기화
	HAL_I2C_DeInit(hi2c1);
	HAL_Delay(50);
	HAL_I2C_Init(hi2c1);
	printf("I2C bus force reset\n");
}

uint8_t i2c_check(uint8_t *i2c_buffer)
{
	uint32_t prevTime = HAL_GetTick();
	while (HAL_I2C_Master_Transmit(&hi2c1, I2C_LCD_ADDRESS, i2c_buffer, 4, 100)	!= HAL_OK)
	{
		uint32_t cullTime = HAL_GetTick();
		uint32_t diffTime = cullTime - prevTime;
		if (diffTime > 1000)
		{
			return 0;
		}
		//HAL_Delay(1);
	}
	return 1;
}
uint8_t lcd_command(uint8_t command)
{
	uint8_t high_nibble, low_nibble;
	uint8_t i2c_buffer[4]; // 4bit 통신을 할 것이기 때문에...

	high_nibble = command & 0xf0; // 상위 비트 4개 뽑기
	low_nibble = (command << 4) & 0xf0; // 하위 비트 4개 뽑기

	//HD44780 명령어 참조
	i2c_buffer[0] = high_nibble | 0x04 | 0x08; // 핀 설정: enable = 1, rs = 0, rw = 0, backlight = 1
	i2c_buffer[1] = high_nibble | 0x00 | 0x08; // 핀 설정: enable = 0, rs = 0, rw = 0, backlight = 1
	i2c_buffer[2] = low_nibble | 0x04 | 0x08; // 핀 설정: enable = 1, rs = 0, rw = 0, backlight = 1
	i2c_buffer[3] = low_nibble | 0x00 | 0x08; // 핀 설정: enable = 0, rs = 0, rw = 0, backlight = 1

	return i2c_check(i2c_buffer);
}

void lcd_data(uint8_t data)
{
	uint8_t high_nibble, low_nibble;
	uint8_t i2c_buffer[4]; // 4bit 통신을 할 것이기 때문에...

	high_nibble = data & 0xf0; // 상위 비트 4개 뽑기
	low_nibble = (data << 4) & 0xf0; // 하위 비트 4개 뽑기

	//HD44780 명령어 참조
	i2c_buffer[0] = high_nibble | 0x05 | 0x08; // 핀 설정: enable = 1, rs = 1, rw = 0, backlight = 1
	i2c_buffer[1] = high_nibble | 0x01 | 0x08; // 핀 설정: enable = 0, rs = 1, rw = 0, backlight = 1
	i2c_buffer[2] = low_nibble | 0x05 | 0x08; // 핀 설정: enable = 1, rs = 1, rw = 0, backlight = 1
	i2c_buffer[3] = low_nibble | 0x01 | 0x08; // 핀 설정: enable = 0, rs = 1, rw = 0, backlight = 1

	if(!(i2c_check(i2c_buffer)))
	{
		printf("LCD 데이터 전송 실패: 데이터 0x%02X\n", data);
	}
}

void i2c_lcd_init()
{
	uint8_t flag = 1;
	while (1)
	{
		HAL_Delay(50); // 안정화 시간이 필요하니까~
		flag = lcd_command(0x33);
		HAL_Delay(5);
		flag = lcd_command(0x32);
		HAL_Delay(5);
		flag = lcd_command(0x28);
		HAL_Delay(5);
		flag = lcd_command(DISPLAY_ON);
		HAL_Delay(5);
		flag = lcd_command(0x06);
		HAL_Delay(5);
		flag = lcd_command(CLEAR_DISPLAY);
		HAL_Delay(2);

		if(flag)
		{
			break;
		}
		else
		{
			force_i2c_reset(&hi2c1);
		}
	}
}
void lcd_string(char *str)
{
	while (*str)lcd_data(*str++);
}

void move_cursor(uint8_t row, uint8_t col)
{
	lcd_command(0x80 | row << 6 | col);
}

void TempHum_to_string(uint8_t t0, uint8_t t1, uint8_t h0, char *buffer_t, char *buffer_h)
{
	sprintf(buffer_t, "Temp: %d.%d", t0, t1);
	sprintf(buffer_h, "Hum :  %d%%", h0);
}

void print_string_to_LCD(char *buffer_t, char *buffer_h)
{
//	lcd_command(CLEAR_DISPLAY);
	HAL_Delay(20);
	move_cursor(0, 0);
	lcd_string(buffer_t);
	move_cursor(1, 0);
	lcd_string(buffer_h);
}
