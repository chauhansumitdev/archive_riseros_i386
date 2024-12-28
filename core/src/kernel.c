#include <stdint.h>
#include "multiboot.h"
#include "./global/globals.h"
#include "./util/util.h"
#include "./cursor/cursor.h"
#include "./assembly/assembly.h"
#include "./gdt/gdt.h"
#include "./idt/idt.h"
#include "./interrupts/interrupts.h"

struct multiboot_header multiboot __attribute__((section(".multiboot"))) = {
    MULTIBOOT_HEADER_MAGIC,
    MULTIBOOT_HEADER_FLAGS,
    MULTIBOOT_HEADER_CHECKSUM
};


void _start(uint32_t multiboot_info_ptr) {
    const char *str = "Welcome to riseros_";

    for (int i = 0; i < 11; i++) {  
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x0F; 
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

    const char* contact = "Developed by Sumit Chauhan github.com/chauhansumitdev";
    for(int i = 0; (i < 80) && (i < 13); i++) {
        video_memory[(row*80+i)*2] = contact[i];
        video_memory[(row*80+i)*2+1] = 0x07;
    }
    for(int i = 13; contact[i] != '\0'; i++) {
        video_memory[(row*80+i)*2] = contact[i];
        video_memory[(row*80+i)*2+1] = 0x09;
    }
    row+=2;

    const char character = 0xDB;  
    int color = 0x0F;  
    for (int i = 0; i < 2; i++) {  
        for (int j = 0; j < 16; j++) {
            video_memory[(row * 80 + j) * 2] = character;  
            video_memory[(row * 80 + j) * 2 + 1] = color; 
            color = (color + 0x01) % 0x0F;  
        }
        row++;  
    }
    move_cursor(6, 54);
    time_delay();
    clear_screen();
    

    move_cursor(0,0);




    // ******************** after boot protected mode check ****

    // println("Checking in protected mode ...");

    // if(is_protected_mode()){
    //     println("In protected mode --- [OK]");
    // }else{
    //     println("In REAL MODE ...");
    // }

    // TODO --
    // multiboot_info(multiboot_info_ptr); -- lacks implementation

    // int a = 10/0; -- interrupt check  -- failed -- reboot


    // ******************************************************
    // impl gdt --> below

    set_gdt_entry(0, 0, 0, 0, 0);  
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); 
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);  
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0x92, 0xCF);
    load_gdt();
    refresh_registers();

    //******************************************* */
    // ****** after gdt protected mode check ********

    if(is_protected_mode()){
        println("In protected mode --- [OK]");
    }else{
        println("In REAL MODE ...");
    }

    // ******** setting up idt ********

    setup_idt();

    // ****** testing interrupt******
    int a = 10/0;

     println(" just after division");
    // -- system HALTED .. does not gets exectured.

    
}
