#include <types.h>
#include <kernlib.h>
#include <irq.h>
#include <idt.h>

int timer_ticks = 0;

void timer_handler(registers_t regs);

void timer_handler(registers_t regs)
{
  timer_ticks++;
  if (timer_ticks % 180 == 0)
  {
    //printf("got tick %d!\n", timer_ticks);
  }
}


void timer_init(u32_t freq)
{
  register_irq_handler(0, timer_handler);
  u32_t divisor = 1193180 / freq;

  outb(0x43, 0x36);

  u8_t l = (u8_t)(divisor & 0xFF);
  u8_t h = (u8_t)((divisor >> 8) & 0xFF);

  outb(0x40, l);
  outb(0x40, h);
}
