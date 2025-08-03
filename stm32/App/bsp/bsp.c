
#include <bsp.h>

void GPIOInit(GPIO_TypeDef *port, uint16_t pin, uint32_t mode, uint32_t pull)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = mode;
	GPIO_InitStruct.Pull = pull;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(port, &GPIO_InitStruct);

	if(mode == GPIO_MODE_OUTPUT_OD || mode == GPIO_MODE_OUTPUT_PP)
	{
		HAL_GPIO_WritePin(port, pin, RESET);
	}
}
