#include <multiboot.h>
#include <kernlib.h>
#include <gdt.h>
#include <idt.h>
#include <timer.h>
#include <keyboard.h>

/* Check if the bit BIT in FLAGS is set.  */
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

void k_main (unsigned long, unsigned long);

inline void enable_interrupts(void); 
inline void disable_interrupts(void); 
inline void cpu_halt(void); 

inline void enable_interrupts() {
__asm__ __volatile__ ("sti");
}

inline void disable_interrupts() {
__asm__ __volatile__ ("cli");
}

inline void cpu_halt() {
  printf("\n\t\t\tHALTED\n");
  disable_interrupts();
  for(;;);
}


void
k_main (unsigned long magic, unsigned long addr)
{
  multiboot_info_t *mbi;

  init_video();
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
  {
    printf ("Invalid magic number: 0x%x\n", (unsigned) magic);
    cpu_halt();
  }

  printf("Booting...\n");

  /* Set MBI to the address of the Multiboot information structure.  */
  mbi = (multiboot_info_t *) addr;

  /* Print out the flags.  */
  printf ("flags = 0x%x (b%b)\n", (unsigned) mbi->flags, (unsigned) mbi->flags);

  /* Are mem_* valid?  */
  if (CHECK_FLAG (mbi->flags, 0))
    printf ("mem_lower = %uKB, mem_upper = %uKB\n",
	    (unsigned) mbi->mem_lower, (unsigned) mbi->mem_upper);

  /* Is boot_device valid?  */
  if (CHECK_FLAG (mbi->flags, 1))
    printf ("boot_device = 0x%x\n", (unsigned) mbi->boot_device);
  
  /* Is the command line passed?  */
  if (CHECK_FLAG (mbi->flags, 2))
    printf ("cmdline = %s\n", (char *) mbi->cmdline);

  /* Are mods_* valid?  */
  if (CHECK_FLAG (mbi->flags, 3))
    {
      module_t *mod;
      int i;
      
      printf ("mods_count = %d, mods_addr = 0x%x\n",
	      (int) mbi->mods_count, (int) mbi->mods_addr);
      for (i = 0, mod = (module_t *) mbi->mods_addr;
	   i < mbi->mods_count;
	   i++, mod++)
	printf (" mod_start = 0x%x, mod_end = 0x%x, string = %s\n",
		(unsigned) mod->mod_start,
		(unsigned) mod->mod_end,
		(char *) mod->string);
    }

  /* Bits 4 and 5 are mutually exclusive!  */
  if (CHECK_FLAG (mbi->flags, 4) && CHECK_FLAG (mbi->flags, 5))
    {
      printf ("Both bits 4 and 5 are set.\n");
      return;
    }

  /* Is the symbol table of a.out valid?  */
  if (CHECK_FLAG (mbi->flags, 4))
    {
      aout_symbol_table_t *aout_sym = &(mbi->u.aout_sym);
      
      printf ("aout_symbol_table: tabsize = 0x%0x, "
	      "strsize = 0x%x, addr = 0x%x\n",
	      (unsigned) aout_sym->tabsize,
	      (unsigned) aout_sym->strsize,
	      (unsigned) aout_sym->addr);
    }

  /* Is the section header table of ELF valid?  */
  if (CHECK_FLAG (mbi->flags, 5))
    {
      elf_section_header_table_t *elf_sec = &(mbi->u.elf_sec);

      printf ("elf_sec: num = %u, size = 0x%x,"
	      " addr = 0x%x, shndx = 0x%x\n",
	      (unsigned) elf_sec->num, (unsigned) elf_sec->size,
	      (unsigned) elf_sec->addr, (unsigned) elf_sec->shndx);
    }

  /* Are mmap_* valid?  */
  if (CHECK_FLAG (mbi->flags, 6))
    {
      memory_map_t *mmap;
      
      printf ("mmap_addr = 0x%x, mmap_length = 0x%x\n",
	      (unsigned) mbi->mmap_addr, (unsigned) mbi->mmap_length);
      for (mmap = (memory_map_t *) mbi->mmap_addr;
	   (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
	   mmap = (memory_map_t *) ((unsigned long) mmap
				    + mmap->size + sizeof (mmap->size)))
      {
	      printf (" size=0x%x, base_addr=0x%x%x (%d KB),"
		      " length=0x%x%x (%d KB), type=0x%x",
		      (unsigned) mmap->size,
		      (unsigned) mmap->base_addr_high,
		      (unsigned) mmap->base_addr_low,
		      (unsigned) mmap->base_addr_low >> 10,
		      (unsigned) mmap->length_high,
		      (unsigned) mmap->length_low,
		      (unsigned) mmap->length_low >> 10,
		      (unsigned) mmap->type);
        if (mmap->type == 0x1)
          printf(" (free)\n");
        else printf("\n");
      }
    }


  printf("Starting initalization...\n");

  gdt_install();
  printf("gdt installed\n");

  idt_install();
  printf("idt installed\n");

  irq_install();
  printf("irq installed\n");

  timer_init(400);
  printf("temer installed\n");

  register_irq_handler(1, keyboard_handler);

  printf("enabling innterrupts... ");
  enable_interrupts();
  printf(" ENABLED\n");

  for(;;);
}

