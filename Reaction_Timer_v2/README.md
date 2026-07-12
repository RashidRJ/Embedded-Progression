# Project 4 - Reaction Timer v2

Bare-metal reaction timer on the STM32F446RE Nucleo board using the TIM2 hardware 
timer for accurate microsecond timing. No HAL used, only direct register access.

## Hardware
- STM32F446RE Nucleo board
- Onboard LED on pin PA5
- Onboard user button on pin PC13

## How it works
1. LED turns off, fixed delay simulates a random wait
2. LED turns on - this is the signal to press the button
3. TIM2 counter value is recorded the moment the LED turns on
4. Program waits for button press via GPIOC IDR
5. TIM2 counter value is recorded the moment the button is pressed
6. Elapsed time is calculated by subtracting the two counter values (in microseconds)
7. LED blinks 5 times - blink speed reflects reaction time
   (fast blinks = fast reaction, slow blinks = slow reaction)
8. Fixed pause before next round

## Registers used
- `RCC->AHB1ENR` - enables clocks for GPIOA (bit 0) and GPIOC (bit 2)
- `RCC->APB1ENR` - enables clock for TIM2 (bit 0)
- `GPIOA->MODER` - sets PA5 to output mode (bits 11:10 = 01)
- `GPIOC->MODER` - sets PC13 to input mode (bits 27:26 = 00)
- `GPIOA->ODR`   - turns LED on/off via bit 5
- `GPIOC->IDR`   - reads button state via bit 13 (active low)
- `TIM2->PSC`    - prescaler set to 15, divides 16MHz clock to 1MHz (1 tick = 1 microsecond)
- `TIM2->ARR`    - set to 0xFFFFFFFF, allows counter to run as high as possible
- `TIM2->CR1`    - bit 0 (CEN) set to start the counter
- `TIM2->CNT`    - read to capture timestamps at LED on and button press

## Notes
- Elapsed time is in microseconds. A typical reaction time of 300ms = ~300,000 ticks.
- Blink delay is TIME_ELAPSED / 50 to scale the feedback to a visible speed.
- The wait before the LED turns on is a fixed delay, not truly random.
  A proper implementation would seed a random delay using a free-running counter.
- Button debouncing is not implemented. A hardware or software debounce  would improve reliability.