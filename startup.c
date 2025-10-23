/**
 * Minimal startup file for STM32C071RB
 * 32KB Flash, 12KB RAM
 */

#include <stdint.h>

/* Initial stack pointer (end of 12KB RAM) */
#define STACK_START 0x20003000

/* Function prototypes */
void Reset_Handler(void);
void Default_Handler(void);

/* External symbols from linker script */
extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss;
extern int main(void);

/* Cortex-M0+ core interrupts */
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));

/* Vector table */
__attribute__((section(".isr_vector")))
const uint32_t vector_table[] = {
    STACK_START,                    /* Initial Stack Pointer */
    (uint32_t)Reset_Handler,        /* Reset Handler */
    (uint32_t)NMI_Handler,          /* NMI Handler */
    (uint32_t)HardFault_Handler,    /* Hard Fault Handler */
    0,                              /* Reserved */
    0,                              /* Reserved */
    0,                              /* Reserved */
    0,                              /* Reserved */
    0,                              /* Reserved */
    0,                              /* Reserved */
    0,                              /* Reserved */
    (uint32_t)SVC_Handler,          /* SVCall Handler */
    0,                              /* Reserved */
    0,                              /* Reserved */
    (uint32_t)PendSV_Handler,       /* PendSV Handler */
    (uint32_t)SysTick_Handler,      /* SysTick Handler */
    /* External interrupts start here - add as needed */
};

/* Reset handler - this is where the program starts */
void Reset_Handler(void) {
    /* Copy initialized data from Flash to RAM */
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    
    while (dst < &_edata) {
        *dst++ = *src++;
    }
    
    /* Clear uninitialized data (BSS) */
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }
    
    /* Call main function */
    main();
    
    /* If main returns, loop forever */
    while(1);
}

/* Default handler for unused interrupts */
void Default_Handler(void) {
    while(1);
}
