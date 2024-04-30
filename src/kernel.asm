bits 32
section .multiboot
align 4
dd 0x1BADB002              ; Multiboot magic number
dd 0x00                    ; Flags
dd - (0x1BADB002 + 0x00)   ; Checksum

section .text
global start
extern kmain               ; The main function of the kernel written in C

start:
    cli                    ; Disable interrupts

    ; Set up the stack before calling C code
    mov esp, stack_space
    mov ebp, 0

    call kmain             ; Call the main kernel function

    ; If kmain returns, halt the CPU
.halt_loop:
    hlt                    ; Halt the CPU
    jmp .halt_loop         ; In case of a wake-up, halt again

section .bss
align 16
stack_space:
    resb 8192              ; Reserve 8KB stack space
