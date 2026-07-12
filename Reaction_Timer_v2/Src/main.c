#include "stm32f4xx.h"
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void) {
	//enable GPIO clocks
	RCC->AHB1ENR |= (1 << 0); //GPIOA
	RCC->AHB1ENR |= (1 << 2); //GPIOC
	RCC->APB1ENR |= (1 << 0); //TIM2
	//enable LED I/O
	GPIOA->MODER &= ~(0x3 << 10);
	GPIOA->MODER |= (0x1 << 10);
	//enable button input
	GPIOC->MODER &= ~(0x3 << 26);
	//PSC and ARR configs
	TIM2->PSC = 15;
	TIM2->ARR = 0xFFFFFFFF;
	TIM2->CR1 |= (1 << 0);
	//measure reaction time
	while(1) {
		uint32_t LED_ON = 0;
		uint32_t BUTTON_PRESSED = 0;
		//wait random time with LED off
		GPIOA->ODR &= ~(1 << 5);
		for(volatile uint32_t y = 0; y < 1000000; y++);
		//LED turns on and timer starts
		GPIOA->ODR |= (1 << 5);
		LED_ON = TIM2->CNT;
		//button gets pressed, timer stops
		while(GPIOC->IDR & (1 << 13)) {}
		BUTTON_PRESSED = TIM2->CNT;
		uint32_t TIME_ELAPSED = BUTTON_PRESSED - LED_ON;
		uint32_t BLINK_DELAY = TIME_ELAPSED / 50;
		for(int b = 0; b < 5; b++) {
			GPIOA->ODR |= (1 << 5);
			for(volatile uint32_t i = 0; i < BLINK_DELAY; i++);
			GPIOA->ODR &= ~(1 << 5);
			for(volatile uint32_t i = 0; i < BLINK_DELAY; i++);
		}
		//blinking speed based on time difference
		GPIOA->ODR |= (1 << 5);
		for(volatile int i = 0; i < TIME_ELAPSED; i++);
		GPIOA->ODR &= ~(1 << 5);
		for(volatile int j = 0; j < TIME_ELAPSED; j++);
		//wait for next round
		for(int volatile x = 0; x < 5000000; x++);
	}

}
