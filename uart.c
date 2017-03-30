#include "uart.h"

int *uart_phys = (int *) (UART_PHYS);
int *uart_busy = (int *) (UART_PHYS + UARTFR);

void putc(char c)
{
	/* If the FIFO is full, wait before pushing data to the UART */
	while (*uart_busy & UARTFR_TXFF);

	*uart_phys = c;

	/* Add the carriage return in case of a line feed character */
	if (c == '\n') {
		putc('\r');
	}
}
