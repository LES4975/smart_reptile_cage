#include "dcfan.h"

/*void DCFanOn_Tim() // DC 팬을 듀티사이클 50%로 켜기
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
//    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 500); // 듀티사이클을 50%로 조정. CCR1 값을 직접 조절하는 것보다 안전함.
}

void DCFanPause_Tim()
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
}

void DCFanOff_Tim() // DC 팬 가동을 완전 종료
{
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}*/

// 만약 DC 팬을 GPIO_Output 핀과 연결해서, 정속 제어만 할 때...

void DCFanOn_GPIO()
{
	HAL_GPIO_WritePin(FAN_PORT, FAN_PIN, GPIO_PIN_SET);
}

void DCFanOff_GPIO()
{
	HAL_GPIO_WritePin(FAN_PORT, FAN_PIN, GPIO_PIN_RESET);
}
