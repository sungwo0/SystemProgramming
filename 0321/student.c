#include<stdio.h> 

int main() { 
  char name[50]; 
  int number;

  printf("학번을 입력해주세요 : ");
  scanf("%d", &number);
  printf("이름을 입력해주세요 : ");
  scanf("%s", name);
  printf("학번 : %d\n이름 : %s\n", number, name);
}
