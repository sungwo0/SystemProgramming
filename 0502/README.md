1. 시스템 호출과 라이브러리 관계



argument.c

#include <stdio.h>

int main(int argc, char *argv[]) {
    // argc: 명령줄 인자의 개수
    printf("인자의 개수: %d\n", argc);

    // 전달된 인자들 출력
    printf("전달된 인자들:\n");
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    return 0;
}


openex.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd;
    if ((fd = open(argv[1], O_RDWR)) == -1)
        printf("파일 열기 오류\n");
    else printf("파일 %s 열기 성공 : %d\n", argv[1], fd);

    close(fd);
    exit(0);
}

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
