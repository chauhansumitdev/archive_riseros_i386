#include "util.h"
#include "../global/globals.h"
#include "../cursor/cursor.h"

void println(const char *str){

    int i = 0;
    while (str[i] != '\0') {
        video_memory[(cursor_row*80 +cursor_col) * 2] = str[i];  
        video_memory[(cursor_row*80+cursor_col) * 2 + 1] = 0x07;
        cursor_col++;
        move_cursor(cursor_row, cursor_col);       
        i++;
    }

    cursor_row++;
    cursor_col = 0;
    move_cursor(cursor_row, cursor_col);
}