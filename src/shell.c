#include "include/shell.h"

void shutdown() {
    print("\nShutting down...\n");
    for (;;);
}

void fill_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        print("Enter number ");
        print(int_to_string(i + 1));
        print(": ");
        arr[i] = str_to_int(readStr());
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        print(int_to_string(arr[i]));
        print(" ");
    }
    print("\n");
}

void echo() {
    print("\n");
    string str = readStr();
    print("\n");
    print(str);
    print("\n");
}

//gcd_couple
int gcd_couple(int a, int b) {
    if (a == 0) {
        return b;
    }
    return gcd_couple(b % a, a);
}
void gcd() {
    print("\nHow many numbers: ");
    int n = str_to_int(readStr());
    int arr[n];
    int matrix[n][n];
    fill_array(arr, n);

    for (int i = 0; i < n; i++) {
        matrix[0][i] = arr[i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            matrix[i][j] = gcd_couple(matrix[i - 1][j], matrix[i - 1][j + 1]);
        }
    }

    print("Result: ");
    print(int_to_string(matrix[n - 1][0]));
    print("\n");
}

void launch_shell(int n) {
    string ch = (string)malloc(200);
    int counter = 0;
    do {
        print("(");
        print(")> ");
        ch = readStr();

        if (strEql(ch, "cmd")) {
            print("\nYou are already in kterm well a new window is added\n");
            launch_shell(n + 1);
        } else if (strEql(ch, "clear")) {
            clearScreen();
        } else if (strEql(ch, "kterm")) {
            print("\n modrick windows open: ");
            print(n);
            print("\n");
        } else if (strEql(ch, "kterm -close")) {
            print("\n modrick closed a kterm");
            launch_shell(n - 1);
        } else if (strEql(ch, "cd")) {
            print("IS BUGGED SO NOPE");
        } else if (strEql(ch, "install")) {
            install();
        } else if (strEql(ch, "dir")) {
            dir();
        } else if (strEql(ch, "sum")) {
            sum();
        } else if (strEql(ch, "cube")) {
            box();
        } else if (strEql(ch, "modrick")) {
          
        } else if (strEql(ch, "exit")) {
            shutdown();
        } else if (strEql(ch, "echo")) {
            echo();
        } else if (strEql(ch, "sort")) {
            sort();
        } else if (strEql(ch, "fibonaci")) {
            fibonaci();
        } else if (strEql(ch, "gcd")) {
            gcd();
        } else if (strEql(ch, "help")) {
            help();
        } else if (strEql(ch, "echo -color")) {
            echocolor();
        } else if (strEql(ch, "color")) {
            set_background_color();
        } else if (strEql(ch, "multiply")) {
            multiply();
        } else {
            print("\n");
            print(ch);
            print(" is a command or file that does not exist\n");
        }
    } while (!strEql(ch, "exit"));
}


void help() {
    print("\nAvailable commands:\n");
    print("cmd - Open a new shell window\n");
    print("clear - Clear the screen\n");
    print("kterm - Display the number of open shell windows\n");
    print("kterm -close - Close a shell window\n");
    print("cd - Change directory (currently bugged)\n");
    print("install - Install a program\n");
    print("dir - List files and directories\n");
    print("sum - Calculate the sum of numbers\n");
    print("cube - Calculate the cube of a number\n");
    print("modrick - Display a special message\n");
    print("exit - Shutdown the system\n");
    print("echo - Read and print a string\n");
    print("sort - Sort an array of numbers\n");
    print("fibonaci - Generate the Fibonacci sequence\n");
    print("gcd - Calculate the greatest common divisor\n");
    print("help - Display this help message\n");
    print("echo -color - Read and print a string with color\n");
    print("color - Change the background color\n");
    print("multiply - Multiply two numbers\n");
    print("\n");
}

void install() {
    print("\nInstalling program...\n");
    // Add installation logic here
    print("Program installed successfully!\n");
}

void dir() {
    print("\nListing files and directories...\n");
    // Add directory listing logic here
    print("Listing complete.\n");
}

void sum() {
    print("\nEnter numbers (separated by spaces): ");
    string input = readStr();
    int sum = 0;
    // Add sum calculation logic here
    print("Sum: ");
    print(int_to_string(sum));
    print("\n");
}

void box() {
    print("\nEnter a number: ");
    int num = str_to_int(readStr());
    int cube = num * num * num;
    print("Cube: ");
    print(int_to_string(cube));
    print("\n");
}

void modrick() {
    print("\n");
    print("  _______ _        _______           _______         \n");
    print(" |__   __| |      |__   __|         |__   __|        \n");
    print("    | |  | |__  _ __ | | __ _  ___     | | ___   ___ \n");
    print("    | |  | '_ \\| '__|| |/ _` |/ _ \\    | |/ _ \\ / _ \\\n");
    print("    | |  | | | | |   | | (_| |  __/    | | (_) |  __/\n");
    print("    |_|  |_| |_|_|   |_|\\__,_|\\___|    |_|\\___/ \\___|\n");
    print("\n");
}

void sort() {
    print("\nEnter numbers (separated by spaces): ");
    string input = readStr();
    // Add sorting logic here
    print("Sorted numbers: ");
    print(input);
    print("\n");
}

void fibonaci() {
    print("\nEnter the number of terms: ");
    int n = str_to_int(readStr());
    // Add Fibonacci sequence generation logic here
    print("Fibonacci sequence: ");
    // Print the generated sequence
    print("\n");
}

void echocolor() {
    print("\nEnter a string: ");
    string str = readStr();
    // Add colored printing logic here
    print("\n");
}

void set_background_color() {
    print("\nEnter a color code (e.g., #FF0000 for red): ");
    string color = readStr();
    // Add background color setting logic here
    print("\n");
}

void multiply() {
    print("\nEnter two numbers (separated by a space): ");
    string input = readStr();
    // Parse the input and multiply the numbers
    print("Product: ");
    // Print the product
    print("\n");
}