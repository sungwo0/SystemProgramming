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
