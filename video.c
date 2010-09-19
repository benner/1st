#include <kernlib.h>

#define TEXT_COL (80)
#define TEXT_ROW (24)

static volatile unsigned short * _text_buffer = (unsigned short *) 0xB8000;
int x_pos, y_pos;
int attrib = 0x0F;


void _video_clear_screen(void); 
void putchar(int); 
void update_cursor(int, int);
void _video_scrool(); 

void update_cursor(int row, int col)
{
unsigned short position=(row*80) + col;

  // cursor LOW port to vga INDEX register
  outb(0x3D4, 0x0F);
  outb(0x3D5, (unsigned char)(position&0xFF));

  // cursor HIGH port to vga INDEX register
  outb(0x3D4, 0x0E);
  outb(0x3D5, (unsigned char )((position>>8)&0xFF));
}

void _video_clear_screen(void) {
  unsigned blank;
  int i;
  
  blank = 0x20 | (attrib << 8);
  for(i = 0; i < 25; i++)
    memsetw ((void *)(_text_buffer + i * 80), blank, 80);
}

void init_video(void) {
  _video_clear_screen();
  x_pos = y_pos = 0;
  update_cursor(y_pos, x_pos);

}

void _video_scrool() {
  unsigned temp, blank;

  blank = 0x20 | (attrib << 8);

  if(y_pos >= 25) {
    temp = y_pos - 25 + 1;
    memcpy((void *)_text_buffer, (void *)(_text_buffer+temp*80), (25-temp)*80*2);
    memsetw ((void *)(_text_buffer + (25 - temp) * 80), blank, 80);
    y_pos = 25 - 1;
  }


}

void putchar(int c) {
  unsigned att = attrib << 8;

  if (c == '\r') return;
  if (c == '\n') {
    x_pos = 0;
    y_pos ++;
  } else {

  *(_text_buffer + y_pos * TEXT_COL + x_pos) = c | att; 

    x_pos++;

    if (x_pos >= TEXT_COL) {
      y_pos ++;
      x_pos = 0;
    }
  }

  _video_scrool(); 
  update_cursor(y_pos, x_pos);
}

/* Convert the integer D to a string and save the string in BUF. If
   BASE is equal to 'd', interpret that D is decimal, and if BASE is
   equal to 'x', interpret that D is hexadecimal.  */
static void
itoa (char *buf, int base, int d)
{
  char *p = buf;
  char *p1, *p2;
  unsigned long ud = d;
  int divisor = 10;

  /* If %d is specified and D is minus, put `-' in the head.  */
  if (base == 'd' && d < 0)
    {
      *p++ = '-';
      buf++;
      ud = -d;
    }
  else if (base == 'x')
    divisor = 16;
  else if (base == 'b')
    divisor = 2;

  /* Divide UD by DIVISOR until UD == 0.  */
  do
    {
      int remainder = ud % divisor;

      *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    }
  while (ud /= divisor);

  /* Terminate BUF.  */
  *p = 0;

  /* Reverse BUF.  */
  p1 = buf;
  p2 = p - 1;
  while (p1 < p2)
    {
      char tmp = *p1;
      *p1 = *p2;
      *p2 = tmp;
      p1++;
      p2--;
    }
}

void printf(const char *format, ...) {
  char **arg = (char **) &format; 
  int c;
  char buf[33]; //32 bits + '\0' 

  arg++;

  while((c = *format++) != '\0') {
    if (c != '%')
      putchar(c);
    else {
      char *p;

      c = *format++;
      switch (c) {
        case 'd':
        case 'u':
        case 'x':
        case 'b':
          itoa(buf, c, *((int *) arg++));
          p = buf;
          goto string;
          break;

        case 's':
          p = *arg++;
          if (!p)
            p = "(NULL)";
string:
        while (*p)
          putchar(*p++);
        break;

      }
    }
  }
}




