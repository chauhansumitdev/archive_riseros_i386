#include "gdt.h"

struct gdt_entry gdt[4];  // Null, Code, Data, Stack -- four entries now :)
struct gdt_descriptor gdtr;

void set_gdt_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[index].base_low = base & 0xFFFF;
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;
    gdt[index].limit_low = limit & 0xFFFF;
    gdt[index].granularity = (limit >> 16) & 0x0F;
    gdt[index].granularity |= granularity & 0xF0;
    gdt[index].access = access;
}

void load_gdt() {
    gdtr.limit = sizeof(gdt) - 1;
    gdtr.base = (uint32_t)&gdt;
    asm volatile ("lgdt (%0)" : : "r"(&gdtr));
}

void refresh_registers() {
    asm volatile (
        "mov $0x10, %ax\n"  
        "mov %ax, %ds\n"
        "mov %ax, %es\n"
        "mov %ax, %fs\n"
        "mov %ax, %gs\n"
        "mov $0x18, %ax\n"  
        "mov %ax, %ss\n"
        "mov $0x08, %ax\n"  
        "jmp $0x08, $flush\n"  
        "flush:\n"
    );
}