#include "App_Config.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

extern IfxCpu_syncEvent g_cpuSyncEvent;

void core1_main(void)
{
    IfxCpu_enableInterrupts();

    // Watchdogs must be disabled here too, or CPU1 will reset
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    // Wait for CPU0 to finish UART initialization
    // This avoids accessing the peripheral before it's properly configured
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    while (1)
    {
        // Print a different message to demonstrate interleaving
        slow_print("Greetings from CPU1...\r\n");

        // Slightly different delay to make overlap more likely
        busy_wait_ms(150);
    }
}
