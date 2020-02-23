 /*
 * esp32.h
 *
 *  Created on: 27 sty 2020
 *      Author: Mateusz
 */

#ifndef SRC_HARDWARE_ESP32_DRIVER_ESP32_H_
#define SRC_HARDWARE_ESP32_DRIVER_ESP32_H_

void esp32_Init(void);
void BufferTransfer(void);
void wifi_driver_transmit(char *str);
void StartTransfers(void);

uint8_t esp32_TestCommunication(void);

typedef union{
	uint8_t byte[4];
	float real;
}channel;

typedef struct{
	char syncWord;
	channel kanal[2];
}ESP32_CHANNEL_SEND_T;

#endif /* SRC_HARDWARE_ESP32_DRIVER_ESP32_H_ */
