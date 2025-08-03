
#ifndef INC_RGB_H_
#define INC_RGB_H_

#include "bsp.h"

typedef enum{
	R, G, B
}LED_RGB;

typedef struct{
	GPIO_TypeDef  *port;
	uint16_t	   pin;
	GPIO_PinState  onState;
	GPIO_PinState  offState;
}RGB;

//RGB* newRGB(GPIO_TypeDef *port, uint16_t pin, uint32_t mode, uint32_t pull, uint32_t speed);
bool RGBInit(RGB *rgb, GPIO_TypeDef *port, uint16_t pin);

void RGB_ON(RGB *rgb);
void RGB_OFF(RGB *rgb);
void RGB_TOGGLE(RGB *rgb);

#endif /* INC_RGB_H_ */
