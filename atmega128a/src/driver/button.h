#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "../commom/def.h"

// Button PORTG에 연결 2,3,4
// Pull-Up 저항 연결 
#define LED_DDR         DDRD
#define LED_PORT        PORTD
#define BUTTON_DDR      DDRG
#define BUTTON_PIN      PING
#define BUTTON_ON       2
#define BUTTON_OFF      3
#define BUTTON_TOGGLE   4

enum {PUSHED, RELEASED};  
enum {NO_ACT, ACT_PUSH, ACT_RELEASE};

typedef struct _button
{
    volatile uint8_t    *ddr;   // 레지스터에 입력, 읽기 하는건 volatile을 붙여서 최적화 금지
    volatile uint8_t    *pin;   // pin이라는 레지스터에서 값을 읽어오기 때문에 volatile를 붙힘 
    uint8_t             btnPin;
    uint8_t             prevState;
}BUTTON;

void buttonInit(BUTTON *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNumber);
uint8_t buttonGetState(BUTTON *button);

#endif /* __BUTTON_H__ */