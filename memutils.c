#include <kernlib.h>

void *memcpy(void *dest, const void *src, size_t n) {
   const char *sp = (const char *)src;
   char *dp = (char *)dest;
   for(; n != 0; n--) *dp++ = *sp++;
    return dest;

 return dest;
}

void *memset(void *dest, char val, size_t count)
{
  char *temp = (char *)dest;
  for( ; count != 0; count--) *temp++ = val;
  return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
  unsigned short *temp = (unsigned short *)dest;
  for( ; count != 0; count--) *temp++ = val;
  return dest;
}

size_t strlen(const char *str)
{
  size_t retval;
  for(retval = 0; *str != '\0'; str++) retval++;
  return retval;
}

