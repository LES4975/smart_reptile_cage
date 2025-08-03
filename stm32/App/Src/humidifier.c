// 가습기 모듈 구조체 선언, 가습기 초기화 함수와 가습기 모듈 조작 함수 정의
#include "humidifier.h"

void humidifierInit(HUM* hum) // 핀 설정이 바뀐 경우 여기를 수정해 주세요!
{
	hum->port = GPIOB;
	hum->pin = GPIO_PIN_4;
	hum->delay = 5000;
	HAL_GPIO_WritePin(hum->port, hum->pin, 0);
}

void humidifierON(HUM* hum)
{
	HAL_GPIO_WritePin(hum->port, hum->pin, SET);
}

void humidifierOFF(HUM* hum)
{
	HAL_GPIO_WritePin(hum->port, hum->pin, RESET);
}

void humidityControl(HUM* hum) // 가습기 모듈을 5초동안 가동합니다.
{
//	HAL_GPIO_WritePin(hum->port, hum->pin, 1);
	humidifierON(hum);
	HAL_Delay(hum->delay); // 가동 시간
//	HAL_GPIO_WritePin(hum->port, hum->pin, 0);
	humidifierOFF(hum);
	HAL_Delay(10); // 혹시나 해서 넣은 딜레이
}
