CC := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
CFLAGS := -mcpu=cortex-m0plus -mthumb -Os -ffunction-sections -fdata-sections -Wall
LDFLAGS := -TSTM32C071RBTx.ld -nostdlib -Wl,--gc-sections -Wl,-Map=firmware.map

SRCS := startup.c main.c memutils.c
OBJS := $(SRCS:.c=.o)
TARGET := firmware.elf

.PHONY: all clean

all: $(TARGET) firmware.bin firmware.hex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET)

firmware.bin: $(TARGET)
	$(OBJCOPY) -O binary $(TARGET) firmware.bin

firmware.hex: $(TARGET)
	$(OBJCOPY) -O ihex $(TARGET) firmware.hex

clean:
	rm -f $(OBJS) $(TARGET) firmware.bin firmware.hex firmware.map
