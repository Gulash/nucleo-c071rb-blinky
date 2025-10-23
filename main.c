/**
 * Simple Blinky for NUCLEO-C071RB
 * LED: PA5 (LD4 on Nucleo board)
 */

#include <stdint.h>

/* Register Addresses for STM32C071 */
#define RCC_BASE        0x40021000
#define GPIOA_BASE      0x50000000

/* Register Offsets */
#define RCC_IOPENR      (*(volatile uint32_t *)(RCC_BASE + 0x34))
#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR       (*(volatile uint32_t *)(GPIOA_BASE + 0x14))

/* Bit Definitions */
#define RCC_IOPENR_GPIOAEN  (1 << 0)  // Enable GPIOA clock

/* Simple delay */
void delay(volatile uint32_t count) {
    while(count--) {
        __asm__("nop");
    }
}

int main(void) {
    /* Enable GPIOA clock */
    RCC_IOPENR |= RCC_IOPENR_GPIOAEN;
    
    /* Configure PA5 as output (LED) */
    /* Clear mode bits for PA5 (bits 10-11) */
    GPIOA_MODER &= ~(3U << 10);
    /* Set PA5 as general purpose output (01) */
    GPIOA_MODER |= (1U << 10);
    
    /* Blink forever */
    while(1) {
        /* Toggle PA5 */
        GPIOA_ODR ^= (1 << 5);
        
        /* Delay ~500ms at default clock */
        delay(400000);
    }
    
    return 0;
}
