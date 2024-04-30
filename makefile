


# Compiler
COMPILER = gcc

# Directories
SRCDIR = src
OBJDIR = obj
OUTDIR = iso
OUTPUT = $(OUTDIR)/kernel.bin
LOGDIR = logs

# Linker, Assembler, Compiler, and Emulator
LINKER = ld
ASSEMBLER = nasm
CFLAGS = -Wall -m32 -c -I include -fno-stack-protector --verbose
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T $(SRCDIR)/link.ld --allow-multiple-definition
EMULATOR = qemu-system-i386
EMULATOR_FLAGS = -kernel

# Color settings for logs
NO_COLOR=\033[0m
OK_COLOR=\033[32;01m
ERROR_COLOR=\033[31;01m
WARN_COLOR=\033[33;01m

# Echo colored messages
ECHO_OK=@echo "$(OK_COLOR)"
ECHO_ERROR=@echo "$(ERROR_COLOR)"
ECHO_WARN=@echo "$(WARN_COLOR)"
ECHO_NO_COLOR=@echo "$(NO_COLOR)"

# Source and Object Files
CSOURCES = $(wildcard $(SRCDIR)/*.c)
ASMSOURCES = $(wildcard $(SRCDIR)/*.asm)
COBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CSOURCES))
ASMOBJECTS = $(patsubst $(SRCDIR)/%.asm, $(OBJDIR)/%.o, $(ASMSOURCES))
OBJS = $(COBJECTS) $(ASMOBJECTS)


all: $(OUTPUT)
	$(ECHO_OK) "Build complete.$(NO_COLOR)"


# Default Target
# Linking the Kernel Binary
$(OUTPUT): $(OBJS)
	@echo "$(OK_COLOR)Linking kernel binary...$(NO_COLOR)"
	mkdir -p $(OUTDIR)
	@{ $(LINKER) $(LDFLAGS) -o $@ $^ 2>&1; ec=$$?; } | tee $(LOGDIR)/linking.log | \
	awk 'BEGIN { red = "\033[31;01m"; yellow = "\033[33;01m"; nc = "\033[0m" } \
	/error: undefined reference/ { print red "Undefined reference: " $$0 nc; next } \
	/error/ { print red $$0 nc; next } \
	/warning/ { print yellow $$0 nc; next } \
	{ print } END { if (ec != 0) exit ec }'
	




# Compiling C Sources
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "$(OK_COLOR)Compiling $<...$(NO_COLOR)"
	mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) -o $@ $< > $(LOGDIR)/compile_$*.log 2>&1
	

# Assembling ASM Sources
$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	@echo "$(OK_COLOR)Assembling $<...$(NO_COLOR)"
	mkdir -p $(OBJDIR)
	$(ASSEMBLER) $(ASFLAGS) -o $@ $< > $(LOGDIR)/assemble_$*.log 2>&1
	


# Run the Emulator
run: $(OUTPUT)
	@echo "$(OK_COLOR)Running emulator...$(NO_COLOR)"
	$(EMULATOR) $(EMULATOR_FLAGS) $<
	@echo "$(OK_COLOR)Emulator started.$(NO_COLOR)"

open_iso:
	@echo "$(OK_COLOR)Opening ISO file...$(NO_COLOR)"
	$(EMULATOR) -cdrom Forest.iso
	@echo "$(OK_COLOR)ISO file opened.$(NO_COLOR)"


# Clean up Objects and Output Directories
clean:
	@echo "$(WARN_COLOR)Cleaning up...$(NO_COLOR)"
	rm -rf $(OBJDIR)/*.o $(OUTDIR)/*.* $(LOGDIR)/*.* Forest.iso
	@echo "$(OK_COLOR)Clean complete.$(NO_COLOR)"

# ISO and GRUB Configuration
build: all
	@echo "$(OK_COLOR)Building ISO image...$(NO_COLOR)"
	mkdir -p $(OUTDIR)/users/root
	mkdir -p $(OUTDIR)/grub
	
	# copy grub config from Grub to Forest/boot/grub
	cp Grub/* $(OUTDIR)/grub/*.*
	grub-mkrescue -o Forest.iso $(OUTDIR)
	@echo "$(OK_COLOR)ISO image built successfully.$(NO_COLOR)"


make_and_build: all build

clean_and_build: clean all build





# Help
help:
	@echo "Makefile for compiling and running a simple OS kernel"
	@echo "Targets:"
	@echo "  all: Builds the kernel binary"
	@echo "  run: Runs the kernel in QEMU"
	@echo "  open_iso: Opens the ISO file in QEMU"
	@echo "  clean: Removes all generated files"
	@echo "  build: Creates a bootable ISO image"#
	@echo "  make_and_build: Builds the kernel and creates a bootable ISO image"
	@echo "  clean_and_build: Cleans up and builds the kernel and creates a bootable ISO image"
	@echo "  help: Displays this help message"

