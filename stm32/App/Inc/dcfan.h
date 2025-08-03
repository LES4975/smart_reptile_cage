
#ifndef INC_DCFAN_H_
#define INC_DCFAN_H_

#include "gpio.h"
#include "tim.h"

#define FAN_PORT	GPIOA
#define FAN_PIN		GPIO_PIN_6

//void DCFanOn_Tim();
//void DCFanPause_Tim();
//void DCFanOff_Tim();
void DCFanOn_GPIO();
void DCFanOff_GPIO();

#endif /* INC_DCFAN_H_ */
