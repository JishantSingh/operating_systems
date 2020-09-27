//
// Created by Jishant Singh on 27/09/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/errno.h>
//#include <zconf.h>

int main()
{
    const int SIZE = 4096;
    const char *name = "OS";
    const char *message_0 = "Hello";
    const char *message_1 = "World!";
    int fd;
    char *ptr;
    fd = shm_open(name,O_CREAT | O_RDWR,0777);
    printf("%d\n", fd);
    ftruncate(fd, SIZE);
    ptr = (char *)
            mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("%p\n", ptr);
    char *ptr2 = ptr;
    sprintf(ptr,"%s",message_0);
    ptr += strlen(message_0);
    sprintf(ptr,"%s",message_1);
    ptr += strlen(message_1);
    printf("%s\n",ptr2);
//    shm_unlink(name);
//    sleep(60);

    fd = shm_open(name, O_RDWR, 0777);
    printf("%d\n",fd);
    char *ptry = (char *)
            mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("%d\n",errno);
    printf("%p\n", ptry);
    printf("%s\n", ptry);

    return 0;
}
