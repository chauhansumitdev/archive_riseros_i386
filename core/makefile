CC=i386-elf-gcc
LD=i386-elf-ld
CFLAGS=-ffreestanding -nostdlib -Wall -Wextra -m32
LDFLAGS=-nostdlib -melf_i386 -T linker.ld

SRC_DIR=src
BUILD_DIR=build
OBJ_DIR=obj
ISO_DIR=$(BUILD_DIR)/iso
GRUB_DIR=$(ISO_DIR)/boot/grub

KERNEL_SRC=$(SRC_DIR)/kernel.c
KERNEL_OBJ=$(OBJ_DIR)/kernel.o
KERNEL_BIN=$(BUILD_DIR)/kernel.bin
GRUB_CFG=$(GRUB_DIR)/grub.cfg

SRC_FILES=$(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES=$(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: iso

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	# Create necessary directories under obj before compiling
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/kernel.bin: $(OBJ_FILES)
	$(LD) $(LDFLAGS) -o $@ $^

$(GRUB_CFG): 
	mkdir -p $(GRUB_DIR)
	echo "set timeout=0" > $(GRUB_CFG)
	echo "set default=0" >> $(GRUB_CFG)
	echo "menuentry \"riseros\" {" >> $(GRUB_CFG)
	echo "    multiboot /boot/grub/kernel.bin" >> $(GRUB_CFG)
	echo "    boot" >> $(GRUB_CFG)
	echo "}" >> $(GRUB_CFG)

iso: $(BUILD_DIR)/kernel.bin $(GRUB_CFG)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(BUILD_DIR)/kernel.bin $(ISO_DIR)/boot/grub/kernel.bin
	grub-mkrescue -o $(BUILD_DIR)/os.iso $(ISO_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)/iso $(BUILD_DIR)/kernel.bin $(GRUB_CFG)

.PHONY: all clean iso
