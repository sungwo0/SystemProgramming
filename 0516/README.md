# 11주차 강의 내용

# 리눅스 파일 시스템 구조 및 파일 입출력 구현

## 6.1 파일 시스템 구조

### ▸ 유닉스 파일 시스템 구성 요소
- **부트 블록 (Boot block)**: 부팅 시 사용되는 코드 저장, 파일 시스템의 첫 번째 섹터.
- **슈퍼 블록 (Super block)**: 파일 시스템 전체에 대한 정보 저장  
  - 총 블록 수  
  - 사용 가능한 i-node 수  
  - 블록 비트맵, 블록 크기 등
- **i-리스트 (i-list)**: 모든 i-node들의 리스트
- **데이터 블록 (Data block)**: 실제 파일 내용이 저장되는 공간

> 리눅스의 ext4 파일 시스템은 ext 시리즈 중 최신이며,  
> - 최대 1EB(엑사바이트) 볼륨  
> - 최대 16TB 파일을 지원함  
> > 해당 구조는 이해를 돕기 위한 단순화된 버전입니다.

---

## 6.2 i-노드 (i-node) 구조

- **한 파일 = 하나의 i-node**
- 파일의 메타데이터 저장
  - 파일 타입 (일반, 디렉터리, 문자/블록 장치 등)
  - 파일 크기
  - 접근 권한
  - 소유자 및 그룹
  - 접근/수정 시간
  - 데이터 블록 포인터

### ▸ i-node의 블록 포인터 구성
- 직접 포인터: 12개
- 간접 포인터: 1개
- 이중 간접 포인터: 1개
- 삼중 간접 포인터: 1개

---

## 6.3 파일 입출력 구현

### ▸ 주요 커널 자료구조
- **파일 디스크립터 배열 (Fd Array)**  
  - 프로세스당 하나  
  - 열린 파일 테이블 항목을 가리킴
- **열린 파일 테이블 (Open File Table)**  
  - 열린 파일 목록  
  - 파일 위치, 플래그, i-node 포인터 포함
- **동적 i-node 테이블 (Active i-node Table)**  
  - 디스크에 존재하는 파일의 i-node를 메모리에서 관리

### ▸ open() 호출 예시
```c
fd = open("file", O_RDONLY);
```

### ▸ dup(), dup2()를 통한 fd 복사
```c
fd = dup(3);
fd = dup2(3, 4);
```
> 열린 파일 테이블은 공유하지만 파일 디스크립터는 별도

---

## 6.4 파일 상태 정보

### ▸ 파일 상태 확인: `stat()`, `fstat()`, `lstat()`
```c
#include <sys/types.h>
#include <sys/stat.h>

int stat(const char *filename, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *filename, struct stat *buf);
```

### ▸ stat 구조체
```c
struct stat {
  mode_t st_mode;     // 파일 타입 및 접근 권한
  ino_t st_ino;       // i-node 번호
  dev_t st_dev;       // 장치 번호
  nlink_t st_nlink;   // 링크 수
  uid_t st_uid;       // 사용자 ID
  gid_t st_gid;       // 그룹 ID
  off_t st_size;      // 파일 크기
  time_t st_atime;    // 마지막 접근 시간
  time_t st_mtime;    // 마지막 수정 시간
  time_t st_ctime;    // 상태 변경 시간
  long st_blksize;    // 블록 크기
  long st_blocks;     // 블록 수
};
```

---

## 6.5 파일 타입

| 타입 | 설명 | 매크로 |
|------|------|--------|
| 일반 파일 | 텍스트, 바이너리 | `S_ISREG()` |
| 디렉터리 | 파일 이름 및 포인터 포함 | `S_ISDIR()` |
| 문자 장치 파일 | 문자 단위 전송 장치 | `S_ISCHR()` |
| 블록 장치 파일 | 블록 단위 전송 장치 | `S_ISBLK()` |
| FIFO | 이름 있는 파이프 | `S_ISFIFO()` |
| 소켓 | 네트워크 통신 | `S_ISSOCK()` |
| 심볼릭 링크 | 다른 파일을 가리킴 | `S_ISLNK()` |

---

## 6.6 접근 권한 및 시간 변경

### ▸ chmod(), fchmod() — 접근권한 변경
```c
#include <sys/stat.h>
int chmod(const char *path, mode_t mode);
int fchmod(int fd, mode_t mode);
```

### ▸ utime() — 접근/수정 시간 변경
```c
#include <utime.h>
int utime(const char *filename, const struct utimbuf *times);
```

```c
struct utimbuf {
  time_t actime;   // 접근 시간
  time_t modtime;  // 수정 시간
};
```

---

## 6.7 파일 소유자 변경

### ▸ chown(), fchown(), lchown()
```c
#include <unistd.h>
int chown(const char *path, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int lchown(const char *path, uid_t owner, gid_t group);
```

---

## 6.8 디렉터리 관련

### ▸ dirent 구조체
```c
#include <dirent.h>
struct dirent {
  ino_t d_ino;
  char d_name[NAME_MAX + 1];
};
```

### ▸ 디렉터리 열기/읽기 함수
```c
DIR *opendir(const char *path);
struct dirent *readdir(DIR *dp);
int closedir(DIR *dp);
```

### ▸ 디렉터리 내용 출력 예시
```c
while ((d = readdir(dp)) != NULL) {
  printf("%s %lu\n", d->d_name, d->d_ino);
}
```

---


# 7장 파일 및 레코드 잠금

## 7.1 파일 잠금

### 파일 및 레코드 잠금의 원리
- **프로세스 간 데이터 공유 방식**  
  한 프로세스가 파일에 쓴 내용을 다른 프로세스가 읽음

- **문제점**
  - 한 프로세스가 파일 내용을 수정하는 중 다른 프로세스가 읽는 경우
  - 두 개의 프로세스가 동시에 같은 파일에 접근하여 쓰는 경우

### 잠금(lock)
- **파일 혹은 레코드 잠금**
  - 특정 영역을 읽거나 수정할 때 다른 프로세스의 접근을 제한
  - 잠금된 영역에는 한 번에 하나의 프로세스만 접근 가능
  - 특히 레코드에 쓰기/수정을 할 경우 잠금 필수

### 잠금이 필요한 예
#### 잠금 없음
1. A 프로세스가 잔액 100만 원 읽음  
2. B 프로세스가 잔액 100만 원 읽음  
3. B가 20만 원 입금 → 잔액 120만 원  
4. A가 10만 원 입금 → 잔액 110만 원 (데이터 손실)

#### 잠금 사용
1. A가 레코드 잠금 후 잔액 100만 원 읽음  
2. A가 10만 원 입금 후 잠금 해제 → 잔액 110만 원  
3. B가 레코드 잠금 후 잔액 110만 원 읽음  
4. B가 20만 원 입금 후 잠금 해제 → 잔액 130만 원

### flock()
- 파일 전체에 잠금
  - `LOCK_SH`: 공유 잠금
  - `LOCK_EX`: 배타 잠금
  - `LOCK_UN`: 잠금 해제
  - `LOCK_NB`: 비차단 방식

## 7.2 레코드 잠금

### 파일 잠금 vs 레코드 잠금
- 파일 잠금: 파일 전체에 대한 잠금
- 레코드 잠금: 특정 바이트 범위(레코드)에 대한 잠금

### fcntl()
- 파일 및 레코드 잠금 지원
- 잠금 종류:
  - `F_RDLCK`: 읽기 잠금 (공유 가능)
  - `F_WRLCK`: 쓰기 잠금 (배타적)
  - `F_UNLCK`: 잠금 해제

#### fcntl() 함수
```c
#include <fcntl.h>
int fcntl(int fd, int cmd, struct flock *lock);
```

#### struct flock 구조체
```c
struct flock {
    short l_type;    // 잠금 종류
    off_t l_start;   // 시작 위치
    short l_whence;  // 기준 위치 (SEEK_SET 등)
    off_t l_len;     // 길이
    pid_t l_pid;     // 프로세스 ID
};
```

## 7.3 잠금 함수

### 간단한 잠금 함수들 (`lockf`)
- `F_LOCK`: 쓰기 잠금, 잠금 해제까지 대기
- `F_TLOCK`: 쓰기 잠금, 대기하지 않음
- `F_TEST`: 잠금 여부 검사
- `F_ULOCK`: 잠금 해제

#### lockf() 함수
```c
#include <unistd.h>
int lockf(int fd, int cmd, off_t len);
```

## 7.4 권고 잠금과 강제 잠금

### 권고 잠금 (Advisory Locking)
- 잠금 규칙을 자발적으로 따름
- 커널이 강제하지 않음
- Linux, BSD, Mac OS 등

### 강제 잠금 (Mandatory Locking)
- 잠금된 영역에 접근 불가
- 시스템이 강제함 (System V, Solaris 등)
- Linux: `-o mand` 마운트 옵션 필요

#### 강제 잠금 설정 방법
```bash
$ chmod 2644 mandatory.txt
$ ls -l mandatory.txt
-rw-r-Sr-- 1 user group 160 날짜 mandatory.txt
```

## 핵심 개념 요약

- 읽기 잠금: 여러 프로세스가 공유 가능  
- 쓰기 잠금: 오직 하나의 프로세스만 허용  
- `fcntl()`: 세밀한 영역에 대한 잠금  
- `lockf()`: 간단한 잠금 구현  
- 권고 잠금은 강제되지 않으며, 강제 잠금은 OS에 따라 지원 여부 다름


# 시스템 프로그래밍 8장: 프로세스

---

## 8.1 쉘과 프로세스

### 📌 쉘(Shell)이란?
- 사용자와 운영체제 사이의 **명령어 처리기 (Command Processor)**
- 명령어를 커널에 전달하고 결과를 출력

### 📌 쉘의 실행 절차
```text
명령어 입력 → 파싱 → fork → exec → wait
```

### 📌 복합 명령어
- **명령어 열**: `명령어1; 명령어2; ...`
- **명령어 그룹**: `(명령어1; 명령어2)` → 리디렉션 등에 사용됨

### 📌 전면 처리 vs 후면 처리
- **전면 처리(Foreground)**: 명령 실행 완료까지 쉘 대기
- **후면 처리(Background)**: `명령어 &` 형태로 동시에 작업 가능

#### 💡 예시
```sh
(sleep 100; echo done) &  # 백그라운드 실행
jobs                      # 작업 목록 확인
fg %1                     # 백그라운드 작업을 전면으로
```

---

## 8.1.2 프로세스 개념

### 📌 프로세스(Process)
- 실행 중인 프로그램
- 고유한 PID (Process ID)를 가짐

### 📌 프로세스 상태 확인 명령어
```sh
ps
ps -ef
ps aux
```
- 출력 항목: PID, PPID, CMD, UID, STIME 등

---

## 8.1.3 프로세스 제어 명령어

| 명령어 | 설명 |
|--------|------|
| `sleep 초` | 일정 시간 대기 |
| `kill PID` | 시그널을 보내 프로세스 종료 |
| `wait [PID]` | 자식 프로세스 종료까지 대기 |
| `exit [코드]` | 프로세스를 종료하며 코드 반환 |

---

## 8.2 프로그램 실행

### 📌 exec 계열 함수
- 새로운 프로그램으로 현재 프로세스를 대체
- 실행 성공 시 return 하지 않음

### 📌 main 함수의 인수
```c
int main(int argc, char *argv[]);
```
- `argc`: 인수 개수
- `argv[]`: 인수 문자열 배열

### 📌 환경 변수 사용
- 전체 환경변수: `extern char **environ;`
- 환경변수 접근:
```c
getenv("HOME");       // 환경 변수 조회
setenv("VAR", "val", 1);  // 설정
unsetenv("VAR");      // 삭제
```

---

## 8.3 프로그램 종료

### 📌 종료 방식

| 종료 함수 | 특징 |
|-----------|------|
| `return` | main 함수에서 정상 종료 |
| `exit()` | 종료 처리기 실행, flush 수행 |
| `_exit()` | 즉시 종료, flush 생략 |
| `abort()` | 비정상 종료 (시그널) |

### 📌 종료 처리기 (atexit)

- 종료 직전에 실행할 함수 등록 가능 (최대 32개)
- 등록한 역순으로 실행됨

```c
void handler1() { ... }
void handler2() { ... }

atexit(handler1);
atexit(handler2);  // 실행 순서: handler2 → handler1
```

---

## 8.4 프로세스 ID와 사용자 ID

### 📌 프로세스 ID
| 함수 | 설명 |
|------|------|
| `getpid()` | 현재 프로세스의 PID |
| `getppid()` | 부모 프로세스의 PID |

### 📌 사용자/그룹 ID
| 함수 | 설명 |
|------|------|
| `getuid()` | 실제 사용자 ID |
| `geteuid()` | 유효 사용자 ID |
| `getgid()` | 실제 그룹 ID |
| `getegid()` | 유효 그룹 ID |

### 📌 set-user-ID (SUID)
- 실행 파일의 소유자 권한으로 실행되도록 설정 가능
- `chmod 4755 파일`로 설정
- 대표적 예: `/bin/passwd`

---
