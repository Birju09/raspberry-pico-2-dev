CROSS_COMPILE ?= arm-none-eabi-

# SDK Directory
REPO_DIR = external/pico-sdk
BRANCH = master

# Compiler and tools
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
SIZE = $(CROSS_COMPILE)size

# MCU settings
CPU = cortex-m33
ARCH = armv8-m

BUILD_DIR = build
TARGET = armv8-m

# Flags
CFLAGS = -mcpu=$(CPU) -mthumb -Wall -O3 \
         -ffunction-sections -fdata-sections \
         -I. \
		 -I $(REPO_DIR)/src/rp2_common/cmsis/stub/CMSIS/Device/RP2350/Include/ \
		 -I $(REPO_DIR)/src/rp2_common/cmsis/stub/CMSIS/Core/Include/ \
		 -I $(REPO_DIR)/src/rp2350/hardware_regs/include/ \
		 -ffreestanding

ASFLAGS = -mcpu=$(CPU) -mthumb

LDFLAGS = -T flash.ld \
          -specs=nosys.specs \
          -Wl,--gc-sections \
		  -nostartfiles \
          -Wl,--print-memory-usage

# Source files
C_SRCS = main.c init.c
OBJS = $(C_SRCS:.c=.o)

# Output files
TARGET = embedded-course.elf
BINARY = embedded-course.bin

uf2: $(BINARY)
	picotool uf2 convert ${BINARY} output.uf2 --family rp2350-arm-s --abs-block

all: $(BINARY) uf2

# Compile C sources
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile assembly sources
%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

# Link
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)
	$(SIZE) $@

# Generate binary
$(BINARY): $(TARGET)
	$(OBJCOPY) -O binary $< $@

# Clean
.PHONY: clean
clean:
	rm -f *.o $(TARGET) $(BINARY) *.uf2

# Print settings (for debugging)
.PHONY: info
info:
	@echo "CC       = $(CC)"
	@echo "CFLAGS   = $(CFLAGS)"
	@echo "LDFLAGS  = $(LDFLAGS)"
	@echo "C_SRCS   = $(C_SRCS)"
	@echo "ASM_SRCS = $(ASM_SRCS)"
	@echo "OBJS     = $(OBJS)"