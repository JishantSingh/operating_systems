//
// Created by Jishant Singh on 23/09/20.
//

#include <sched.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define TEMP_FILENAME   "shm.tmp"

int main(void)
{
    int fd1 = shm_open(TEMP_FILENAME, O_CREAT | O_RDWR, 0777);
    int fd2 = shm_open(TEMP_FILENAME, O_RDWR, 0777);
    int *p1, *p2;
    int buf[1024] = {0x12345678};

    // Write initial contents to shared memory.
    write(fd1, buf, 4096);
    p1 = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd1, 0);
    p2 = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd2, 0);
    printf("fd1 = %d, p1 = %p\n", fd1, p1);
    printf("fd2 = %d, p2 = %p\n", fd2, p2);
    printf("p1[0] = 0x%08x, p2[0] = 0x%08x\n", p1[0], p2[0]);
    p1[0] = 0xdeadbeef;
    printf("p1[0] = 0x%08x, p2[0] = 0x%08x\n", p1[0], p2[0]);
    close(fd2);
    close(fd1);
    shm_unlink(TEMP_FILENAME);
    return 0;
}
