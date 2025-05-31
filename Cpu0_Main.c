#include "App_Config.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

extern volatile uint32 g_spinlock;
IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;

void core0_main(void)
{
    IfxCpu_enableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    initUART();
    initLEDs();
    turnOnLEDs();

    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    while (1)
    {
        while (!IfxCpu_setSpinLock(&g_spinlock, 1000))
        {
        }
        slow_print("Hello from CPU0...\r\n");
        IfxCpu_resetSpinLock(&g_spinlock);
    }
}
