#include "util.h"

#define VGA_ADDRESS 0xB8000
#define VGA_COLS 80
#define VGA_ROWS 25

void clear_screen() {
    char *video_memory = (char *)VGA_ADDRESS;

    for (int i = 0; i < VGA_ROWS; i++) {
        for (int j = 0; j < VGA_COLS; j++) {
            int index = (i * VGA_COLS + j) * 2;
            video_memory[index] = 0x20; 
            video_memory[index + 1] = 0x07; 
        }
    }
}

