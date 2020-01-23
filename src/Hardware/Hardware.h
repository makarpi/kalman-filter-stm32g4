/*
 * Hardware.h
 *
 *  Created on: 11 kwi 2017
 *      Author: Janusz
 */

#ifndef SYSTEM_HARDWARE_H_
#define SYSTEM_HARDWARE_H_

#include "main.h"

#define TIMP_S				0.001f

typedef const struct
{
  GPIO_TypeDef *TxPort;
  uint32_t TxPin;
  uint32_t TxPinAlternateFunction;

  GPIO_TypeDef *RxPort;
  uint32_t RxPin;
  uint32_t RxPinAlternateFunction;

  USART_TypeDef *USART;

  DMA_TypeDef* TxDmaType;
  uint32_t TxDmaRequest;
  uint32_t TxDmaChannel;

  DMA_TypeDef* RxDmaType;
  uint32_t RxDmaRequest;
  uint32_t RxDmaChannel;

  TIM_TypeDef *Timer;
} HarvesterDriverHardwareConstants;

// global variables
extern const HarvesterDriverHardwareConstants HarvesterDriverConstants;


// global functions
void HardwareInit(void);

#endif /* SYSTEM_HARDWARE_H_ */
