@echo off
setlocal

if not exist STM32C071RBTx.ld (
  echo ERROR: missing STM32C071RBTx.ld
  exit /b 1
)

echo Building...
arm-none-eabi-gcc -c -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -fdata-sections -Wall startup.c -o startup.o
arm-none-eabi-gcc -c -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -fdata-sections -Wall main.c -o main.o
arm-none-eabi-gcc -c -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -fdata-sections -Wall memutils.c -o memutils.o

arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -nostdlib -Wl,--gc-sections -Wl,-Map=firmware.map -TSTM32C071RBTx.ld main.o startup.o memutils.o -o firmware.elf

arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
arm-none-eabi-objcopy -O ihex firmware.elf firmware.hex

arm-none-eabi-size firmware.elf

dir firmware.* /b
echo Done.
endlocal
