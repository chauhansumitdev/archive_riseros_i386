#include "multiboot.h"

struct multiboot_header multiboot __attribute__((section(".multiboot"))) = {
    MULTIBOOT_HEADER_MAGIC,
    MULTIBOOT_HEADER_FLAGS,
    MULTIBOOT_HEADER_CHECKSUM
};


void _start() {
    const char *str = "Welcome to riseros_";
    char *video_memory = (char *) 0xb8000;
    for (int i = 0; str[i] != '\0'; i++) {
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x07; 
    }
}
