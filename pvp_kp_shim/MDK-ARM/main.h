#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f3xx.h"                  // Device header
#include "ports.h"
#include "RTE_Components.h"
#include CMSIS_device_header


void port_ini(void);
void delay(volatile uint32_t count);

void port_ini(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN; //включим тактирование порта
	GPIOE->MODER |= 0x55550000;
	GPIOE->OTYPER = 0; //включим подт€гивающее сопротивление на весь порт
	GPIOE->OSPEEDR = 0; //установим скорость LOW на все лапки порта
}

void delay(volatile uint32_t count) 
{
	while(count--)
		__NOP();
}

#endif /* MAIN_H_ */
