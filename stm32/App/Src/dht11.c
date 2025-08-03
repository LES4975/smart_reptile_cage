
#include "dht11.h"

// Initialize dht11
void dht11Init(DHT11 *dht, GPIO_TypeDef *port, uint16_t pin)
{
	// structure port
	dht->port = port;
	dht->pin = pin;
}

void dht11GpioMode(DHT11 *dht, uint8_t mode)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};	// reset of structure about port

	if(mode == OUTPUT)
	{
//		GPIOInit(dht->port, dht->pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL);
		// set of output
		GPIO_InitStruct.Pin = dht->pin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(dht->port, &GPIO_InitStruct);
	}
	else if(mode == INPUT)
	{
		GPIOInit(dht->port, dht->pin, GPIO_MODE_INPUT, GPIO_NOPULL);
		// set of input
		GPIO_InitStruct.Pin = dht->pin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(dht->port, &GPIO_InitStruct);
	}
}

uint8_t dht11Read(DHT11 *dht)
{
//	if(dht == 0) return false;

	uint16_t timeTick = 0;		// reset value of Measurement time
	uint8_t pulse[40] = {0};	// reset array value of stored data for 40bit

//	// temperature and humidity data value
//	uint8_t humValue1 = 0, humValue2 = 0;	// humidity
//	uint8_t temValue1 = 0, temValue2 = 0;	// temperature
//	uint8_t parityValue = 0;				// check sum

	uint8_t values[5] = {0};

	// start timer
	HAL_TIM_Base_Start(&htim11);

	// Transmitting a communication start signal
	dht11GpioMode(dht, OUTPUT);							// mode set Output for GPIO
	HAL_GPIO_WritePin(dht->port, dht->pin, 0);	// transmit low of dht
	HAL_Delay(20);										// start bit signal (maintain low)
	HAL_GPIO_WritePin(dht->port, dht->pin, 1);	// transmit high of dht
	delay_us(30);										// wait a 30us
	dht11GpioMode(dht, INPUT);							// mode set Input for GPIO

	if(ResponseSignal(dht, 100, GPIO_PIN_RESET)) return 0;
	if(ResponseSignal(dht, 100, GPIO_PIN_SET)) return 0;


	for(uint8_t i = 0; i < sizeof(pulse); i++)
	{
		while(HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_RESET);

		__HAL_TIM_SET_COUNTER(&htim11, 0);

		while(HAL_GPIO_ReadPin(dht->port, dht->pin) == GPIO_PIN_SET)
		{
			timeTick = __HAL_TIM_GET_COUNTER(&htim11);	// measurement of length for high signal

			if(timeTick > 20 && timeTick < 30)
			{
				pulse[i] = 0;
			}
			else if(timeTick > 65 && timeTick < 85)
			{
				pulse[i] = 1;
			}
		}
	}

	// stop timer
	HAL_TIM_Base_Stop(&htim11);

	for(uint8_t i = 0; i < sizeof(values); i++)
	{
		ByteToBit(pulse, &values[i], i);
	}
//	ByteToBit(pulse, &humValue1, 0);	// humidity value of integer
//	ByteToBit(pulse, &humValue2, 1);	// humidity value of decimal
//	ByteToBit(pulse, &temValue1, 2);	// temperature value of integer
//	ByteToBit(pulse, &temValue2, 3);	// temperature value of decimal
//	ByteToBit(pulse, &parityValue, 4);	// check sum value

//	printf("%d, %d\n",values[0], values[1]);
//	printf("%d, %d\n",values[2], values[3]);

	dht->humidity[0] = values[0];
	dht->humidity[1] = values[1];
	dht->temperature[0] = values[2];
	dht->temperature[1] = values[3];

	uint8_t checkSum = 0;
	for(uint8_t i = 0; i < sizeof(values) - 1; i++)
	{
		checkSum += values[i];
	}

	if(checkSum != values[4])
	{
		return 0;
	}

	return 1;
}

void ByteToBit(uint8_t *byteValue, uint8_t *bitValue, uint8_t index)
{
	// Processing data stored in an array
	for (uint8_t i = index * 8; i < (index + 1) * 8; i++)
	{
		*bitValue = (*bitValue << 1) + byteValue[i];	// 8bit data of dht11
	}
}


uint8_t ResponseSignal(DHT11 *dht, uint16_t timer, GPIO_PinState state)
{
	// wait for response signal of dht11
	__HAL_TIM_SET_COUNTER(&htim11, 0);
	while(HAL_GPIO_ReadPin(dht->port, dht->pin) == state)
	{
		if(__HAL_TIM_GET_COUNTER(&htim11) > timer)
		{
			printf("non signal of %s\n\r", state ? "HIGT": "LOW");	// print of timeout error
			return 1;							// escape from while by timeout error
		}
	}
	return 0;
}
