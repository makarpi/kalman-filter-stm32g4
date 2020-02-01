/*
 * mems.c
 *
 *  Created on: 26 sty 2020
 *      Author: Mateusz
 */
#include <stdlib.h>

#include "main.h"

static void LSM6DSO_Init(void) {
	LL_I2C_InitTypeDef I2C_InitStruct = { 0 };

	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
	/**I2C1 GPIO Configuration
	 PB8   ------> I2C1_SCL
	 PB9   ------> I2C1_SDA
	 */
	GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* Peripheral clock enable */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

	/* USER CODE BEGIN I2C1_Init 1 */
	/* Configure Event IT:
	 *  - Set priority for I2C1_EV_IRQn
	 *  - Enable I2C1_EV_IRQn
	 */
//	  NVIC_SetPriority(I2C1_EV_IRQn, 0);
//	  NVIC_EnableIRQ(I2C1_EV_IRQn);
	/* Configure Error IT:
	 *  - Set priority for I2C1_ER_IRQn
	 *  - Enable I2C1_ER_IRQn
	 */
//	  NVIC_SetPriority(I2C1_ER_IRQn, 0);
//	  NVIC_EnableIRQ(I2C1_ER_IRQn);
	/* Reset I2C1 data registers */
	if (LL_I2C_DeInit(I2C1) != SUCCESS) {
		/* Initialization Error */
		LED_Blinking(LED_BLINK_ERROR);
	}
	/* USER CODE END I2C1_Init 1 */
	/** I2C Initialization
	 */

//	  __LL_I2C_CONVERT_TIMINGS()
	I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
//	  I2C_InitStruct.Timing = __LL_I2C_CONVERT_TIMINGS(1, ;
	I2C_InitStruct.Timing = 0x00e05cff;
	//	  I2C_InitStruct.Timing = 0x00303D5B;
	I2C_InitStruct.AnalogFilter = LL_I2C_ANALOGFILTER_ENABLE;
	I2C_InitStruct.DigitalFilter = 0;
	I2C_InitStruct.OwnAddress1 = 0;
	I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
	I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
	LL_I2C_Init(I2C1, &I2C_InitStruct);
	LL_I2C_EnableAutoEndMode(I2C1);
	LL_I2C_SetOwnAddress2(I2C1, 0, LL_I2C_OWNADDRESS2_NOMASK);
	LL_I2C_DisableOwnAddress2(I2C1);
	LL_I2C_DisableGeneralCall(I2C1);
	LL_I2C_EnableClockStretching(I2C1);
	/* USER CODE BEGIN I2C1_Init 2 */
	/* Initialize I2C instance according to parameters defined in initialization structure. */
	if (LL_I2C_Init(I2C1, &I2C_InitStruct) != SUCCESS) {
		/* Initialization Error */
		LED_Blinking(LED_BLINK_ERROR);
	}

	/* (5) Enable I2C1 transfer complete/error interrupts:
	 *  - Enable Receive Interrupt
	 *  - Enable Not acknowledge received interrupt
	 *  - Enable Error interrupts
	 *  - Enable Stop interrupt
	 */
	LL_I2C_EnableIT_RX(I2C1);
	LL_I2C_EnableIT_NACK(I2C1);
	LL_I2C_EnableIT_ERR(I2C1);
	LL_I2C_EnableIT_STOP(I2C1);
	/* USER CODE END I2C1_Init 2 */
}

void Mems_Init(void) {
	LSM6DSO_Init();
}

//char pTransmitBuffer[2] = { 0x10, 0xa0 };

//static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
int32_t LSM6DSO_I2C_Write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{

	uint16_t transmitBufferIndex = 0;
//	uint8_t *pTransmitBuffer;

	/* (1) Initiate a Start condition to the Slave device ***********************/

	/* Master Generate Start condition for a write request :              */
	/*    - to the Slave with a 7-Bit SLAVE_OWN_ADDRESS                   */
	/*    - with a auto stop condition generation when transmit all bytes */
	LL_I2C_HandleTransfer(handle, 0xd6, LL_I2C_ADDRSLAVE_7BIT, len + 1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);

	/* (2) Loop until end of transfer received (STOP flag raised) ***************/

#if (USE_TIMEOUT == 1)
  Timeout = I2C_SEND_TIMEOUT_TXIS_MS;
#endif /* USE_TIMEOUT */

	/* Loop until STOP flag is raised  */
	while (!LL_I2C_IsActiveFlag_STOP(handle)) {
		/* (2.1) Transmit data (TXIS flag raised) *********************************/

		/* Check TXIS flag value in ISR register */
		if (LL_I2C_IsActiveFlag_TXIS(handle)) {
			/* Write data in Transmit Data register.
			 TXIS flag is cleared by writing data in TXDR register */
			if(transmitBufferIndex++ == 0)
			{
				LL_I2C_TransmitData8(handle, reg);
			}
			else
			{
				LL_I2C_TransmitData8(handle, *(bufp++));
//				transmitBufferIndex
			}

#if (USE_TIMEOUT == 1)
      Timeout = I2C_SEND_TIMEOUT_TXIS_MS;
#endif /* USE_TIMEOUT */
		}

#if (USE_TIMEOUT == 1)
    /* Check Systick counter flag to decrement the time-out value */
    if (LL_SYSTICK_IsActiveCounterFlag())
    {
      if (Timeout-- == 0)
      {
        /* Time-out occurred. Set LED2 to blinking mode */
        LED_Blinking(LED_BLINK_SLOW);
      }
    }
#endif /* USE_TIMEOUT */
	}

	/* (3) Clear pending flags, Data consistency are checking into Slave process */

	/* End of I2C_SlaveReceiver_MasterTransmitter Process */
	LL_I2C_ClearFlag_STOP(handle);

	return 0;
}

char RxBuffer[32];


//void LSM6DSO_I2C_Read(uint8_t Addr)
int32_t LSM6DSO_I2C_Read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
	int BufferIndex = 0;

	LL_I2C_HandleTransfer(handle, 0xd6, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_AUTOEND,
			LL_I2C_GENERATE_START_WRITE);

	while (!LL_I2C_IsActiveFlag_STOP(handle)) // Loop until end of transfer received (STOP flag raised)
	{
		/* Check TXIS flag value in ISR register */
		if (LL_I2C_IsActiveFlag_TXIS(handle))
		{
			/* Write data in Transmit Data register. TXIS flag is cleared by writing data in TXDR register */
			LL_I2C_TransmitData8(handle, reg);
		}
	}

	LL_I2C_ClearFlag_STOP(handle);

	LL_I2C_HandleTransfer(handle, 0xd6, LL_I2C_ADDRSLAVE_7BIT, len, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);

	while (!LL_I2C_IsActiveFlag_STOP(handle)) // Loop until end of transfer received (STOP flag raised)
	{
		/* Check RXNE flag value in ISR register */
		if (LL_I2C_IsActiveFlag_RXNE(handle))
		{
			/* Read character in Receive Data register. RXNE flag is cleared by reading data in RXDR register */
			*(bufp++) = LL_I2C_ReceiveData8(handle);
		}
	}

	LL_I2C_ClearFlag_STOP(handle);

	return 0;
}

