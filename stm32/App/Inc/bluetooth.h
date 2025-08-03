#ifndef INC_BLUETOOTH_H_
#define INC_BLUETOOTH_H_

#include "bsp.h"
#include "usart.h"

#define Serial		USART2
#define Bluetooth	USART6
#define RX_BUFFER_SIZE 100

void BluetoothInit();
void Transmit_Serial(uint8_t *data, uint16_t len);
void Transmit_Bluetooth(uint8_t *data, uint16_t len);
uint8_t* Bluetooth_RxHandler(UART_HandleTypeDef *huart, uint16_t Size);

#endif /* INC_BLUETOOTH_H_ */
