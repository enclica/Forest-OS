# Compiler and Linker Configuration
CC = gcc
LD = ld
AS = nasm

# Compiler and Linker Flags
CFLAGS = -m32 -c -ffreestanding -Wall
LDFLAGS = -m elf_i386 -T src/link.ld --allow-multiple-definition
ASFLAGS = -f elf32

# Colors
NO_COLOR=\033[0m
OK_COLOR=\033[32;01m
ERROR_COLOR=\033[31;01m
WARN_COLOR=\033[33;01m

# Directories
SRCDIR = src
OBJDIR = obj
OUTDIR = iso
GRUBDIR = $(OUTDIR)/boot/grub

# Output Binary and ISO
OUTPUT = $(OUTDIR)/boot/kernel.bin
ISO = iso.iso

# Source Files
CSOURCES = $(wildcard $(SRCDIR)/*.c)
ASMSOURCES = $(wildcard $(SRCDIR)/*.asm)

# Object Files
COBJECTS = $(CSOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
ASMOBJECTS = $(ASMSOURCES:$(SRCDIR)/%.asm=$(OBJDIR)/%.o)

# Build Targets
all: $(OUTPUT)
	@echo "$(OK_COLOR)Build successful.$(NO_COLOR)"

$(OUTPUT): $(COBJECTS) $(ASMOBJECTS)
	@mkdir -p $(GRUBDIR)
	@echo "$(OK_COLOR)Linking objects...$(NO_COLOR)"
	@$(LD) $(LDFLAGS) -o $@ $^
	@echo "$(OK_COLOR)Kernel binary generated successfully.$(NO_COLOR)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "$(OK_COLOR)Compiling $<...$(NO_COLOR)"
	@$(CC) $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	@mkdir -p $(OBJDIR)
	@echo "$(OK_COLOR)Assembling $<...$(NO_COLOR)"
	@$(AS) $(ASFLAGS) -o $@ $<

# Run the Kernel in QEMU
run: $(ISO)
	@echo "$(OK_COLOR)Running kernel in QEMU...$(NO_COLOR)"
	@qemu-system-i386 -cdrom $(ISO)

# Build ISO Image
build: all
	@echo "Building ISO image..."
	mkdir -p $(GRUBDIR)
	cp Grub/grub.cfg $(GRUBDIR)/grub.cfg
	grub-mkrescue -o $(ISO) $(OUTDIR)
	@echo "ISO image built successfully."

# Clean Up
clean:
	@echo "$(OK_COLOR)Cleaning up...$(NO_COLOR)"
	@rm -rf $(OBJDIR) $(OUTDIR) $(ISO)
	@echo "$(OK_COLOR)Clean up complete.$(NO_COLOR)"

# Help Message
help:
	@echo "Usage: make [all|run|build|clean|help]"
	@echo "  all:    Build the kernel binary"
	@echo "  run:    Run the kernel in QEMU"
	@echo "  build:  Build the ISO image"
	@echo "  clean:  Clean up the build files"
	@echo "  help:   Display this help message"
