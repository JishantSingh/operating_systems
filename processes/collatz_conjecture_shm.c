//
// Created by Jishant Singh on 07/10/20.
//

/******************
In Exercise 3.21, the child process must output the sequence of numbers
generated from the algorithm specified by the Collatz conjecture
because the parent and child have their own copies of the data. Another
approach to designing this program is to establish a shared-memory
object between the parent and child processes. This technique allows
the child to write the contents of the sequence to the shared-memory
object. The parent can then output the sequence when the child completes.
Because the memory is shared, any changes the child makes will
be reflected in the parent process as well.
This program will be structured using POSIX shared memory as
described in Section 3.7.1. The parent process will progress through the
following steps:
a. Establish the shared-memory object (shm open(), ftruncate(),
and mmap()).
b. Create the child process and wait for it to terminate.
c. Output the contents of shared memory.
d. Remove the shared-memory object.
One area of concern with cooperating processes involves synchronization
issues. In this exercise, the parent and child processes must be
coordinated so that the parent does not output the sequence until the
child finishes execution. These two processeswill be synchronized using
the wait() system call: the parent process will invoke wait(), which
will suspend it until the child process exits.
***********************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>

void func(int n) {
    char *fname = "temp_file";
    int shmfd = shm_open(fname, O_RDWR | O_CREAT, 0666);
    pid_t pid;
    while (n > 1) {
        printf("%d %d\n", n, getpid());
        ftruncate(shmfd, sizeof(int));
        int *val = (int *) mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
        pid = fork();
        printf("child pid is %d\n", pid);
        if (pid == 0) {
            if ((n & 1) == 0) {
                n /= 2;
            } else {
                n = 3 * n + 1;
            }
            *val = n;
            shm_unlink(fname);
            //very important to return here, else will create n recursive calls.
            return;
        } else if (pid > 0) {
            wait(NULL);
            n = *val;
        }
    }
    printf("%d\n", n);
}

int main(int argc, char *argv[]) {
    func(atoi(argv[1]));
    return 0;
}