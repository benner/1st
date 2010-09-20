#ifndef _IDT_H_
#define _IDT_H_
#include <types.h>

struct idt_entry_struct
{
  u16_t base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
  u16_t sel;                 // Kernel segment selector.
  u8_t  always0;             // This must always be zero.
  u8_t  flags;               // More flags. See documentation.
  u16_t base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct
{
  u16_t limit;
  u32_t base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

typedef struct registers
{
  u32_t ds;
  u32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  u32_t int_no, err_code;
  u32_t eip, cs, eflags, useresp, ss;
} registers_t; 

typedef void (*isr_t)(registers_t);


extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10 ();
extern void isr11 ();
extern void isr12 ();
extern void isr13 ();
extern void isr14 ();
extern void isr15 ();
extern void isr16 ();
extern void isr17 ();
extern void isr18 ();
extern void isr19 ();
extern void isr20 ();
extern void isr21 ();
extern void isr22 ();
extern void isr23 ();
extern void isr24 ();
extern void isr25 ();
extern void isr26 ();
extern void isr27 ();
extern void isr28 ();
extern void isr29 ();
extern void isr30 ();
extern void isr31 ();

void isr_handler(registers_t);
void idt_set_gate(u8_t, u32_t, u16_t, u8_t);
void idt_flush(u32_t);
extern void idt_install();
#endif


