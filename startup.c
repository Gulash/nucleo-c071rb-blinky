/* Minimal startup for Cortex-M0+ (Reset handler, vector table) */
#include <stdint.h>

/* Symbols from linker script */
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sidata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _estack;

int main(void);
void Reset_Handler(void);
void Default_Handler(void);

__attribute__((section(".isr_vector")))
uint32_t *vector_table[] = {
    (uint32_t *)&_estack,
    (uint32_t *)Reset_Handler,
    (uint32_t *)Default_Handler, /* NMI */
    (uint32_t *)Default_Handler, /* HardFault */
    (uint32_t *)0, /* reserved */
    (uint32_t *)0, /* reserved */
    (uint32_t *)0, /* reserved */
    (uint32_t *)0, /* reserved */
    (uint32_t *)0, /* reserved */
    (uint32_t *)0, /* reserved */
    (uint32_t *)0, /* reserved */
    (uint32_t *)Default_Handler, /* SVCall */
    (uint32_t *)Default_Handler, /* DebugMonitor */
    (uint32_t *)0, /* reserved */
    (uint32_t *)Default_Handler, /* PendSV */
    (uint32_t *)Default_Handler  /* SysTick */
};

void Reset_Handler(void) {
    uint32_t *src, *dst;

    /* copy .data from flash to SRAM */
    src = &_sidata;
    dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    /* zero .bss */
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }

    /* call main */
    main();

    /* If main returns, loop forever */
    while (1) { }
}

void Default_Handler(void) {
    while (1) { }
}
