#include "LEDS.h"

void initLEDS(void)
{
    IfxPort_setPinModeOutput(LED_1.port, LED_1.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(LED_2.port, LED_2.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    //IfxPort_setPinModeInput(BUTTON_1.port, BUTTON_1.pinIndex, IfxPort_InputMode_pullUp);
}

void turnLED1On(void)
{
    IfxPort_setPinState(LED_1.port, LED_1.pinIndex, IfxPort_State_high);
}
void turnLED1Off(void)
{
    IfxPort_setPinState(LED_1.port, LED_1.pinIndex, IfxPort_State_low);
}
void turnLED2On(void)
{
    IfxPort_setPinState(LED_2.port, LED_2.pinIndex, IfxPort_State_high);
}
void turnLED2Off(void)
{
    IfxPort_setPinState(LED_2.port, LED_2.pinIndex, IfxPort_State_low);
}


