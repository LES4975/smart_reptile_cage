#include "hw.h"

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART2 and Loop
     until the end of transmission */
  if(ch == '\n')
    HAL_UART_Transmit(&huart2, (uint8_t*) "\r", 1, 0xFFFF);
    HAL_UART_Transmit(&huart2, (uint8_t*) &ch, 1, 0xFFFF);
}

static RGB rgb[3];
static uint8_t temperature_state = 0;
static uint8_t humidity_state = 0;
static HUM hum;

void hwInit()
{
	RGBInit(&rgb[0], R_Port, R_Pin);
	RGBInit(&rgb[1], G_Port, G_Pin);
	RGBInit(&rgb[2], B_Port, B_Pin);
	BluetoothInit();
	humidifierInit(&hum);
	i2c_lcd_init();
}

void LED_On(LED_RGB color)
{
	RGB_ON(&rgb[color]);
}

void LED_Off(LED_RGB color)
{
	RGB_OFF(&rgb[color]);
}

void LED_Toggle(LED_RGB color)
{
	RGB_TOGGLE(&rgb[color]);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	// Debugging and Received data
	uint8_t *rx_data = Bluetooth_RxHandler(huart, Size);
	if (rx_data != NULL && Size > 5)
	{
		 if (isdigit(rx_data[1]) && isdigit(rx_data[4]))
		{
			temperature_state = (SENSOR_STATE)(rx_data[1] - '0');
			humidity_state = (SENSOR_STATE)(rx_data[4] - '0');
			printf("%d, %d\r\n",temperature_state, humidity_state);
		}
	}
}

void ProcessSensorState()
{
	if(temperature_state == IDLE)
	{
		LED_On(R);
		LED_On(G);
		LED_On(B);
	}
	else if(temperature_state == UNDER)
	{
		LED_On(R);
		LED_Off(G);
		LED_Off(B);
	}
	else if(temperature_state == OVER)
	{
		LED_Off(R);
		LED_Off(G);
		LED_On(B);
	}

	if(humidity_state == IDLE)
	{
		humidifierOFF(&hum);
//		DCFanPause_Tim();
//		DCFanOff_Tim();
		DCFanOff_GPIO();
	}
	else if(humidity_state == UNDER)
	{
		humidifierON(&hum);
//		DCFanOff_Tim();
		DCFanOff_GPIO();
	}
	else if(humidity_state == OVER)
	{
		humidifierOFF(&hum);
//		DCFanOn_Tim();
		DCFanOn_GPIO();
	}
}

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	if(GPIO_Pin == Button_Pin)
//	{
//		if(Button_Pin != 0)
//		{
//			flag = 1;
//		}
//	}
//}
