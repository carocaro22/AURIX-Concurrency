#ifndef UART_H_
#define UART_H_

#include "IfxAsclin_Asc.h"
#include "Ifx_Shell.h"
#include "IfxStdIf.h"

void initUART(void);
void print_line(char *text);
void print_character(char c);
void slow_print(const char *msg);
void busy_wait_ms(uint32 ms);

#endif /* UART_H_ */
