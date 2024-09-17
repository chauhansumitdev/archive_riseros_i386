ASM = nasm
SRC_DIR = src
BUILD_DIR = build

$(BUILD_DIR)/main_floppy.img: $(BUILD_DIR)/main.bin
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	copy $(BUILD_DIR)\main.bin $(BUILD_DIR)\main_floppy.img
	@echo This system does not support truncate natively. Consider using another tool to create the floppy image.

$(BUILD_DIR)/main.bin: $(SRC_DIR)/main.asm
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(ASM) $(SRC_DIR)\main.asm -f bin -o $(BUILD_DIR)\main.bin

all: $(BUILD_DIR)/main_floppy.img

clean:
	rd /s /q $(BUILD_DIR)
