#include "stm32f4xx.h"
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void) {
	//enable clocks
	RCC->AHB1ENR |= (1 << 0); //GPIOA
	RCC->AHB1ENR |= (1 << 2); //GPIOC
	//enable LED I/O
	GPIOA->MODER &= ~(0x3 << 10);
	GPIOA->MODER |= (0x1 << 10);
	//enable button input
	GPIOC->MODER &= ~(0x3 << 26);
	//timer loop
	while(1) {
		//wait random time
		GPIOA->ODR |= (1 << 5);
		for(volatile uint32_t i = 0; i < 1000000; i++);
	    //LED on, start timer
		uint32_t count = 0;
		while(GPIOC->IDR & (1 << 13)) {
			count++;
		}
		//LED turns off
		GPIOA->ODR &= ~(1 << 5);
		//signal result
		for(volatile int i = 0; i < 10; i++) {
			GPIOA->ODR |= (1 << 5);
			for(volatile int x = 0; x < count; x++);
			GPIOA->ODR &= ~(1 << 5);
			for(volatile int y = 0; y < count;y++);
		}
		//wait before next round
		for(volatile int j = 0; j < 1000000; j++);
	}

}
