
#include "src/ap/ap.h"

int main()
{
    apInit();
    apMain();
    
    while (1)
    {
        
    } 
}







// #include <stdio.h>
// #include <avr/io.h>
// #include <util/delay.h>


// int main()
// {
//     DDRD = 0xff;

//     while (1)
//     {
//         PORTD = 0x00; // 0b 0000 0000 Low
//         _delay_ms(500); // 0.5sec
//         PORTD = 0xff; // 0b 1111 1111 HIGH
//         _delay_ms(500); // 0.5sec
//     }
// }

// #define LED_DDR     DDRD
// #define LED_PORT    PORTD

// int main()
// {
//     LED_DDR = 0xff; // D포트를 출력으로 설정
//     //LED_DDR = 0b11111111; // 0xff 와 같은 것

//     while (1)
//     {
//         for(uint8_t i = 0;i < 8;i++)
//         {
//             LED_PORT = (1 << i);
//             _delay_ms(1000);
//         }
//     }   
// }

// uint8_t ledArr[]= {
//     0x00, // 0000 0000
//     0x80, // 1000 0000
//     0xC0, // 1100 0000
//     0xE0, // 1110 0000
//     0xF0, // 1111 0000
//     0xF8, // 1111 1000
//     0xFC, // 1111 1100
//     0xFE, // 1111 1110
//     0xFF, // 1111 1111
//     0x7F, // 0111 1111
//     0x3F, // 0011 1111
//     0x1F, // 0001 1111
//     0x0F, // 0000 1111
//     0x07, // 0000 0111
//     0x03, // 0000 0011
//     0x01, // 0000 0001
//     0x00, // 0000 0000  
// };

// int main()
// {
//     DDRD = 0xFF;
//     //uint8_t arrSize = sizeof(ledArr) / sizeof(ledArr[0]);
//     while (1)
//     {
//         for(uint8_t i = 0;i < arrSize;i++)
//         {
//             PORTD = ledArr[i];
//             _delay_ms(200);
//         }
//     } 
// }

// int main()
// {
//     DDRD = 0xFF;
//     uint8_t led = 0x00;

//     while (1)
//     {
//         // 점점 켜짐
//         //uint8_t led = 0x00;
//         for(uint8_t i = 0;i< 8;i++)
//         {
//             led |= (1 << (7 - i));
//             PORTD = led;
//             _delay_ms(500);
//         }

//         // 점점 꺼짐(왼쪽부터)
//         // for(uint8_t i = 0;i < 8;i++)
//         // {
//         //     led &= ~(1 << (7 - i));
//         //     PORTD = led;
//         //     _delay_ms(500);
//         // }

//         // 점점 꺼짐(오른쪽부터)
//         for(uint8_t i = 0;i < 8;i++)
//         {
//             led &= ~(1 << i);
//             PORTD = led;
//             _delay_ms(500);
//         }
//     }
// }

// #define LED_DDR     DDRD
// #define LED_PORT    PORTD

// int main()
// {
//     LED_DDR = 0xff; // 출력 설정 (0b11111111)

//     while (1)
//     {
//         // // LED를 왼쪽으로 이동하면서 켜고 끄기
//         // for(uint8_t i = 0;i < 4;i++)
//         // {
//         //     LED_PORT = ((0x01 << i) | (0x80 >> i));
//         //     _delay_ms(500);
//         // }
        
//         // // LED를 오른쪽으로 이동하면서 켜고 끄기
//         // for(uint8_t i = 0;i < 4;i++)
//         // {
//         //     LED_PORT = ((0x01 << (3 - i)) | (0x01 << (4 + i)));
//         //     _delay_ms(500);
//         // }

//         for(uint8_t i = 0; i < 8; i++)
//         {
//             LED_PORT = ((0x80 >> i) | (0x01 << i));
//             _delay_ms(100);
//         }
//     }
// }

// 함수를 만들어서 켜보자

// #define LED_DDR     DDRD
// #define LED_PORT    PORTD

// // LED 출력 함수
// void GPIO_Output(uint8_t data) // LED 포트에 8비트 데이터를 매개변수로 받음
// {
//     LED_PORT = data;  // 매개변수를 통해서 받은 데이터를 LED포트에 대입함
// }

// // LED 초기화 함수
// void ledInit()
// {
//     LED_DDR = 0xff; // 포트D의 모든 핀을 출력으로 설정
// }

// // 이동함수
// void ledShift(uint8_t i, uint8_t *data) // 포인터 선언 
// {
//     *data = (1 << i) | (1 << (7 - i));
// }

// int main()
// {
//     DDRD = 0xFF;
//     uint8_t led = 0x00;

//     while (1)
//     {
//         // 양쪽에서 켜짐
//         for(uint8_t i = 0;i < 4;i++)
//         {
//             led |= (1 << i);
//             led |= (1 << (7 - i));
//             PORTD = led;
//             _delay_ms(500);
//         }

//         // 안쪽에서 바깥쪽으로 꺼짐
//         for(int8_t i = 3;i >= 0;i--) // uint 부호가 없는 정수이기 때문에 (i>=0)이 항상 참이 되어 무한루프에 빠짐 int8_t로 변경 
//         {
//             led &= ~(1 << i);
//             led &= ~(1 << (7 - i));
//             PORTD = led;
//             _delay_ms(500);
//         }

//         // 바깥쪽에서 부터 꺼짐 
//         for(uint8_t i = 0;i < 4;i++)
//         {
//             led &= ~(1 << i);
//             led &= ~(1 << (7 - i));
//             PORTD = led;
//             _delay_ms(500);
//         }
//     }
// }

// 함수를 만듦 
// #include "../src/driver/led.h"
// #include "../src/driver/button.h"

// int main()
// {
//     ledInit();
//     uint8_t ledData = 0x81; //0b 1000 0001

//     while (1)
//     {
//         for(uint8_t i = 0;i < 8;i++)
//         {
//             ledShift(i, &ledData);
//             GPIO_Output(ledData);
//             _delay_ms(400);
//         }
//     }
// }

// int main()
// {
//     LED led;
//     led.port = &PORTD;
//     led.pinNumber = 0;

//     //ledInit(&led);

//     while (1)
//     {
//         for(led.pinNumber = 0; led.pinNumber < 8;led.pinNumber++) //uint8_t i =0;i < 8;i++
//         {
//             //led.pinNumber = i;
//             ledInit(&led);
//             ledOn(&led);
//             _delay_ms(500);
//             ledOff(&led);
//             _delay_ms(500);
//         }
//     }
    
// }

// int main()
// {
//     LED led;
//     led.port = &PORTD;
//     led.pinNumber = 0;

//     while (1)
//     {
//         // LeftShift 
//         for(led.pinNumber = 7;(int8_t)led.pinNumber >= 0;led.pinNumber--)
//         {
//             ledInit(&led);
//             ledOn(&led);
//             _delay_ms(500);
//         }

//         for(led.pinNumber = 7;(int8_t)led.pinNumber >= 0;led.pinNumber--)
//         {
//             ledOff(&led);   
//             _delay_ms(500);
//         }
//     }
// }


// int main()
// {
//     LED led;
//     led.port = &PORTD;
//     led.pinNumber = 0;
//     while (1)
//     {
//         // RightShift
//         for(led.pinNumber = 0; led.pinNumber < 8;led.pinNumber++) //uint8_t i =0;i < 8;i++
//         {
//             //led.pinNumber = i;
//             ledInit(&led);
//             ledOn(&led);
//             _delay_ms(500);
//         }
        
//         for(led.pinNumber = 0;led.pinNumber < 8;led.pinNumber++)
//         {
//             ledOff(&led);
//             _delay_ms(500);
//         }
//     }
// }

// int main()
// {
//     // Flower
//     LED led;
//     led.port = &PORTD;

//     while (1)
//     {
//         ledInit(&led);
//         ledFlower(&led);
//     }
    
// }

// int main()
// {
//     LED led;
//     led.port = &PORTD;

//     // flower
//     uint8_t leftSeq[4]  = {3, 2, 1, 0};
//     uint8_t rightSeq[4] = {4, 5, 6, 7};

//     while (1)
//     {
//         for (uint8_t i = 0;i < 4;i++)
//         {
//             // 왼쪽 LED
//             led.pinNumber = leftSeq[i];
//             ledInit(&led);
//             ledOn(&led);

//             // 오른쪽 LED
//             led.pinNumber = rightSeq[i];
//             ledInit(&led);
//             ledOn(&led);
//             _delay_ms(300);
//         }
//         for(uint8_t i = 0; i < 4;i++)
//         {
//             led.pinNumber = leftSeq[i];
//             ledInit(&led);
//             ledOff(&led);

//             led.pinNumber = rightSeq[i];
//             ledInit(&led);
//             ledOff(&led);
//             _delay_ms(300);
//         }
//     }
// }

// int main()
// {
//     LED led;
//     led.port = &PORTD;

//     while (1)
//     {
//         // 짝수 LED ON
//         for(led.pinNumber = 0;led.pinNumber < 8;led.pinNumber+=2)
//         {
//             ledInit(&led);
//             ledOn(&led);
//             _delay_ms(300);
//         }
        
//         // 짝수 LED OFF
//         for(led.pinNumber = 0;led.pinNumber < 8;led.pinNumber+=2)
//         {
//             ledInit(&led);
//             ledOff(&led);
//             _delay_ms(300);
//         }
//     }
    
// }

// int main()
// {
//     LED led;
//     led.port = &PORTD;

//     while (1)
//     {
//         // 홀수 LED ON
//         for(led.pinNumber = 1;led.pinNumber < 8;led.pinNumber+=2)
//         {
//             ledInit(&led);
//             ledOn(&led);
//             _delay_ms(300);
//         }
        
//         // 홀수 LED OFF
//         for(led.pinNumber = 1;led.pinNumber < 8;led.pinNumber+=2)
//         {
//             ledInit(&led);
//             ledOff(&led);
//             _delay_ms(300);
//         }
//     }
    
// }

// int main()
// {
//     LED led;
//     led.port = &PORTD;  

//     while (1)
//     {
//         // 홀수, 짝수 번갈아 ON OFF
//         ledInit(&led);
//         ledEven(&led);
//         ledOdd(&led);
//     }
    
// }


// int main()
// {
//     uint8_t fndNumber[] = {
//         0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67
//     };

//     // int count = 0; // 2바이트 (C언어에서는 4바이트) 
//     uint16_t count = 0;
//     DDRA = 0xff; // FND 연결한 포트

//     while (1)
//     {
//         PORTA = fndNumber[count];
//         count = (count + 1) % 10;

//         _delay_ms(500);
//     }
    
// }

// #define FND_DATA_DDR    DDRB    // 실질적인 데이터 포트
// #define FND_SELECT_DDR  DDRC    // 디지트 선택 포트 
// #define FND_DATA_PORT   PORTB
// #define FND_SELECT_PORT PORTC

// void FND_Display(uint16_t data); // 아래에 만든 함수의 원형 선언 

// int main()
// {
//     FND_DATA_DDR = 0xFF;    // 데이터 포트 출력으로 설정  (PORTB : 0 ~ 7)
//     FND_SELECT_DDR = 0xff;  // 디지트 선택 포트 출력 설정 (PORTC : 0 ~ 3)
//     FND_SELECT_PORT = 0x00; // 디지트 선택 포트 초기값 0 설정
    
//     uint16_t count = 0;     // 16bit(0 ~ 65535)
//     uint32_t timeTick = 0;  // 32bit (0 ~ 약 42억)
//     uint32_t prevTime = 0;  

//     while (1)
//     {
//         FND_Display(count);
//         if(timeTick - prevTime >= 100)   // 100ms가 지날 때 마다 count 값을 1 증가
//         {
//             prevTime = timeTick;        // 현재 시간을 prevTime에 저장
//             count++;
//         }
//         _delay_ms(1);                       // 1msec 대기
//         timeTick++;                         // timeTick을 1ms 증가 시킴
//     }
    
// }

// void FND_Display(uint16_t data)         // FND에 숫자를 표출하는 함수 
// {
//     static uint8_t position = 0;    //디지트 포지션
//     uint8_t fndData[10] =
//     {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};

//     switch (position) // 조건식(판단식) ==> 정수값
//     {
//     case 0: 
//         // 첫 번째 자리의 FND데이터를 출력하기 위해 0번핀 LOW, 1, 2, 3번핀 HIGH 
//         FND_SELECT_PORT &= ~(1<<0);     // 0번핀 LOW 
//         FND_SELECT_PORT |= (1<<1) | (1<<2) | (1<<3);     // 1, 2, 3번핀 HIGH 
//         // 입력한 데이터의 천의 자리 구해서 해당 FND데이터를 출력
//         FND_DATA_PORT = fndData[data/1000];
//         break;

//     case 1:
//         // 두번째 자리의 FND데이터를 출력하기 위해 0번핀 LOW, 0, 2, 3번핀 HIGH 
//         FND_SELECT_PORT &= ~(1<<1);     // 1번핀 LOW 
//         FND_SELECT_PORT |= (1<<0) | (1<<2) | (1<<3);     // 0, 2, 3번핀 HIGH 
//         // 입력한 데이터의 천의 자리 구해서 해당 FND데이터를 출력
//         FND_DATA_PORT = fndData[data/100%10];
//         break;

//     case 2:
//         // 세번째 자리의 FND데이터를 출력하기 위해 0번핀 LOW, 0, 1, 3번핀 HIGH 
//         FND_SELECT_PORT &= ~(1<<2);     // 2번핀 LOW 
//         FND_SELECT_PORT |= (1<<0) | (1<<1) | (1<<3);     // 0, 1, 3번핀 HIGH 
//         // 입력한 데이터의 천의 자리 구해서 해당 FND데이터를 출력
//         FND_DATA_PORT = fndData[data/10%10];
//         break;

//     case 3:
//         // 네번째 자리의 FND데이터를 출력하기 위해 3번핀 LOW, 0, 1, 2번핀 HIGH 
//         FND_SELECT_PORT &= ~(1<<3);     // 3번핀 LOW 
//         FND_SELECT_PORT |= (1<<0) | (1<<1) | (1<<2);     // 0, 1, 2번핀 HIGH 
//         // 입력한 데이터의 천의 자리 구해서 해당 FND데이터를 출력
//         FND_DATA_PORT = fndData[data%10];
//         break; 
//     }
//     position++;     // 다음 자리로 이동하기 위해서 position을 증가
//     position = position % 4;    // 4자리수 출력한 후에 다시 첫번째로 돌아가기 위해 
// }


// Button PORTG에 연결 2,3,4
// Pull-Up register 연결 

// int main()
// {
    
//     DDRD = 0xFF;        // LED 연결된 곳

//     //DDRG &= ~(1<<2);    // PORTG 2번핀을 입력으로 설정
//     PORTG |= (1<<2);    // 내부 풀업 저항 활성화 
//     DDRG &= ~((1<<2) | (1<<3) | (1<<4));    // PORTG 2번핀을 입력으로 설정 

//     while (1)
//     {
//         if(PING & (1<<2))
//         {
//             PORTD = 0x00;
//         }    
//         else
//         {
//             PORTD = 0xFF;
//         }
//     }
// }


// int main()
// {

//     DDRD = 0xFF; // 출력 설정  
//     PORTD = 0x00;

//     DDRG &= ~((1 << 2) | (1 << 3) | (1 << 4));  // 입력 설정 
//     PORTG |= (1 << 2) | (1 << 3) | (1 << 4);    // 내부 풀업 활성화 

//     uint8_t buttonData;

//     while (1)
//     {
//         buttonData = PING;

//         if((buttonData & (1 << 2)) == 0)
//         {
//             PORTD = 0xff;
//         }
//         if((buttonData & (1 << 3)) == 0)
//         {
//             //ledLeftShift();
//         }
//         if((buttonData & (1 << 4)) == 0)
//         {
//             PORTD = 0x00;
//         }    
//     }
    
// }
