//
// Created by Jishant Singh on 07/10/20.
//

/***********************
Design a file-copying program named filecopy.c using ordinary
pipes. This program will be passed two parameters: the name of the file
to be copied and the name of the destination file. The program will then
create an ordinary pipe and write the contents of the file to be copied to
the pipe. The child process will read this file from the pipe and write it
to the destination file. For example, ifwe invoke the program as follows:
./filecopy input.txt copy.txt
the file input.txt will be written to the pipe. The child processwill read
the contents of this file and write it to the destination file copy.txt. You
may write this program using either UNIX orWindows pipes.
*************************/

#include <unistd.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <stdio.h>

#define BUFF_SIZE 1000

int file_copy(char *input, char *output) {
    int fd[2];
    pipe(fd);
    int read_fd = open(input, O_RDONLY, 0666);
    char buff[BUFF_SIZE];
    int read_size = read(read_fd, buff, BUFF_SIZE);
    if(read_size == -1){
        printf("error1 %d", errno);
        return errno;
    }
    while (read_size > 0) {
        int wr_sz = write(fd[1], buff, read_size);
        if(wr_sz == -1){
            printf("error2 %d", errno);
            return errno;
        }
        read_size = read(read_fd, buff, BUFF_SIZE);
        if(read_size == -1){
            printf("error3 %d", errno);
            return errno;
        }
    }
    close(read_fd);
//    close(fd[0]);
    close(fd[1]);
    pid_t pid = fork();
    if(pid > 0){
        close(fd[0]);
    }
    else if (pid == 0) {
        int write_fd = creat(output, 0666);
        read_size = read(fd[0], buff, BUFF_SIZE);
        if(read_size == -1){
            printf("error4 %d", errno);
            return errno;
        }
        while (read_size > 0) {
            int wr_sz = write(write_fd, buff, read_size);
            if(wr_sz == -1){
                printf("error5 %d", errno);
                return errno;
            }
            read_size = read(fd[0], buff, BUFF_SIZE);
            if(read_size == -1){
                printf("error6 %d", errno);
                return errno;
            }
        }
        close(fd[0]);
        close(write_fd);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    file_copy(argv[1],argv[2]);
    return 0;
}