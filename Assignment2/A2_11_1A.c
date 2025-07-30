/*********************************************************************************
*
* ASSIGNMENT 2A: Signal Handling (SIGINT)
* ----------------------------------------
* Team          : 11
* Date          : 29-July-2025
*
* Member:
* 1. Akshat Verma      (Roll No: 002311001001)
*
***********************************************************************************
*
* Assignment DESCRIPTION:
* Catch the signal ‘SIGINT’ and display “Ha Ha, Not Stopping”. Use
*‘signal’ system call. Always use “perror” to check the return status of
* a library/system call.
* 
* Program DESCRIPTION:
* This C program demonstrates signal handling using the signal system call.
* It catches the interrupt signal SIGINT (usually sent by Ctrl+C) and instead
* of terminating, it prints "Ha Ha, Not Stopping" to the terminal.
*
***
* Input:
* No input required.
***
* Output:
* After successfully executing the program when pressed ctrl+c it prints "Ha Ha Not Stopping".
* To terminate the program, open another terminal and type command kill -TERM <pid>.
*
***********************************************************************************
*
* COMPILATION:
* gcc -Wall A2_11_2A.c -o A2_11_2A
*
* EXECUTION SEQUENCE:
* ./A2_11_2A
* (Then press Ctrl+C to test SIGINT behavior)
*
***********************************************************************************
*
* SAMPLE OUTPUT:
* --------output-------
* wasting cycles.. 32
* wasting cycles.. 32
* Ha Ha Not Stopping!...
* wasting cycles.. 32
* ---------------------
**********************************************************************************/

#include <stdio.h>     // For printf 
#include <unistd.h>    // For write() and sleep() system calls
#include <signal.h>    // For signal() and SIGINT handling
#include <string.h>    // For strlen() to calculate message length
#include <stdlib.h>    // For exit() and EXIT_FAILURE

// Signal handler function to catch SIGINT (Ctrl+C)
void handler(int sig) {
    (void)sig;  // Mark 'sig' as unused to avoid compiler warnings

    const char* msg = "Ha Ha Not Stopping!...\n";
    // Using write() instead of printf() because it's async-signal-safe
    // Write the message directly to standard output (terminal)
    write(STDOUT_FILENO, msg, strlen(msg));
}

int main() {
    // Register the signal handler for SIGINT (Ctrl+C)
    // If registration fails, signal() returns SIG_ERR
    if (signal(SIGINT, handler) == SIG_ERR) {
        perror("Error registering signal handler"); // Print error message
        exit(EXIT_FAILURE); // Exit with failure status
    }

    // Infinite loop to simulate a running process
    while (1) {
        printf("wasting cycles.. %d\n", getpid()); // Show some output to indicate process is running
        sleep(2); // Sleep for 2 seconds between prints
    }

    return 0; // Unreachable, but good practice to include
}

