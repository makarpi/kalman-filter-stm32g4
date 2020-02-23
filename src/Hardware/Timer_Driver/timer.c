/*
 * timer.c
 *
 *  Created on: 14 gru 2019
 *      Author: Mateusz
 */
#include "main.h"


#define HRTIM_INPUT_CLOCK 170000000
#define TIMD_PWM_FREQ 100000
#define TIMD_DUTY_CYCLE 0.75
#define LED2_Pin LL_GPIO_PIN_5
#define LED2_GPIO_Port GPIOA


#define TIMD_PERIOD ((uint16_t)((((uint64_t)HRTIM_INPUT_CLOCK) * 32) / TIMD_PWM_FREQ))

/* Private defines -----------------------------------------------------------*/
#define HRTIM_INPUT_CLOCK 170000000
#define TIMD_PWM_FREQ 100000
#define DEADTIME_IN_NS 100
#define LED2_Pin LL_GPIO_PIN_5
#define LED2_GPIO_Port GPIOA
#define T_SWDIO_Pin LL_GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin LL_GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define T_SWO_Pin LL_GPIO_PIN_3
#define T_SWO_GPIO_Port GPIOB
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif
//#define TIMD_PERIOD ((uint16_t)((((uint64_t)HRTIM_INPUT_CLOCK) * 32) / TIMD_PWM_FREQ))

#define DEADTIME ((uint16_t)(((uint64_t)HRTIM_INPUT_CLOCK * 32 * DEADTIME_IN_NS) / 1000000000))



void Timer_Init(void)
{

	  /* USER CODE BEGIN HRTIM1_Init 0 */

	  /* USER CODE END HRTIM1_Init 0 */

	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* Peripheral clock enable */
	  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_HRTIM1);

	  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
	  /**HRTIM1 GPIO Configuration
	  PB8-BOOT0   ------> HRTIM1_EEV8
	  PB9   ------> HRTIM1_EEV5
	  */
	  GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_13;
	  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_13;
	  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /* HRTIM1 interrupt Init */
	  NVIC_SetPriority(HRTIM1_TIMD_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	  NVIC_EnableIRQ(HRTIM1_TIMD_IRQn);

	  /* USER CODE BEGIN HRTIM1_Init 1 */

	  /* USER CODE END HRTIM1_Init 1 */
	  LL_HRTIM_ConfigDLLCalibration(HRTIM1, LL_HRTIM_DLLCALIBRATION_MODE_CONTINUOUS, LL_HRTIM_DLLCALIBRATION_RATE_3);

	  /* Poll for DLL end of calibration */
	#if (USE_TIMEOUT == 1)
	  uint32_t Timeout = 10; /* Timeout Initialization */
	#endif  /*USE_TIMEOUT*/

	  while(LL_HRTIM_IsActiveFlag_DLLRDY(HRTIM1) == RESET){
	#if (USE_TIMEOUT == 1)
	    if (LL_SYSTICK_IsActiveCounterFlag())  /* Check Systick counter flag to decrement the time-out value */
	    {
	        if(Timeout-- == 0)
	        {
	          Error_Handler();  /* error management */
	        }
	    }
	#endif  /* USE_TIMEOUT */
	  }

	  LL_HRTIM_EE_SetPrescaler(HRTIM1, LL_HRTIM_EE_PRESCALER_DIV1);
	  LL_HRTIM_EE_SetSrc(HRTIM1, LL_HRTIM_EVENT_5, LL_HRTIM_EEV5SRC_GPIO);
	  LL_HRTIM_EE_SetPolarity(HRTIM1, LL_HRTIM_EVENT_5, LL_HRTIM_EE_POLARITY_HIGH);
	  LL_HRTIM_EE_SetSensitivity(HRTIM1, LL_HRTIM_EVENT_5, LL_HRTIM_EE_SENSITIVITY_LEVEL);
	  LL_HRTIM_EE_SetFastMode(HRTIM1, LL_HRTIM_EVENT_5, LL_HRTIM_EE_FASTMODE_DISABLE);
	  LL_HRTIM_EE_SetSrc(HRTIM1, LL_HRTIM_EVENT_8, LL_HRTIM_EEV8SRC_GPIO);
	  LL_HRTIM_EE_SetPolarity(HRTIM1, LL_HRTIM_EVENT_8, LL_HRTIM_EE_POLARITY_HIGH);
	  LL_HRTIM_EE_SetSensitivity(HRTIM1, LL_HRTIM_EVENT_8, LL_HRTIM_EE_SENSITIVITY_BOTHEDGES);
	  LL_HRTIM_EE_SetFilter(HRTIM1, LL_HRTIM_EVENT_8, LL_HRTIM_EE_FILTER_NONE);
	  LL_HRTIM_TIM_SetPrescaler(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_PRESCALERRATIO_MUL32);
	  LL_HRTIM_TIM_SetCounterMode(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_MODE_CONTINUOUS);
	  LL_HRTIM_TIM_SetPeriod(HRTIM1, LL_HRTIM_TIMER_D, TIMD_PERIOD);
	  LL_HRTIM_TIM_SetRepetition(HRTIM1, LL_HRTIM_TIMER_D, 0x02);
	  LL_HRTIM_TIM_SetUpdateGating(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_UPDATEGATING_INDEPENDENT);
	  LL_HRTIM_TIM_SetCountingMode(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_COUNTING_MODE_UP);
	  LL_HRTIM_TIM_SetTriggeredHalfMode(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_TRIGHALF_DISABLED);
	  LL_HRTIM_TIM_SetComp1Mode(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_GTCMP1_EQUAL);
	  LL_HRTIM_TIM_SetComp3Mode(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_GTCMP3_EQUAL);
	  LL_HRTIM_TIM_SetDACTrig(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_DACTRIG_NONE);
	  LL_HRTIM_TIM_DisableHalfMode(HRTIM1, LL_HRTIM_TIMER_D);
	  LL_HRTIM_TIM_SetInterleavedMode(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_INTERLEAVED_MODE_DISABLED);
	  LL_HRTIM_TIM_DisableStartOnSync(HRTIM1, LL_HRTIM_TIMER_D);
	  LL_HRTIM_TIM_DisableResetOnSync(HRTIM1, LL_HRTIM_TIMER_D);
	  LL_HRTIM_TIM_EnablePreload(HRTIM1, LL_HRTIM_TIMER_D);
	  LL_HRTIM_TIM_DisableResyncUpdate(HRTIM1, LL_HRTIM_TIMER_D);
	  LL_HRTIM_TIM_SetUpdateTrig(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_UPDATETRIG_NONE|LL_HRTIM_UPDATETRIG_REPETITION);
	  LL_HRTIM_TIM_SetResetTrig(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_RESETTRIG_NONE);
	  LL_HRTIM_TIM_DisablePushPullMode(HRTIM1, LL_HRTIM_TIMER_D);
	  LL_HRTIM_TIM_DisableDeadTime(HRTIM1, LL_HRTIM_TIMER_D);
	  LL_HRTIM_TIM_SetBurstModeOption(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_BURSTMODE_MAINTAINCLOCK);
	  LL_HRTIM_ForceUpdate(HRTIM1, LL_HRTIM_TIMER_D);
	  LL_HRTIM_TIM_SetCompare1(HRTIM1, LL_HRTIM_TIMER_D, DEADTIME);
	  LL_HRTIM_TIM_SetCompareMode(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_COMPAREUNIT_2, LL_HRTIM_COMPAREMODE_DELAY_CMP3);
	  LL_HRTIM_TIM_SetCompare2(HRTIM1, LL_HRTIM_TIMER_D, DEADTIME);
	  LL_HRTIM_TIM_SetCompare3(HRTIM1, LL_HRTIM_TIMER_D, TIMD_PERIOD/2);
	  LL_HRTIM_TIM_SetCompare4(HRTIM1, LL_HRTIM_TIMER_D, DEADTIME);
	  LL_HRTIM_TIM_SetCompareMode(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_COMPAREUNIT_4, LL_HRTIM_COMPAREMODE_DELAY_NOTIMEOUT);
	  LL_HRTIM_TIM_SetCaptureTrig(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_CAPTUREUNIT_1, LL_HRTIM_CAPTURETRIG_EEV_8);
	  LL_HRTIM_TIM_SetCaptureTrig(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_CAPTUREUNIT_2, LL_HRTIM_CAPTURETRIG_EEV_8);
	  LL_HRTIM_TIM_SetEventFilter(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_EVENT_8, LL_HRTIM_EEFLTR_BLANKINGCMP1);
	  LL_HRTIM_TIM_SetEventLatchStatus(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_EVENT_8, LL_HRTIM_EELATCH_ENABLED);
	  LL_HRTIM_OUT_SetPolarity(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUT_POSITIVE_POLARITY);
	  LL_HRTIM_OUT_SetOutputSetSrc(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUTPUTSET_TIMCMP1);
	  LL_HRTIM_OUT_SetOutputResetSrc(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUTPUTRESET_TIMCMP3|LL_HRTIM_OUTPUTRESET_EEV_5
	                              |LL_HRTIM_OUTPUTRESET_EEV_8);
	  LL_HRTIM_OUT_SetIdleMode(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUT_NO_IDLE);
	  LL_HRTIM_OUT_SetIdleLevel(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUT_IDLELEVEL_INACTIVE);
	  LL_HRTIM_OUT_SetFaultState(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUT_FAULTSTATE_NO_ACTION);
	  LL_HRTIM_OUT_SetChopperMode(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUT_CHOPPERMODE_DISABLED);
	  LL_HRTIM_OUT_SetPolarity(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUT_POSITIVE_POLARITY);
	  LL_HRTIM_OUT_SetOutputSetSrc(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUTPUTSET_TIMCMP2);
	  LL_HRTIM_OUT_SetOutputResetSrc(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUTPUTRESET_TIMCMP4|LL_HRTIM_OUTPUTRESET_TIMPER
	                              |LL_HRTIM_OUTPUTRESET_EEV_5);
	  LL_HRTIM_OUT_SetIdleMode(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUT_NO_IDLE);
	  LL_HRTIM_OUT_SetIdleLevel(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUT_IDLELEVEL_INACTIVE);
	  LL_HRTIM_OUT_SetFaultState(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUT_FAULTSTATE_NO_ACTION);
	  LL_HRTIM_OUT_SetChopperMode(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUT_CHOPPERMODE_DISABLED);
	  /* USER CODE BEGIN HRTIM1_Init 2 */

	  /* This is to override a limitaion in CubeMX v5.2.0 */
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;

	  /* USER CODE END HRTIM1_Init 2 */
	  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
	  /**HRTIM1 GPIO Configuration
	  PB14   ------> HRTIM1_CHD1
	  PB15   ------> HRTIM1_CHD2
	  */
	  GPIO_InitStruct.Pin = LL_GPIO_PIN_14;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_13;
	  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LL_GPIO_PIN_15;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_13;
	  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void Timer_Timer6_init(void)
{
	LL_TIM_InitTypeDef TIM_InitStruct = {0};
	LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};


	/* Peripheral clock enable */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);

	/* TIM6 interrupt Init */
	NVIC_SetPriority(TIM6_DAC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(TIM6_DAC_IRQn);

	/* USER CODE BEGIN TIM6_Init 1 */

	/* USER CODE END TIM6_Init 1 */
	TIM_InitStruct.Prescaler = 1000-1;
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
	TIM_InitStruct.Autoreload = 1000;
	TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	LL_TIM_Init(TIM6, &TIM_InitStruct);
	LL_TIM_DisableARRPreload(TIM6);
	LL_TIM_EnableIT_UPDATE(TIM6);
	//	  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_TOGGLE;
	//	  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
	//	  TIM_OC_InitStruct.OCNState = LL_TIM_OCSTATE_DISABLE;
	//	  TIM_OC_InitStruct.CompareValue = tim_pulse_value;
	//	  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
//	LL_TIM_OC_Init(TIM6, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
	LL_TIM_OC_DisableFast(TIM6, LL_TIM_CHANNEL_CH1);
	LL_TIM_SetOCRefClearInputSource(TIM6, LL_TIM_OCREF_CLR_INT_COMP1);
	LL_TIM_DisableExternalClock(TIM6);
	LL_TIM_ConfigETR(TIM6, LL_TIM_ETR_POLARITY_NONINVERTED, LL_TIM_ETR_PRESCALER_DIV1, LL_TIM_ETR_FILTER_FDIV1);
	LL_TIM_SetTriggerOutput(TIM6, LL_TIM_TRGO_RESET);
	LL_TIM_DisableMasterSlaveMode(TIM6);

}

void TIM6_DAC_IRQHandler(void)
{
	if(LL_TIM_IsActiveFlag_UPDATE(TIM6))
	{
		LL_TIM_ClearFlag_UPDATE(TIM6);

	}

}
