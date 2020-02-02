#include "stm32g4xx.h"
#include "main.h"
#include <stdio.h>
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
typedef union{
  int16_t i16bit[3];
  uint8_t u8bit[6];
} axis3bit16_t;

typedef union{
  int16_t i16bit;
  uint8_t u8bit[2];
} axis1bit16_t;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t whoamI, rst;
float acceleration_mg[3];
float angular_rate_mdps[3];
float temperature_degC;
axis3bit16_t data_raw_acceleration;
axis3bit16_t data_raw_angular_rate;
axis1bit16_t data_raw_temperature;

/* Private function prototypes -----------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config(void);

int main(void)
{
	stmdev_ctx_t dev_ctx;

	/*
	*  Initialize mems driver interface
	*/
	dev_ctx.write_reg = LSM6DSO_I2C_Write;
	dev_ctx.read_reg = LSM6DSO_I2C_Read;
	dev_ctx.handle = I2C1;

	Main_HardwareInit();


	/*
	 *  Check device ID
	*/
	lsm6dso_device_id_get(&dev_ctx, &whoamI);
	if (whoamI != LSM6DSO_ID)
	while(1);

	/*
	 *  Restore default configuration
	*/
	lsm6dso_reset_set(&dev_ctx, PROPERTY_ENABLE);
	do {
	lsm6dso_reset_get(&dev_ctx, &rst);
	} while (rst);

	/*
	 * Disable I3C interface
	*/
	lsm6dso_i3c_disable_set(&dev_ctx, LSM6DSO_I3C_DISABLE);

	/*
	*  Enable Block Data Update
	*/
	lsm6dso_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);

	/*
	* Set Output Data Rate
	*/
	lsm6dso_xl_data_rate_set(&dev_ctx, LSM6DSO_XL_ODR_6667Hz);
	lsm6dso_gy_data_rate_set(&dev_ctx, LSM6DSO_GY_ODR_6667Hz);

	/*
	* Set full scale
	*/
	lsm6dso_xl_full_scale_set(&dev_ctx, LSM6DSO_2g);
	lsm6dso_gy_full_scale_set(&dev_ctx, LSM6DSO_2000dps);

	/*
	* Configure filtering chain(No aux interface)
	*
	* Accelerometer - LPF1 + LPF2 path
	*/
	lsm6dso_xl_hp_path_on_out_set(&dev_ctx, LSM6DSO_LP_ODR_DIV_100);
	lsm6dso_xl_filter_lp2_set(&dev_ctx, PROPERTY_ENABLE);


	while (1)
	{

		uint8_t reg;

		/*
		 * Read output only if new xl value is available
		 */
		lsm6dso_xl_flag_data_ready_get(&dev_ctx, &reg);
		if (reg)
		{
			memset(data_raw_acceleration.u8bit, 0x00, 3 * sizeof(int16_t));
			lsm6dso_acceleration_raw_get(&dev_ctx, data_raw_acceleration.u8bit);
			acceleration_mg[0] = lsm6dso_from_fs2_to_mg(data_raw_acceleration.i16bit[0]);
			acceleration_mg[1] = lsm6dso_from_fs2_to_mg(data_raw_acceleration.i16bit[1]);
			acceleration_mg[2] = lsm6dso_from_fs2_to_mg(data_raw_acceleration.i16bit[2]);

			LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
//			LL_mDelay(500);
		}

		lsm6dso_gy_flag_data_ready_get(&dev_ctx, &reg);
		    if (reg)
		    {
		      /*
		       * Read angular rate field data
		       */
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
		      /*
		       * Read temperature data
		       */
		      memset(data_raw_temperature.u8bit, 0x00, sizeof(int16_t));
		      lsm6dso_temperature_raw_get(&dev_ctx, data_raw_temperature.u8bit);
		      temperature_degC = lsm6dso_from_lsb_to_celsius(data_raw_temperature.i16bit);
		    }
	}
}

/**
  * @brief This function handles ADC interrupt.
  */
void Main_AdcInterrupt(void)
{

}

/**
  * @brief This function initialization Hardware.
  */
void Main_HardwareInit(void)
{
	/* Local variables */
	LL_GPIO_InitTypeDef LED2_GPIO_User = {0};

	/* Configure the system clock to 170 MHz */
	SystemClock_Config();

	/* Enable all GPIO clock */
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOE);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOF);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOG);

	/* Init GPIO LED2 */
	LED2_GPIO_User.Pin = LED2_PIN;
	LED2_GPIO_User.Mode = LL_GPIO_MODE_OUTPUT;
	LED2_GPIO_User.Pull = LL_GPIO_PULL_NO;
	LED2_GPIO_User.Speed = LL_GPIO_SPEED_FAST;

	LL_GPIO_Init(LED2_GPIO_PORT, &LED2_GPIO_User);

	/* ADC initialization function */
//	ADC_Init();

	/* HRTIM initialization function */
//	Timer_Init();

	/* MEMS initialization function */
	Mems_Init();
}

/**
  * @brief This function configure interrupts priority.
  */
void Main_InterruptsPriorityConfiguration(void)
{

}

/**
  * @brief This function enables interrupts.
  */
void Main_EnableInterrupt(void)
{

}

/* ==============   BOARD SPECIFIC CONFIGURATION CODE BEGIN    ============== */
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 170000000
  *            HCLK(Hz)                       = 170000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 4
  *            PLL_N                          = 85
  *            PLL_P                          = 2
  *            PLL_Q                          = 2
  *            PLL_R                          = 2
  *            Flash Latency(WS)              = 8
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Enable voltage range 1 boost mode for frequency above 150 Mhz */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  LL_PWR_EnableRange1BoostMode();
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* Set Flash Latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_8);

  /* HSI already enabled at reset */

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_4, 85, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* PLL system Output activation */
  LL_RCC_PLL_EnableDomain_SYS();

  /* Sysclk activation on the main PLL */
  /* Intermediate AHB prescaler 2 when target frequency clock is higher than 80 MHz */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  /* Insure 1�s transition state at intermediate medium speed clock based on DWT */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT = 0;
  while(DWT->CYCCNT < 100);

  /* AHB prescaler 1 */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 170MHz */
  /* This frequency can be calculated through LL RCC macro */
  /* ex: __LL_RCC_CALC_PLLCLK_FREQ(HSI_VALUE,
                                  LL_RCC_PLLM_DIV_4, 85, LL_RCC_PLLR_DIV_2) */
  LL_Init1msTick(170000000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(170000000);
}
/* ==============   BOARD SPECIFIC CONFIGURATION CODE END      ============== */
