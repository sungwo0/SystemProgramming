#include <stdio.h>
#include <string.h>

#define MAXLINE 100

char line[MAXLINE];     // 입력 줄
char longest[MAXLINE];  // 가장 긴 줄

void copy(char from[], char to[]);

/* 입력 줄 가운데 가장 긴 줄을 프린트 */
int main() {
    int len;
    int max = 0;

    // 한 줄씩 입력을 받아서 길이를 비교
    while (fgets(line, MAXLINE, stdin) != NULL) {
        len = strlen(line);
        if (len > max) {
            max = len;
            copy(line, longest);
        }
    }

    // 입력 줄이 하나라도 있었으면 출력
    if (max > 0) {
        printf("%s", longest);
    }

    return 0;
}

/* copy: from을 to에 복사; to가 충분히 크다고 가정 */
void copy(char from[], char to[]) {
    int i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}
