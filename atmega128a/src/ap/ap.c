#include "ap.h"

void apInit()
{
    // 당분간 비워둘게요
}


void apMain() // add servo toggle mode
{
    uint8_t buttonData, prevButtonData;

    DDRA = 0xff; // FND
    DDRB |= (1 << PB4) | (1 << PB5);
    DDRD = 0xff; // LED

    // button 입력 설정 (GPORT)
    DDRG &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4));

    // Fan: Timer0 (8bit fast pwm, 256분주)
    TCCR0 |= (1 << WGM00) | (1 << COM01) | (1 << WGM01) | (1 << CS02);

    // Servo: Timer1 (16bit fast pwm, TOP -> ICR1, 64분주, 주기 = 20ms = 50Hz)
    TCCR1A |= (1 << COM1A1) | (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);
    ICR1 = 4999; // TOP 값 (16MHz / 64 = 250kHz, 250kHz / 5000 = 50Hz -> 20ms주기)
    // OCR1A = 2500;

    uint8_t sevo_state = 0;     // 서보 모터 동작 상태 (0 = OFF, 1 = ON)
    int sevo_count = 0;         // 서보 위치 값  (PWM duty 조절)

    while (1)
    {
        buttonData = PING;   // 현재 버튼 입력 읽기 

        if (sevo_state == 1) // 서브모터 활성화 1, 비활성화 0
        {
            static int direction = 1;   // 1이면 증가, -1이면 감소
                                        // 왜 static을 쓰는지? direction 변수가 while(1) 루프 안에 있으면, 매 반복마다 새로 생성되고 초기화돼서 값이 유지되지 않음
                                        // static을 쓰면 이 변수는 한 번만 초기화되고, 이후엔 이전 값을 계속 기억

            if (sevo_count >= 600) // 최대 도달 시 방향 전환
                direction = -1;

            else if (sevo_count <= 100) // 최소 도달 시 방향 전환
                direction = 1;

            OCR1A = sevo_count;          // 서보 모터 위치 설정
            sevo_count += direction ; // 방향에 따라 증가 또는 감소 (속도 조절)
            _delay_ms(10);               // 10ms 대기 (서보 동작 딜레이)
        }

        // 버튼 1
        if ((buttonData & (1 << 0)) == 0)
        {
            PORTA = 0x06; // 1
            PORTD = 0x03;
            OCR0 = 100;
        }

        // 버튼 2
        if ((buttonData & (1 << 1)) == 0)
        {
            PORTA = 0x5B; // 2
            PORTD = 0x1f;
            OCR0 = 178;
        }

        // 버튼 3
        if ((buttonData & (1 << 2)) == 0)
        {
            PORTA = 0x4F; // 3
            PORTD = 0xff;
            OCR0 = 255;
        }

        // 버튼 4
        if (((prevButtonData & (1 << 3)) != 0) && ((buttonData & (1 << 3)) == 0))
        { 
            sevo_state = !sevo_state; // 토글
        }

        if ((buttonData & (1 << 4)) == 0)
        {
            PORTA = 0x00;
            PORTD = 0x00;
            OCR0 = 0;
            sevo_state = 0;
        }

        prevButtonData = buttonData; // 이전 상태 저장
        _delay_ms(1);
    }
}





// void apMain()
// {
//     LCD_Init();

//     // LCD_GotoXY(0,0);
//     // LCD_WriteString("Hello LCD");
//     // LCD_GotoXY(1,0);
//     // LCD_WriteString("Hello AVR");

//     char buff[30];
//     sprintf(buff, "Hello ATmega128A");  // sprintf -> "" 안에 있는 놈을 buff안에 집어넣는 놈 
//     LCD_WriteStringXY(0,0,buff);
//     uint16_t count = 0;

//     while (1)
//     {
//         sprintf(buff, "Count : %d", count++);
//         LCD_WriteStringXY(1,2,buff);
//         _delay_ms(100);
//     }
    
// }


// void apMain()
// {

//     stdout = &OUTPUT;
    
//     UART_Init();   
//     sei();

//     while (1)
//     {
//         if(rxFlag == 1)
//         {
//             rxFlag = 0;             
//             printf(rxBuff);
//         }
//     }        
// }




// void apMain()
// {
//     LED_DDR = 0xff;

//     // 버튼 관련 변수선언 (기능별 분류)
//     BUTTON btnOn;
//     BUTTON btnOff;
//     BUTTON btnToggle;

//     buttonInit(&btnOn, &BUTTON_DDR, &BUTTON_PIN, BUTTON_ON);    // 변수주소, DDR주소, PIN주소, 2번핀
//     buttonInit(&btnOff, &BUTTON_DDR, &BUTTON_PIN, BUTTON_OFF);
//     buttonInit(&btnToggle, &BUTTON_DDR, &BUTTON_PIN, BUTTON_TOGGLE);

//     while (1)
//     {
//         if(buttonGetState(&btnOn) == RELEASED)
//         {
//             LED_PORT = 0xff;
//         }
//         if(buttonGetState(&btnOff) == RELEASED)
//         {
//             LED_PORT = 0x00;
//         }
//         if(buttonGetState(&btnToggle) == RELEASED)
//         {
//             LED_PORT ^= 0xff;
//         }
//     }
// }

// ISR(INT4_vect)
// {
//     PORTD = 0xff;
// }

// ISR(INT5_vect)
// {
//     PORTD = 0x00;
// }

// ISR(TIMER0_OVF_vect)
// {
//     LED_PORT ^= LED_PORT;
// }   // 이게 있으면 PORTD = ~PORTD; 필표없음

// void apMain()
// {
//     ledInit();
//     DDRD = 0xff;    // D포트 출력

//     sei();      // 전역 인터럽트 enable

//     //EICRB = 0x0E;   // INT4 falling edge, INT5 rasing edge
//     EICRB = (1<<ISC51) | (1<<ISC50) | (1<<ISC41);   // 0x0E와 같은 것

//     //EIMSK = 0x30;   // INT4, INT5 Interrupt Enable
//     EIMSK = (1<<INT5) | (1<<INT4); // 0x30과 같은 것

//     while (1)
//     {

//     }

// }

// void apMain()
// {
//     DDRD = 0xff;    // 주파수를 보기 위해서 D포트 출력
//     TCCR0 |= (1<<CS02) | (1<<CS00);
//     TCNT0 = 131;
//     //DDRB = 0xff;    // PB4를 통해서 주파수를 출력해야 하니깐
//     //TCCR0 = 0x1C;   // 레지스터 셋팅 (CTC 모드, Toggle 모드, 분주비 64)
//     //TCCR0 = 0x1D;   // 레지스터 셋팅 (CTC 모드, Toggle 모드, 분주비 128)
//     //TCCR0 |= (1<<WGM01) | (1<<COM01) | (1<<CS02);     // TCCR0 = 0x1C 와 같음

//     //OCR0 = 124;   // 60hz
//     //OCR0 = 249;     // 250hz

//     while (1)
//     {
//         while ((TIFR & 0x01 /*0x02*/) == 0)
//         {

//         };
//         PORTD = ~PORTD;
//         TCNT0 = 131;
//         TIFR = 0x01;
//         // TIFR = 0x02;
//         //OCR0 = 124;   // 64hz
//         //OCR0 = 249;     // 250hz

//     }

// }

// void apMain()
// {
//     //DDRB = 0xff;        // B포트 전체 출력
//     DDRB |= (1<<PB4);   // PB4 포트만 출력 설정

//     TCCR0 |= (1<<WGM00) | (1<<COM01) | (1<<WGM01) | (1<<CS02);      // TCCR0 = 0x6C; 와 같음
//     //TCCR0 = 0x6C;

//     OCR0 = 255;

//     while (1)
//     {
//         // for(uint8_t i = 0;i <= 255;i++)
//         // {
//         //     OCR0 = i;
//         //     _delay_ms(10);
//         // }
//     }

// }

// void apMain()
// {
//     DDRB |= (1<<PB5);   // PB5 포트만 출력

//     // 16bit past PWM 설정, 64분주, 50Hz
//     TCCR1A |= (1<<COM1A1) | (1<< WGM11);
//     TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);

//     ICR1 = 4999;    // TOP값
//     //OCR1A = 2700;   // 50%

//     while (1)
//     {
//       OCR1A = 125;  // -90 degree
//       _delay_ms(1000);
//       OCR1A = 345;
//       _delay_ms(1000);
//       OCR1A = 590;  // +90 degree
//       _delay_ms(1000);
//     }

// }

// void apMain()
// {
//   // FND 숫자 패턴 (0~2)
//   const uint8_t FND[3] =
//       {
//           0b11000000, // 0
//           0b11111001, // 1
//           0b10100100  // 2
//       };

//   // 디바운스 버튼 (PG0~PG4)
//   uint8_t read_buttons_debounced()
//   {
//     uint8_t first = ~PING & 0x1F;
//     _delay_ms(20);
//     uint8_t second = ~PING & 0x1F;
//     return first & second;
//   }

//   // 팬 PWM 초기화 (Timer0 - OC0A = PB3)
//   void init_fan_pwm()
//   {
//     DDRB |= (1 << PB3);
//     TCCR1A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
//     TCCR1A = (1 << CS01) | (1 << CS00); // Prescaler 64
//     OCR0 = 0;
//   }

//   void set_fan_speed_raw(uint8_t value)
//   {
//     OCR0 = value; // 0~255
//   }

//   // 서보 PWM 초기화 (Timer1 - OC1B = PD4)
//   void init_servo_pwm()
//   {
//     DDRD |= (1 << PD4);                                 // OC1B 출력
//     TCCR1A = (1 << COM1B1) | (1 << WGM11);              // Fast PWM
//     TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8
//     ICR1 = 40000;                                       // TOP 값 = 20ms
//     OCR1B = 4000;                                       // 초기 각도 (0도)
//   }

//   void set_servo_angle(int angle)
//   {
//     uint16_t pulse = 3000 + ((angle + 90) * 1000) / 180; // 3000~7000
//     OCR1B = pulse;
//   }

//   // LED Shfit
//   void animate_led_shift()
//   {
//     // 왼쪽 시프트 (0001 → 0010 → 0100 → 1000)
//     for (uint8_t i = 0; i < 4; i++)
//     {
//       PORTD = (1 << i);
//       _delay_ms(100);
//     }

//     // 오른쪽 시프트 (1000 → 0100 → 0010 → 0001)
//     for (int8_t i = 2; i >= 0; i--)
//     {
//       PORTD = (1 << i);
//       _delay_ms(100);
//     }
//   }

//   int main(void)
//   {
//     // 포트 설정
//     DDRG &= ~0x1F; // PG0~PG4 입력
//     PORTG |= 0x1F; // 풀업
//     DDRA = 0xFF;   // FND 출력
//     PORTA = 0xFF;
//     DDRD |= 0x0F; // LED Bar 출력 (PD0~PD3)

//     // 초기화
//     init_fan_pwm();   // Timer0
//     init_servo_pwm(); // Timer1

//     bool servo_running = false;
//     int angles[] = {-90, 0, 90};
//     uint8_t angle_index = 0;

//     while (1)
//     {
//       uint8_t btn = read_buttons_debounced();

//       // 버튼 기능 처리

//       if (btn & (1 << 0))
//       { // 버튼 1
//         PORTA = FND[0];
//         PORTD &= ~0x0F;
//         set_fan_speed_raw(0);
//       }
//       else if (btn & (1 << 1))
//       { // 버튼 2
//         PORTA = FND[1];
//         PORTD = (PORTD & 0xF0) | 0x03; // LED 절반
//         set_fan_speed_raw(128);        // 팬 50%
//       }
//       else if (btn & (1 << 2))
//       { // 버튼 3
//         PORTA = FND[2];
//         PORTD |= 0x0F;
//         set_fan_speed_raw(255); // 팬 100%
//       }

//       if (btn & (1 << 3))
//         servo_running = true; // 버튼 4: 서보 시작
//       if (btn & (1 << 4))
//         servo_running = false; // 버튼 5: 서보 정지

//       // 서보모터 + LED

//       if (servo_running)
//       {
//         set_servo_angle(angles[angle_index]);
//         angle_index = (angle_index + 1) % 3;

//         animate_led_shift(); // 좌→우 시프트
//         _delay_ms(400);      // 서보 안정화 시간
//       }

//       _delay_ms(50); // 루프 딜레이
//     }
//   }
// }

// void apMain()
// {
//   uint8_t buttonData, prevButtonData = 0xFF; // 초기값: 전부 안 눌림
//   bool servoRepeat = false;
//   bool leftToRight = true;
//   uint8_t ledPattren = 0x01;

//   DDRA = 0xFF; // FND
//   DDRB |= (1 << PB4) | (1 << PB5);
//   DDRD = 0xFF;                                                     // LED
//   DDRG &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4)); // 버튼 입력
//   PORTG |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);

//   // 팬 - 8비트 PWM
//   TCCR0 |= (1 << WGM01) | (1 << WGM00) | (1 << COM01) | (1 << CS02);

//   // 서보 - 16비트 Fast PWM, 64분주, 50Hz
//   TCCR1A |= (1 << WGM11) | (1 << COM1A1);
//   TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);
//   ICR1 = 4999;
//   OCR1A = 2700; // 중간 위치

//   // uint8_t sevo_state=0;
//   // int sevo_count=0;

//   while (1)
//   {
//     // if(sevo_state == 1)
//     //     {
//     //         if(sevo_count == 500)
//     //         {
//     //             sevo_count = 0;
//     //         }

//     //         OCR1A = sevo_count;
//     //         sevo_count++;
//     //         _delay_ms(100);
//     //     }

//     // fan, fnd 동작
//     buttonData = PING;

//     if ((buttonData & (1 << 0)) == 0)
//     {
//       PORTA = 0x3F; // 0
//       PORTD = 0x00;
//       OCR0 = 0;
//     }
//     if ((buttonData & (1 << 1)) == 0)
//     {
//       PORTA = 0x06; // 1
//       PORTD = 0x0F;
//       OCR0 = 100;
//     }
//     if ((buttonData & (1 << 2)) == 0)
//     {
//       PORTA = 0x5B; // 2
//       PORTD = 0xFF;
//       OCR0 = 200;
//     }

//     // 4번째 버튼 눌림 순간 토글
//     if (((prevButtonData & (1 << 3)) != 0) && ((buttonData & (1 << 3)) == 0))
//     {
//       servoRepeat = !servoRepeat;
//     }

//     // if (servoRepeat)
//     // {
//     //   OCR1A = 125;
//     //   _delay_ms(700);

//     //   OCR1A = 400;
//     //   _delay_ms(700);

//     //   OCR1A = 625;
//     //   _delay_ms(700);

//     //   OCR1A = 400;
//     //   _delay_ms(700);

//     //   OCR1A = 125;
//     //   _delay_ms(700);
//     // }

//     // if ((buttonData & (1 << 4)) == 0)
//     // {
//     //   PORTA = 0x00;
//     //   PORTD = 0x00;
//     //   OCR0 = 0;
//     //   OCR1A = 2700;
//     //   servoRepeat = false;
//     //   continue;
//     // }
//     prevButtonData = buttonData;
//     //_delay_ms(1);

//     // 서보 & LED 시프트 루프
//     while (servoRepeat)
//     {
//       uint16_t servoPos[] = {125, 400, 625, 400, 125};
//       uint8_t led = 0x01;
//       bool dir = true;

//       for (int i = 0; i < 5 && servoRepeat; i++)
//       {
//         OCR1A = servoPos[i];

//         for (int j = 0; j < 70; j++)  // 약 700ms
//         {
//           // 중단 조건
//           buttonData = PING;
//           if ((buttonData & (1 << 4)) == 0)
//           {
//             PORTA = 0x00;
//             PORTD = 0x00;
//             OCR0 = 0;
//             OCR1A = 2700;
//             servoRepeat = false;
//             break;
//           }

//           PORTD = led;
//           _delay_ms(100);

//           // 시프트 방향
//           if (dir)
//           {
//             led <<= 1;
//             if (led == 0x80) dir = false;
//           }
//           else
//           {
//             led >>= 1;
//             if (led == 0x01) dir = true;
//           }
//         }
//       }
//       OCR1A = 2700;
//     }

//     _delay_ms(1);
//   }
// }
//   //}
// //}

// void apMain()
// {
//     uint8_t buttonData;

//     DDRA = 0xff;    // FND
//     DDRB |= (1<<PB4) | (1<<PB5);    // fan, servo 연결 핀
//     DDRD = 0xff;    // LED bar 연결된 곳

//     DDRG &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4));  // button
//     TCCR0 |= (1<<WGM00) | (1<<COM01) | (1<<WGM01) | (1<<CS02);  // fan 8bit setting
//     // 16bit past pwm 설정 64분주 50hz
//     TCCR1A |= (1<<COM1A1) | (1<<WGM11);
//     TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11 | (1<<CS10));

//     ICR1 = 4999;        // TOP 값
//     // OCR1A = 2500;

//     uint8_t sevo_state=0;
//     int sevo_count=0;

//     while (1)
//     {
//         if(sevo_state == 1)
//         {
//             if(sevo_count == 500)
//             {
//                 sevo_count = 0;
//             }

//             OCR1A = sevo_count;
//             sevo_count++;
//             _delay_ms(100);
//         }

//         buttonData = PING;

//         if((buttonData & (1<<0)) == 0)
//         {
//             PORTA = 0x3F;   // 0
//             PORTD = 0x00;
//             OCR0 = 0;
//         }

//         if((buttonData & (1<<1)) == 0)
//         {
//             PORTA = 0x06;   // 1
//             PORTD = 0x0f;
//             OCR0 = 127;
//         }

//         if((buttonData & (1<<2)) == 0)
//         {
//             PORTA = 0x5B;   // 2
//             PORTD = 0xff;
//             OCR0 = 255;
//         }

//         if((buttonData & (1<<3)) == 0)
//         {
//             sevo_state = 1;

//             OCR1A = 100;
//             _delay_ms(100);
//             OCR1A = 500;
//             _delay_ms(100);
//         }

//         if((buttonData & (1<<4)) == 0)
//         {

//         }

//     }
// }
