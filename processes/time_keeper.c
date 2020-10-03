//
// Created by Jishant Singh on 04/10/20.
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]){
    int pid=0, fd;
    char* cmd = argv[1];
    char *name = "time_mem_name";
    fd = shm_open(name,O_RDWR | O_CREAT,0666);
    ftruncate(fd,sizeof(struct timeval));
    struct timeval *t = (struct timeval*)mmap(0,sizeof(struct timeval),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    pid = fork();
    if(pid == 0){
        struct timeval cur;
        gettimeofday(&cur,NULL);
        //preferred instead of memcpy as it allows flexibility for compiler optimization
        *t = cur;
        shm_unlink(name);
        execlp(cmd,cmd,NULL);
    } else if(pid >0){
        wait(NULL);
        struct timeval cur;
        gettimeofday(&cur,NULL);
        long del = cur.tv_sec;
        del -= t->tv_sec;
        shm_unlink(name);
        printf("%ld.%ld\n",cur.tv_sec - t->tv_sec,cur.tv_usec-t->tv_usec);
    } else {
        printf("Error in fork");
    }
}

