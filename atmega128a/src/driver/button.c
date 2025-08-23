#include "button.h"

void buttonInit(BUTTON *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNumber)
{
    button->ddr = ddr;
    button->pin = pin;
    button->btnPin = pinNumber;
    button->prevState = RELEASED;   // 초기화 상태로 아무것도 안누른 상태 
    *button->ddr &= ~(1 << button->btnPin);   // 버튼 핀을 입력으로 설정  
}

// BUTTON *button --> ddr, pin 주소를 받기 위해서 
uint8_t buttonGetState(BUTTON *button)
{
    uint8_t curState = *button->pin & (1<<button->btnPin);  // 버튼의 상태를 읽어옴 

    if((curState == PUSHED) && (button->prevState == RELEASED)) // 버튼을 안누른 상태에서 누르면
    {
        _delay_ms(50);              // debounce code 
        button->prevState = PUSHED; // 버튼의 상태를 누름으로 변경 
        return ACT_PUSH;            // 버튼이 눌렀음을 반환
    }
    else if((curState != PUSHED) && (button->prevState == PUSHED))  // 버튼을 누른 상태에서 손을 떼면
    {
        _delay_ms(50);
        button->prevState = RELEASED;   // 버튼 상태를 안누름으로 변경 
        return ACT_RELEASE;             // 버튼이 떨어졌음을 반환 
    }
    return NO_ACT;
}