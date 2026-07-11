#include "stm32f4xx.h"
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void) {
    //Enable clocks
	RCC->AHB1ENR |= (1 << 0);
    RCC->AHB1ENR |= (1 << 2);
    //Enable LED I/O
    GPIOA->MODER &= ~(0x3 << 10);
    GPIOA->MODER |= (0x1 << 10);
    //Enable button input
    GPIOC->MODER &= ~(0x3 << 26);
    //loop for button press
    while(1) {
    	if(GPIOC->IDR & (1<<13)) {
    		GPIOA->ODR &= ~(1 << 5);
    	} else {
    		GPIOA->ODR |= (1 << 5);
    	}
    }


}
