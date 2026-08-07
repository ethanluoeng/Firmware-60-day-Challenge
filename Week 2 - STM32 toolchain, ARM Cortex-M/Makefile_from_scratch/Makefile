CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

DRIVERS = C:/Users/ethan/Documents/Firmware-60-day-Challenge/Week 2 - STM32 toolchain, ARM Cortex-M/F4_chip_headers

CFLAGS  = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 \
          -ffunction-sections -fdata-sections -Og -g3 -Wall \
          -DSTM32F446xx \
          -I"$(DRIVERS)/CMSIS/Device/ST/STM32F4xx/Include" \
          -I"$(DRIVERS)/CMSIS/Include"

LDFLAGS = -T STM32F446RETX_FLASH.ld --specs=nosys.specs -Wl,--gc-sections

OBJS    = main.o startup_stm32f446retx.o

all: firmware.bin

firmware.bin: firmware.elf
	$(OBJCOPY) -O binary $< $@

firmware.elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean flash gdb

flash: firmware.bin
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
	  -c "program firmware.bin 0x08000000 verify reset exit"

gdb: firmware.elf
	arm-none-eabi-gdb $< -ex "target extended-remote :3333"

clean:
	rm -f *.o *.elf *.bin


# To run: 
# make            # compiles, links, makes firmware.bin, prints size
# make            # run again — "Nothing to be done" (the graph at work)
# make flash      # programs the chip (LED should blink)
# make clean      # wipes artifacts, then `make` rebuilds from scratch
