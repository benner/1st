#include <irq.h>
#include <kernlib.h>
#include <timer.h>

isr_t interrupt_handlers[256];


void irq_handler(registers_t regs)
{
if (regs.int_no >= 40)
{
  // Send reset signal to slave.
  outb(PIC2_COMMAND, PIC_EOI);
}
  // Send reset signal to master. (As well as slave, if necessary).
  outb(PIC1_COMMAND, PIC_EOI);

  if (interrupt_handlers[regs.int_no] != 0)
  {
    isr_t handler = interrupt_handlers[regs.int_no];
    handler(regs);
  } else {
    printf("IRQ %u received\n", regs.int_no-32);
  }
} 

void irq_install(void) {
  outb(PIC1_COMMAND, 0x11);
  outb(PIC2_COMMAND, 0x11);

  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x0);
  outb(0xA1, 0x0);

  idt_set_gate(32, (u32_t)irq0, 0x08, 0x8E);
  idt_set_gate(33, (u32_t)irq1, 0x08, 0x8E);
  idt_set_gate(34, (u32_t)irq2, 0x08, 0x8E);
  idt_set_gate(35, (u32_t)irq3, 0x08, 0x8E);
  idt_set_gate(36, (u32_t)irq4, 0x08, 0x8E);
  idt_set_gate(37, (u32_t)irq5, 0x08, 0x8E);
  idt_set_gate(38, (u32_t)irq6, 0x08, 0x8E);
  idt_set_gate(39, (u32_t)irq7, 0x08, 0x8E);
  idt_set_gate(40, (u32_t)irq8, 0x08, 0x8E);
  idt_set_gate(41, (u32_t)irq9, 0x08, 0x8E);
  idt_set_gate(42, (u32_t)irq10, 0x08, 0x8E);
  idt_set_gate(43, (u32_t)irq11, 0x08, 0x8E);
  idt_set_gate(44, (u32_t)irq12, 0x08, 0x8E);
  idt_set_gate(45, (u32_t)irq13, 0x08, 0x8E);
  idt_set_gate(46, (u32_t)irq14, 0x08, 0x8E);
  idt_set_gate(47, (u32_t)irq15, 0x08, 0x8E);

}

void register_irq_handler(u8_t irq_nr, isr_t handler)
{
  interrupt_handlers[irq_nr + IRQ_OFFSET] = handler;
}


//  register_irq_handler(0, timer_handler);
