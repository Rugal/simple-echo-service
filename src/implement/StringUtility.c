#include <string.h>
#include "StringUtility.h"

static char seps[] = {'\t', '\n', '\v', '\f', '\r', ' ', '\0'};

char *ltrim(char *str) {
  size_t totrim;
  totrim = strspn(str, seps);
  if (totrim > 0) {
    size_t len = strlen(str);
    if (totrim == len) {
      str[0] = '\0';
    }
    else {
      memmove(str, str + totrim, len + 1 - totrim);
    }
  }
  return str;
}

char *rtrim(char *str) {
  int i;
  i = strlen(str) - 1;
  for (; i >= 0 && strchr(seps, str[i]) != NULL; --i) {
    str[i] = '\0';
  }
  return str;
}

char *trim(char *str) {
  return ltrim(rtrim(str));
}

