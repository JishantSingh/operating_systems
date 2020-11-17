//
// Created by Jishant Singh on 04/10/20.
//
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
    int fd[2];
    char* cmd = argv[1];
    if(pipe(fd) == -1){
        printf("Error in pipe");
        return 1;
    }
    pid_t pid = fork();
    if(pid == 0){
        close(fd[0]);
        struct timeval cur;
        gettimeofday(&cur,NULL);
        write(fd[1],&cur,sizeof(cur));
        close(fd[1]);
        execlp(cmd,cmd,NULL);
    } else if(pid >0 ){
        close(fd[1]);
        wait(NULL);
        struct timeval t;
        read(fd[0],&t,sizeof(t));
        struct timeval cur;
        gettimeofday(&cur,NULL);
        close(fd[0]);
        printf("%ld.%ld\n",cur.tv_sec - t.tv_sec,cur.tv_usec-t.tv_usec);
    }
    return 0;
}
