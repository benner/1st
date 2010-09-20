CFLAGS=-m32 -g -fno-stack-protector -I. -Wall -Wmissing-prototypes -Wunused -Wshadow -Wpointer-arith -falign-jumps=1 -falign-loops=1 -falign-functions=1 -Wundef -fno-builtin -nostdinc -O -Werror 
ASFLAGS=-m32 -g -fno-stack-protector -I. -Wall -Wmissing-prototypes -Wunused -Wshadow -Wpointer-arith -falign-jumps=1 -falign-loops=1 -falign-functions=1 -Wundef -Werror 
LDFLAGS=-m32 -melf_i386 -T linker.ld -g 
CC=gcc
LD=ld
SRCS=boot.o ports.o memutils.o video.o gdt.o idt_lo.o idt.o irq_lo.o irq.o timer.o keyboard.o paging.o k_main.o
CTAGS=ctags -x >tags
LODEV=$(shell sudo losetup -f)

all: kernel 

tags:   $(SRCS)
	      ${CTAGS} $(SRCS)

kernel: $(SRCS) 
				$(LD) $(LDFLAGS) $(SRCS) -o $@

mount:
	sudo losetup -o 32256 $(LODEV) ../c.img
	sudo mount $(LODEV) /mnt
	
install: kernel
	rm -f /mnt/boot/kernel
	cp kernel /mnt/boot/kernel
	sync

test: install
	echo $(LODEV)
	bochs

test_q: kernel
	qemu ../c.img

clean:
	rm -f *.o *~ core kernel tags
