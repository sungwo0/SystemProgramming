# 12주차 강의 내용

# 9장 프로세스 제어

## 9.1 프로세스 생성

### 🧬 프로세스 생성

- 부모 프로세스가 자식 프로세스를 생성한다.
- `fork()` 시스템 호출을 사용한다.
- 부모 프로세스를 그대로 복제하여 자식 프로세스를 만든다 (자기복제).

```c
#include <sys/types.h>
#include <unistd.h>

pid_t fork(void);
```

- 자식 프로세스에는 `0`을 반환.
- 부모 프로세스에는 자식의 프로세스 ID(PID)를 반환.

---

### 🪄 `fork()`의 동작

- `fork()`는 **한 번 호출되면 두 번 리턴**한다.
- 반환값으로 부모/자식을 구분할 수 있다.

```c
pid = fork();
if (pid == 0) {
    // 자식 프로세스 실행 코드
} else {
    // 부모 프로세스 실행 코드
}
```

---

### 📄 예제 1: `fork1.c`

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    int pid;
    printf("[%d] 프로세스 시작\n", getpid());
    pid = fork();
    printf("[%d] 프로세스 : 리턴값 %d\n", getpid(), pid);
}
```

#### 💻 실행 결과 예시
```
[15065] 프로세스 시작
[15065] 프로세스 : 반환값 15066
[15066] 프로세스 : 반환값 0
```

---

### 📄 예제 2: `fork2.c` - 부모와 자식이 서로 다른 메시지 출력

```c
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int pid;
    pid = fork();
    if (pid == 0) { // 자식 프로세스
        printf("[Child] : Hello, world! pid=%d\n", getpid());
    } else { // 부모 프로세스
        printf("[Parent] : Hello, world! pid=%d\n", getpid());
    }
}
```

#### 💻 실행 결과 예시
```
[Parent] : Hello, world! pid=15799
[Child]  : Hello, world! pid=15800
```

---

### 📄 예제 3: `fork3.c` - 두 개의 자식 프로세스 생성

```c
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int pid1, pid2;
    pid1 = fork();
    if (pid1 == 0) {
        printf("[Child 1] : Hello, world! pid=%d\n", getpid());
        exit(0);
    }
    pid2 = fork();
    if (pid2 == 0) {
        printf("[Child 2] : Hello, world! pid=%d\n", getpid());
        exit(0);
    }
    printf("[Parent] : Hello, world! pid=%d\n", getpid());
}
```

#### 💻 실행 결과 예시
```
[Parent] : Hello, world! pid=15740
[Child 1] : Hello, world! pid=15741
[Child 2] : Hello, world! pid=15742
```

---

## 🕒 프로세스 기다리기: `wait()`

- 부모가 자식이 종료될 때까지 대기
- 종료된 자식의 PID를 반환하며, 종료 코드는 `status`에 저장됨

```c
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *statloc, int options);
```

---

### 📄 예제 4: `forkwait.c`

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pid, child, status;
    printf("[%d] 부모 프로세스 시작\n", getpid());
    pid = fork();
    if (pid == 0) {
        printf("[%d] 자식 프로세스 시작\n", getpid());
        exit(1);
    }
    child = wait(&status);
    printf("[%d] 자식 프로세스 %d 종료\n", getpid(), child);
    printf("\t종료 코드 %d\n", status >> 8);
}
```

#### 💻 실행 결과 예시
```
[15943] 부모 프로세스 시작
[15944] 자식 프로세스 시작
[15943] 자식 프로세스 15944 종료
        종료 코드 1
```

---

### 📄 예제 5: `waitpid.c` - 특정 자식 프로세스 기다리기

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pid1, pid2, child, status;

    printf("[%d] 부모 프로세스 시작\n", getpid());

    pid1 = fork();
    if (pid1 == 0) {
        printf("[%d] 자식 프로세스[1] 시작\n", getpid());
        sleep(1);
        printf("[%d] 자식 프로세스[1] 종료\n", getpid());
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        printf("[%d] 자식 프로세스[2] 시작\n", getpid());
        sleep(2);
        printf("[%d] 자식 프로세스[2] 종료\n", getpid());
        exit(2);
    }

    child = waitpid(pid1, &status, 0);
    printf("[%d] 자식 프로세스 #1 %d 종료\n", getpid(), child);
    printf("\t종료 코드 %d\n", status >> 8);
}
```

#### 💻 실행 결과 예시
```
[16840] 부모 프로세스 시작
[16841] 자식 프로세스[1] 시작
[16842] 자식 프로세스[2] 시작
[16841] 자식 프로세스[1] 종료
[16840] 자식 프로세스 #1 16841 종료
        종료 코드 1
[16842] 자식 프로세스[2] 종료
```




<!--13 14주차(6/13) -> 매주 한 디렉토리에 정리(15점)
발표 주제 2개 -> 깃허브 정리 및 수업내용 정리(지금부터라도 빠진 README.md 파일 정리)
gpt 이용 코드 정리
깃허브 정리 후  30점 만점에 몇점인지 다룬 ppt(3분내로 발표 가능하게)
발표 하루(6/13 예정정)
-->

