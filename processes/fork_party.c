//
// Created by Jishant Singh on 29/09/20.
//
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int c=0;
int main(){
    pid_t t;
    for(int i=0;i<4;i++){
        t = fork();
        if(t == 0) c++;
        if(t > 0) wait(NULL);
//        printf("%d %d\n",i,c);
        printf("The process with the PID=%d\n", getpid());
    }
//    printf("cnt \n");
}