#ifndef TIMER_H
#define TIMER_H

#include <types.h>
#include <kernlib.h>

void timer_phase(int);
void timer_handler(registers_t);
void timer_init(u32_t);

#endif
