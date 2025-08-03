#include "bluetooth.h"

static uint8_t rxBuffer2[RX_BUFFER_SIZE];
static uint8_t rxBuffer6[RX_BUFFER_SIZE];

static UART_HandleTypeDef *serial = &huart2;
static UART_HandleTypeDef *bluetooth = &huart6;

void BluetoothInit()
{
	// Receive until USART status becomes idle
	HAL_UARTEx_ReceiveToIdle_IT(serial, rxBuffer2, RX_BUFFER_SIZE);
	HAL_UARTEx_ReceiveToIdle_IT(bluetooth, rxBuffer6, RX_BUFFER_SIZE);
}

void Transmit_Serial(uint8_t *data, uint16_t len)
{
	// Transmit Data in Serial
	HAL_UART_Transmit(serial, data, len, 100);
}

void Transmit_Bluetooth(uint8_t *data, uint16_t len)
{
	// Transmit Data in Bluetooth
	HAL_UART_Transmit(bluetooth, data, len, 100);
}

// Debugging
uint8_t* Bluetooth_RxHandler(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == Bluetooth)
	{
		Transmit_Serial(rxBuffer6, RX_BUFFER_SIZE);
		HAL_UARTEx_ReceiveToIdle_IT(bluetooth, rxBuffer6, RX_BUFFER_SIZE);
		return rxBuffer6;
	}
	return NULL;
}

// Data until USART status becomes idle
//void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
//{
//  if (huart->Instance == USART6)
//  {
//	  // Transmit data in USB Serial
//	  HAL_UART_Transmit(Serial, rxBuffer6, Size, 100);
//
//    // Waiting for reception again
//    HAL_UARTEx_ReceiveToIdle_IT(Bluetooth, rxBuffer6, sizeof(rxBuffer6));
//  }
//  if (huart->Instance == USART2)
//  {
//	// Transmit data in Bluetooth
//	HAL_UART_Transmit(Bluetooth, rxBuffer2, Size, 100);
//
//    // Waiting for reception again
//    HAL_UARTEx_ReceiveToIdle_IT(Serial, rxBuffer2, sizeof(rxBuffer2));
//  }
//}
