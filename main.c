#include <stdint.h>

/* STM32C0 / G0 style addresses (common mapping):
   RCC base  ~ 0x4002_1000 ; IOPENR offset 0x34 (IO port enable)
   GPIO base ~ 0x5000_0000 ; port stride 0x400 ; ODR offset 0x14
   These values match STM32C0 examples and RM0490 usage.
*/

#define RCC_BASE        0x40021000UL
#define RCC_IOPENR      (*(volatile uint32_t *)(RCC_BASE + 0x34UL))

#define GPIO_BASE       0x50000000UL
#define GPIO_PORT_STRIDE 0x400UL
#define GPIO_ODR_OFFSET  0x14UL

/* Configure to use PA5 (port index 0, pin 5) */
#define LED_PORT_INDEX 0U  /* 0 => GPIOA */
#define LED_PIN        5U

#define GPIOx_ODR(port_index) (*(volatile uint32_t *)(GPIO_BASE + (port_index)*GPIO_PORT_STRIDE + GPIO_ODR_OFFSET))

static void delay(volatile uint32_t n) {
    while (n--) { __asm__ volatile("nop"); }
}

int main(void) {
    /* Enable GPIOA clock: set bit 0 in RCC IOPENR */
    RCC_IOPENR |= (1U << LED_PORT_INDEX);

    /* Set PA5 as output:
       For minimal code we directly set the MODER bits:
       MODER offset = 0x00, each pin has 2 bits: 00=input, 01=output, 10=alt, 11=analog.
       We'll set MODE5 = 01.
       For simplicity we use the address and manipulate register bits.
    */
    volatile uint32_t *gpio_moder = (volatile uint32_t *)(GPIO_BASE + (LED_PORT_INDEX * GPIO_PORT_STRIDE) + 0x00UL);
    /* clear bit pair then set to 01 */
    *gpio_moder &= ~(0x3UL << (LED_PIN * 2));
    *gpio_moder |=  (0x1UL << (LED_PIN * 2));

    volatile uint32_t *odr = &GPIOx_ODR(LED_PORT_INDEX);

    while (1) {
        /* toggle pin */
        *odr ^= (1U << LED_PIN);
        delay(300000);
    }

    return 0;
}
