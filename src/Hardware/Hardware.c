/*
 * Hardware.c
 *
 *  Created on: 11 kwi 2017
 *      Author: Janusz
 */

#include "main.h"


const HarvesterDriverHardwareConstants HarvesterDriverConstants = {
  .TxPort = GPIOA,
  .TxPin = LL_GPIO_PIN_2,
  .TxPinAlternateFunction = LL_GPIO_AF_7,

  .RxPort = GPIOA,
  .RxPin = LL_GPIO_PIN_3,
  .RxPinAlternateFunction = LL_GPIO_AF_7,

  .USART = USART2,

  .TxDmaType = DMA1,
//  .TxDmaRequest = LL_DMA_,
  .TxDmaChannel = LL_DMA_CHANNEL_7,

  .RxDmaType = DMA1,
//  .RxDmaRequest = LL_DMA_REQUEST_2,
  .RxDmaChannel = LL_DMA_CHANNEL_6,

  .Timer = TIM3,
};

void HardwareInit(void)
{
  go_DebugPort.Init();
}

