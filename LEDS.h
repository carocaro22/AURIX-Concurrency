#ifndef LEDS_H_
#define LEDS_H_

#include "IfxPort_PinMap.h"

#define LED_1                   IfxPort_P00_5
#define LED_2                   IfxPort_P00_6
//#define BUTTON_1                IfxPort_P00_7

void initLEDS(void);
void turnLED1On(void);
void turnLED1Off(void);
void turnLED2On(void);
void turnLED2Off(void);

#endif /* LEDS_H_ */
