/********************************************************************************
* ASSIGNMENT 4: mmap and page fault
* --------------------------------------------------
* Team          : 11
* Date          : 22-Aug-2025
*
* Members:
* 1. Akshat Verma     | (Roll No: 002311001001)
* 2. Persis Azem Sada | (Roll No: 002311001078)
*
*********************************************************************************
* Assignment Description: 
*
* Create an 8GB file using fallocate, write a single byte value X at random offset F.
* The random function should generate a quantity anywhere between 0 and 8GB for F 
* and between 0–255 for X.
* The big file should be mapped into virtual address space using mmap(). 
* Once mapped, read back the data from the same offset (F). 
* If the read value X` matches the written value X, continue; 
* otherwise, print an error and terminate.
* Offset values must be displayed in hexadecimal format.
* The sequence of write → read → verify should repeat forever in a loop.
*
* Program Description:
* 
*  - Opens the given large file.
*  - Maps it into memory using mmap().
*  - Generates random offset F (0–8GB) and random byte X (0–255).
*  - Writes X at offset F and reads it back.
*  - Verifies correctness: mismatch → error message + exit.
*  - Prints offset in hexadecimal format.
*  - Loops infinitely to continuously perform this operation.
*  - In another terminal, run `sar -B 1` to observe increasing page faults.
*
* COMPILATION: 
*   gcc A2_11_4.c -o A2_11_4
*
* EXECUTION:
*
* Pre-Execution Setup:
*   1. fallocate -l 8G <filename.dat>    //(To create an 8GB file)
*   2. ./A2_11_4 <filename.dat>
*
* While-Executing:
*   3. In another terminal, run the "sar -B 1" command to monitor page faults.
*
*--------------------------------------------------------------------------------
* Sample SAR OUTPUT: (observed with `sar -B 1`):
 slc-lib14@slclib14-Veriton-M4650G:~$ sar -B 1
 Linux 5.15.0-139-generic (slclib14-Veriton-M4650G) 22/08/25 _x86_64_(8 CPU)
 
 02:12:37 PM IST  pgpgin/s pgpgout/s   fault/s  majflt/s  pgfree/s pgscank/s pgscand/s pgsteal/s    %vmeff
 02:12:38 PM IST      0.00      0.00    160.00      0.00    995.00      0.00      0.00      0.00      0.00
 02:12:39 PM IST      0.00      0.00    438.00    157.00    475.00      0.00      0.00      0.00      0.00
 02:12:40 PM IST      0.00      0.00   2013.00    859.00   3436.00      0.00      0.00      0.00      0.00
 02:12:41 PM IST      0.00      0.00   1737.00    853.00    627.00      0.00      0.00      0.00      0.00
 02:12:42 PM IST      0.00      0.00   1713.00    847.00   2200.00      0.00      0.00      0.00      0.00
 02:12:43 PM IST      0.00      0.00   1713.00    853.00    364.00      0.00      0.00      0.00      0.00
 02:12:44 PM IST      0.00    112.00   2509.00    851.00    505.00      0.00      0.00      0.00      0.00 ...
 ... (page faults keep increasing while program runs) ...
*
*--------------------------------------------------------------------------------
* Sample Program OUTPUT:
*--------------------------------------------------------------------------------
 slc-lib14@slclib14-Veriton-M4650G:~/A$ ./A2_11_4 file.dat
 Offset: 0x73582084   Written: 52   Read: 52
 Offset: 0x14b159976  Written: 229  Read: 229
 Offset: 0x141e53821  Written: 47   Read: 47
 Offset: 0x69d86586   Written: 173  Read: 173
*--------------------------------------------------------------------------------
********************************************************************************/

#include <stdio.h>        // for printf(), fprintf(), perror()
#include <stdlib.h>       // for rand(), exit()
#include <unistd.h>       // for close(), usleep()
#include <fcntl.h>        // for open() flags like O_RDWR
#include <sys/mman.h>     // for mmap() and munmap()
#include <sys/stat.h>     // for fstat() to get file size
#include <time.h>         // for time() to seed RNG

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *FILE_PATH = argv[1];

    // Open the large file in read-write mode
    int fd = open(FILE_PATH, O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // fstat() retrieves information about the file (e.g., size).
    // We need the file size to know how big a region to map into memory.
    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1) {
        perror("Error getting file size");
        close(fd);
        return 1;
    }
    off_t file_size = file_stat.st_size;   // should be 8GB

    // mmap() maps the file into the virtual address space.
    // This allows us to access the file using normal memory operations
    // instead of read/write system calls.
    unsigned char *mapped_file = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_file == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        return 1;
    }

    // Seed the random number generator with current time
    srand(time(NULL));

    // Infinite loop to test random offsets continuously
    while (1) {
        // Generate random 64-bit offset within file.
        // rand() only gives up to 31 bits, so we combine two calls:
        // (rand() << 32) | rand() gives a 63-bit number, then % file_size 
        // keeps it within the file's size range.
        off_t offset = (((off_t)rand() << 32) | rand()) % file_size;

        // Generate random byte value between 0 and 255
        unsigned char value = rand() % 256;

        // Write the value at the chosen offset
        mapped_file[offset] = value;

        // Read back the value from the same offset
        unsigned char read_value = mapped_file[offset];

        // Print the offset (in hex) and the values
        printf("Offset: 0x%lx  Written: %u  Read: %u\n",
               (unsigned long)offset, value, read_value);

        // Verify correctness
        if (read_value != value) {
            fprintf(stderr, "Error: Data mismatch at offset 0x%lx. Expected %u, got %u.\n",
                    (unsigned long)offset, value, read_value);
            break;
        }

        // usleep(1000) pauses the loop for ~1 millisecond.
        // This avoids flooding the terminal with output and reduces CPU usage.
        usleep(1000);
    }

    // munmap() removes the mapped region from virtual memory.
    if (munmap(mapped_file, file_size) == -1) {
        perror("Error unmapping file");
    }

    // Close the file descriptor
    close(fd);

    return 0;
}
