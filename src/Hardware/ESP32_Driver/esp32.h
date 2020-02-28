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

#define ESP32_TX_CHANNEL 10

typedef union{
	uint8_t byte[4];
	float real;
}unionChannel;

typedef struct{
	char syncWord;
	unionChannel channel[ESP32_TX_CHANNEL];
} __attribute__((packed)) ESP32_CHANNEL_SEND_T;

extern ESP32_CHANNEL_SEND_T esp32_TxBuffer;

#endif /* SRC_HARDWARE_ESP32_DRIVER_ESP32_H_ */
