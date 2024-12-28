#include "idt.h"
#include <stdint.h>
#include "../interrupts/interrupts.h"

struct idt_entry idt[IDT_ENTRIES];
struct idt_descriptor idtr;

extern void divide_by_zero();

void set_idt_entry(int index, uint32_t base, uint16_t selector, uint8_t flags) {
    idt[index].base_low = base & 0xFFFF;
    idt[index].base_high = (base >> 16) & 0xFFFF;
    idt[index].selector = selector;
    idt[index].always_zero = 0;
    idt[index].flags = flags;
}

void load_idt() {
    idtr.limit = sizeof(idt) - 1;
    idtr.base = (uint32_t)&idt;
    asm volatile ("lidt (%0)" : : "r"(&idtr));
}

void setup_idt() {
    set_idt_entry(0, (uint32_t)divide_by_zero, 0x08, 0x8E); 
    load_idt();
}
