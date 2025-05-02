#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd1, fd2, fd3;
    fd1 = open(argv[1], O_RDWR);
    printf("파일 %s 열기 성공 : %d\n", argv[1], fd1);
    fd2 = open(argv[1], O_RDWR);
    printf("파일 %s 열기 성공 : %d\n", argv[1], fd2);
    fd3 = open(argv[1], O_RDWR);
    printf("파일 %s 열기 성공 : %d\n", argv[1], fd3);

    close(fd);
    exit(0);
}
