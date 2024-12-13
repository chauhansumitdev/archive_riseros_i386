#include "cursor.h"

void outb(unsigned short port, unsigned char value) {
    __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

void move_cursor(int row, int col) {
    cursor_row = row;
    cursor_col = col;
    unsigned short position = row * 80 + col;
    outb(0x3D4, 0x0F); 
    outb(0x3D5, (unsigned char)(position & 0xFF));  
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));  
}