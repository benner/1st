#ifndef KERNLIB_H
#define KERNLIB_H

#include <types.h>

// memory functions
extern void* memcpy(void *, const void *, size_t); 
extern unsigned short *memsetw(unsigned short *, unsigned short, size_t);
extern void *memset(void *, char , size_t );
extern size_t strlen(const char *);

// io functions
extern unsigned char inb (unsigned short);
extern void outb (unsigned short, unsigned char);

// video functions
void init_video(void);
void printf(const char *, ...);
void putchar(int);

#endif
