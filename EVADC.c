#include "IfxEvadc_Adc.h"
#include "EVADC.h"
#include "IfxPort.h"                 // <<< for the pin-config routines

static IfxEvadc_Adc         g_evadc;           // EVADC module handle
static IfxEvadc_Adc_Group   g_adcGroup8;       // EVADC1.Group0 (API GroupId = 8)
static IfxEvadc_Adc_Channel g_adcChannel7_AN39; // Channel index 7 → AN39


void initEVADC_AN39(void)
{
    /*--------------------------------------------------
     * 0) Configure P40.9 as analog-input pad
     *-------------------------------------------------*/
    IfxPort_setPinMode(&MODULE_P40, 9, IfxPort_Mode_inputNoPullDevice);
    IfxPort_setPinPadDriver(&MODULE_P40, 9, IfxPort_PadDriver_cmosAutomotiveSpeed1);

    /*--------------------------------------------------
     * 1) EVADC module init
     *-------------------------------------------------*/
    IfxEvadc_Adc_Config adcConfig;
    IfxEvadc_Adc_initModuleConfig(&adcConfig, &MODULE_EVADC);
    IfxEvadc_Adc_initModule(&g_evadc, &adcConfig);

    /*--------------------------------------------------
     * 2) EVADC1.Group0 → API GroupId_8
     *-------------------------------------------------*/
    {
        IfxEvadc_Adc_GroupConfig groupConfig;
        IfxEvadc_Adc_initGroupConfig(&groupConfig, &g_evadc);
        groupConfig.groupId = IfxEvadc_GroupId_8;
        IfxEvadc_Adc_initGroup(&g_adcGroup8, &groupConfig);
    }

    /*--------------------------------------------------
     * 3) Channel 7 (AN39) → resultReg 7
     *-------------------------------------------------*/
    {
        IfxEvadc_Adc_ChannelConfig channelConfig;
        IfxEvadc_Adc_initChannelConfig(&channelConfig, &g_adcGroup8);

        channelConfig.channelId      = (IfxEvadc_ChannelId)7;  // index 7 == AN39
        channelConfig.resultRegister = (IfxEvadc_ChannelResult)7;

        IfxEvadc_Adc_initChannel(&g_adcChannel7_AN39, &channelConfig);
    }

    /*--------------------------------------------------
     * 4) (Optional) continuous / background scan
     *-------------------------------------------------*/
    // IfxEvadc_Adc_enableBackgroundScan(&g_adcGroup8);
}
