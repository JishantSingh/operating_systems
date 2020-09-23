//
// Created by Jishant Singh on 24/09/20.
//

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t  pid;
    pid = fork();
    if(pid < 0){
        printf("Error");
        return EXIT_FAILURE;
    } else if (pid == 0){
        printf("This is child process\n");
    } else {
        wait(NULL);
        printf("Parent exiting after child exited\n");
    }
    printf("This is a common statement  %d\n",pid);
    return EXIT_SUCCESS;
}
