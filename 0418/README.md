# 7주차 강의 내용

# 📘 시스템 프로그래밍 6장: 프로세스 요약

## 1. 프로세스

- 실행 중인 프로그램 = 프로세스
- 각 프로세스는 고유한 **PID**(프로세스 ID)를 가짐
- `ps`, `pgrep` 명령어로 프로세스 상태 확인 가능

### 🔧 프로세스 조회 예시

```bash
$ ps -ef | grep sshd
$ pgrep -l sshd
$ pgrep -ln sshd
```

---

## 2. 작업 제어

- 쉘에서 명령을 **백그라운드(`&`) 실행** 가능
- `Ctrl + C`: 강제 종료, `Ctrl + Z`: 일시 정지
- `fg`, `bg` 명령으로 작업 전환 가능

### ✅ 예시

```bash
$ sleep 10 &    # 백그라운드 실행
$ fg %1         # 포그라운드 복귀
$ bg %1         # 백그라운드 전환
```

---

## 3. 프로세스 제어

- `kill`: 프로세스 종료
- `wait`: 자식 프로세스 대기
- `nice`, `renice`: 우선순위 조정

### 🔧 명령어 예시

```bash
$ kill 12345
$ wait 67890
$ renice -n 5 -p 4321
```

---

## 4. 프로세스와 사용자 ID

- `id`, `$UID`, `$EUID`로 사용자 정보 확인
- **set-user-ID (SUID)**, **set-group-ID (SGID)** 를 통해 권한 설정 가능

### 🔐 SUID/SGID 예시

```bash
$ chmod u+s somefile  # set-user-ID
$ chmod g+s somefile  # set-group-ID
```

```bash
$ ls -l /bin/passwd
-rwsr-xr-x. 1 root root 59976 ...
```

---

## 5. 시그널과 프로세스

- 시그널: 소프트웨어 인터럽트
- 프로세스 종료, 일시 정지, 재개 등에 사용

### 🚨 주요 시그널

| 시그널 | 설명 |
|--------|------|
| `SIGINT`  | Ctrl+C |
| `SIGTSTP` | Ctrl+Z |
| `SIGKILL` | 강제 종료 |
| `SIGCHLD` | 자식 프로세스 종료 시 부모에게 알림 |

### 🔧 시그널 명령어

```bash
$ kill -9 PID         # 강제 종료 (SIGKILL)
$ kill -STOP PID      # 일시 정지
$ kill -CONT PID      # 재개
$ kill -l             # 시그널 목록 출력
```

---

## 📝 정리

- 프로세스는 실행 중인 프로그램 단위이며 PID로 식별됨
- 쉘에서 작업 제어(`fg`, `bg`, `Ctrl+C/Z`) 가능
- `kill`, `nice`, `wait` 등을 통해 프로세스 제어
- 사용자 권한은 RUID/EUID로 관리되고, SUID/SGID로 위임 가능
- 시그널은 프로세스를 소프트웨어적으로 제어하는 수단

---

## 📂 참고 명령 요약

```bash
# 프로세스 목록 보기
$ ps -ef

# 특정 프로세스 검색
$ pgrep -l processname

# 작업 제어
$ command &
$ fg %1
$ bg %1

# 시그널 전달
$ kill -9 PID
$ kill -STOP PID
$ kill -CONT PID

# 우선순위 조정
$ nice -n 10 command
$ renice -n 5 -p PID
```

---

# 📘 시스템 프로그래밍 7장 요약: 인터넷과 서버

## 1. TCP/IP 프로토콜

TCP/IP (Transmission Control Protocol / Internet Protocol)는 인터넷에서 사용하는 기본 통신 프로토콜이다. 데이터는 **패킷** 형태로 전송되며, 계층적으로 구성되어 있다.

### TCP/IP 4계층 모델

| 계층 | 설명 | 예시 |
|------|------|------|
| 애플리케이션 (Application) | 사용자 서비스 제공 | HTTP, FTP, SMTP |
| 전송 (Transport) | 종단 간 데이터 전송 보장 | TCP (신뢰성 보장), UDP (속도 우선) |
| 인터넷 (Internet) | 패킷을 목적지까지 전달 | IP, ICMP |
| 네트워크 인터페이스 (Network Interface) | 물리적 전송 수행 | 이더넷, 와이파이 등 |

---

## 2. IP 주소와 포트번호

- **IP 주소**: 네트워크 상에서 장치를 구분하는 고유 주소 (예: `192.168.0.1`)
- **포트 번호**: 하나의 IP 주소 내에서 여러 서비스 식별 (예: HTTP는 80, HTTPS는 443)

---

## 3. 클라이언트-서버 모델

- **서버(Server)**: 서비스를 제공하는 프로그램
- **클라이언트(Client)**: 서비스를 요청하는 프로그램
- **소켓(Socket)**: 클라이언트와 서버 간 통신 인터페이스

---

## 4. 소켓 프로그래밍

네트워크 통신을 위해 소켓을 생성하고 데이터를 송수신한다.

### 주요 함수 (C 언어 기준)

#### 서버 측

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0); // 소켓 생성
bind(sockfd, ...);       // IP 주소와 포트 연결
listen(sockfd, 5);       // 연결 요청 대기
int connfd = accept(sockfd, ...); // 연결 수락
read(connfd, ...);       // 데이터 읽기
write(connfd, ...);      // 데이터 쓰기
```

#### 클라이언트 측

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0); // 소켓 생성
connect(sockfd, ...);     // 서버에 연결 요청
write(sockfd, ...);       // 데이터 쓰기
read(sockfd, ...);        // 데이터 읽기
```

---

## 5. TCP vs UDP

| 항목 | TCP | UDP |
|------|-----|-----|
| 연결 방식 | 연결 지향 | 비연결 지향 |
| 신뢰성 | 높음 (데이터 손실 없음) | 낮음 (데이터 유실 가능) |
| 속도 | 느림 | 빠름 |
| 사용 예 | 웹, 이메일 등 | 스트리밍, 온라인 게임 등 |

---

## 6. 네트워크 바이트 순서 (Byte Order)

서로 다른 시스템 간 데이터 전송 시 바이트 순서 통일 필요:
- **Big-endian**: 네트워크 바이트 순서
- **Little-endian**: x86 시스템 기본 방식

### 변환 함수

- `htons()`, `htonl()` : 호스트 → 네트워크
- `ntohs()`, `ntohl()` : 네트워크 → 호스트

---

## 7. inet 관련 함수

IP 주소와 문자열 간 변환을 위한 함수:

```c
inet_pton(AF_INET, "127.0.0.1", &addr); // 문자열 → 바이너리
inet_ntop(AF_INET, &addr, str, sizeof(str)); // 바이너리 → 문자열
```

---

