#include "../include/kb.h"
#include "../include/isr.h"
#include "../include/idt.h"
#include "../include/util.h"

void kmain()
{

	print("Launching.........");
	#include "../include/shell.h"
	isr_install();
    
	clearScreen();
	print_colored("forest os.",2,0);
	launch_shell(1);

	
}