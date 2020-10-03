//
// Created by Jishant Singh on 03/10/20.
//
#include <unistd.h>
int main(){
    execl("/usr/bin/ls","ls",NULL);
    return 0;
}
