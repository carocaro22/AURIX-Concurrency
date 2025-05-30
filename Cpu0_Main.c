#include "App_Config.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;

void core0_main(void)
{
    IfxCpu_enableInterrupts();

    // Disable CPU and safety watchdogs
    // These watchdogs are enabled by default and would reset the system
    // if we loop indefinitely without servicing them
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    // UART should only be initialized by one core (e.g., CPU0)
    // to prevent concurrent configuration or reinitialization
    initUART();

    initLEDs();
    turnOnLEDs();

    // Emit a sync event so that CPU1 knows UART is initialized
    // This is NOT meant to synchronize output — it just prevents CPU1
    // from writing to the UART before it's ready
    IfxCpu_emitEvent(&g_cpuSyncEvent);

    // Wait for CPU1 to catch up before starting the loop
    // Again, this is just to make sure initialization order is correct
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    while (1)
    {
        // This function prints each character slowly,
        // which increases the chance of interleaving output
        slow_print("Hello from CPU0...\r\n");

        // Fixed delay between prints
        // You can randomize this for a more chaotic UART conflict
        // busy_wait_ms(200);
    }
}
