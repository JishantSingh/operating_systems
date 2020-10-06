//
// Created by Jishant Singh on 07/10/20.
//
/*************
The Collatz conjecture concerns what happens when we take any positive
integer n and apply the following algorithm:
n = { n∕2,
 if n is even
3 × n + 1, if n is odd
The conjecture states that when this algorithm is continually applied,
all positive integers will eventually reach 1. For example, if n = 35, the
sequence is
35, 106, 53, 160, 80, 40, 20, 10, 5, 16, 8, 4, 2, 1
Write a C program using the fork() system call that generates this
sequence in the child process. The starting number will be provided
from the command line. For example, if 8 is passed as a parameter on
the command line, the child process will output 8, 4, 2, 1. Because the
parent and child processes have their own copies of the data, it will be
necessary for the child to output the sequence. Have the parent invoke
the wait() call to wait for the child process to complete before exiting
the program. Perform necessary error checking to ensure that a positive
integer is passed on the command line.
 *****************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void rec(int n) {
    printf("%d\n", n);
    if (n == 1) return;
    if ((n & 1) == 0) {
        n /= 2;
    } else {
        n = 3 * n + 1;
    }

    pid_t pid;
    pid = fork();
    if (pid == 0) {
        rec(n);
    } else {
        wait(NULL);
    }

}

int main(int argc, char *argv[]) {

    rec(atoi(argv[1]));
    return 0;
}
