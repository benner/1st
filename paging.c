#include <types.h>
#include <kernlib.h>
#include <paging.h>

void page_fault(registers_t regs);
void init_paging(void);
void swich_page_directory(page_directory_t *);
void get_page(void);


void page_fault(registers_t regs)
{
  u32_t faulting_address;
  asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

  int present   = !(regs.err_code & 0x1);
  int rw = regs.err_code & 0x2;
  int us = regs.err_code & 0x4;
  int reserved = regs.err_code & 0x8;
  int id = regs.err_code & 0x10;

  printf("Got page fault! ( ");

  if (present) { printf("present "); }
  if (rw) { printf("read-only "); }
  if (us) { printf("user-mode "); }
  if (reserved) { printf("reserved "); }
  
  printf(" id=%d) @ 0x %X\n", id, faulting_address);
  for(;;); //panic

}

void init_paging()
{
}

void swich_page_directory(page_directory_t *new)
{
}

void get_page()
{
}

