#ifndef UART_H_
#define UART_H_

#include "IfxAsclin_Asc.h"
#include "Ifx_Shell.h"
#include "IfxStdIf.h"

void initUART(void);
void print_line(char *text);
void print_character(char c);

#endif /* UART_H_ */
