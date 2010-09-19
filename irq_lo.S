.macro IRQ source, destination
.global irq\source
irq\source:
  cli
  push $\source
  push $\destination
  jmp irq_common
.endm

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

irq_common:
  pusha
  
  mov %ds, %ax
  push %eax

  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %ss
  mov %ax, %fs
  mov %ax, %gs

  call irq_handler

  pop %eax
  mov %ax, %ds
  mov %ax, %ss
  mov %ax, %fs
  mov %ax, %gs

  popa
  add $0x8, %esp
  sti
  iret
