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

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
uint8_t flag_key1_press = 1;
uint32_t time_key1_press = 0;
uint32_t count = 16384;

uint32_t delay = 891;
uint32_t i;
volatile uint32_t d; //
uint32_t delay_1sec_one_led = 891;
uint32_t delay_05sec_one_led = 441;
uint32_t delay_025sec_one_led = 216;
uint32_t delay_004sec_one_led = 26;
uint32_t delay_1sec_two_leds = 1794;
uint32_t delay_05sec_two_leds = 894;
uint32_t delay_025sec_two_leds = 443;
uint32_t delay_004sec_two_leds = 65;
_Bool direction_mode = 0;
uint8_t number_leds_mode = 1;
uint8_t switch_speeds_mode = 1;
_Bool restart = 0;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
void switch_speeds_one_led(uint16_t speed_mode);
void switch_speeds_two_led(uint16_t speed_mode);
void Clockwise_One(void);
void Counterclockwise_One(void);
void Clockwise_Two(void);
void Counterclockwise_Two(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
	
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start (&htim1, TIM_CHANNEL_1);   // start shim on cannel 1(ch1)
  HAL_TIMEx_PWMN_Start (&htim1, TIM_CHANNEL_1);// start shim on complimentary channel 1(ch1n)
  HAL_TIM_PWM_Start (&htim1, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start (&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start (&htim1, TIM_CHANNEL_3);
  HAL_TIMEx_PWMN_Start (&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start (&htim1, TIM_CHANNEL_4);
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_BREAK);
  
  TIM1->CCER &= ~TIM_CCER_CC2NE; // clear bits in ch2n and ch3n that is disable this channels
  TIM1->CCER &= ~TIM_CCER_CC3NE;
	/* USER CODE END 2 */
  
	/* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
	/* USER CODE END WHILE */
}

// handler for k0 button with external interrupt - speed mode
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
	// chatter protection with 100ms time
	if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 100)
	{
		flag_key1_press = 1;
	}
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_RESET && flag_key1_press)
	{
		flag_key1_press = 0;
		// click action
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
// handler for k1 button with external interrupt - direction mode
void EXTI1_IRQHandler(void)
{
	// chatter protection with 100ms time
	if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 100)
	{
		flag_key1_press = 1;
	}
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_RESET && flag_key1_press)
	{
		flag_key1_press = 0;
		if(direction_mode == 1)
			direction_mode = 0;
		else direction_mode = 1;
		printf("direction = %i\n", direction_mode);	
		restart = 1;
		time_key1_press = HAL_GetTick();
	}
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

/**
  * @brief This function handles EXTI line2 and Touch Sense controller.
  */
// handler for k2 button with external interrupt - number leds mode
void EXTI2_TSC_IRQHandler(void)
{
  // chatter protection with 100ms time
	if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 100)
	{
		flag_key1_press = 1;
	}
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == GPIO_PIN_RESET && flag_key1_press)
	{
		flag_key1_press = 0;
		if(number_leds_mode == 1)
			++number_leds_mode;
		else number_leds_mode = 1;
		printf("number of leds = %i\n", number_leds_mode);
		restart = 1; // flag for reset mode
		time_key1_press = HAL_GetTick();
	}
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}



void switch_speeds_one_led(uint16_t speed_mode) {
	// speed mode =
	// 1 - 1 s for ignition and decay, those are 2 s
	// 2 - 0.5 s, those are 1 s
	// 3 - 0.25s, those are 0.5s
	// 4 - 0.04 s, those 0.08 s

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
	// 1 - 1 s for ignition and decay, those are 2 s
	// 2 - 0.5 s, those are 1 s
	// 3 - 0.25s, those are 0.5s
	// 4 - 0.04 s, those 0.08 s
	
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
	TIM1->CCER &= ~TIM_CCER_CC4E;// clear bits in ch4 that is disable this channel
	TIM1->CCR4 = 0;              // set zero value for ch4, so that the LED does not light up
	
	TIM1->CCER |= TIM_CCER_CC1NE;// set bits for ch1n that is enable this channel
	TIM1->CCER &= ~TIM_CCER_CC1E;// disable ch1
	for(i=0;i<=count_16_parts*14;i++)
	{
		if (restart) // if flag restart = 1 then clear all channels
		{
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
		//delay
		for(d=0;d<delay;d++)
		{
		}
	}
}

void Counterclockwise_One(void)
{
	uint32_t count_16_parts = count/16;
	TIM1->CCER &= ~TIM_CCER_CC1NE; // disable ch1n
	TIM1->CCR1 = 0;
	TIM1->CCER |= TIM_CCER_CC4E;   // set bits for ch4nthat is enable this channel
	for(i=0;i<=count_16_parts*14;i++)
	{
		if (restart) { // if flag restart = 1 then clear all channels
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
		//delay
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
	//on 7, off 7, on 6, off 1, CCR increases
	TIM1->CCER &= ~TIM_CCER_CC1NE; // disable complimentary channel 1 (1) (in case it's not the first round)

	TIM1->CCER |= TIM_CCER_CC4P;   // enable polarity on forward channel 4 (7)
	TIM1->CCER |= TIM_CCER_CC4E;   // enable direct channel 4 (7)

	TIM1->CCER |= TIM_CCER_CC3E; // enable direct channel 3 (6)
	TIM1->CCER &= ~TIM_CCER_CC3NE; // disable complimentary channel 3 (5)
	for (i = 0;i <= count_16_parts * 7;i++)
	{
		if (restart){ //disable all
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
		//on 6, off 6, on 5, off 7, CCR decreases
		else if (i == count_16_parts)
		{
			TIM1->CCER &= ~TIM_CCER_CC4E;  // disable direct channel 4 (7

			TIM1->CCER &= ~TIM_CCER_CC3NP; // enable polarity on complementary channel 3 (5)
			TIM1->CCER |= TIM_CCER_CC3NE;  // enable complimentary channel 3 (5)
		}
		else if ((i > count_16_parts - 1) && (i < count_16_parts * 2))
		{
			TIM1->CCR3 = 65535 * (count_16_parts * 2 - i) / (count_16_parts);
		}
		
		//on 5, off 5, on 4, off 6, CCR increases
		else if (i == count_16_parts * 2)
		{
			TIM1->CCER &= ~TIM_CCER_CC3E; // disable direct channel 3 (6)

			TIM1->CCER |= TIM_CCER_CC2E;  // enable direct channel 2 (4)
			TIM1->CCER |= TIM_CCER_CC3NP; // disable polarity on complementary channel 3 (5)
			TIM1->CCER &= ~TIM_CCER_CC2NE;// disable complimentary channel 2 (3)
		}
		else if ((i > count_16_parts * 2 - 1) && (i < count_16_parts * 3))
		{
			TIM1->CCR3 = 65535 * (i - count_16_parts * 2) / (count_16_parts);
			TIM1->CCR2 = 65535 * (i - count_16_parts * 2) / (count_16_parts);
		}
		//on 4, off 4, on 3, off 5, CCR decreases
		else if (i == count_16_parts * 3)
		{
			TIM1->CCER &= ~TIM_CCER_CC3NE; // disable complimentary channel 3 (5)

			TIM1->CCER &= ~TIM_CCER_CC2NP; // enable polarity on complementary channel 2 (3)
			TIM1->CCER |= TIM_CCER_CC2NE;  // enable complimentary channel 2 (3)
		}
		else if ((i > count_16_parts * 3 - 1) && (i < count_16_parts * 4))
		{
			TIM1->CCR2 = 65535 * (count_16_parts * 4 - i) / (count_16_parts);
		}
		//on 3, off 3, on 2, off 4, CCR increases
		else if (i == count_16_parts * 4)
		{
			TIM1->CCER &= ~TIM_CCER_CC2E;  // disable direct channel 2 (4)

			TIM1->CCER |= TIM_CCER_CC1E;   // enable direct channel 1 (2)
			TIM1->CCER |= TIM_CCER_CC2NP;  // disable polarity on complementary channel 2 (3)
			TIM1->CCER &= ~TIM_CCER_CC1NE; // disable complimentary channel 1 (1)
		}
		else if ((i > count_16_parts * 4 - 1) && (i < count_16_parts * 5))
		{
			TIM1->CCR2 = 65535 * (i - count_16_parts * 4) / (count_16_parts);
			TIM1->CCR1 = 65535 * (i - count_16_parts * 4) / (count_16_parts);
		}
		//on 2, off 2, on 1, off 3, CCR decreases
		else if (i == count_16_parts * 5)
		{
			TIM1->CCER &= ~TIM_CCER_CC2NE; // disable complimentary channel 2 (3)

			TIM1->CCER &= ~TIM_CCER_CC1NP; // enable polarity on complementary channel 1 (1)
			TIM1->CCER |= TIM_CCER_CC1NE;  // enable complimentary channel 1 (1)
		}
		else if ((i > count_16_parts * 5 - 1) && (i < count_16_parts * 6))
		{
			TIM1->CCR1 = 65535 * (count_16_parts * 6 - i) / (count_16_parts);
		}
		//on 1, off 1, on 7, off 2, CCR increases
		else if (i == count_16_parts * 6)
		{
			TIM1->CCER &= ~TIM_CCER_CC1E; // disable direct channel 1 (2)

			TIM1->CCER |= TIM_CCER_CC1NP; // disable polarity on complementary channel 1 (1)
			
			TIM1->CCER &= ~TIM_CCER_CC4P; // disable polarity on forward channel 4 (7) (in case it's not the first circle)
			TIM1->CCER |= TIM_CCER_CC4E;  // enable direct channel 4 (7)
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

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

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

  HAL_TIM_MspPostInit(&htim1);

}

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
