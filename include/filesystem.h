#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdint.h> // For standard integer types

#define MAX_FILES 16
#define MAX_FILE_NAME 32
#define MAX_FILE_SIZE 1024

// File structure
typedef struct {
    char name[MAX_FILE_NAME];
    uint8_t data[MAX_FILE_SIZE];
    uint32_t size;
    uint8_t used;
} file_t;

// Filesystem initialization
void fs_init();

// File operations
int fs_open(const char* filename);
int fs_close(int file_descriptor);
int fs_read(int file_descriptor, char* buf, int nbytes);
int fs_write(int file_descriptor, const char* buf, int nbytes);

#endif // FILESYSTEM_H
