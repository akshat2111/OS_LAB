/*********************************************************************************
*
* ASSIGNMENT 1B: Get and Set Environment Variables
* ------------------------------------------------
* Team          : 11
* Date          : 26-July-2025
*
* Member:
* 1. Akshat Verma      (Roll No: 002311001001)
*
***********************************************************************************
*
* Task Details:
* This C program demonstrates how to use the standard system calls
* getenv() and setenv() to access and define environment variables.
* It reads and prints a few common environment variables. Then it
* sets two custom environment variables and verifies their values.
***
* Input:
* The program does not require interactive input or arguments,
* but is written to comply with command-line usage standards.
***
* Output:
* The program first displays the current values of several common
* environment variables such as USER, HOME, etc. It then sets two
* new environment variables — MY_NAME and MY_COURSE — and verifies
* them by reading them back using getenv().
*
***********************************************************************************
*
* COMPILATION:
* gcc -Wall A2_11_1B.c -o A2_11_1B
*
* EXECUTION:
* ./A2_11_1B
*
***********************************************************************************
*
* SAMPLE OUTPUT:
*
* --- Checking default environment variables ---

    USER = be2301
    HOME = /home/usr/student/ug/yr23/be2301
    HOSTNAME = localhost.localdomain
    PATH = /usr/lib64/qt-3.3/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/usr/student/ug/yr23/be2301/.local/bin:/home/usr/student/ug/yr23/be2301/bin
    DISPLAY is not set.
    ARCH is not set.
    PRINTER is not set.

    --- Setting custom environment variables ---

    Environment variables set successfully.

    --- Verifying the new ones ---

    MY_NAME = Akshat Verma
    MY_SUBJECT = Operating Systems Lab

**********************************************************************************/

#include <stdio.h>    // For input/output functions
#include <stdlib.h>   // For getenv() and setenv()


// A simple function to check and print an environment variable
void show_env(const char *var) {
    char *val = getenv(var);
    if (val != NULL) {
        printf("%s = %s\n", var, val);
    } else {
        printf("%s is not set.\n", var);
    }
}

int main() {
    printf("\n--- Checking default environment variables ---\n\n");

    // List of variables to check
    const char *vars[] = {
        "USER", "HOME", "HOSTNAME", "PATH", "DISPLAY", "ARCH", "PRINTER"
    };

    for (int i = 0; i < 7; i++) {
        show_env(vars[i]);
    }

    printf("\n--- Setting custom environment variables ---\n\n");

    // Set a few custom environment variables
    if (setenv("MY_NAME", "Akshat Verma", 1) != 0) {
        perror("Error setting MY_NAME");
    }

    if (setenv("MY_SUBJECT", "Operating Systems Lab", 1) != 0)
    {
        perror("Error setting MY_SUBJECT");
    }

    printf("Environment variables set successfully.\n");

    printf("\n--- Verifying the new ones ---\n\n");
    
    // printing the set variables
    show_env("MY_NAME");
    show_env("MY_SUBJECT");

    printf("\n");

    return 0;
}
