#include "interrupts.h"
#include "../util/util.h"


void divide_by_zero(){
    println("DIVIDED BY ZERO----[HANDLED - OK]");
    while(1){
        // halting the system till we get to know how to resume from this.
    }
}