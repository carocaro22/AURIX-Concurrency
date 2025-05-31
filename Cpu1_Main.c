#include "App_Config.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

extern IfxCpu_syncEvent g_cpuSyncEvent;
extern volatile uint32 g_spinlock;

void core1_main(void)
{
    IfxCpu_enableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    while (1)
    {
        while (!IfxCpu_setSpinLock(&g_spinlock, 1000))
        {
        }
        slow_print("Greetings from CPU1...\r\n");
        IfxCpu_resetSpinLock(&g_spinlock);
    }
}
