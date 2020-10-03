//
// Created by Jishant Singh on 03/10/20.
//
#include <unistd.h>
#include <sys/time.h>
#include "stdio.h"
int main(){
//    execlp("ls","ls",NULL);
    struct timeval cur;
    gettimeofday(&cur,NULL);
    printf("%ld", (long)cur.tv_sec);
    return 0;
}
