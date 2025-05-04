#include "TASKS.h"

#define LED1_BLINKY_PERIOD_MS (250)

SemaphoreHandle_t xMutex;

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
    print_line("Created task 2.");

    print_line("Starting Scheduler");
    print_line("--------------------------------------------------");
    vTaskStartScheduler();
}

void task_1(void *arg)
{
    while (1)
    {
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE)
        {
            slow_print("Hello from Task 1.\r\n");
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task_2(void *arg)
{
    while (1)
    {
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE)
        {
            slow_print("Greetings from Task 2.\r\n");
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void slow_print(const char *msg)
{
    for (int i = 0; msg[i] != '\0'; i++) {
        print_character(msg[i]);  // Char-by-char print
        busy_wait_ms(200); // Artificial delay between chars, Human typing feel, 5 chars/sec
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

