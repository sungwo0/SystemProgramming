#include <stdio.h>

int main() {
    int num;
    int count = 0;
    int binary[8] = {0}; // 8비트 배열 초기화
    
    // 사용자로부터 0~255 사이의 정수 입력 받기
    printf("0에서 255 사이의 정수를 입력하세요: ");
    scanf("%d", &num);
    
    // 입력 범위 검증
    if(num < 0 || num > 255) {
        printf("잘못된 입력입니다. 0에서 255 사이의 정수를 입력하세요.\n");
        return 1;
    }
    
    // 정수를 이진수로 변환하고 배열에 저장
    for(int i = 7; i >= 0; i--) {
        binary[i] = num % 2;
        num /= 2;
    }
    
    // 이진수 출력
    printf("이진수: ");
    for(int i = 0; i < 8; i++) {
        printf("%d", binary[i]);
        if(binary[i] == 1) {
            count++; // 1의 개수 세기
        }
    }
    printf("\n");
    
    // 1의 개수 출력
    printf("1의 개수: %d\n", count);
    
    // 상위 4비트 출력
    printf("상위 4비트: ");
    for(int i = 0; i < 4; i++) {
        printf("%d", binary[i]);
    }
    printf("\n");
    
    return 0;
}
