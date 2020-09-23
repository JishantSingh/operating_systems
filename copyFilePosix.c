//2.24
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    int BUF_SIZE = 8192;
    char src[100], dst[100], s, d = '\n', buff[BUF_SIZE], *src2, *dst2;
    int i = 0, j = 0;
    src2 = src;
    dst2 = dst;
    while (read(STDIN_FILENO, src2, 1) > 0) {
        if (*src2 == '\n') {
            *src2 = '\0';
            break;
        }
        src2++;
    }
    while (read(STDIN_FILENO, dst2, 1) > 0) {
        if (*dst2 == '\n') {
            *dst2 = '\0';
            break;
        }
        dst2++;
    }
    write(STDOUT_FILENO, src, src2 - src);
    write(STDOUT_FILENO, &d, sizeof(d));
    write(STDOUT_FILENO, dst, dst2 - dst);
    int sc = open((const char *) src, O_RDONLY);
    if (sc < 0) exit(2);
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int dc = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dc < 0) {

        exit(3);
    }

    while (1) {
        int in = read(sc, buff, BUF_SIZE);
        if (in <= 0)break;
        int out = write(dc, buff, in);
        if (out <= 0)break;
    }
    close(sc);
    close(dc);

    return EXIT_SUCCESS;

}