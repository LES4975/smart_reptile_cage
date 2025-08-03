#ifndef HW_HW_H_
#define HW_HW_H_

#include "bluetooth.h"
#include "dht11.h"
#include "rgb.h"
#include "i2c_lcd.h"
#include "humidifier.h"
#include "dcfan.h"

#define R_Port		GPIOB
#define R_Pin		GPIO_PIN_13
#define G_Port		GPIOB
#define G_Pin		GPIO_PIN_14
#define B_Port		GPIOB
#define B_Pin		GPIO_PIN_15

typedef enum{
	IDLE, UNDER, OVER
}SENSOR_STATE;

#define DHT11_Port	GPIOC
#define DHT11_Pin	GPIO_PIN_3
#define PUTCHAR_PROTOTYPE int  __io_putchar(int ch)

void hwInit();
void LED_On(LED_RGB color);
void LED_Off(LED_RGB color);
void LED_Toggle(LED_RGB color);
void ProcessSensorState();
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


#endif /* HW_HW_H_ */
