#include <kernlib.h>
#include <idt.h>

idt_entry_t idt[256];
idt_ptr_t   ip;

void isr_handler(registers_t regs)
{
  printf("received interrupt: %u\n", regs.int_no);
  if (regs.int_no == 13) for(;;);
} 

void idt_set_gate(u8_t num, u32_t base, u16_t sel, u8_t flags)
{
  idt[num].base_lo = base & 0xFFFF;
  idt[num].base_hi = (base >> 16) & 0xFFFF;

  idt[num].sel     = sel;
  idt[num].always0 = 0;
  idt[num].flags   = flags /* | 0x60 */;
} 

void idt_install()
{
  ip.limit = sizeof(idt_entry_t) * 256 -1;
  ip.base  = (u32_t)&idt;
  memset(&idt, 0, sizeof(idt_entry_t)*256);

  idt_set_gate(0, (u32_t)isr0 , 0x08, 0x8E);
  idt_set_gate(1, (u32_t)isr1 , 0x08, 0x8E);
  idt_set_gate(2, (u32_t)isr2 , 0x08, 0x8E);
  idt_set_gate(3, (u32_t)isr3 , 0x08, 0x8E);
  idt_set_gate(4, (u32_t)isr4 , 0x08, 0x8E);
  idt_set_gate(5, (u32_t)isr5 , 0x08, 0x8E);
  idt_set_gate(6, (u32_t)isr6 , 0x08, 0x8E);
  idt_set_gate(7, (u32_t)isr7 , 0x08, 0x8E);
  idt_set_gate(8, (u32_t)isr8 , 0x08, 0x8E);
  idt_set_gate(9, (u32_t)isr9 , 0x08, 0x8E);
  idt_set_gate(10, (u32_t)isr10 , 0x08, 0x8E);
  idt_set_gate(11, (u32_t)isr11 , 0x08, 0x8E);
  idt_set_gate(12, (u32_t)isr12 , 0x08, 0x8E);
  idt_set_gate(13, (u32_t)isr13 , 0x08, 0x8E);
  idt_set_gate(14, (u32_t)isr14 , 0x08, 0x8E);
  idt_set_gate(15, (u32_t)isr15 , 0x08, 0x8E);
  idt_set_gate(16, (u32_t)isr16 , 0x08, 0x8E);
  idt_set_gate(17, (u32_t)isr17 , 0x08, 0x8E);
  idt_set_gate(18, (u32_t)isr18 , 0x08, 0x8E);
  idt_set_gate(19, (u32_t)isr19 , 0x08, 0x8E);
  idt_set_gate(20, (u32_t)isr20 , 0x08, 0x8E);
  idt_set_gate(21, (u32_t)isr21 , 0x08, 0x8E);
  idt_set_gate(22, (u32_t)isr22 , 0x08, 0x8E);
  idt_set_gate(23, (u32_t)isr23 , 0x08, 0x8E);
  idt_set_gate(24, (u32_t)isr24 , 0x08, 0x8E);
  idt_set_gate(25, (u32_t)isr25 , 0x08, 0x8E);
  idt_set_gate(26, (u32_t)isr26 , 0x08, 0x8E);
  idt_set_gate(27, (u32_t)isr27 , 0x08, 0x8E);
  idt_set_gate(28, (u32_t)isr28 , 0x08, 0x8E);
  idt_set_gate(29, (u32_t)isr29 , 0x08, 0x8E);
  idt_set_gate(30, (u32_t)isr30 , 0x08, 0x8E);
  idt_set_gate(31, (u32_t)isr31 , 0x08, 0x8E);

  idt_flush((u32_t)&ip);
}

