/**
 * Linker script for STM32C071RB
 * Memory: 32KB Flash, 12KB RAM
 */

/* Entry point */
ENTRY(Reset_Handler)

/* Memory regions */
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 32K
    RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 12K
}

/* Sections */
SECTIONS
{
    /* Vector table goes first in Flash */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } >FLASH
    
    /* Program code and constants */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    } >FLASH
    
    /* Initialized data */
    _sidata = LOADADDR(.data);
    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } >RAM AT>FLASH
    
    /* Uninitialized data */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >RAM
    
    /* Stack (grows down from top of RAM) */
    .stack :
    {
        . = ALIGN(8);
        . = . + 0x400; /* 1KB stack */
        . = ALIGN(8);
        _estack = .;
    } >RAM
}
