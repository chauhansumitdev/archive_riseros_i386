#include "interrupts.h"
#include "../util/util.h"


void divide_by_zero(){
    println("DIVIDED BY ZERO----[HANDLED - OK]");
    println("System HALTED----[OK]");
    // here i need to get my code execution back so for now returning back to the normal code execution just after where the interrupt occured.
    //asm volatile("iret");
    //--- leh not working -- :(

    while(1){}
}