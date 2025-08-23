#ifndef __AP_H__
#define __AP_H__


#include "../driver/led.h"
#include "../driver/button.h"
#include "../driver/lcd.h"
//#include "../driver/uart0.h"      // 폴링방식 UART 헤더
#include "../driver/uart0_int.h"    // 인터럽트 UART 헤더



void apInit();
void apMain();



#endif /* __AP_H__ */