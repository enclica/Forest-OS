#ifndef STRING_H
#define STRING_H

#include "types.h"
uint16 strlength(string ch);

uint8 strEql(string ch1,string ch2);
typedef unsigned long size_t;


void *memset(void *s, int c, size_t n);
int strcmp(const char *s1, const char *s2);
char *strncpy(char *dest, const char *src, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

#endif
