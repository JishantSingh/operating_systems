//
// Created by Jishant Singh on 02/10/20.
//
#include <unistd.h>
#include <sys/wait.h>
int main(){
    pid_t pid = fork();
    if(pid >0){
        sleep(20);
        wait(NULL);
    }
}
