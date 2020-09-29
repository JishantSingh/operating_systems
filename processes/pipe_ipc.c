//
// Created by Jishant Singh on 29/09/20.
//
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(){
    int fd[2];
    pipe(fd);
    char *mess = "message no 1";
    pid_t pid = fork();
    if(pid > 0){
        close(fd[0]);
        write(fd[1], mess, 13);
        close(fd[1]);
        printf("going to child now\n");
    } else{
        close(fd[1]);
        char rd[100];
        int ret = read(fd[0],rd,100);
//        printf("%d", errno);
        printf("%s\n%d\n",rd, ret);
        int ret2 = read(fd[0],rd,100);
        printf("%d\n", ret2);
        close(fd[0]);
    }
    printf("exiting\n");
    return 0;
}