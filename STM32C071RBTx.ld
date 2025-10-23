/* Minimal linker script for STM32C071x8 / NUCLEO-C071RB
   FLASH: 0x08000000 (128 KB)
   SRAM : 0x20000000 (24  KB)
*/
ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 0x20000  /* 128K */
  RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 0x6000   /* 24K  */
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    *(.text*)
    *(.rodata*)
    *(.glue_7)
    *(.glue_7t)
    KEEP(*(.init))
    KEEP(*(.fini))
  } > FLASH

  .data : AT(ADDR(.text) + SIZEOF(.text))
  {
    _sidata = LOADADDR(.data);
    _sdata = .;
    *(.data*)
    _edata = .;
  } > RAM

  .bss :
  {
    _sbss = .;
    *(.bss*)
    *(COMMON)
    _ebss = .;
  } > RAM

  /DISCARD/ : { *(.eh_frame) }
}
