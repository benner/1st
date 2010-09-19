.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31

isr0:
  cli
  push $0
  push $0
  jmp isr_common

isr1:
  cli
  push $0
  push $1
  jmp isr_common

isr2:
  cli
  push $0
  push $2
  jmp isr_common

isr3:
  cli
  push $0
  push $3
  jmp isr_common

isr4:
  cli
  push $0
  push $4
  jmp isr_common

isr5:
  cli
  push $0
  push $5
  jmp isr_common

isr6:
  cli
  push $0
  push $6
  jmp isr_common


isr7:
  cli
  push $0
  push $7
  jmp isr_common


isr8:
  cli
  push $8
  jmp isr_common

isr9:
  cli
  push $0
  push $9
  jmp isr_common


isr10:
  cli
  push $10
  jmp isr_common

isr11:
  cli
  push $11
  jmp isr_common

isr12:
  cli
  push $12
  jmp isr_common

isr13:
  cli
  push $13
  jmp isr_common

isr14:
  cli
  push $14
  jmp isr_common

isr15:
  cli
  push $0
  push $15
  jmp isr_common


isr16:
  cli
  push $0
  push $16
  jmp isr_common

isr17:
  cli
  push $0
  push $17
  jmp isr_common

isr18:
  cli
  push $0
  push $18
  jmp isr_common

isr19:
  cli
  push $0
  push $19
  jmp isr_common

isr20:
  cli
  push $0
  push $20
  jmp isr_common

isr21:
  cli
  push $21
  jmp isr_common

isr22:
  cli
  push $0
  push $22
  jmp isr_common

isr23:
  cli
  push $0
  push $23
  jmp isr_common

isr24:
  cli
  push $0
  push $24
  jmp isr_common


isr25:
  cli
  push $0
  push $25
  jmp isr_common


isr26:
  cli
  push $0
  push $26
  jmp isr_common

isr27:
  cli
  push $0
  push $27
  jmp isr_common

isr28:
  cli
  push $0
  push $28
  jmp isr_common

isr29:
  cli
  push $0
  push $29
  jmp isr_common

isr30:
  cli
  push $0
  push $30
  jmp isr_common

isr31:
  cli
  push $0
  push $31
  jmp isr_common

isr_common:
  pusha
  
  mov %ds, %ax
  push %eax

  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %ss
  mov %ax, %fs
  mov %ax, %gs

  call isr_handler

  pop %eax
  mov %ax, %ds
  mov %ax, %ss
  mov %ax, %fs
  mov %ax, %gs

  popa
  add $0x8, %esp
  sti
  iret

