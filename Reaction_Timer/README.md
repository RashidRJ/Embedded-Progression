# Project 3 - Reaction Timer

Bare-metal reaction timer on the STM32F446RE Nucleo board. 
No HAL used, only direct register access.

## Hardware
- STM32F446RE Nucleo board
- Onboard LED on pin PA5
- Onboard user button on pin PC13

## How it works
1. LED turns off and waits a fixed delay (simulating a random wait)
2. LED turns on - this is the signal to press the button
3. A counter increments every iteration while waiting for the button press
4. When the button is pressed, the counter stops
5. The LED blinks 10 times with the blink speed reflecting reaction time 
   (fast blinks = fast reaction, slow blinks = slow reaction)

## Registers used
- `RCC->AHB1ENR` - enables clocks for GPIOA (bit 0) and GPIOC (bit 2)
- `GPIOA->MODER` - sets PA5 to output mode (bits 11:10 = 01)
- `GPIOC->MODER` - sets PC13 to input mode (bits 27:26 = 00)
- `GPIOA->ODR`   - turns LED on/off via bit 5
- `GPIOC->IDR`   - reads button state via bit 13

## Notes
- The counter is just a loop, not a real hardware timer