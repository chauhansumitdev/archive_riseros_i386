#include <stdint.h>
#include "assembly.h"

int is_protected_mode() {
    uint32_t cr0;
    
    __asm__ volatile (
        "mov %%cr0, %0"  
        : "=r"(cr0)       
        :                
    );
    
    return (cr0 & 0x1) != 0;  
}

