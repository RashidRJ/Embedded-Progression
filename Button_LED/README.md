# Project 2 - Button Controlled LED

Bare-metal LED blink using button on the STM32F446RE Nucleo board. No HAL used, only direct register access.

# Hardware
- STM32F446RE Nucleo board
- Onboard LED on pin PA5
- Onboard button on pin PC13

# Process
1. Enable GPIOA clock using RCC_AHB1ENR
2. Configure PA5 as output using GPIOA_MODER
3. Enable PC13 for input using GPIOC_MODER
4. Read PC13 state using GPIOC_IDR -> if button is pressed turn LED on, otherwise turn LED off.

# Registers used
- 'RCC->AHB1ENR'  - Enables clock for GPIOA (bit 0) and GPIOC (bit 2)
- 'GPIOA->MODER' - Sets pin 5 to output mode using bits 11:10
- 'GPIOA->ODR'   - Toggles pin 5 high or low using bit 5
- 'GPIOC->MODER' - Enables button input
- 'GPIOC->IDR'   - Reads button input on pin 13