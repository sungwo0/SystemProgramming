# 3주차 강의 내용

## 경로 이동 (cd)
- `/` = root (루트 디렉터리)
- `.` = self (현재 디렉터리)
- `..` = parent (상위 디렉터리)
- `~` = home (사용자의 홈 디렉터리)

## 와일드카드 (Wild Character)
- `*` = 모든 파일/디렉터리 (all)
- `?` = 한 글자만 대체 (one)

## 파일 및 디렉터리 관리
- `rm 파일명 -r` ➝ 디렉터리 삭제

## 파일 생성 및 확인
- `touch 파일명`  
  - 파일이 없을 경우, 빈 파일을 생성  
  - 파일이 있을 경우, 타임스탬프 갱신  
- `cat 파일명` ➝ 파일 내용 확인  
- `head 파일명` ➝ 파일의 앞부분 출력  
- `tail 파일명` ➝ 파일의 뒷부분 출력  
- `wc 파일명` ➝ 파일의 **라인 수, 단어 수, 문자 수 출력**  

## C 언어 컴파일 (`gcc`)
- `gcc` ➝ C 언어 컴파일러  
- 설치 명령어:  
  ```bash
  sudo apt install build-essential

## gcc 사용 후 화면

![Image](https://github.com/user-attachments/assets/7d37c00e-5315-4718-9dd1-5c2139b7366f)

![Image](https://github.com/user-attachments/assets/83d1b799-9b89-455d-8642-faeced518f31)

## 참고
[[리눅스 우분투] gcc 컴파일러 설치하기 (Linux ubuntu)](https://mryeo.tistory.com/23)
