#ifndef __LED_H__
#define __LED_H__

#include "../commom/def.h"

// 포트에 대한 설정 (방향 - 출력)
#define LED_DDR     DDRD
#define LED_PORT    PORTD

// // 함수의 원형 선언 
// void GPIO_Output(uint8_t data); // LED 포트에 8비트 데이터를 매개변수로 받음
// void ledInit();
// void ledShift(uint8_t i, uint8_t *data); // 포인터 선언

typedef struct 
{
    volatile uint8_t    *port;
    uint8_t             pinNumber;
}LED;

//void ledInit(LED *led);
void ledInit();
//void ledOn(LED *led);
void ledOn();
void ledOff(LED *led);

void LeftToRightShift(LED *led);
void RightToLeftShift(LED *led);


// void ledLeftShift(LED *led);
// void ledRightShift(LED *led);
void ledFlower(LED *led);
void ledEven(LED *led); // 짝수
void ledOdd(LED *led); // 홀수

#endif /* __LED_H__ */
 


