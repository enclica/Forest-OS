#include "../include/util.h"

void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);             //    dest[i] = source[i]
    }
}

void memory_set(uint8 *dest, uint8 val, uint32 len) {
    uint8 *temp = (uint8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {          
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';         
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    /* TODO: implement "reverse" */
    return str;
}
string int_to_string(int n)
{
	string ch = malloc(50);
	int_to_ascii(n,ch);
	int len = strlength(ch);
	int i = 0;
	int j = len - 1;
	while(i<(len/2 + len%2))
	{
		char tmp = ch[i];
		ch[i] = ch[j];
		ch[j] = tmp;
		i++;
		j--;
	}
	return ch;
}
int strncmp( const char * s1, const char * s2, size_t n )
{
    while ( n && *s1 && ( *s1 == *s2 ) )
    {
        ++s1;
        ++s2;
        --n;
    }
    if ( n == 0 )
    {
        return 0;
    }
    else
    {
        return ( *(unsigned char *)s1 - *(unsigned char *)s2 );
    }
}

int str_to_int(string ch)
{
	int n = 0;
	int p = 1;
	int strlen = strlength(ch);
	int i;
	for (i = strlen-1;i>=0;i--)
	{
		n += ((int)(ch[i] - '0')) * p;
		p *= 10;
	}
	return n;
}
void * malloc(int nbytes)
{
	char variable[nbytes];
	return &variable;
}

bool StartsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlength(b)) == 0) return 1;
   return 0;
}


char **split(char *string, const char delimiter) {
    int length = 0, count = 0, i = 0, j = 0;
    while(*(string++)) {
        if (*string == delimiter) count++;
        length++;
    }
    string -= (length + 1); // string was incremented one more than length
    char **array = (char **)malloc(sizeof(char *) * (length + 1));
    char ** base = array;
    for(i = 0; i < (count + 1); i++) {
        j = 0;
        while(string[j] != delimiter) j++;
        j++;
        *array = (char *)malloc(sizeof(char) * j);
        memory_copy(*array, string, (j-1));
        (*array)[j-1] = '\0';
        string += j;
        array++;
    }
    *array = '\0';
    return base;  
}

