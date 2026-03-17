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
![Microchip Studio](https://img.shields.io/badge/IDE-Microchip%20Studio-orange?style=flat)

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

민우님의 `ap.c` 코드에 적용된 핵심 하드웨어 설정 내용입니다.

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
- **Power**: 5V DC Supply

---

## 🔧 Trouble Shooting

- **문제 1: 물리적 버튼의 채터링 현상**
  - 버튼 입력 시 신호가 튀어 풍량 단계가 단번에 여러 번 건너뛰는 문제 발생.
  - ✅ **해결**: `_delay_ms(50)`를 이용한 소프트웨어적 디바운싱 로직과 `prevButtonData` 변수를 활용한 상태 변화 감지 로직을 구현하여 입력 무결성을 확보했습니다.

- **문제 2: 16비트 타이머 주기 설정**
  - 서보 모터 구동을 위한 정확한 50Hz(20ms) 주기를 맞추는 데 어려움이 있었음.
  - ✅ **해결**: 데이터시트의 공식($f_{PWM} = \frac{f_{clk\_I/O}}{N \cdot (1 + TOP)}$)을 활용하여 분주비 64와 ICR1 값을 4999로 산출, 정확한 주기를 구현했습니다.

---

## 🎥 시연 영상
[선풍기 제어 시스템 작동 영상](여기에_유튜브_링크_삽입)
