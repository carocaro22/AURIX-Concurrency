#include "TASKS.h"

#define LED1_BLINKY_PERIOD_MS (250)

void task_1(void *arg);
void task_2(void *arg);
void slow_print(const char *msg);
void busy_wait_ms(uint32 ms);

void start_tasks(void) {
    initUART();
    print_line("UART initialisation was successful!");

    xTaskCreate(task_1, "Task1", 256, NULL, 2, NULL);
    print_line("Created task 1.");
    xTaskCreate(task_2, "Task2", 256, NULL, 2, NULL);
    print_line("Created task 2");

    vTaskStartScheduler();
    print_line("Started Scheduler");
    print_line("--------------------------------------------------");
}

void task_1(void *arg)
{
    while (1)
    {
        slow_print("Hello from Task 1. \r\n");
    }
}

void task_2(void *arg)
{
    while (1)
    {
        slow_print("Greetings from Task 2 \r\n.");
    }
}

void slow_print(const char *msg)
{
    for (int i = 0; msg[i] != '\0'; i++) {
        print_character(msg[i]);
        busy_wait_ms(200);
    }
}

void busy_wait_ms(uint32 ms)
{
    volatile uint32 cycles = (10000 * ms); // (calculate this)
    while (cycles--) {
        __nop();  // No-operation to burn CPU cycles
    }
}

/* Required FreeRTOS callback, called in case of a stack overflow.
 * For the sake of simplicity, this function will loop indefinitely
 * and the root cause can be confirmed by using a debugger
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    while (1)
    {
        __nop();
    }
}

