#include "io_ports.h" // Assumed header file for port I/O functions

#define MOUSE_IRQ 12
#define MOUSE_PORT 0x60
#define MOUSE_STATUS_PORT 0x64
#define MOUSE_CMD_PORT 0x64

// Commands for the mouse
#define ENABLE_MOUSE 0xA8
#define SET_DEFAULTS 0xF6
#define ENABLE_PACKET_STREAMING 0xF4

// Mouse packet size
#define MOUSE_PACKET_SIZE 3

unsigned char mouse_cycle = 0;   // Keeps track of the byte number in the packet
char mouse_byte[3];              // Buffer to store bytes from mouse packet

void mouse_wait(unsigned char type) {
    unsigned int _time_out = 100000; // Arbitrary timeout value
    if (type == 0) {
        while (--_time_out) {
            if ((inportb(MOUSE_STATUS_PORT) & 1) == 1) {
                return;
            }
        }
        return;
    } else {
        while (--_time_out) {
            if ((inportb(MOUSE_STATUS_PORT) & 2) == 0) {
                return;
            }
        }
        return;
    }
}

void mouse_write(unsigned char data) {
    // Wait to be able to send a command
    mouse_wait(1);
    // Tell the mouse we are sending a command
    outportb(MOUSE_CMD_PORT, 0xD4);
    // Wait for the final part
    mouse_wait(1);
    // Finally write
    outportb(MOUSE_PORT, data);
}

unsigned char mouse_read() {
    // Get's response from mouse
    mouse_wait(0);
    return inportb(MOUSE_PORT);
}

void mouse_handler() {
    switch (mouse_cycle) {
        case 0:
            mouse_byte[0] = mouse_read();
            mouse_cycle++;
            break;
        case 1:
            mouse_byte[1] = mouse_read();
            mouse_cycle++;
            break;
        case 2:
            mouse_byte[2] = mouse_read();
            // We now have a full mouse packet ready to process
            process_mouse_packet();
            mouse_cycle = 0;
            break;
    }
}

void process_mouse_packet() {
    // Implement your logic to handle each packet here
    // This function can handle mouse position updates, button presses, etc.
}

void init_mouse() {
    // Enable the auxiliary mouse device
    mouse_wait(1);
    outportb(MOUSE_CMD_PORT, ENABLE_MOUSE);
    
    // Set default settings
    mouse_write(SET_DEFAULTS);
    mouse_read();  // Acknowledge
    
    // Enable packet streaming
    mouse_write(ENABLE_PACKET_STREAMING);
    mouse_read();  // Acknowledge

    // Set up the mouse handler as an interrupt service routine
   
}

