#include "ap.h"

static DHT11 dht;

static uint32_t prevTime = 0;
static uint32_t currTime = 0;
static uint32_t diffTime = 0;

void apInit()
{
	hwInit();
	dht11Init(&dht, DHT11_Port, DHT11_Pin);
}

void apMain()
{
	char buffer_t[16];
	char buffer_h[16];
	while(1)
	{
		// 문자열 출력용 버퍼에 온습도 정보 저장
		TempHum_to_string(dht.temperature[0], dht.temperature[1], dht.humidity[0], buffer_t, buffer_h);
		// LCD에 문자열 출력
		print_string_to_LCD(buffer_t, buffer_h);

		currTime = HAL_GetTick();

		diffTime = currTime - prevTime;
		ProcessSensorState();
		if(diffTime > 1000)
		{
			if(dht11Read(&dht))
			{
				// Debugging of Serial Port
				printf("Temperature : %d.%d C, Humidity : %d.%d%% \r\n", dht.temperature[0], dht.temperature[1],
						dht.humidity[0], dht.humidity[1]);

				// Debugging of Bluetooth Port
				char str[20] = "";
				sprintf(str, "%d.%d,%d.%d", dht.temperature[0], dht.temperature[1], dht.humidity[0], dht.humidity[1]);
				Transmit_Bluetooth((uint8_t*)str, sizeof(str));

//				// 문자열 출력용 버퍼에 온습도 정보 저장
//				TempHum_to_string(dht.temperature[0], dht.temperature[1], dht.humidity[0], buffer_t, buffer_h);
//				// LCD에 문자열 출력
//				print_string_to_LCD(buffer_t, buffer_h);
			}
			prevTime = currTime;
		}
	}
}
