#ifndef _IRQ_H_
#define _IRQ_H_
#include <types.h>
#include <idt.h>

#define PIC1    (0x20)    /* IO base address for master PIC */
#define PIC2    (0xA0)    /* IO base address for slave PIC */
#define PIC1_COMMAND  PIC1
#define PIC1_DATA (PIC1+1)
#define PIC2_COMMAND  PIC2
#define PIC2_DATA (PIC2+1)

#define PIC_EOI   (0x20)    /* End-of-interrupt command code */

#define IRQ_OFFSET (32)
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void irq_handler(registers_t);
void irq_install(void);
void register_irq_handler(u8_t, isr_t);


#endif
