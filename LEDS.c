/*
 * LEDS.c
 *
 *  Created on: 19 de mai. de 2025
 *      Author: carolina
 */

#include "IfxPort.h"
#include "LEDS.h"

void initLEDs(void)
{
    // Configure P0.1, P0.3, P0.5, P0.7, P0.9 as push-pull outputs
    IfxPort_setPinModeOutput(&MODULE_P15, 3, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(&MODULE_P15, 2, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(&MODULE_P02, 0, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(&MODULE_P01, 1, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(&MODULE_P10, 4, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
}

void turnOnLEDs(void)
{
    // Optional: Set all to low initially
    IfxPort_setPinLow(&MODULE_P00, 1);
    IfxPort_setPinLow(&MODULE_P00, 3);
    IfxPort_setPinLow(&MODULE_P00, 5);
    IfxPort_setPinLow(&MODULE_P00, 7);
    IfxPort_setPinLow(&MODULE_P00, 9);
//
//    IfxPort_setPinHigh(&MODULE_P00, 1);
//    IfxPort_setPinHigh(&MODULE_P00, 3);
//    IfxPort_setPinHigh(&MODULE_P00, 5);
//    IfxPort_setPinHigh(&MODULE_P00, 7);
//    IfxPort_setPinHigh(&MODULE_P00, 9);
}
