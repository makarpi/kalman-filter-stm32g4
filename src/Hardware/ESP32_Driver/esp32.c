/*
 * esp32.c
 *
 *  Created on: 27 sty 2020
 *      Author: Mateusz
 */
#include "main.h"
#include <math.h>

uint8_t ubSend = 0;
uint8_t aStringToSend[] = {0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0xc2};
uint8_t esp32_RxCyclicBuffer[128];

//float sinus = 0.0f, cosinus = 0.0f;
float ro = 0.0f;
#define D_RO M_PI / 1000.0f

ESP32_CHANNEL_SEND_T esp32_TxBuffer;

union{
	char byte[4];
	float real;
}unia;



/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void esp32_uart_Init(void)
{
  LL_USART_InitTypeDef USART_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMAMUX1);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

  /* NVIC priority enable */
  NVIC_SetPriority(DMA1_Channel7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(DMA1_Channel7_IRQn);

  NVIC_SetPriority(DMA1_Channel6_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(DMA1_Channel6_IRQn);

  NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 1));
  NVIC_EnableIRQ(USART1_IRQn);


  /**USART1 GPIO Configuration
  PA9   ------> USART1_TX
  PA10   ------> USART1_RX
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USART1 DMA Init */

  /* USART1_TX Init */
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_7, LL_DMAMUX_REQ_USART1_TX);
  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_7, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_7, LL_DMA_PRIORITY_HIGH);
  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_7, LL_DMA_MODE_NORMAL);
  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_7, LL_DMA_PERIPH_NOINCREMENT);
  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_7, LL_DMA_MEMORY_INCREMENT);
  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_7, LL_DMA_PDATAALIGN_BYTE);
  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_7, LL_DMA_MDATAALIGN_BYTE);

  /* USART1_RX Init */
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_6, LL_DMAMUX_REQ_USART1_RX);
  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_6, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_6, LL_DMA_PRIORITY_HIGH);
  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_6, LL_DMA_MODE_CIRCULAR);
  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_6, LL_DMA_PERIPH_NOINCREMENT);
  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_6, LL_DMA_MEMORY_INCREMENT);
  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_6, LL_DMA_PDATAALIGN_BYTE);
  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_6, LL_DMA_MDATAALIGN_BYTE);

  /* Configure the DMA functional parameters for transmission */
  LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_7,
                         (uint32_t)aStringToSend,
                         LL_USART_DMA_GetRegAddr(USART1, LL_USART_DMA_REG_DATA_TRANSMIT),
                         LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_7));
  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_7, sizeof(aStringToSend));

  LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_6,
                         LL_USART_DMA_GetRegAddr(USART1, LL_USART_DMA_REG_DATA_RECEIVE),
                         (uint32_t)esp32_RxCyclicBuffer,
                         LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_6));
  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_6, 128);

  LL_USART_EnableDMAReq_RX(USART1);
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_6);

  /* Enable interrupt */
  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_7);
  LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_7);

  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_6);
  LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_6);

  USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;

  LL_USART_EnableIT_RTO(USART1);
  LL_USART_SetRxTimeout(USART1, 2000);

  LL_USART_EnableRxTimeout(USART1);
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_SetTXFIFOThreshold(USART1, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetRXFIFOThreshold(USART1, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_DisableFIFO(USART1);
  LL_USART_ConfigAsyncMode(USART1);

  LL_USART_Enable(USART1);





  /* Polling USART1 initialisation */
  while((!(LL_USART_IsActiveFlag_TEACK(USART1))) || (!(LL_USART_IsActiveFlag_REACK(USART1))))
  {
  }
}

void esp32_Init(void)
{
	esp32_uart_Init();
}


/**
	*	@brief	Wysylanie pojedynczego znaku poprzez USART
	*	@param 	data - jeden znak do wyslania
	*	@retval Brak
*/
void USART_putc(char data)
{
	/* oczekiwanie az bufor nadawania bedzie pusty */
	// TODO - dodac timeout
//	while( !((USART3->SR) & USART_SR_TXE));

	while (!LL_USART_IsActiveFlag_TXE(USART1));
	/* przypisanie znaku do rejestru DR */
	LL_USART_TransmitData8(USART1, data);

}

/**
	*	@brief	Wysylanie ciagu znakow poprzez USART
	*	@param 	*str - tablica znakow, wskaznik do tablicy
	*	@retval Brak
*/
void wifi_driver_transmit(char *str)
{
	// TODO - dodac timeout
	char c;
	while ((c = *str++)) USART_putc(c);
}

typedef union{
  int16_t i16bit[3];
  uint8_t u8bit[6];
} axis3bit16_t;

typedef union{
  int16_t i16bit;
  uint8_t u8bit[2];
} axis1bit16_t;

float acceleration_mg[3];
float angular_rate_mdps[3];
float temperature_degC;
axis3bit16_t data_raw_acceleration;
axis3bit16_t data_raw_angular_rate;
axis1bit16_t data_raw_temperature;


void StartTransfers(void)
{
	uint8_t reg;

	lsm6dso_xl_flag_data_ready_get(&dev_ctx, &reg);
	if (reg)
	{
		memset(data_raw_acceleration.u8bit, 0x00, 3 * sizeof(int16_t));
		lsm6dso_acceleration_raw_get(&dev_ctx, data_raw_acceleration.u8bit);
		acceleration_mg[0] = lsm6dso_from_fs2_to_mg(data_raw_acceleration.i16bit[0]);
		acceleration_mg[1] = lsm6dso_from_fs2_to_mg(data_raw_acceleration.i16bit[1]);
		acceleration_mg[2] = lsm6dso_from_fs2_to_mg(data_raw_acceleration.i16bit[2]);
	}

	lsm6dso_gy_flag_data_ready_get(&dev_ctx, &reg);
	if (reg)
	{
	  memset(data_raw_angular_rate.u8bit, 0x00, 3 * sizeof(int16_t));
	  lsm6dso_angular_rate_raw_get(&dev_ctx, data_raw_angular_rate.u8bit);
	  angular_rate_mdps[0] =
			  lsm6dso_from_fs2000_to_mdps(data_raw_angular_rate.i16bit[0]);
	  angular_rate_mdps[1] =
			  lsm6dso_from_fs2000_to_mdps(data_raw_angular_rate.i16bit[1]);
	  angular_rate_mdps[2] =
			  lsm6dso_from_fs2000_to_mdps(data_raw_angular_rate.i16bit[2]);
	}

	lsm6dso_temp_flag_data_ready_get(&dev_ctx, &reg);
	if (reg)
	{
	  memset(data_raw_temperature.u8bit, 0x00, sizeof(int16_t));
	  lsm6dso_temperature_raw_get(&dev_ctx, data_raw_temperature.u8bit);
	  temperature_degC = lsm6dso_from_lsb_to_celsius(data_raw_temperature.i16bit);
	}

	esp32_TxBuffer.syncWord = 0xaa;
	esp32_TxBuffer.channel[0].real = temperature_degC;
	esp32_TxBuffer.channel[1].real = angular_rate_mdps[0];
	esp32_TxBuffer.channel[2].real = angular_rate_mdps[1];
	esp32_TxBuffer.channel[3].real = angular_rate_mdps[2];
	esp32_TxBuffer.channel[4].real = acceleration_mg[0];
	esp32_TxBuffer.channel[5].real = acceleration_mg[1];
	esp32_TxBuffer.channel[6].real = acceleration_mg[2];
	esp32_TxBuffer.channel[7].real = 0.0f;
	esp32_TxBuffer.channel[8].real = 0.0f;
	esp32_TxBuffer.channel[9].real = 0.0f;

	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_7);


	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_7,
						 (uint32_t)&esp32_TxBuffer,
						 LL_USART_DMA_GetRegAddr(USART1, LL_USART_DMA_REG_DATA_TRANSMIT),
						 LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_7));

	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_7, sizeof(esp32_TxBuffer));

	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_7);

	LL_USART_EnableDMAReq_TX(USART1);
}

uint8_t esp32_TestCommunication(void)
{
	wifi_driver_transmit("AT\r\n");

	while(1)
	{
		if(strncmp(strstr((char*) esp32_RxCyclicBuffer, "OK"), "OK", 2) == 0)
		{
//			memset(esp32_RxCyclicBuffer, 0, 128 * sizeof(uint8_t));
			return 1;
		}
	}
	return 0;
}

uint8_t esp32_ResetModule(void)
{
	return 0;
}

uint8_t esp32_ClientMode(void)
{
	return 0;
}


