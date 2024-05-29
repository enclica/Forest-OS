#include "../include/system.h"
#include "../include/string.h"
uint8 inportb (uint16 _port)
{
    	uint8 rv;
    	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    	return rv;
}

void outportb (uint16 _port, uint8 _data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void *memset(void *s, int c, size_t n) {
    unsigned char* p = s;
    while (n--) *p++ = (unsigned char)c;
    return s;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++, s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char *strncpy(char *dest, const char *src, size_t n) {
    char *ret = dest;
    do {
        if (!n--) return ret;
    } while ((*dest++ = *src++));
    while (n--) *dest++ = 0;
    return ret;
}

void *memcpy(void *dest, const void *src, size_t n) {
    char *dp = dest;
    const char *sp = src;
    while (n--) *dp++ = *sp++;
    return dest;
}