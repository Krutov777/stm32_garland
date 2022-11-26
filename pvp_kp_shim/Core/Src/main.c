/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "time.h"
#include "stdio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
uint8_t flag_key1_press = 1;
uint32_t time_key1_press = 0;
uint32_t count = 16384;

uint32_t delay = 891;//n o?aoii iioeceiaoeae o0
uint32_t i;
volatile uint32_t d; //
uint32_t delay_1sec_one_led = 891;
uint32_t delay_05sec_one_led = 441;
uint32_t delay_025sec_one_led = 216;
uint32_t delay_004sec_one_led = 26;//4in iia?aoiinou
uint32_t delay_1sec_two_leds = 1794;
uint32_t delay_05sec_two_leds = 894;
uint32_t delay_025sec_two_leds = 443;
uint32_t delay_004sec_two_leds = 65;
_Bool direction_mode = 0;
uint8_t number_leds_mode = 1;
uint8_t switch_speeds_mode = 1;
_Bool restart = 0;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
void switch_speeds_one_led(uint16_t speed_mode);
void switch_speeds_two_led(uint16_t speed_mode);
void Clockwise_One(void);
void Counterclockwise_One(void);
void Clockwise_Two(void);
void Counterclockwise_Two(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int SER_PutChar(int c) {
  ITM_SendChar (c);
  return (c);
}
 
int fputc(int c, FILE *f) {
  return (SER_PutChar(c));
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//uint32_t i, d; // d-aey caaa??ee
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start (&htim1, TIM_CHANNEL_1);//caionoei OEI
	HAL_TIMEx_PWMN_Start (&htim1, TIM_CHANNEL_1);//caionoei OEI
	HAL_TIM_PWM_Start (&htim1, TIM_CHANNEL_2);//caionoei OEI
	HAL_TIMEx_PWMN_Start (&htim1, TIM_CHANNEL_2);//caionoei OEI
	HAL_TIM_PWM_Start (&htim1, TIM_CHANNEL_3);//caionoei OEI
	HAL_TIMEx_PWMN_Start (&htim1, TIM_CHANNEL_3);//caionoei OEI
	HAL_TIM_PWM_Start (&htim1, TIM_CHANNEL_4);//caionoei OEI
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_BREAK);
	
	TIM1->CCER &= ~TIM_CCER_CC2NE;
	TIM1->CCER &= ~TIM_CCER_CC3NE;
	
	
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
		if(number_leds_mode == 1) {
			switch_speeds_one_led(switch_speeds_mode);
			if(direction_mode == 0) {
				Clockwise_One();
				printf("time = %i\n", HAL_GetTick()*2);
			}
			else if(direction_mode == 1) {
				Counterclockwise_One();
				printf("time = %i\n", HAL_GetTick()*2);
			}
		}
		else if(number_leds_mode == 2) {
			switch_speeds_two_led(switch_speeds_mode);
			if(direction_mode == 0) {
				Clockwise_Two();
				printf("time = %i\n", HAL_GetTick()*2);
			}
			else if(direction_mode == 1) {
				Counterclockwise_Two();
				printf("time = %i\n", HAL_GetTick()*2);
			}
		}
  }
  /* USER CODE END 3 */
}

void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
	if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 100)
	{
		flag_key1_press = 1;
	}
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_RESET && flag_key1_press) // iianoaaeou naie iei
	{
		flag_key1_press = 0;
		// aaenoaea ia ia?aoea
		if(switch_speeds_mode == 1 || switch_speeds_mode == 2 || switch_speeds_mode == 3)
			++switch_speeds_mode;
		else
			switch_speeds_mode = 1;
		printf("speed = %i\n", switch_speeds_mode);
		restart = 1;
		time_key1_press = HAL_GetTick();
	}
  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */
  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
	if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 100)
	{
		flag_key1_press = 1;
	}
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_RESET && flag_key1_press) // iianoaaeou naie iei
	{
		flag_key1_press = 0;
		// aaenoaea ia ia?aoea
		if(direction_mode == 1)
			direction_mode = 0;
		else direction_mode = 1;
		printf("direction = %i\n", direction_mode);	
		restart = 1;
		time_key1_press = HAL_GetTick();
	}
  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);

  /* USER CODE BEGIN EXTI1_IRQn 1 */
  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line2 and Touch Sense controller.
  */
void EXTI2_TSC_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_TSC_IRQn 0 */
	if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 100)
	{
		flag_key1_press = 1;
	}
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == GPIO_PIN_RESET && flag_key1_press) // iianoaaeou naie iei
	{
		flag_key1_press = 0;
		// aaenoaea ia ia?aoea
		if(number_leds_mode == 1)
			++number_leds_mode;
		else number_leds_mode = 1;
		printf("number of leds = %i\n", number_leds_mode);
		restart = 1;
		time_key1_press = HAL_GetTick();
	}
  /* USER CODE END EXTI2_TSC_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  /* USER CODE BEGIN EXTI2_TSC_IRQn 1 */
  /* USER CODE END EXTI2_TSC_IRQn 1 */
}



void switch_speeds_one_led(uint16_t speed_mode) {
	// speed mode =
	// 1 - 1 n ia ca?eaaiea e caoooaiea, oa 2 n
	// 2 - 0.5 n, oa 1 n
	// 3 - 0.25 n, oa 0.5 n
	// 4 - 0.04 n, oa 0.08 n
	if (speed_mode == 1) {
		delay = delay_1sec_one_led;
	}
	else if (speed_mode == 2) {
		delay = delay_05sec_one_led;
	}
	else if (speed_mode == 3) {
		delay = delay_025sec_one_led;
	}
	else  {
		delay = delay_004sec_one_led;
	}
}

void switch_speeds_two_led(uint16_t speed_mode) {
	// speed mode =
	// 1 - 1 n ia ca?eaaiea e caoooaiea, oa 2 n
	// 2 - 0.5 n, oa 1 n
	// 3 - 0.25 n, oa 0.5 n
	// 4 - 0.04 n, oa 0.08 n
	
	if (speed_mode == 1) {
		delay = delay_1sec_two_leds;
	}
	else if (speed_mode == 2) {
		delay = delay_05sec_two_leds;
	}
	else if (speed_mode == 3) {
		delay = delay_025sec_two_leds;
	}
	else {
		delay = delay_004sec_two_leds;
	}
}

void Clockwise_One(void)
{
	  uint32_t count_16_parts = count/16;
		TIM1->CCER &= ~TIM_CCER_CC4E;
		TIM1->CCR4 = 0;
	
		TIM1->CCER |= TIM_CCER_CC1NE;
		TIM1->CCER &= ~TIM_CCER_CC1E;
		for(i=0;i<=count_16_parts*14;i++)
		{
			if (restart){
				TIM1->CCER &= ~(TIM_CCER_CC1E | TIM_CCER_CC1NE 
				| TIM_CCER_CC2E | TIM_CCER_CC2NE
				| TIM_CCER_CC3E | TIM_CCER_CC3NE
				| TIM_CCER_CC4E);
				TIM1->CCR1 = 0;
				TIM1->CCR2 = 0;
				TIM1->CCR3 = 0;
				TIM1->CCR4 = 0;
				restart = 0;
				break;
			}
			//volatile int i;
			if(i<count_16_parts) 
			{
				TIM1->CCR1 = 65535 * i / (count_16_parts);
			}
			else if((i>count_16_parts   - 1)&&(i<count_16_parts*2)) 
			{
				TIM1->CCR1 = 65535 * (count_16_parts*2-i) / count_16_parts;
			}
			else if (i == count_16_parts*2) 
			{
				TIM1->CCER |= TIM_CCER_CC1E;
				TIM1->CCER &= ~TIM_CCER_CC1NE;
			}
			else if((i>count_16_parts*2 - 1)&&(i<count_16_parts*3))
			{
				TIM1->CCR1 = 65535 * (i-count_16_parts*2) / count_16_parts;
			}
			else if((i>count_16_parts*3 - 1)&&(i<count_16_parts*4))
			{ 
				TIM1->CCR1 = 65535 * (count_16_parts*4-i) / count_16_parts;
			}
			else if (i == count_16_parts*4) {
				TIM1->CCER &= ~TIM_CCER_CC1E;
				
				TIM1->CCER |= TIM_CCER_CC2NE;
				TIM1->CCER &= ~TIM_CCER_CC2E;
			}
			else if((i>count_16_parts*4 - 1)&&(i<count_16_parts*5))
			{
				TIM1->CCR2 = 65535 * (i-count_16_parts*4) / count_16_parts;
			}
			else if((i>count_16_parts*5 - 1)&&(i<count_16_parts*6))
			{
				TIM1->CCR2 = 65535 * (count_16_parts*6-i) / count_16_parts;
			}
			else if (i == count_16_parts*6)
			{
				TIM1->CCER |= TIM_CCER_CC2E;
				TIM1->CCER &= ~TIM_CCER_CC2NE;
			}
			else if((i>count_16_parts*6 - 1)&&(i<count_16_parts*7))
			{
				TIM1->CCR2 = 65535 * (i-count_16_parts*6) / count_16_parts;
			}
			else if((i>count_16_parts*7 - 1)&&(i<count_16_parts*8))
			{
				TIM1->CCR2 = 65535 * (count_16_parts*8-i) / count_16_parts;
			}
			else if (i == count_16_parts*8)
			{
				TIM1->CCER &= ~TIM_CCER_CC2E;
				
				TIM1->CCER |= TIM_CCER_CC3NE;
				TIM1->CCER &= ~TIM_CCER_CC3E;
			}
			else if((i>count_16_parts*8 - 1)&&(i<count_16_parts*9))
			{
				TIM1->CCR3 = 65535 * (i-count_16_parts*8) / count_16_parts;
			}
			else if((i>count_16_parts*9 - 1)&&(i<count_16_parts*10))
			{
				TIM1->CCR3 = 65535 * (count_16_parts*10-i) / count_16_parts;
			}
			else if (i == count_16_parts*10)
			{
				TIM1->CCER |= TIM_CCER_CC3E;
				TIM1->CCER &= ~TIM_CCER_CC3NE;
			}
			else if((i>count_16_parts*10 - 1)&&(i<count_16_parts*11))
			{
				TIM1->CCR3 = 65535 * (i-count_16_parts*10) / count_16_parts;
			}

			else if((i>count_16_parts*11 - 1)&&(i<count_16_parts*12))
			{
				TIM1->CCR3 = 65535 * (count_16_parts*12-i) / count_16_parts;
			}
			else if (i == count_16_parts*12) 
			{	
				TIM1->CCER &= ~TIM_CCER_CC3E;
				
				TIM1->CCER |= TIM_CCER_CC4E;
			}
			else if((i>count_16_parts*12 - 1)&&(i<count_16_parts*13))
			{	
				TIM1->CCR4 = 65535 * (i-count_16_parts*12) / count_16_parts;
			}
			else if((i>count_16_parts*13 - 1)&&(i<count_16_parts*14))
			{
				TIM1->CCR4 = 65535 * (count_16_parts*14-i) / count_16_parts;
			}
			//caaa??ea
			for(d=0;d<delay;d++)
			{
			}
		}
}

void Counterclockwise_One(void)
{
		uint32_t count_16_parts = count/16;
		TIM1->CCER &= ~TIM_CCER_CC1NE;
		TIM1->CCR1 = 0;
		TIM1->CCER |= TIM_CCER_CC4E;
		for(i=0;i<=count_16_parts*14;i++)
		{
			if (restart){
				TIM1->CCER &= ~(TIM_CCER_CC1E | TIM_CCER_CC1NE 
				| TIM_CCER_CC2E | TIM_CCER_CC2NE
				| TIM_CCER_CC3E | TIM_CCER_CC3NE
				| TIM_CCER_CC4E);
				TIM1->CCR1 = 0;
				TIM1->CCR2 = 0;
				TIM1->CCR3 = 0;
				TIM1->CCR4 = 0;
				restart = 0;
				break;
			}
			if(i<count_16_parts) 
			{
				TIM1->CCR4 = 65535 * i / (count_16_parts);
			}
			else if((i>count_16_parts - 1)&&(i<count_16_parts*2)) 
			{
				TIM1->CCR4 = 65535 * (count_16_parts*2-i) / count_16_parts;
			}
			else if (i == count_16_parts * 2)
			{
				TIM1->CCER &= ~TIM_CCER_CC4E;
				
				TIM1->CCER |= TIM_CCER_CC3E;
				TIM1->CCER &= ~TIM_CCER_CC3NE;
			}
			else if((i>count_16_parts*2 - 1)&&(i<count_16_parts*3))
			{
				TIM1->CCR3 = 65535 * (i-count_16_parts*2) / count_16_parts;
			}
			else if((i>count_16_parts*3 - 1)&&(i<count_16_parts*4))
			{ 
				TIM1->CCR3 = 65535 * (count_16_parts*4-i) / count_16_parts;
			}
			else if (i == count_16_parts * 4) 
			{
				TIM1->CCER |= TIM_CCER_CC3NE;
				TIM1->CCER &= ~TIM_CCER_CC3E;
			}
			else if((i>count_16_parts*4 - 1)&&(i<count_16_parts*5))
			{
				TIM1->CCR3 = 65535 * (i-count_16_parts*4) / count_16_parts;
			}
			else if((i>count_16_parts*5 - 1)&&(i<count_16_parts*6))
			{
				TIM1->CCR3 = 65535 * (count_16_parts*6-i) / count_16_parts;
			}
			else if (i == count_16_parts * 6)
			{
				TIM1->CCER &= ~TIM_CCER_CC3NE;
				
				TIM1->CCER |= TIM_CCER_CC2E;
				TIM1->CCER &= ~TIM_CCER_CC2NE;
			}
			else if((i>count_16_parts*6 - 1)&&(i<count_16_parts*7))
			{
				TIM1->CCR2 = 65535 * (i-count_16_parts*6) / count_16_parts;
			}
			else if((i>count_16_parts*7 - 1)&&(i<count_16_parts*8))
			{
				TIM1->CCR2 = 65535 * (count_16_parts*8-i) / count_16_parts;
			}
			else if (i == count_16_parts * 8) 
			{
				TIM1->CCER |= TIM_CCER_CC2NE;
				TIM1->CCER &= ~TIM_CCER_CC2E;
			}
			else if((i>count_16_parts*8 - 1)&&(i<count_16_parts*9))
			{
				TIM1->CCR2 = 65535 * (i-count_16_parts*8) / count_16_parts;
			}
			else if((i>count_16_parts*9 - 1)&&(i<count_16_parts*10))
			{
				TIM1->CCR2 = 65535 * (count_16_parts*10-i) / count_16_parts;
			}
			else if (i == count_16_parts * 10)
			{
				TIM1->CCER &= ~TIM_CCER_CC2NE;
				
				TIM1->CCER |= TIM_CCER_CC1E;
				TIM1->CCER &= ~TIM_CCER_CC1NE;
			}
			else if((i>count_16_parts*10 - 1)&&(i<count_16_parts*11))
			{
				TIM1->CCR1 = 65535 * (i-count_16_parts*10) / count_16_parts;
			}
			else if((i>count_16_parts*11 - 1)&&(i<count_16_parts*12))
			{
				TIM1->CCR1 = 65535 * (count_16_parts*12-i) / count_16_parts;
			}
			else if (i == count_16_parts * 12)
			{
				TIM1->CCER |= TIM_CCER_CC1NE;
				TIM1->CCER &= ~TIM_CCER_CC1E;
			}
			else if((i>count_16_parts*12 - 1)&&(i<count_16_parts*13))
			{	
				TIM1->CCR1 = 65535 * (i-count_16_parts*12) / count_16_parts;
			}
			else if((i>count_16_parts*13 - 1)&&(i<count_16_parts*14))
			{
				TIM1->CCR1 = 65535 * (count_16_parts*14-i) / count_16_parts;
			}
			//caaa??ea
			for(d=0;d<delay;d++)
			{
			}
		}	
}

void Clockwise_Two()
{
		uint32_t count_16_parts = count/16;
    TIM1->CCER &= ~TIM_CCER_CC1NP; // polarity on
		TIM1->CCER |= TIM_CCER_CC1NE | TIM_CCER_CC1E; // channel on
		for(i=0;i<=count_16_parts*7;i++)
		{
			if (restart){
				TIM1->CCER &= ~(TIM_CCER_CC1E | TIM_CCER_CC1NE 
				| TIM_CCER_CC2E | TIM_CCER_CC2NE
				| TIM_CCER_CC3E | TIM_CCER_CC3NE
				| TIM_CCER_CC4E);
				TIM1->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP 
				| TIM_CCER_CC2P | TIM_CCER_CC2NP
				| TIM_CCER_CC3P | TIM_CCER_CC3NP
				| TIM_CCER_CC4P);
				TIM1->CCR1 = 0;
				TIM1->CCR2 = 0;
				TIM1->CCR3 = 0;
				TIM1->CCR4 = 0;
				restart = 0;
				break;
			}
			else if(i<count_16_parts) 
			{
				TIM1->CCR1 = 65535 * i / (count_16_parts);
			}
      else if(i == count_16_parts) 
      {
        TIM1->CCER &= ~TIM_CCER_CC1NP; // polarity on
        TIM1->CCER |= TIM_CCER_CC1E; // channel on
				TIM1->CCER &= ~TIM_CCER_CC1NE; // comp. channel off
          
        TIM1->CCER |= TIM_CCER_CC2NP; // polarity off ??
        TIM1->CCER |= TIM_CCER_CC2NE; // comp. channel on
				TIM1->CCER &= ~TIM_CCER_CC2E; // channel off
      }
			else if((i>count_16_parts   - 1)&&(i<count_16_parts*2)) 
			{
				TIM1->CCR1 = 65535 * (count_16_parts*2-i)/(count_16_parts);
				TIM1->CCR2 = 65535 * (count_16_parts*2-i)/(count_16_parts);
			}
      else if(i == count_16_parts*2)
      {
        TIM1->CCR1 = 0;
        TIM1->CCER &= ~TIM_CCER_CC2NP; // polarity on
        TIM1->CCER |= TIM_CCER_CC2E; // channel on
      }
			else if((i>count_16_parts*2 - 1)&&(i<count_16_parts*3))
			{
        TIM1->CCR2 = 65535 * (i-count_16_parts*2)/(count_16_parts);
			}
      else if(i == count_16_parts*3)
      {
				TIM1->CCER &= ~TIM_CCER_CC2NP;
				TIM1->CCER |= TIM_CCER_CC2E;
				TIM1->CCER &= ~TIM_CCER_CC2NE;
				
				TIM1->CCER |= TIM_CCER_CC3NP;
				TIM1->CCER |= TIM_CCER_CC3NE;
				TIM1->CCER &= ~TIM_CCER_CC3E;
      }
			else if((i>count_16_parts*3 - 1)&&(i<count_16_parts*4))
			{ 
				TIM1->CCR2 = 65535 * (count_16_parts*4-i)/(count_16_parts);
				TIM1->CCR3 = 65535 * (count_16_parts*4-i)/(count_16_parts);
			}
      else if(i == count_16_parts*4)
      {
				TIM1->CCR2 = 0;
				TIM1->CCER &= ~TIM_CCER_CC3NP;
				TIM1->CCER |= TIM_CCER_CC3E;
      }
			else if((i>count_16_parts*4 - 1)&&(i<count_16_parts*5))
			{
				TIM1->CCR3 = 65535 * (i-count_16_parts*4)/(count_16_parts);
			}
      else if(i == count_16_parts*5)
      {
				TIM1->CCER &= ~TIM_CCER_CC3NP;
				TIM1->CCER |= TIM_CCER_CC3E;
				TIM1->CCER &= ~TIM_CCER_CC3NE;
				
				TIM1->CCER |= TIM_CCER_CC4P;
				TIM1->CCER |= TIM_CCER_CC4E;
      }
			else if((i>count_16_parts*5 - 1)&&(i<count_16_parts*6))
			{
				TIM1->CCR3 = 65535 * (count_16_parts*6-i)/(count_16_parts);
				TIM1->CCR4 = 65535 * (count_16_parts*6-i)/(count_16_parts);
			}
      else if(i == count_16_parts*6)
      {
				TIM1->CCR3 = 0;
				TIM1->CCER |= TIM_CCER_CC1NE;
				
				TIM1->CCER &= ~TIM_CCER_CC1NP;
				TIM1->CCER |= TIM_CCER_CC1NE;
				TIM1->CCER &= ~TIM_CCER_CC1E;
      }
			else if((i>count_16_parts*6 - 1)&&(i<count_16_parts*7))
			{
				TIM1->CCR4 = 65535 * (i-count_16_parts*6)/(count_16_parts);
				TIM1->CCR1 = 65535 * (i-count_16_parts*6)/(count_16_parts);
			}
      else if(i == count_16_parts*7)
      {
				TIM1->CCR4 = 65535;
				
				TIM1->CCER &= ~TIM_CCER_CC1NP;
				TIM1->CCER |= TIM_CCER_CC1E;
				TIM1->CCER |= TIM_CCER_CC1NE;
      }
			
			
			for(d=0;d<delay;d++)
			{
			}
		}
}

void Counterclockwise_Two(void)
{
	uint32_t count_16_parts = count/16;

	//зажжён 7, тухнет 7, загорается 6, выключаем 1, CCR увеличивается
	TIM1->CCER &= ~TIM_CCER_CC1NE; // отключение комплиментарного канала 1 (1) (на случай если это не первый круг)

	TIM1->CCER |= TIM_CCER_CC4P; // включение полярности на прямом канале 4 (7)
	TIM1->CCER |= TIM_CCER_CC4E; // включение прямого канала 4 (7)

	TIM1->CCER |= TIM_CCER_CC3E; // включение прямого канала 3 (6)
	TIM1->CCER &= ~TIM_CCER_CC3NE; // отключение комплиментарного канала 3 (5)
	for (i = 0;i <= count_16_parts * 7;i++)
	{
		if (restart){
			TIM1->CCER &= ~(TIM_CCER_CC1E | TIM_CCER_CC1NE 
			| TIM_CCER_CC2E | TIM_CCER_CC2NE
			| TIM_CCER_CC3E | TIM_CCER_CC3NE
			| TIM_CCER_CC4E);
			TIM1->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP 
			| TIM_CCER_CC2P | TIM_CCER_CC2NP
			| TIM_CCER_CC3P | TIM_CCER_CC3NP
			| TIM_CCER_CC4P);
			TIM1->CCR1 = 0;
			TIM1->CCR2 = 0;
			TIM1->CCR3 = 0;
			TIM1->CCR4 = 0;
			restart = 0;
			break;
		}
		if (i < count_16_parts)
		{
			TIM1->CCR4 = 65535 * i / (count_16_parts);
			TIM1->CCR3 = 65535 * i / (count_16_parts);
		}
		//ca???i 6, oooiao 6, caai?aaony 5, auee??aai 7, CCR oiaiuoaaony
		else if (i == count_16_parts)
		{
			TIM1->CCER &= ~TIM_CCER_CC4E; // ioee??aiea i?yiiai eaiaea 4 (7)

			TIM1->CCER &= ~TIM_CCER_CC3NP; // aee??aiea iiey?iinoe ia eiiieeiaioa?iii eaiaea 3 (5)
			TIM1->CCER |= TIM_CCER_CC3NE; // aee??aiea eiiieeiaioa?iiai eaiaea 3 (5)
		}
		else if ((i > count_16_parts - 1) && (i < count_16_parts * 2))
		{
			TIM1->CCR3 = 65535 * (count_16_parts * 2 - i) / (count_16_parts);
		}
		//ca???i 5, oooiao 5, caai?aaony 4, auee??aai 6, CCR oaaee?eaaaony
		else if (i == count_16_parts * 2)
		{
			TIM1->CCER &= ~TIM_CCER_CC3E; // ioee??aiea i?yiiai eaiaea 3 (6)

			TIM1->CCER |= TIM_CCER_CC2E; // aee??aiea i?yiiai eaiaea 2 (4)
			TIM1->CCER |= TIM_CCER_CC3NP; // ioee??aiea iiey?iinoe ia eiiieeiaioa?iii eaiaea 3 (5)
			TIM1->CCER &= ~TIM_CCER_CC2NE; // ioee??aiea eiiieeiaioa?iiai eaiaea 2 (3)
		}
		else if ((i > count_16_parts * 2 - 1) && (i < count_16_parts * 3))
		{
			TIM1->CCR3 = 65535 * (i - count_16_parts * 2) / (count_16_parts);
			TIM1->CCR2 = 65535 * (i - count_16_parts * 2) / (count_16_parts);
		}
		//ca???i 4, oooiao 4, caai?aaony 3, auee??aai 5, CCR oiaiuoaaony
		else if (i == count_16_parts * 3)
		{
			TIM1->CCER &= ~TIM_CCER_CC3NE; // ioee??aiea eiiieeiaioa?iiai eaiaea 3 (5)

			TIM1->CCER &= ~TIM_CCER_CC2NP; // aee??aiea iiey?iinoe ia eiiieeiaioa?iii eaiaea 2 (3)
			TIM1->CCER |= TIM_CCER_CC2NE; // aee??aiea eiiieeiaioa?iiai eaiaea 2 (3)
		}
		else if ((i > count_16_parts * 3 - 1) && (i < count_16_parts * 4))
		{
			TIM1->CCR2 = 65535 * (count_16_parts * 4 - i) / (count_16_parts);
		}
		//ca???i 3, oooiao 3, caai?aaony 2, auee??aai 4, CCR oaaee?eaaaony
		else if (i == count_16_parts * 4)
		{
			TIM1->CCER &= ~TIM_CCER_CC2E; // ioee??aiea i?yiiai eaiaea 2 (4)

			TIM1->CCER |= TIM_CCER_CC1E; // aee??aiea i?yiiai eaiaea 1 (2)
			TIM1->CCER |= TIM_CCER_CC2NP; // ioee??aiea iiey?iinoe ia eiiieeiaioa?iii eaiaea 2 (3)
			TIM1->CCER &= ~TIM_CCER_CC1NE; // ioee??aiea eiiieeiaioa?iiai eaiaea 1 (1)
		}
		else if ((i > count_16_parts * 4 - 1) && (i < count_16_parts * 5))
		{
			TIM1->CCR2 = 65535 * (i - count_16_parts * 4) / (count_16_parts);
			TIM1->CCR1 = 65535 * (i - count_16_parts * 4) / (count_16_parts);
		}
		//ca???i 2, oooiao 2, caai?aaony 1, auee??aai 3, CCR oiaiuoaaony
		else if (i == count_16_parts * 5)
		{
			TIM1->CCER &= ~TIM_CCER_CC2NE; // ioee??aiea eiiieeiaioa?iiai eaiaea 2 (3)

			TIM1->CCER &= ~TIM_CCER_CC1NP; // aee??aiea iiey?iinoe ia eiiieeiaioa?iii eaiaea 1 (1)
			TIM1->CCER |= TIM_CCER_CC1NE; // aee??aiea eiiieeiaioa?iiai eaiaea 1 (1)
		}
		else if ((i > count_16_parts * 5 - 1) && (i < count_16_parts * 6))
		{
			TIM1->CCR1 = 65535 * (count_16_parts * 6 - i) / (count_16_parts);
		}
		//ca???i 1, oooiao 1, caai?aaony 7, auee??aai 2, CCR oaaee?eaaaony
		else if (i == count_16_parts * 6)
		{
			TIM1->CCER &= ~TIM_CCER_CC1E; // ioee??aiea i?yiiai eaiaea 1 (2)

			TIM1->CCER |= TIM_CCER_CC1NP; // ioee??aiea iiey?iinoe ia eiiieeiaioa?iii eaiaea 1 (1)
			
			TIM1->CCER &= ~TIM_CCER_CC4P; // ioee??aiea iiey?iinoe ia i?yiii eaiaea 4 (7) (ia neo?ae anee yoi ia ia?aue e?oa)
			TIM1->CCER |= TIM_CCER_CC4E; // aee??aiea i?yiiai eaiaea 4 (7)
		}
		else if ((i > count_16_parts * 6 - 1) && (i < count_16_parts * 7))
		{
			TIM1->CCR1 = 65535 * (i - count_16_parts * 6) / (count_16_parts);
			TIM1->CCR4 = 65535 * (i - count_16_parts * 6) / (count_16_parts);
		}
		else if (i == count_16_parts * 7)
		{
		}

		for (d = 0;d < delay;d++)
		{
		}
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_TIM1;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_ENABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC0 PC1 PC2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC4 PC5 PC6 PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_TSC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_TSC_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
