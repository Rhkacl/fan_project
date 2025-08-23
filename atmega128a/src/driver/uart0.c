#include "uart0.h"


void UART0_Init()
{
    // BaudRate 9600bps (통신속도)
    UBRR0H = 0x00;
    UBRR0L = 207;

    UCSR0A |= (1<<U2X0);    // 2배속 모드

    UCSR0B |= (1<<RXEN0);   // 수신가능
    UCSR0B |= (1<<TXEN0);   // 송신가능 

    // 비동기, 8bit data, 패리티비트 x, 1bit stopbit 사용     
    //UCSR0C |= 설정 필요 x, 초기값 사용 
}

void UART0_Transmit(unsigned char data)
{
    while (!(UCSR0A & (1<<UDRE0)));     // 송신 가능 대기, UDR이 비어있는지 확인 
    UDR0 = data;
}

unsigned char UART0_Receive()
{
    while (!(UCSR0A & (1<<RXC0)));      // 데이터 수신 대기 
    return UDR0;
}