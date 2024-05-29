#include "../include/screen.h"
int cursorX = 0, cursorY = 0;
const uint8 sw = 80,sh = 25,sd = 2; 
int color = 0x0F;
void clearLine(uint8 from,uint8 to)
{
        uint16 i = sw * from * sd;
        string vidmem=(string)0xb8000;
        for(i;i<(sw*to*sd);i++)
        {
                vidmem[(i / 2)*2 + 1 ] = color ;
                vidmem[(i / 2)*2 ] = 0;
        }
}
void updateCursor()
{
    unsigned temp;

    temp = cursorY * sw + cursorX-1;                                                      

    outportb(0x3D4, 14);                                                                
    outportb(0x3D5, temp >> 8);                                                         
    outportb(0x3D4, 15);                                                               
    outportb(0x3D5, temp);                                                             
}
void clearScreen()
{
        clearLine(0,sh-1);
        cursorX = 0;
        cursorY = 0;
        updateCursor();
}

void scrollUp(uint8 lineNumber)
{
        string vidmem = (string)0xb8000;
        uint16 i = 0;
        clearLine(0,lineNumber-1);                                            //updated
        for (i;i<sw*(sh-1)*2;i++)
        {
                vidmem[i] = vidmem[i+sw*2*lineNumber];
        }
        clearLine(sh-1-lineNumber,sh-1);
        if((cursorY - lineNumber) < 0 ) 
        {
                cursorY = 0;
                cursorX = 0;
        } 
        else 
        {
                cursorY -= lineNumber;
        }
        updateCursor();
}


void newLineCheck()
{
        if(cursorY >=sh-1)
        {
                scrollUp(1);
        }
}

void printch(char c)
{
    string vidmem = (string) 0xb8000;     
    switch(c)
    {
        case (0x08):
                if(cursorX > 0) 
                {
	                cursorX--;									
                        vidmem[(cursorY * sw + cursorX)*sd]=0;	     //(0xF0 & color)                          
	        }
	        break;
       case (0x09):
                cursorX = (cursorX + 8) & ~(8 - 1); 
                break;
        case ('\r'):
                cursorX = 0;
                break;
        case ('\n'):
                cursorX = 0;
                cursorY++;
                break;
        default:
                vidmem [((cursorY * sw + cursorX))*sd] = c;
                vidmem [((cursorY * sw + cursorX))*sd+1] = color;
                cursorX++; 
                break;
	
    }
    if(cursorX >= sw)                                                                   
    {
        cursorX = 0;                                                                
        cursorY++;                                                                    
    }
    updateCursor();
    newLineCheck();
}

void print (string ch)
{
        uint16 i = 0;
        uint8 length = strlength(ch);              
        for(i;i<length;i++)
        {
                printch(ch[i]);
        }
     
        
}
void set_screen_color(int text_color,int bg_color)
{
	color =  (bg_color << 4) | text_color;;
}
void set_screen_color_from_color_code(int color_code)
{
	color = color_code;
}
void print_colored(string ch,int text_color,int bg_color)
{
	int current_color = color;
	set_screen_color(text_color,bg_color);
	print(ch);
	set_screen_color_from_color_code(current_color);
}
