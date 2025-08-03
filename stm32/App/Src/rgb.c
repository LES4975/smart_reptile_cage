#include "rgb.h"

bool RGBInit(RGB *rgb, GPIO_TypeDef *port, uint16_t pin)
{
	rgb->port = port;
	rgb->pin = pin;
	rgb->onState = GPIO_PIN_SET;
	rgb->offState = GPIO_PIN_RESET;

	if(rgb == NULL) return false;

	GPIOInit(rgb->port, rgb->pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL);

	return true;
}

void RGB_ON(RGB *rgb){
	HAL_GPIO_WritePin(rgb->port, rgb->pin, rgb->onState);
}

void RGB_OFF(RGB *rgb){
	HAL_GPIO_WritePin(rgb->port, rgb->pin, rgb->offState);
}

void RGB_TOGGLE(RGB *rgb){
	HAL_GPIO_TogglePin(rgb->port, rgb->pin);
}
