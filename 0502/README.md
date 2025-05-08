# 9주차 강의 내용

# 📘 리눅스 시스템 프로그래밍 요약

---

## 📌 1. 시스템 프로그래밍과 커널

- **유닉스 커널의 역할**
  - 파일 관리 (File Management)
  - 프로세스 관리 (Process Management)
  - 메모리 관리 (Memory Management)
  - 통신 관리 (Communication Management)
  - 주변장치 관리 (Device Management)

---

## 📌 2. 시스템 호출 (System Call)

- 응용 프로그램이 커널의 기능을 요청하기 위한 **프로그래밍 인터페이스**
- 시스템 호출은 C 언어 함수처럼 사용되며, 내부적으로 커널에 접근함

---

## 📌 3. 주요 시스템 호출

### 🗃️ 파일 관련
- `open()` : 파일 열기
- `creat()` : 파일 생성
- `close()` : 파일 닫기
- `read()` : 파일에서 데이터 읽기
- `write()` : 파일에 데이터 쓰기
- `lseek()` : 파일 위치 포인터 이동
- `dup()`, `dup2()` : 파일 디스크립터 복제

### 👨‍💻 프로세스 관련
- `fork()`, `exec()`, `exit()`, `wait()`, `getpid()`, `getppid()`

### 🧠 메모리 관련
- `malloc()`, `calloc()`, `free()` *(일반적으로 라이브러리 함수로 사용됨)*

### 📡 IPC 및 기타
- `signal()`, `alarm()`, `kill()`, `sleep()`
- `pipe()`, `socket()`

---

## 📌 4. 파일 디스크립터와 파일 위치 포인터

- **파일 디스크립터**: 열린 파일을 나타내는 정수형 식별자
- **파일 위치 포인터**: 현재 파일 내 읽기/쓰기 위치
  - `lseek()`을 통해 조작 가능

---

## 📌 5. 파일 시스템 관련 개념 요약

- **open()**
  - 다양한 플래그 사용 가능:  
    `O_RDONLY`, `O_WRONLY`, `O_RDWR`, `O_CREAT`, `O_TRUNC`, `O_APPEND`, `O_EXCL` 등

- **creat()**
  - 쓰기 전용으로 파일 생성, 기존 파일이 있으면 내용 삭제

- **read() / write()**
  - 파일 입출력의 핵심 시스템 호출

- **dup() / dup2()**
  - 파일 디스크립터 복제. 동일한 파일에 대해 두 개 이상의 디스크립터 사용 가능

- **lseek()**
  - 현재 파일 위치 포인터를 원하는 위치로 이동  
    `SEEK_SET`, `SEEK_CUR`, `SEEK_END` 사용

---

## 📌 6. 학생 데이터베이스 예제 설명 (`student.h` 기반)

- 학생 정보를 파일에 저장하고, 조회 및 수정하는 프로그램 예제
- 구조체를 그대로 `write()`, `read()`로 처리
- `lseek()`을 사용해 특정 학번의 오프셋 계산 후 저장/수정 수행

```c
lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);
write(fd, (char *) &record, sizeof(record));
