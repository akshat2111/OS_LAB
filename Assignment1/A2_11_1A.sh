#!/bin/bash
#
# Assignment    : 1A
# Subject       : Operating System Lab
# Date          : 26-July-2025
# Team          : 11
#
# Member:
# 1. Akshat Verma      (Roll No: 002311001001)
#
# Description:
# This script demonstrates the use of basic user-level and system-level
# Linux commands, which are essential for understanding how to interact
# with a Unix/Linux environment. The output has been either captured
# or explained where necessary.
# ======================================================================

# Q1. who – Lists all users currently logged into the system.
# who
# --- OUTPUT ---
# (unknown) :0           Oct 21 11:46 (:0)
# be2385   pts/0        Jul 26 21:54 (172.18.0.3)
# be2372   pts/1        Jul 26 20:35 (172.18.0.3)
# be2301   pts/3        Jul 26 23:19 (172.18.0.3)
# (Note: May not show anything if no users are logged into terminals.)
# --------------

# Q2. whoami – Displays the effective username of the current user.
# whoami
# --- OUTPUT ---
# be2301
# --------------

# Q3. pwd – Prints the full path of the current working directory.
# pwd
# --- OUTPUT ---
# /home/usr/student/ug/yr23/be2301/os_lab
# --------------

# Q4. date – Prints the system's current date and time.
# date
# --- OUTPUT ---
# Sat Jul 26 23:23:33 IST 2025
# --------------

# Q5. ls – Lists files and directories in the current directory.
# ls
# --- OUTPUT ---
# A2_11_1A.sh
# --------------

# Q6. mkdir – Used to create a new directory.
# mkdir demo_dir
# --- OUTPUT ---
# (No output if successful)
# --------------

# Q7. clear – Clears the terminal screen.
# clear
# --- OUTPUT ---
# (The screen gets cleared; no textual output is shown)
# --------------

# Q8. cd – Changes the current working directory to another.
# cd demo_dir
# --- OUTPUT ---
# /home/usr/student/ug/yr23/be2301/os_lab/demo_dir
# (Directory is changed)
# --------------

# Q9. df – Displays disk space usage of mounted file systems.
# df -h
# --- OUTPUT ---
# Filesystem                   Size  Used Avail Use% Mounted on
# /dev/mapper/scientific-root   50G   27G   24G  54% /
# devtmpfs                      32G     0   32G   0% /dev
# tmpfs                         32G   11M   32G   1% /dev/shm
# tmpfs                         32G  779M   31G   3% /run
# tmpfs                         32G     0   32G   0% /sys/fs/cgroup
# /dev/sda2                   1016M  233M  783M  23% /boot
# /dev/mapper/scientific-home  2.2T  131G  2.0T   7% /home
# tmpfs                        6.3G   16K  6.3G   1% /run/user/42
# tmpfs                        6.3G     0  6.3G   0% /run/user/3067
# tmpfs                        6.3G     0  6.3G   0% /run/user/3097
# tmpfs                        6.3G     0  6.3G   0% /run/user/3014
# tmpfs                        6.3G     0  6.3G   0% /run/user/3107
# tmpfs                        6.3G     0  6.3G   0% /run/user/3218
# tmpfs                        6.3G     0  6.3G   0% /run/user/3213
# tmpfs                        6.3G     0  6.3G   0% /run/user/3271
# ...
# --------------

# Q10. rmdir – Removes an empty directory.
# cd .. && rmdir demo_dir
# --- OUTPUT ---
# (Directory is deleted if empty, silently)
# --------------

# Q11. cat – Used to display content of files.
# echo "Hello from Akshat!" > file1.txt
# cat file1.txt
# --- OUTPUT ---
# Hello from Akshat!
# --------------

# Q12. cp – Copies files from one name/location to another.
# cp file1.txt file2.txt
# --- OUTPUT ---
# (File copied; no output unless there's an error)
# --------------

# Q13. mv – Renames or moves a file.
# mv file2.txt renamed_file.txt
# --- OUTPUT ---
# (No output on success)
# --------------

# Q14. rm – Deletes a specified file.
# rm renamed_file.txt
# --- OUTPUT ---
# (Removed silently on success)
# --------------

# Q15. stat – Shows detailed information about a file.
# stat file1.txt
# --- OUTPUT ---
#   File: 'file1.txt'
# Size: 22              Blocks: 8          IO Block: 4096   regular file
# Device: fd02h/64770d    Inode: 2147684406  Links: 1
# Access: (0644/-rw-r--r--)  Uid: ( 3204/  be2301)   Gid: ( 2926/  ugyr23)
# Context: unconfined_u:object_r:user_home_t:s0
# Access: 2025-07-26 23:23:33.517330673 +0530
# Modify: 2025-07-26 23:23:33.515330673 +0530
# Change: 2025-07-26 23:23:33.515330673 +0530
# Birth: -
# --------------

# Q16. ln – Creates a hard link to a file (both share same inode).
# ln file1.txt hardlink_file.txt
# --- OUTPUT ---
# (No output; check with `ls -li`)
# --------------

# Q17. tty – Shows the terminal you're working from.
# tty
# --- OUTPUT ---
# /dev/pts/3
# --------------

# Q18. uname – Prints system info like kernel and OS.
# uname -a
# --- OUTPUT ---
# Linux localhost.localdomain 3.10.0-514.21.1.el7.x86_64 #1 SMP Thu May 25 12:04:35 CDT 2017 x86_64 x86_64 x86_64 GNU/Linux
# --------------

# Q19. umask – Shows current default permission mask.
# umask
# --- OUTPUT ---
# 0022
# --------------

# Q20. find – Used to locate files in a directory hierarchy.
# find . -name "file1.txt"
# --- OUTPUT ---
# ./file1.txt
# --------------

# Q21. sort – Sorts the lines in a text file alphabetically.
# echo -e "mango\napple\nbanana" > fruits.txt
# sort fruits.txt
# --- OUTPUT ---
# apple
# banana
# mango
# --------------

# Q22. ps – Displays the list of current processes.
# ps
# --- OUTPUT ---
#  PID TTY          TIME CMD
# 14061 pts/3    00:00:00 bash
# 14180 pts/3    00:00:00 A1_01_1A.sh
# 14199 pts/3    00:00:00 ps
# --------------

# Q23. chmod – Changes permission of a file.
# chmod 755 file1.txt
# ls -l file1.txt
# --- OUTPUT ---
# -rwxr--r--. 2 be2301 ugyr23 22 Jul 26 23:23 file1.txt
# --------------

# Q24. grep – Searches for patterns in a file.
# grep "apple" fruits.txt
# --- OUTPUT ---
# apple
# --------------

# Q25. touch – Creates an empty file or updates timestamp.
# touch emptyfile.txt
# ls -l emptyfile.txt
# --- OUTPUT ---
# -rw-r--r--. 1 be2301 ugyr23 0 Jul 26 23:23 emptyfile.txt
# --------------

# Q26. more – Views file contents page by page.
# more fruits.txt
# --- OUTPUT ---
# apple
# banana
# mango
# --------------

# Q27. head/tail – Shows top/bottom 10 lines of a file.
# head fruits.txt
# tail fruits.txt
# --- OUTPUT ---
# apple
# banana
# mango
# --------------

# Q28. top – Dynamic process monitor. Run once in batch mode.
# top -b -n 1 | head -n 10
# --- OUTPUT ---
# top - 23:23:33 up 278 days, 11:37,  5 users,  load average: 0.00, 0.01
# Tasks: 326 total,   1 running, 322 sleeping,   0 stopped,   0 zombie
# %Cpu(s):  0.3 us,  1.8 sy,  0.0 ni, 96.7 id,  0.0 wa,  0.0 hi,  1.1 si
# KiB Mem : 65549308 total, 53935908 free,  2278196 used,  9335204 buff/
# KiB Swap: 32899068 total, 32899068 free,        0 used. 61722788 avail

# PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+
# 14208 be2301    20   0  157864   2228   1440 R   5.9  0.0   0:00.02
#  1 root      20   0  194444   7592   3988 S   0.0  0.0  29:45.18
#  2 root      20   0       0      0      0 S   0.0  0.0   0:26.13
# (Shows real-time CPU & process stats)
# --------------

# Q29. kill – Ends a process using its PID.
# sleep 60 &
# kill $!
# --- OUTPUT ---
# (sleep process killed silently)
# --------------

# Q30. history – Lists previous commands in this terminal.
# history | tail -n 5
# --- OUTPUT ---
#  ./A2_11_1A.sh: line 27: 14210 Terminated              sleep 60
# --------------

# Q31. du – Shows disk usage of current directory.
# du -sh .
# --- OUTPUT ---
# 12K     .
# --------------

# Q32. ping – Sends ICMP packets to test network connection.
# ping -c 1 google.com
# --- OUTPUT ---
# ping: google.com: Name or service not known
# --------------

# Q33. wc – Word count for lines, words, characters.
# wc fruits.txt
# --- OUTPUT ---
# 3  3 19 fruits.txt
# --------------

# Q34. > / >> – Redirects output to file (overwrite/append).
# echo "Line A" > out.txt
# echo "Line B" >> out.txt
# cat out.txt
# --- OUTPUT ---
# Line A
# Line B
# --------------

# Q35. | – Pipes output from one command to another.
# cat out.txt | grep Line
# --- OUTPUT ---
# Line A
# Line B
# --------------

# --- Final Cleanup ---
# Removes all temp files used in demo.
# rm file1.txt hardlink_file.txt fruits.txt emptyfile.txt out.txt
