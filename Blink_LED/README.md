# Project 1 - Blinking LED

Bare-metal LED blink on the STM32F446RE Nucleo board. No HAL used, only direct register access.

# Hardware
- STM32F446RE Nucleo board
- Onboard LED on pin PA5

# Process
1. Enable GPIOA clock using RCC_AHB1ENR
2. Configure PA5 as output using GPIOA_MODER
3. Toggle PA5 between high/low using GPIOA_ODR with slight delay loop

# Registers used
- 'RCC-AHB1ENR' - Enables clock for GPIOA
- 'GPIOA->MODER' - Sets pin 5 to output mode using bits 11:10
- 'GPIOA->ODR' - Toggles pin 5 high or low using bit 5