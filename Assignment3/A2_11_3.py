#!/usr/bin/python3

"""
15-Aug-2025 ::: Akshat Verma (Roll No: 002311001001), Persis Azem Sada (Roll No: 002311001078)

USAGE:
    python3 A2_11_3.py <N> <num_processes> <mod_value> <print_switch>

COMMAND LINE PARAMETER DESCRIPTION:
    <N>              : Dimension of the square matrices (e.g., 3000 means 3000x3000)
    <num_processes>  : Number of parallel processes (1 to CPU count)
    <mod_value>      : Maximum random value (elements will be between 0 and mod_value-1)
    <print_switch>         : 1 to print matrices, 0 to suppress output

WHAT THIS PROGRAM DOES:
    - Creates two NxN unsigned integer matrices filled with random numbers.
    - Multiplies them in parallel using the multiprocessing module.
    - Splits the workload across the given number of processes.
    - Measures and prints the time taken for multiplication (excluding initialization time).
    - Optionally prints input and result matrices if print_switch is set to 1.

SAMPLE INPUT/OUTPUT:
    Command:
        python3 A2_11_3.py 1000 3 100 1

    Sample Output:
        Matrix A:
        [[...], [...], ...]
        Matrix B:
        [[...], [...], ...]
        Time taken for multiplication:  2.153287 seconds
        Result Matrix C:
        [[...], [...], ...]

INPUT DETAILS:
    - Matrix A and Matrix B are randomly generated with dtype=uint32.
    - Values are between 0 and <mod_value>-1.

OUTPUT DETAILS:
    - Time taken for multiplication.
    - Result matrix C (only if print_switch=1).

TIME TAKEN ::: SYSTEM DETAILS:
    - Time Taken (Example): 2.15 seconds for 1000x1000 matrix with 3 processes
    - CPU Utilization (cpustat 1 output):
        %CPU   %USR   %SYS   PID S  CPU    Time Task
        98.00  98.00   0.00  566 R    0   1.64s python3
        94.00  94.00   0.00  568 R    0   1.52s python3
        94.00  94.00   0.00  567 R    0   1.55s python3
"""
import os   # to control thread usage by setting env variables
import sys  # for handling command line arguements
import time # for time.perf_counter()
import numpy as np # for fast numerical operations on matrix
from multiprocessing import Pool, cpu_count # for enabling parallel computation 
                                            # Pool is used for automatically divide work across processes and collecting result
                                            # cpu_count get the count of logical cpu cores.


# to make sure numpy/BLAS doesn’t use extra threads
# Limit NumPy and related libraries to use only 1 thread
# This avoids conflict with multiprocessing (no cpu oversubscription)
os.environ["OMP_NUM_THREADS"] = "1"
os.environ["OPENBLAS_NUM_THREADS"] = "1"
os.environ["MKL_NUM_THREADS"] = "1"
os.environ["VECLIB_MAXIMUM_THREADS"] = "1"
os.environ["NUMEXPR_NUM_THREADS"] = "1"

# global variables to be shared in worker processes
B_global = None     # Matrix B (read-only in workers)
mod_global = None

# function for each process to multiply chunk of matrix A with global B
def multiply_chunk(A_chunk):
    C_temp = np.dot(A_chunk.astype(np.uint64), B_global.astype(np.uint64)) #to prevent overflow convert to uint64
    if mod_global > 0:  # apply modulus
        C_temp %= mod_global
    return C_temp.astype(np.uint32)     #to save memory while storing 

# initializer for each process -- sets global variables
def init_worker(B, mod):
    global B_global, mod_global
    B_global = B
    mod_global = mod

def main():
    if len(sys.argv) != 5:
        print("Usage: python3 A2_11_3.py <N> <num_processes> <mod_value> <print_switch>")
        sys.exit(1)

    N = int(sys.argv[1])
    num_proc = int(sys.argv[2])
    mod_value = int(sys.argv[3])
    print_switch = int(sys.argv[4])

    if num_proc < 1 or num_proc > cpu_count():
        print(f"Number of processes must be between 1 and {cpu_count()}")
        sys.exit(1)

    # initialize matrices with random numbers
    A = np.random.randint(0, mod_value, size=(N, N), dtype=np.uint32)
    B = np.random.randint(0, mod_value, size=(N, N), dtype=np.uint32)

    if print_switch == 1:
        print("Matrix A:")
        print(A)
        print("Matrix B:")
        print(B)

    # split A into chunks for each process row wise
    A_chunks = np.array_split(A, num_proc, axis=0)

    # start timing multiplication
    start = time.perf_counter()

    with Pool(processes=num_proc, initializer=init_worker, initargs=(B, mod_value)) as pool:    # "with" is used to automatically close the resources and cleanup
        #mapping each chunk of A to the multiply_chunk function in parallel
        result_parts = pool.map(multiply_chunk, A_chunks)

    # combine results
    C = np.vstack(result_parts)

    end = time.perf_counter()

    print(f"Time taken: {end - start:.6f} seconds")

    if print_switch == 1:
        print("Result Matrix C:\n", C)

if __name__ == "__main__":
    main()

