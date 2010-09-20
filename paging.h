#ifndef _PAGING_H_
#define _PAGING_H_
#include <types.h>
#include <idt.h>

typedef struct page
{
   u32_t present    : 1;   // Page present in memory
   u32_t rw         : 1;   // Read-only if clear, readwrite if set
   u32_t user       : 1;   // Supervisor level only if clear
   u32_t accessed   : 1;   // Has the page been accessed since last refresh?
   u32_t dirty      : 1;   // Has the page been written to since last refresh?
   u32_t unused     : 7;   // Amalgamation of unused and reserved bits
   u32_t frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
   page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
   /**
      Array of pointers to pagetables.
   **/
   page_table_t *tables[1024];
   /**
      Array of pointers to the pagetables above, but gives their *physical*
      location, for loading into the CR3 register.
   **/
   u32_t tablesPhysical[1024];
   /**
      The physical address of tablesPhysical. This comes into play
      when we get our kernel heap allocated and the directory
      may be in a different location in virtual memory.
   **/
   u32_t physicalAddr;
} page_directory_t;




void page_fault(registers_t regs);
void swich_page_directory(page_directory_t *);
void get_page(void);
void init_paging(void);

#endif
