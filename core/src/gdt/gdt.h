#ifndef GDT_H
#define GDT_H

#include <stdint.h>   

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_descriptor {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern struct gdt_entry gdt[4];  
extern struct gdt_descriptor gdtr;

void set_gdt_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);
void load_gdt(void);
void refresh_registers(void);

#endif  
