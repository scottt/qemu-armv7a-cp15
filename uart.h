#pragma once

#define UARTDR      UART_PHYS
#define UARTFR      0x18
#define UARTFR_TXFF (1 << 5)

void putc(char c);
