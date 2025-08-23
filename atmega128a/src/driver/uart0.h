#ifndef __UART0_H__
#define __UART0_H__

#include "../commom/def.h"


void UART0_Init();
void UART0_Transmit(unsigned char data);
unsigned char UART0_Receive();



#endif /* __UART0_H__ */