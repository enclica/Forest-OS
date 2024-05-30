#include "include/filesystem.h"
#include <string.h> // For memory and string operations
#include <stdint.h> // For standard integer types

// File array to store files
static file_t file_table[MAX_FILES];

// Initialize the filesystem
void fs_init() {
    memset(file_table, 0, sizeof(file_table));
}

// Open a file
int fs_open(const char* filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (file_table[i].used && strcmp(file_table[i].name, filename) == 0) {
            return i;  // File is already open
        }
    }

    for (int i = 0; i < MAX_FILES; i++) {
        if (!file_table[i].used) {
            // Found a free file slot
            strncpy(file_table[i].name, filename, MAX_FILE_NAME);
            file_table[i].name[MAX_FILE_NAME - 1] = '\0';  // Ensure null termination
            file_table[i].size = 0;
            file_table[i].used = 1;
            return i;
        }
    }

    return -1;  // No free file slots or file not found
}

// Close a file
int fs_close(int file_descriptor) {
    if (file_descriptor >= 0 && file_descriptor < MAX_FILES && file_table[file_descriptor].used) {
        file_table[file_descriptor].used = 0;
        return 0;
    }
    return -1;
}

// Read from a file
int fs_read(int file_descriptor, char* buf, int nbytes) {
    if (file_descriptor < 0 || file_descriptor >= MAX_FILES || !file_table[file_descriptor].used)
        return -1;

    if (nbytes > file_table[file_descriptor].size)
        nbytes = file_table[file_descriptor].size;

    memcpy(buf, file_table[file_descriptor].data, nbytes);
    return nbytes;
}

// Write to a file
int fs_write(int file_descriptor, const char* buf, int nbytes) {
    if (file_descriptor < 0 || file_descriptor >= MAX_FILES || !file_table[file_descriptor].used)
        return -1;

    if (nbytes > MAX_FILE_SIZE)
        nbytes = MAX_FILE_SIZE;

    memcpy(file_table[file_descriptor].data, buf, nbytes);
    file_table[file_descriptor].size = nbytes;
    return nbytes;
}
