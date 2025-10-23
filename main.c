#include <stdint.h>

/* === CONFIGURE THIS FOR YOUR BOARD ===
   Default below assumes NUCLEO-C071RB user LED on PC9.
   If your board uses PA5 (common on many Nucleo-64), change accordingly.
   ODR offset is 0x14 for STM32 GPIO; GPIO block base commonly in 0x4800_0000 range.
*/

#define GPIO_BASE_PLIN      0x48000000U  /* base for GPIOA; adjust if needed */
#define GPIO_PORT_OFFSET    0x400U       /* port stride: A +0x000, B +0x400, C +0x800 ... */
#define GPIO_ODR_OFFSET     0x14U

/* Choose the port index: 0=A, 1=B, 2=C, ... */
#define LED_PORT_INDEX      2U   /* 2 => GPIOC */
#define LED_PIN             9U   /* pin number (0..15) */

/* compute ODR address for chosen port */
#define GPIOx_BASE(port_index) (GPIO_BASE_PLIN + ((port_index) * GPIO_PORT_OFFSET))
#define GPIOx_ODR_ADDR(port_index) (GPIOx_BASE(port_index) + GPIO_ODR_OFFSET)

volatile uint32_t * const LED_ODR = (volatile uint32_t *)GPIOx_ODR_ADDR(LED_PORT_INDEX);

static void delay(volatile uint32_t n) {
    while (n--) {
        __asm__ volatile("nop");
    }
}

int main(void) {
    /* NOTE: Many STM32 MCUs require enabling the GPIO port clock in RCC before toggling.
       If LED doesn't react, you must enable the corresponding RCC AHBENR bit for the port.
       For example (pseudocode):
         RCC->AHBENR |= (1 << (LED_PORT_INDEX + X));
       The exact RCC register & bit depend on MCU family; check reference manual.
    */

    while (1) {
        /* toggle pin by XORing the ODR bit (this is simple but non-atomic) */
        *LED_ODR ^= (1U << LED_PIN);
        delay(300000);
    }

    return 0;
}
