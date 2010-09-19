#include <types.h>

struct gdt_entry_struct
{
   u16_t limit_low;           // The lower 16 bits of the limit.
   u16_t base_low;            // The lower 16 bits of the base.
   u8_t  base_middle;         // The next 8 bits of the base.
   u8_t  access;              // Access flags, determine what ring this segment can be used in.
   u8_t  granularity;
   u8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t; 

struct gdt_ptr_struct
{
   u16_t limit;               // The upper 16 bits of all selector limits.
   u32_t base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t; 


void gdt_set_gate(int, unsigned long, unsigned long, unsigned char, unsigned char);
void gdt_install();
void gdt_flush(u32_t);
