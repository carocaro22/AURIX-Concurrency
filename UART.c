#include "UART.h"

#define ISR_PRIORITY_ASCLIN_TX 8
#define UART_TX_BUFFER_SIZE 256

IfxStdIf_DPipe g_ascStandardInterface;
IfxAsclin_Asc g_asc;
uint8 g_uartTxBuffer[UART_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

IFX_INTERRUPT(asc0TxISR, 0, ISR_PRIORITY_ASCLIN_TX);
void asc0TxISR(void)
{
    IfxStdIf_DPipe_onTransmit(&g_ascStandardInterface);
}


void initUART(void)
{
    IfxAsclin_Asc_Config ascConf;
    IfxAsclin_Asc_initModuleConfig(&ascConf, &MODULE_ASCLIN0);
    // It is necessary to set interrupt priority, because the default is initialise it to to zero
    // which effectively means that that interrupt is disabled
    ascConf.interrupt.txPriority = ISR_PRIORITY_ASCLIN_TX;

    const IfxAsclin_Asc_Pins pins = {
            .cts        = NULL_PTR,
            .ctsMode    = IfxPort_InputMode_pullUp,
            .rx         = &IfxAsclin0_RXA_P14_1_IN,
            .rxMode     = IfxPort_InputMode_pullUp,
            .rts        = NULL_PTR,
            .rtsMode    = IfxPort_OutputMode_pushPull,
            .tx         = &IfxAsclin0_TX_P14_0_OUT,
            .txMode     = IfxPort_OutputMode_pushPull,
            .pinDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConf.pins = &pins;

    /* FIFO buffers configuration */
    ascConf.txBuffer = g_uartTxBuffer;
    ascConf.txBufferSize = UART_TX_BUFFER_SIZE;

    IfxAsclin_Asc_initModule(&g_asc, &ascConf);
    IfxAsclin_Asc_stdIfDPipeInit(&g_ascStandardInterface, &g_asc);
}

void print_line(char *text)
{
    IfxStdIf_DPipe_print(&g_ascStandardInterface, text);
    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\r\n");
}

void print_character(char c)
{
    char buf[2] = { c, '\0' };  // Single char string
    IfxStdIf_DPipe_print(&g_ascStandardInterface, buf);
}
