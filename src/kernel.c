#include "../include/kb.h"
#include "../include/isr.h"
#include "../include/idt.h"
#include "../include/util.h"
#include "../include/shell.h"

void start(){
		isr_install();

		kmain();

}

void kmain()
{

    
	clearScreen();
	print("Forest OS KERNEL\n");
    	print(">$~\n");
    print("logged in as 'root'\n");
    launch_shell(0);    
}
