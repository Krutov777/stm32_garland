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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);

void Clockwise_One(uint32_t);
void Counterclockwise_One(uint32_t);
void Clockwise_Two(uint32_t);
void Counterclockwise_Two(uint32_t);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	
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
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start (&htim1, TIM_CHANNEL_1);//�������� ���
	HAL_TIMEx_PWMN_Start (&htim1, TIM_CHANNEL_1);//�������� ���
	HAL_TIM_PWM_Start (&htim1, TIM_CHANNEL_2);//�������� ���
	HAL_TIMEx_PWMN_Start (&htim1, TIM_CHANNEL_2);//�������� ���
	HAL_TIM_PWM_Start (&htim1, TIM_CHANNEL_3);//�������� ���
	HAL_TIMEx_PWMN_Start (&htim1, TIM_CHANNEL_3);//�������� ���
	HAL_TIM_PWM_Start (&htim1, TIM_CHANNEL_4);//�������� ���
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
	_Bool clockwise = 0;
	_Bool two_mode = 0;
	uint32_t delay = 100;
	if (clockwise && !two_mode)
	{
		Clockwise_One(delay);
	}
	else if (!clockwise && !two_mode)
	{
		Counterclockwise_One(delay);
	}
	else if (clockwise && two_mode)
	{
		Clockwise_Two(delay);
	}
	else
	{
		Counterclockwise_Two(delay);
	}
}

void Clockwise_One(uint32_t delay)
{
	uint32_t i,d; //d - ��� ��������
	while (1)
  {
		//int count = 131072;
		int count = 262144;
		//int count = 524288;
		//int count = 16040960;
		for(i=0;i<=count/16*14;i++)
		{
			if(i<count/16) 
			{
				TIM1->CCR1 = i;
				TIM1->CCER |= TIM_CCER_CC1NE;
				TIM1->CCER &= ~TIM_CCER_CC1E;
			}
			else if((i>count/16   - 1)&&(i<count/16*2)) 
			{
				TIM1->CCR1 = count/16*2-i;
				TIM1->CCER |= TIM_CCER_CC1NE;
				TIM1->CCER &= ~TIM_CCER_CC1E;
			}					
			else if((i>count/16*2 - 1)&&(i<count/16*3))
			{
				TIM1->CCR1 = i-count/16*2;
				TIM1->CCER |= TIM_CCER_CC1E;
				TIM1->CCER &= ~TIM_CCER_CC1NE;
			}
			else if((i>count/16*3 - 1)&&(i<count/16*4))
			{ 
				TIM1->CCR1 = count/16*4-i;
				TIM1->CCER |= TIM_CCER_CC1E;
				TIM1->CCER &= ~TIM_CCER_CC1NE;
			}
			else if((i>count/16*4 - 1)&&(i<count/16*5))
			{
				TIM1->CCR2 = i-count/16*4;
				TIM1->CCER |= TIM_CCER_CC2NE;
				TIM1->CCER &= ~TIM_CCER_CC2E;
			}
			else if((i>count/16*5 - 1)&&(i<count/16*6))
			{
				TIM1->CCR2 = count/16*6-i;
				TIM1->CCER |= TIM_CCER_CC2NE;
				TIM1->CCER &= ~TIM_CCER_CC2E;
			}
			else if((i>count/16*6 - 1)&&(i<count/16*7))
			{
				TIM1->CCR2 = i-count/16*6;
				TIM1->CCER |= TIM_CCER_CC2E;
				TIM1->CCER &= ~TIM_CCER_CC2NE;
			}
			else if((i>count/16*7 - 1)&&(i<count/16*8))
			{
				TIM1->CCR2 = count/16*8-i;
				TIM1->CCER |= TIM_CCER_CC2E;
				TIM1->CCER &= ~TIM_CCER_CC2NE;
			}
			else if((i>count/16*8 - 1)&&(i<count/16*9))
			{
				TIM1->CCR3 = i-count/16*8;
				TIM1->CCER |= TIM_CCER_CC3NE;
				TIM1->CCER &= ~TIM_CCER_CC3E;
			}
			else if((i>count/16*9 - 1)&&(i<count/16*10))
			{
				TIM1->CCR3 = count/16*10-i;
				TIM1->CCER |= TIM_CCER_CC3NE;
				TIM1->CCER &= ~TIM_CCER_CC3E;
			}
			else if((i>count/16*10 - 1)&&(i<count/16*11))
			{
				TIM1->CCR3 = i-count/16*10;
				TIM1->CCER |= TIM_CCER_CC3E;
				TIM1->CCER &= ~TIM_CCER_CC3NE;
			}
			else if((i>count/16*11 - 1)&&(i<count/16*12))
			{
				TIM1->CCR3 = count/16*12-i;
				TIM1->CCER |= TIM_CCER_CC3E;
				TIM1->CCER &= ~TIM_CCER_CC3NE;
			}
			else if((i>count/16*12 - 1)&&(i<count/16*13))
			{	
				TIM1->CCR4 = i-count/16*12;
			}
			else if((i>count/16*13 - 1)&&(i<count/16*14))
			{
				TIM1->CCR4 = count/16*14-i;
			}
			else if((i>count/16*14 - 1)&&(i<count/16*15))
			{	
			}
			else
			{
			}
			//��������
			for(d=0;d<delay;d++)
			{
			}
		}
	}
}

void Counterclockwise_One(uint32_t delay)
{
	uint32_t i,d; //d - ��� ��������
	while (1)
  {
		//int count = 131072;
		int count = 262144;
		//int count = 524288;
		//int count = 16040960;
		for(i=0;i<=count/16*14;i++)
		{
			if(i<count/16) 
			{
				TIM1->CCR1 = i;
				TIM1->CCER |= TIM_CCER_CC1NE;
				TIM1->CCER &= ~TIM_CCER_CC1E;
			}
			else if((i>count/16   - 1)&&(i<count/16*2)) 
			{
				TIM1->CCR1 = count/16*2-i;
				TIM1->CCER |= TIM_CCER_CC1NE;
				TIM1->CCER &= ~TIM_CCER_CC1E;
			}					
			else if((i>count/16*2 - 1)&&(i<count/16*3))
			{
				TIM1->CCR4 = i-count/16*2;
			}
			else if((i>count/16*3 - 1)&&(i<count/16*4))
			{ 
				TIM1->CCR4 = count/16*4-i;
			}
			else if((i>count/16*4 - 1)&&(i<count/16*5))
			{
				TIM1->CCR3 = i-count/16*4;
				TIM1->CCER |= TIM_CCER_CC3E;
				TIM1->CCER &= ~TIM_CCER_CC3NE;
			}
			else if((i>count/16*5 - 1)&&(i<count/16*6))
			{
				TIM1->CCR3 = count/16*6-i;
				TIM1->CCER |= TIM_CCER_CC3E;
				TIM1->CCER &= ~TIM_CCER_CC3NE;
			}
			else if((i>count/16*6 - 1)&&(i<count/16*7))
			{
				TIM1->CCR3 = i-count/16*6;
				TIM1->CCER |= TIM_CCER_CC3NE;
				TIM1->CCER &= ~TIM_CCER_CC3E;
			}
			else if((i>count/16*7 - 1)&&(i<count/16*8))
			{
				TIM1->CCR3 = count/16*8-i;
				TIM1->CCER |= TIM_CCER_CC3NE;
				TIM1->CCER &= ~TIM_CCER_CC3E;
			}
			else if((i>count/16*8 - 1)&&(i<count/16*9))
			{
				TIM1->CCR2 = i-count/16*8;
				TIM1->CCER |= TIM_CCER_CC2E;
				TIM1->CCER &= ~TIM_CCER_CC2NE;
				
			}
			else if((i>count/16*9 - 1)&&(i<count/16*10))
			{
				TIM1->CCR2 = count/16*10-i;
				TIM1->CCER |= TIM_CCER_CC2E;
				TIM1->CCER &= ~TIM_CCER_CC2NE;
			}
			else if((i>count/16*10 - 1)&&(i<count/16*11))
			{
				TIM1->CCR2 = i-count/16*10;
				TIM1->CCER |= TIM_CCER_CC2NE;
				TIM1->CCER &= ~TIM_CCER_CC2E;
			}
			else if((i>count/16*11 - 1)&&(i<count/16*12))
			{
				TIM1->CCR2 = count/16*12-i;
				TIM1->CCER |= TIM_CCER_CC2NE;
				TIM1->CCER &= ~TIM_CCER_CC2E;
			}
			else if((i>count/16*12 - 1)&&(i<count/16*13))
			{	
				TIM1->CCR1 = i-count/16*12;
				TIM1->CCER |= TIM_CCER_CC1E;
				TIM1->CCER &= ~TIM_CCER_CC1NE;
			}
			else if((i>count/16*13 - 1)&&(i<count/16*14))
			{
				TIM1->CCR1 = count/16*14-i;
				TIM1->CCER |= TIM_CCER_CC1E;
				TIM1->CCER &= ~TIM_CCER_CC1NE;
			}
			else if((i>count/16*14 - 1)&&(i<count/16*15))
			{	
			}
			else
			{
			}
			//��������
			for(d=0;d<delay;d++)
			{
			}
		}
  }	
}

void Clockwise_Two(uint32_t delay)
{
	uint32_t i,d; //d - ��� ��������
	while (1)
  {
		//int count = 131072;
		int count = 262144;
		//int count = 524288;
		//int count = 16040960;
		for (i=0;i<=count;i++)
		{
			if(i<count/8)
			{
				TIM1->CCR1 = count/8 - i;
				TIM1->CCER |= TIM_CCER_CC1NE;
				TIM1->CCER &= ~TIM_CCER_CC1E;
				TIM1->CCR1 = i;
				TIM1->CCER |= TIM_CCER_CC1E;
			}
			else if((i>count/8   - 1)&&(i<count/8*2))
			{
				TIM1->CCR1 = count/8*2 - i;
				TIM1->CCER |= TIM_CCER_CC1E;
				TIM1->CCER &= ~TIM_CCER_CC1NE;
				TIM1->CCR2 = i - count/8;
				TIM1->CCER |= TIM_CCER_CC2NE;				
			}
			else if((i>count/8*2 - 1)&&(i<count/8*3))
			{
				TIM1->CCR2= count/8*3 - i;
				TIM1->CCER |= TIM_CCER_CC2NE;
				TIM1->CCER &= ~TIM_CCER_CC2E;
				TIM1->CCR2 = i - count/8*2;
				TIM1->CCER |= TIM_CCER_CC2E;	
			}
			else if((i>count/8*3 - 1)&&(i<count/8*4)) 
			{
				TIM1->CCR2= count/8*4 - i;
				TIM1->CCER |= TIM_CCER_CC2E;
				TIM1->CCER &= ~TIM_CCER_CC2NE;
				TIM1->CCR3 = i - count/8*3;
				TIM1->CCER |= TIM_CCER_CC3NE;	
			}
			else if((i>count/8*4 - 1)&&(i<count/8*5)) 
			{
				TIM1->CCR3= count/8*5 - i;
				TIM1->CCER |= TIM_CCER_CC3NE;
				TIM1->CCER &= ~TIM_CCER_CC3E;
				TIM1->CCR3 = i - count/8*6;
				TIM1->CCER |= TIM_CCER_CC3E;
			}
			else if((i>count/8*5 - 1)&&(i<count/8*6))
			{
				TIM1->CCR3= count/8*7 - i;
				TIM1->CCER |= TIM_CCER_CC3E;
				TIM1->CCER &= ~TIM_CCER_CC3NE;
				TIM1->CCR4 = i - count;
			}
			else if((i>count/8*6 - 1)&&(i<count/8*7)) 
			{
				TIM1->CCR4=count - i;
				TIM1->CCR1 = i - count;
				TIM1->CCER |= TIM_CCER_CC1NE;
				TIM1->CCER &= ~TIM_CCER_CC1E;
			}
			else 
			{
				//TIM1->CCR4=count-i;
			}
			//��������
			for(d=0;d<delay;d++)
			{
			}
		}
		//for(i=0;i<=count/16*14;i++)
		//{
		//	if(i<count/16) 
		//	{
		//		TIM1->CCR1 = count/16*2-i;
		//		TIM1->CCER |= TIM_CCER_CC1NE;
		//		TIM1->CCER &= ~TIM_CCER_CC1E;
		//		TIM1->CCR1 = i-count/16*2;
		//		TIM1->CCER |= TIM_CCER_CC1E;
		//		TIM1->CCER &= ~TIM_CCER_CC1NE;
		//	}
		//	else if((i>count/16   - 1)&&(i<count/16*2)) 
		//	{
		//		TIM1->CCR1 = count/16*4-i;
		//		TIM1->CCER |= TIM_CCER_CC1E;
		//		TIM1->CCER &= ~TIM_CCER_CC1NE;
		//		TIM1->CCR2 = i-count/16*4;
		//		TIM1->CCER |= TIM_CCER_CC2NE;
		//		TIM1->CCER &= ~TIM_CCER_CC2E;
		//	}					
		//	else if((i>count/16*2 - 1)&&(i<count/16*3))
		//	{
		//		TIM1->CCR2 = count/16*6-i;
		//		TIM1->CCER |= TIM_CCER_CC2NE;
		//		TIM1->CCER &= ~TIM_CCER_CC2E;
		//		TIM1->CCR2 = i-count/16*6;
		//		TIM1->CCER |= TIM_CCER_CC2E;
		//		TIM1->CCER &= ~TIM_CCER_CC2NE;
		//	}
		//	else if((i>count/16*3 - 1)&&(i<count/16*4))
		//	{ 
		//		TIM1->CCR2 = count/16*8-i;
		//		TIM1->CCER |= TIM_CCER_CC2E;
		//		TIM1->CCER &= ~TIM_CCER_CC2NE;
		//		TIM1->CCR3 = i-count/16*8;
		//		TIM1->CCER |= TIM_CCER_CC3NE;
		//		TIM1->CCER &= ~TIM_CCER_CC3E;
		//	}
		//	else if((i>count/16*4 - 1)&&(i<count/16*5))
		//	{
		//		TIM1->CCR3 = i-count/16*8;
		//		TIM1->CCER |= TIM_CCER_CC3NE;
		//		TIM1->CCER &= ~TIM_CCER_CC3E;
		//		TIM1->CCR3 = i-count/16*10;
		//		TIM1->CCER |= TIM_CCER_CC3E;
		//		TIM1->CCER &= ~TIM_CCER_CC3NE;
		//	}
		//	else if((i>count/16*5 - 1)&&(i<count/16*6))
		//	{
		//		TIM1->CCR3 = count/16*12-i;
		//		TIM1->CCER |= TIM_CCER_CC3E;
		//		TIM1->CCER &= ~TIM_CCER_CC3NE;
		//		TIM1->CCR4 = i-count/16*12;
		//	}
		//	else if((i>count/16*6 - 1)&&(i<count/16*7))
		//	{
		//		
		//	}
		//	else if((i>count/16*7 - 1)&&(i<count/16*8))
		//	{
		//		
		//	}
		//	else if((i>count/16*8 - 1)&&(i<count/16*9))
		//	{
		//		
		//	}
		//	else if((i>count/16*9 - 1)&&(i<count/16*10))
		//	{
		//		
		//	}
		//	else if((i>count/16*10 - 1)&&(i<count/16*11))
		//	{
		//		
		//	}
		//	else if((i>count/16*11 - 1)&&(i<count/16*12))
		//	{
		//		
		//	}
		//	else if((i>count/16*12 - 1)&&(i<count/16*13))
		//	{	
		//		
		//	}
		//	else if((i>count/16*13 - 1)&&(i<count/16*14))
		//	{
		//		
		//	}
		//	else if((i>count/16*14 - 1)&&(i<count/16*15))
		//	{	
		//	}
		//	else
		//	{
		//	}
		//	//��������
		//	for(d=0;d<delay;d++)
		//	{
		//	}
		//}
	}
}

void Counterclockwise_Two(uint32_t delay)
{
	uint32_t i,d; //d - ��� ��������
	while (1)
  {
		//int count = 131072;
		int count = 262144;
		//int count = 524288;
		//int count = 16040960;
		for(i=0;i<=count/16*14;i++)
		{
			if(i<count/16) 
			{
				TIM1->CCR1 = i;
				TIM1->CCER |= TIM_CCER_CC1NE;
				TIM1->CCER &= ~TIM_CCER_CC1E;
			}
			else if((i>count/16   - 1)&&(i<count/16*2)) 
			{
				TIM1->CCR1 = count/16*2-i;
				TIM1->CCER |= TIM_CCER_CC1NE;
				TIM1->CCER &= ~TIM_CCER_CC1E;
			}					
			else if((i>count/16*2 - 1)&&(i<count/16*3))
			{
				TIM1->CCR4 = i-count/16*2;
			}
			else if((i>count/16*3 - 1)&&(i<count/16*4))
			{ 
				TIM1->CCR4 = count/16*4-i;
			}
			else if((i>count/16*4 - 1)&&(i<count/16*5))
			{
				TIM1->CCR3 = i-count/16*4;
				TIM1->CCER |= TIM_CCER_CC3E;
				TIM1->CCER &= ~TIM_CCER_CC3NE;
			}
			else if((i>count/16*5 - 1)&&(i<count/16*6))
			{
				TIM1->CCR3 = count/16*6-i;
				TIM1->CCER |= TIM_CCER_CC3E;
				TIM1->CCER &= ~TIM_CCER_CC3NE;
			}
			else if((i>count/16*6 - 1)&&(i<count/16*7))
			{
				TIM1->CCR3 = i-count/16*6;
				TIM1->CCER |= TIM_CCER_CC3NE;
				TIM1->CCER &= ~TIM_CCER_CC3E;
			}
			else if((i>count/16*7 - 1)&&(i<count/16*8))
			{
				TIM1->CCR3 = count/16*8-i;
				TIM1->CCER |= TIM_CCER_CC3NE;
				TIM1->CCER &= ~TIM_CCER_CC3E;
			}
			else if((i>count/16*8 - 1)&&(i<count/16*9))
			{
				TIM1->CCR2 = i-count/16*8;
				TIM1->CCER |= TIM_CCER_CC2E;
				TIM1->CCER &= ~TIM_CCER_CC2NE;
				
			}
			else if((i>count/16*9 - 1)&&(i<count/16*10))
			{
				TIM1->CCR2 = count/16*10-i;
				TIM1->CCER |= TIM_CCER_CC2E;
				TIM1->CCER &= ~TIM_CCER_CC2NE;
			}
			else if((i>count/16*10 - 1)&&(i<count/16*11))
			{
				TIM1->CCR2 = i-count/16*10;
				TIM1->CCER |= TIM_CCER_CC2NE;
				TIM1->CCER &= ~TIM_CCER_CC2E;
			}
			else if((i>count/16*11 - 1)&&(i<count/16*12))
			{
				TIM1->CCR2 = count/16*12-i;
				TIM1->CCER |= TIM_CCER_CC2NE;
				TIM1->CCER &= ~TIM_CCER_CC2E;
			}
			else if((i>count/16*12 - 1)&&(i<count/16*13))
			{	
				TIM1->CCR1 = i-count/16*12;
				TIM1->CCER |= TIM_CCER_CC1E;
				TIM1->CCER &= ~TIM_CCER_CC1NE;
			}
			else if((i>count/16*13 - 1)&&(i<count/16*14))
			{
				TIM1->CCR1 = count/16*14-i;
				TIM1->CCER |= TIM_CCER_CC1E;
				TIM1->CCER &= ~TIM_CCER_CC1NE;
			}
			else if((i>count/16*14 - 1)&&(i<count/16*15))
			{	
			}
			else
			{
			}
			//��������
			for(d=0;d<delay;d++)
			{
			}
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

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