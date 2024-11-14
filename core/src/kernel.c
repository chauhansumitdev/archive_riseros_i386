#include "multiboot.h"

struct multiboot_header multiboot __attribute__((section(".multiboot"))) = {
    MULTIBOOT_HEADER_MAGIC,
    MULTIBOOT_HEADER_FLAGS,
    MULTIBOOT_HEADER_CHECKSUM
};

void _start() {
    const char *str = "Welcome to riseros_";
    char *video_memory = (char *) 0xb8000;

    for (int i = 0; i < 11; i++) {  
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x07; 
    }
    for(int i = 11; str[i] != '\0'; i++){
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x0C;
    }

    const char *riseros[5] = {
        "*****   ***  *****  *****  *****   ***   *****",
        "*    *   *   *      *      *    * *   *  *    ",
        "*****    *   ***    ****   *****  *   *  ***  ",
        "*   *    *      *   *      *   *  *   *     * ",
        "*    *  ***  *****  *****  *    *  ***   *****"
    };

    int row = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; riseros[i][j] != '\0'; j++) {
            video_memory[(row * 80 + j) * 2] = riseros[i][j];
            video_memory[(row * 80 + j) * 2 + 1] = 0x0C;  
        }
        row++;  
    }

    
}
