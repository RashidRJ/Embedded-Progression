#include "stm32f4xx.h"
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void) {
	RCC->AHB1ENR |= (1 << 0);
	GPIOA->MODER &= ~(0x3 << 10);
	GPIOA->MODER |= (0x1 << 10);

	while(1) {
		GPIOA->ODR |= (1 << 5);
		for(int i = 0; i < 1000000; i++);
		GPIOA->ODR &= ~(1 << 5);
		for(int i = 0; i < 1000000; i++);
	}
}
