# 10주차 강의 내용

# 📁 파일 디스크립터 복제

### 🔹 `dup()` / `dup2()` 호출
- 기존의 파일 디스크립터를 복제한다.
- `oldfd`와 복제된 새로운 디스크립터는 **하나의 파일을 공유**한다.

#### ✅ `int dup(int oldfd);`
- `oldfd`에 대한 복제본인 **새로운 파일 디스크립터를 생성**하여 반환한다.
- 실패 시 `-1` 반환

#### ✅ `int dup2(int oldfd, int newfd);`
- `oldfd`를 `newfd`에 복제하고 **복제된 새로운 파일 디스크립터를 반환**한다.
- 실패 시 `-1` 반환

---

# 📍 파일 위치 포인터 (File Position Pointer)

- 파일 내에서 읽거나 쓸 위치인 **현재 파일 위치**를 가리킨다.

---

# 🔀 파일 위치 포인터 이동: `lseek()`

### 🔹 시스템 호출 형식
```c
off_t lseek(int fd, off_t offset, int whence);
```
- 이동에 성공하면 **현재 위치 반환**, 실패하면 `-1` 반환

### ✅ 사용 예
- `lseek(fd, 0L, SEEK_SET);` : 파일 **시작으로 이동**
- `lseek(fd, 100L, SEEK_SET);` : 시작에서 **100바이트 위치로**
- `lseek(fd, 0L, SEEK_END);` : **파일 끝으로 이동**

### ✅ 레코드 단위 이동
- `lseek(fd, n * sizeof(record), SEEK_SET);` : **n+1번째 레코드** 시작 위치로 이동
- `lseek(fd, sizeof(record), SEEK_CUR);` : **다음 레코드**로 이동
- `lseek(fd, -sizeof(record), SEEK_CUR);` : **이전 레코드**로 이동
- `lseek(fd, sizeof(record), SEEK_END);` : **파일 끝 이후**로 이동

---

# 📝 레코드 저장 예시
- 순서대로 레코드 저장
    1. `record1` 저장
    2. `record2` 저장
    3. 파일 끝으로 이동 후 `record3` 저장

---

# 🧾 student.h 구조체

- `MAX = 24`
- `START_ID = 1401001`

```c
struct student {
  char name[MAX];
  int id;
  int score;
};
```

---

# 📦 dbcreate.c 기능

- **학생 정보를 입력받아 파일에 저장**
- 파일을 `O_WRONLY | O_CREAT | O_EXCL` 모드로 열고
- 학번을 기준으로 위치 계산 후 `write()`로 저장

---

# 🔍 dbquery.c 기능

- **학번을 입력받아 해당 레코드를 검색/출력**
- 파일을 `O_RDONLY` 모드로 열고
- 위치 계산 후 `read()`로 레코드 출력
- 학번이 존재하지 않으면 `"레코드 없음"` 출력

---

# ✏️ 레코드 수정 과정

1. **해당 레코드를 읽음**
2. **수정**
3. **다시 파일 내 원래 위치에 씀**

---

# 🛠️ dbupdate.c 기능

- **학번 입력 → 해당 학생 정보 수정**
- 파일을 `O_RDWR` 모드로 열고
- 위치 계산 후 `read()`로 레코드 읽음
- 점수 수정 후 `lseek()`을 사용해 원위치로 이동
- `write()`로 덮어쓰기

## 1. 파일 시스템 구조

- **파일 시스템**: 저장 장치 위에서 파일을 저장하고 관리하는 구조.
- **디스크 구조**: 디스크는 섹터(sector) 단위로 나뉘고, 여러 섹터가 모여 블록(block)을 구성함.
- **블록(Block)**: 데이터 저장의 최소 단위.
- **슈퍼블록(Superblock)**: 파일 시스템 전체 구조 정보를 저장하는 블록.
  - 파일 시스템 크기
  - 사용된 블록 수
  - i-node 정보 등

---

## 2. i-node (Index Node)

- **정의**: 파일의 메타데이터를 저장하는 자료구조.
- **i-node가 저장하는 정보**:
  - 파일 유형
  - 접근 권한 (Permission)
  - 소유자 UID/GID
  - 파일 크기
  - 데이터 블록 주소 (포인터)
  - 생성/수정/접근 시간
- **블록 포인터의 종류**:
  - 직접 블록 (Direct block): 실제 데이터 블록 주소
  - 간접 블록 (Indirect block): 블록 주소를 담는 블록의 주소
    - 단일 간접, 이중 간접, 삼중 간접 블록

---

## 3. 파일 입출력 구현 (C)

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("sample.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buffer[128];
    int n = read(fd, buffer, sizeof(buffer) - 1);
    if (n < 0) {
        perror("read");
        return 1;
    }
    buffer[n] = '\0';
    printf("읽은 내용: %s\n", buffer);

    close(fd);
    return 0;
}
```

- `open()`: 파일 열기, 파일 디스크립터 반환
- `read()`: 파일에서 데이터를 읽음
- `close()`: 파일 닫기

---

## 4. 파일 상태 확인 (stat, fstat)

```c
#include <sys/stat.h>
#include <stdio.h>

int main() {
    struct stat st;
    if (stat("sample.txt", &st) == -1) {
        perror("stat");
        return 1;
    }

    printf("파일 크기: %ld bytes\n", st.st_size);
    printf("파일 유형: ");
    if (S_ISREG(st.st_mode)) printf("일반 파일\n");
    else if (S_ISDIR(st.st_mode)) printf("디렉터리\n");

    return 0;
}
```

- `stat()`: 파일 경로 기반 정보 조회
- `fstat()`: 파일 디스크립터 기반 정보 조회
- 주요 필드:
  - `st_size`: 파일 크기
  - `st_mode`: 파일 유형 및 권한

---

## 5. 디렉터리 처리 (opendir, readdir, closedir)

```c
#include <dirent.h>
#include <stdio.h>

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("파일 이름: %s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
```

- `opendir()`: 디렉터리 열기
- `readdir()`: 디렉터리 내 파일 정보 순차적으로 읽기
- `closedir()`: 디렉터리 닫기

---

## 요약

| 항목 | 설명 |
|------|------|
| i-node | 파일의 메타데이터 저장 |
| 블록 포인터 | 직접/간접 포인터로 파일 크기 확장 지원 |
| open/read/close | 파일 입출력 함수 |
| stat/fstat | 파일 상태 정보 확인 |
| opendir/readdir | 디렉터리 탐색 함수 |
