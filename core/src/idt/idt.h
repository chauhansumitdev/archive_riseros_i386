#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_ENTRIES 256

struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t always_zero;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_descriptor {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void set_idt_entry(int index, uint32_t base, uint16_t selector, uint8_t flags);
void load_idt();
void setup_idt();

#endif
