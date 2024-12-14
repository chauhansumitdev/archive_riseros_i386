#include <stdint.h>
#include <stddef.h>
#include "../util/util.h"

typedef struct {
    uint32_t size;
    uint64_t base_addr;
    uint64_t length;
    uint32_t type;
} __attribute__((packed)) multiboot_memory_map_t;

typedef struct {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t mmap_length;
    uint32_t mmap_addr;
} __attribute__((packed)) multiboot_info_t;

void multiboot_info(uint32_t multiboot_info_ptr) {
    multiboot_info_t* mbi = (multiboot_info_t*) multiboot_info_ptr;

    if (mbi->flags & (1 << 6)) { 
        multiboot_memory_map_t* mmap = (multiboot_memory_map_t*) mbi->mmap_addr;
        println("Memory Map");
        
        while ((uint32_t) mmap < mbi->mmap_addr + mbi->mmap_length) {
            // println("Base: 0x%016llx, Length: 0x%016llx, Type: %u\n",
            //        mmap->base_addr,
            //        mmap->length,
            //        mmap->type);

            println("Inside while");

            if (mmap->type == 1) { 
                // Usable memory
                // printf("  Usable Region -> Base: 0x%016llx, Length: 0x%016llx\n",
                //        mmap->base_addr,
                //        mmap->length);

                println("Inside if");

                // usable memory for the kernel ... ???
            }

            mmap = (multiboot_memory_map_t*) ((uint32_t) mmap + mmap->size + sizeof(mmap->size));
        }
    } else {
        println("Memory map not available --- [ FAILED ]");
    }
}
