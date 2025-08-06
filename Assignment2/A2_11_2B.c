/********************************************************************************
* ASSIGNMENT 2B: IPC Using FIFO and fork()
* --------------------------------------------------
* Team          : 11
* Date          : 8-Aug-2025
*
* Members:
* 1. Akshat Verma     | (Roll No: 002311001001)
* 2. Persis Azem Sada | (Roll No: 002311001078)
*
*********************************************************************************
* Assignment Discription: 
* Using the fork system call, create a Child Process.. Transfer 1GB file
* from the Parent Process to Child Process using a FIFO. Now, transfer
* the same file from the Child Process to the Parent Process using
* another FIFO. Now, compare the two files(use cmp or diff command)
* to make sure that the same file has returned back. Also, print the time
* required to do this double transfer. Attach this output to the source file
* as a comment.
*
* Program Description:
* This program demonstrates Inter-Process Communication using Named Pipes (FIFOs).
* - A 1GB file is transferred from Parent → Child via FIFO1
* - Then the same file is sent back from Child → Parent via FIFO2
* - The program records the time taken for the full round-trip
* - It uses the `cmp` command to verify the file’s integrity
*
*
* COMPILATION: 
*
* gcc A2_11_2B.c -o A2_11_2B
*
* EXECUTION:
*
* Pre-Execution Setup:
* $1. dd if=/dev/urandom of=original_file.bin bs=1M count=1024  //(To create a 1Gb file)
* $2. ./A2_11_2B
* Post-Execution:
* $3. ls -l original_file.bin returned_file.bin child_received.bin fifo_parent_to_chil
d fifo_child_to_parent 
* (Output pasted below)
*
* Sample ls -l Output:
* -----------------------------------------------
* -rw-r--r-- 1 akubu akubu 380870656 Aug  6 16:02 child_received.bin
* prw-r--r-- 1 akubu akubu         0 Aug  6 16:03 fifo_child_to_parent
* prw-r--r-- 1 akubu akubu         0 Aug  6 16:02 fifo_parent_to_child
* -rw-r--r-- 1 akubu akubu 380870656 Aug  6 16:02 original_file.bin
* -rw-r--r-- 1 akubu akubu 380870656 Aug  6 16:03 returned_file.bin
* -----------------------------------------------
* Sample Program Output:
* -----------------------------------------------
* Double transfer completed in 4.32 seconds.
* Success: Files are identical.
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define BUF_SIZE 4096

int safe_open(const char *path, int flags, mode_t mode) {
    int fd = open(path, flags, mode);
    if (fd == -1) {
        perror(path);
        exit(EXIT_FAILURE);
    }
    return fd;
}

int main() {
    const char *fifo1 = "fifo_parent_to_child";
    const char *fifo2 = "fifo_child_to_parent";

    // Create FIFOs
    if (mkfifo(fifo1, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo fifo1");
        exit(EXIT_FAILURE);
    }

    if (mkfifo(fifo2, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo fifo2");
        exit(EXIT_FAILURE);
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    else if (pid == 0) {
        // --- CHILD ---

        // Step 1: Receive from parent
        int fd_read = safe_open(fifo1, O_RDONLY, 0);
        int fd_out = safe_open("child_received.bin", O_WRONLY | O_CREAT | O_TRUNC, 0666);

        char buffer[BUF_SIZE];
        ssize_t bytes;

        while ((bytes = read(fd_read, buffer, BUF_SIZE)) > 0) {
            if (write(fd_out, buffer, bytes) != bytes) {
                perror("write child_received.bin");
                exit(EXIT_FAILURE);
            }
        }

        close(fd_read);
        close(fd_out);

        // Step 2: Send back to parent
        int fd_in = safe_open("child_received.bin", O_RDONLY, 0);
        int fd_write = safe_open(fifo2, O_WRONLY, 0);

        while ((bytes = read(fd_in, buffer, BUF_SIZE)) > 0) {
            if (write(fd_write, buffer, bytes) != bytes) {
                perror("write fifo2");
                exit(EXIT_FAILURE);
            }
        }

        close(fd_in);
        close(fd_write);
    }

    else {
        // --- PARENT ---

        // Step 1: Send to child
        int fd_in = safe_open("original_file.bin", O_RDONLY, 0);
        int fd_write = safe_open(fifo1, O_WRONLY, 0);

        char buffer[BUF_SIZE];
        ssize_t bytes;

        while ((bytes = read(fd_in, buffer, BUF_SIZE)) > 0) {
            if (write(fd_write, buffer, bytes) != bytes) {
                perror("write fifo1");
                exit(EXIT_FAILURE);
            }
        }

        close(fd_in);
        close(fd_write);

        // Step 2: Receive back from child
        int fd_read = safe_open(fifo2, O_RDONLY, 0);
        int fd_out = safe_open("returned_file.bin", O_WRONLY | O_CREAT | O_TRUNC, 0666);

        while ((bytes = read(fd_read, buffer, BUF_SIZE)) > 0) {
            if (write(fd_out, buffer, bytes) != bytes) {
                perror("write returned_file.bin");
                exit(EXIT_FAILURE);
            }
        }

        close(fd_read);
        close(fd_out);

        wait(NULL); // Wait for child to finish

        // Step 3: Stop timer
        gettimeofday(&end, NULL);
        double time_taken = (end.tv_sec - start.tv_sec) +
                            (end.tv_usec - start.tv_usec) / 1e6;

        printf("Double transfer completed in %.2f seconds.\n", time_taken);

        // Step 4: Compare files
        int result = system("cmp original_file.bin returned_file.bin > /dev/null");
        if (result == 0) {
            printf("Success: Files are identical.\n");
        } else {
            printf("Failure: Files differ!\n");
        }
    }

    return 0;
}
