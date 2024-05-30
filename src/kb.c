#include "include/kb.h"
#include "include/isr.h"


// Define necessary types
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned long size_t;



// Define a mapping from scan codes to characters
static const char keymap[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', // 0-15
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', // 16-31
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', // 32-47
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, // 48-63
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', // 64-79
    '2', '3', '0', '.' // 80-87
};

// Read a string from the keyboard
string readStr() {
    string buffstr = (string)malloc(200);
    uint8_t i = 0;
    uint8_t reading = 1;

    while (reading) {
        if (inportb(0x64) & 0x1) {
            uint8_t scancode = inportb(0x60);
            char ch = keymap[scancode];

            if (ch != 0) {
                printch(ch);
                buffstr[i] = ch;
                i++;
            } else {
                // Handle special cases, such as backspace
                switch (scancode) {
                    case 0x0E: // Backspace
                        if (i > 0) {
                            printch('\b');
                            i--;
                        }
                        break;
                    case 0x1C: // Enter
                        printch('\n');
                        buffstr[i] = '\0'; // Null-terminate the string
                        reading = 0;
                        break;
                    case 0x2A: // Left shift pressed
                        case 0x36: // Right shift pressed
                                break;
                    default:
                                break;

                }
            }
        }
    }
    return buffstr;
}
