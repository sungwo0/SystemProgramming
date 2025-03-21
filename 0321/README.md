cd 경로

/ = root
. = self
.. = parent
~ = home


리눅스 > c언어로 변환

wild character
* = all
? = one

rm + 파일명 + -r = > 디렉터리 삭제 

touch > 파일이 없을 시 내용이 빈 파일을 만들어줌
기존 파일이 있을 시 타임스탬프 시간 변경

cat > 파일의 내용 확인

head > 파일의 앞 부분 출력

tail > 파일의 뒷 부분 출력

wc > 파일에 저장된 라인의 수, 단어의 수, 문자의 수를 출력

gcc > 

code > vs code와 wsl을 연동
sudo snap install --classic code 해당 명령어로 다운 후 실행

\\wsl$\ > wsl에서 작성한 파일경로(윈도우 탐색기 통해 검색)

scanf 이용

hello.c 와 학번 이름 입력 후 출력 하는 파일 2개 업로드

학번을 입력해주세요
#include<stdio.h>
int main()
{
	char name[50];
	int number;

	printf("학번을 입력해주세요 : ");
	scanf("%d", &number);
	printf("이름을 입력해주세요 : ");
	scanf("%s", name);
	printf("학번 : %d\n 이름 : %s\n", number, name);
}

hello.c
#include<stdio.h>
int main()
{
	printf("Hello C world!!!");

	return 0;
}
