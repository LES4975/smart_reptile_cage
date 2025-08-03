/*
 * dht11.h
 *
 *  Created on: Mar 28, 2025
 *      Author: USER
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "bsp.h"
#include "delay.h"

enum
{
	INPUT,
	OUTPUT
};

typedef struct
{
	GPIO_TypeDef *port;			// data port
	uint16_t     pin;		// data pin number
	uint8_t		 temperature[2];	// temperature value
	uint8_t		 humidity[2];		// humidity value
}DHT11;

void dht11Init(DHT11 *dht, GPIO_TypeDef *port, uint16_t pin);
void dht11GpioMode(DHT11 *dht, uint8_t mode);
uint8_t	dht11Read(DHT11 *dht);
void ByteToBit(uint8_t *byteValue, uint8_t *bitValue, uint8_t index);
uint8_t ResponseSignal(DHT11 *dht, uint16_t timer, GPIO_PinState state);

#endif /* INC_DHT11_H_ */
