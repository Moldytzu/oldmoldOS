#include <utils.h>

int strlen(const char* str) {
    int i;
    for(i = 0;str[i] != 0;i++);
    return i;
}

int strcmp(const char* a, const char* b) {
  const unsigned char *s1 = (const unsigned char *) a;
  const unsigned char *s2 = (const unsigned char *) b;
  unsigned char c1, c2;
  do
    {
      c1 = (unsigned char) *s1++;
      c2 = (unsigned char) *s2++;
      if (c1 == '\0')
        return c1 - c2;
    }
  while (c1 == c2);
  return c1 - c2;
}