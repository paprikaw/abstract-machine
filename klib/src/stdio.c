#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

void IntegertoString(char *string, int number);
int printf(const char *fmt, ...)
{
  char str_buf[128];
  va_list ap;
  int d;
  char c;
  char *s;

  va_start(ap, fmt);
  while (*fmt)
  {
    if (*fmt == '%')
    {
      switch (*(++fmt))
      {
      case 's': /* string */
        s = va_arg(ap, char *);
        putstr(s);
        break;
      case 'd': /* int */
        d = va_arg(ap, int);
        IntegertoString(str_buf, d);
        putstr(str_buf);
        break;
      case 'c': /* char */
        /* need a cast here since va_arg only
           takes fully promoted types */
        c = (char)va_arg(ap, int);
        putch(c);
        break;
      default:
        panic("printf: format is wrong");
      }
    }
    else
    {
      putch(*fmt);
    }
    fmt++;
  }
  putch('\0');
  va_end(ap);
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap)
{
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...)
{
  panic("Not implemented");
}

int snprintf(char *out, size_t n, const char *fmt, ...)
{
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap)
{
  panic("Not implemented");
}

// https://stackoverflow.com/a/29728839/13739428
void IntegertoString(char *string, int number)
{

  if (number == 0)
  {
    string[0] = '0';
    return;
  };
  int divide = 0;
  int modResult;
  int length = 0;
  int isNegative = 0;
  int copyOfNumber;
  copyOfNumber = number;
  if (number < 0)
  {
    isNegative = 1;
    number = 0 - number;
    length++;
  }
  while (copyOfNumber != 0)
  {
    length++;
    copyOfNumber /= 10;
  }

  for (divide = 0; divide < length; divide++)
  {
    modResult = number % 10;
    number = number / 10;
    string[length - (divide + 1)] = modResult + '0';
  }
  if (isNegative)
  {
    string[0] = '-';
  }
  string[length] = '\0';
}
#endif