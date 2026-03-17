# 🌀 Fan Control System – AVR (ATmega128)

ATmega128 MCU를 활용하여 설계한 **선풍기 제어 시스템**입니다.  
Timer/Counter 레지스터 설정을 통해 DC 팬 모터와 서보 모터를 정밀하게 제어하며
시스템의 풍량 상태를 LED Bar와 FND(7-Segment)로 시각화하는 임베디드 제어 구현을 목표로 했습니다.

<p align="left"> 
  <a href="#-프로젝트-개요">프로젝트 개요</a> • 
  <a href="#-skill-stack">Skill Stack</a> • 
  <a href="#-주요-기능">주요 기능</a> • 
  <a href="#-레지스터-설정-상세">레지스터 설정 상세</a> • 
  <a href="#-trouble-shooting">Trouble Shooting</a> • 
  <a href="#-시연-영상">시연 영상</a>
</p>

---

## 📌 프로젝트 개요
- **플랫폼/언어**: ATmega128 (AVR), Embedded C (Microchip Studio)
- **핵심 목표**
  - **PWM 제어**: 레지스터 직접 설정을 통한 DC 모터 속도 및 서보 모터 각도 제어
  - **상태 시각화**: LED Bar와 FND를 활용한 현재 풍량 단계 표시
  - **입력 처리**: Push Button을 활용한 모드 및 풍량 토글 제어

---

## 🛠 Skill Stack

![C](https://img.shields.io/badge/C-A8B9CC?style=flat&logo=c&logoColor=white)
![AVR](https://img.shields.io/badge/MCU-ATmega128-blue?style=flat)
![PWM](https://img.shields.io/badge/Control-PWM-red?style=flat)
![VS Code](https://img.shields.io/badge/VS%20Code-007ACC?style=flat&logo=visual-studio-code&logoColor=white)

---

## ✨ 주요 기능

### 1. DC 팬 모터 속도 제어 (Timer/Counter 0)
- **8bit Fast PWM** 모드를 사용하여 팬 모터의 속도를 조절합니다.
- 버튼 입력에 따라 `OCR0` 값을 변경하여 풍량을 Off / 1단계 / 2단계 / 3단계로 가변 제어합니다.

### 2. 서보 모터 회전 제어 (Timer/Counter 1)
- **16bit Fast PWM (TOP=ICR1)** 모드를 활용하여 50Hz(20ms) 주기를 생성합니다.
- 서보 모터의 회전 기능을 구현하며, `OCR1A` 값을 조절하여 선풍기의 헤드 방향을 제어합니다.

### 3. 풍량 시각화 (LED Bar & FND)
- **LED Bar**: 풍량 단계에 따라 LED 개수가 점등되는 시각적 인디케이터 역할을 합니다.
- **FND (7-Segment)**: 현재 풍량 단계를 숫자(0~3)로 명확하게 표시합니다.

---

## ⚙️ 레지스터 설정 상세 (Register Configuration)

1. 타이머0 (Fan Motor PWM)

TCCR0 (Timer/Counter Control Register)

Fast PWM 모드 설정: WGM01=1, WGM00=1
클럭 분주비 설정: CS02=0, CS01=1, CS00=1 (64 분주)


OCR0 (Output Compare Register)

PWM Duty 값 설정
70% 속도: OCR0 = 179
100% 속도: OCR0 = 255


2. 타이머1 (Servo Motor)

TCCR1A, TCCR1B

Fast PWM 모드, TOP=ICR1
16bit 타이머로 20ms 주기 생성


ICR1 (Input Capture Register)

주기 설정: ICR1 = 39999 (20ms@8MHz, 8분주)


OCR1A (Output Compare Register)

서보 각도 제어 (1ms~2ms 펄스)


3. 포트 레지스터

DDRA, DDRB, DDRD, DDRG: 입출력 방향 설정
PORTA, PORTB, PORTD, PORTG: 데이터 읽기/쓰기

### DC Fan (Timer 0)
* **TCCR0**: `(1 << WGM00) | (1 << COM01) | (1 << WGM01) | (1 << CS02)`
  - Fast PWM 모드 선택
  - Non-inverting Compare Output 모드
  - 256분주 설정

### Servo Motor (Timer 1)
* **TCCR1A/B**: `WGM13, WGM12, WGM11` (Mode 14, Fast PWM with ICR1 as TOP)
* **ICR1**: `4999` (16MHz 클럭 기준 64분주 사용 시 50Hz 주기 생성)
* **동작 원리**: `OCR1A` 값을 125~625 범위 내에서 조절하여 0.5ms~2.5ms의 Duty Cycle을 생성, 서보 각도를 제어합니다.



---

## 🔧 사용 부품
- **MCU**: ATmega128
- **Motor**: DC Fan Motor, SG90 Servo Motor
- **Display**: FND (4-Digit 7-Segment), LED Bar (8-bit)
- **Input**: Push Button Switch (x5)

---

## 🔧 Trouble Shooting

- **문제 1: 서보모터 반복 회전**
  - 4번 버튼(회전버튼)을 눌렀을 때 회전을 1회만 하는 문제 발생.
  - ✅ **해결**: `회전 동작 루프가 While문 밖에 있는 걸 발견 후 While문 안으로 위치 변경

- **문제 2: 서보모터 급속 복귀**
  - 회전모드에서 모터의 왼/오른쪽 이동 속도가 다른 문제 발생.
  - ✅ **해결**: 서보모터 회전 방향을 알려주는 변수 direction이 while문 안에 있으면 반복할 때 마다 새로 생성되고 초기화 되기 떄문에 유지가 안되는 것을 확인 후 한 번만 초기화되고 이후에는 이전 값을 계속 기억하도록 static 변수로 변경

---

## 🎥 시연 영상
[선풍기 제어 시스템 작동 영상](https://youtu.be/8TnaFotBZME)
