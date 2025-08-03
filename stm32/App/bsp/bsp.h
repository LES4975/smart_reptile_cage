
#ifndef BSP_BSP_H_
#define BSP_BSP_H_

#include "def.h"
#include "gpio.h"

void GPIOInit(GPIO_TypeDef *port, uint16_t pin, uint32_t mode, uint32_t pull);

#endif /* BSP_BSP_H_ */
