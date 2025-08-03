
#ifndef INC_HUMIDIFIER_H_
#define INC_HUMIDIFIER_H_

#include "gpio.h"

typedef struct humidifier // 가습기 모듈 구조체
{
	GPIO_TypeDef *port;
	uint16_t pin;
	uint16_t delay;
}HUM;

void humidifierInit(HUM * hum); //가습기 모듈 초기화
void humidifierON(HUM* hum);
void humidifierOFF(HUM* hum);
void humidityControl(HUM* hum); // 가습기 모듈 조작

#endif /* INC_HUMIDIFIER_H_ */
