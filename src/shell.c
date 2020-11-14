#include "../include/shell.h"
	string kernel = (string )"Alder";
	string errorcode = (string) "0xFFFFFF";
	string countinue = (string) "yes";
	string whoami = (string) "root";
	int counter = 0;
	int critical = 0;
	int loggedin = 0;
	
void launch_shell(int n)
{
	int counter = 0;
	string ch = (string) malloc(200); // util.h
	if(countinue == "no"){return;}
	do
{
			if(countinue == "no"){return;}
		print_colored("\nforest>",9,0);
	
		    ch = readStr(); 
		    if(StartsWith(ch,"shell"))
		    {
		            print("\nYou are allready in cmd. A new recursive shell is opened\n");
					launch_shell(n+1);
			}else if(StartsWith(ch,"whoami"))
		    {
		            printl(whoami);
		    }else if(StartsWith(ch,"about"))
		    {
		            printl("F O R E S T  O S");
					print("Kernel version: ");print(kernel);print("\n");
					print("Who am i: \n");print(whoami);


		    }else if(StartsWith(ch,"crash"))
		    {
		           
				   crash();
				  
		    }else{
				print("Not a command.");
			}
	} while (!strEql(ch,"exit"));
}

void crash(){
	countinue = "no";
	set_screen_color(15,13);
	clearScreen();
	if(kernel == "") {print_colored("CRITICAL: NO KERNEL TYPE FOUND UNSTABLE STATE.\n",12,4);}
	print("Forest os " ); print(kernel); print( errorcode);
	print("\nForest OS has created an unstable state and must be shutdown to protect your system.\n");	
}