#include "uart.h"

typedef __builtin_va_list va_list;
#define va_start(ap, X)     __builtin_va_start(ap, X)
#define va_arg(ap, type)    __builtin_va_arg(ap, type)
#define va_end(ap)          __builtin_va_end(ap)

static void print_str(char *s)
{
	while (*s) {
		putc(*s++);
	}
}

static void print_num(unsigned long long value, int base)
{
	char digits[] = "0123456789abcdef";
	/* This is not working with arm-none-eabi-gcc v5.1, since memset is not
	 * found.
	 * char buf[32] = { 0 };*/
	char buf[32];
	int i = sizeof(buf) - 2, j;

	/* Set the buffer to 0. See problem of before. */
	for (j = 0; j < 32; j++) {
		buf[j] = 0;
	}

	do {
		buf[i--] = digits[value % base];
		value /= base;
	}
	while (value);

	print_str(&buf[i + 1]);
}

void printf(const char *fmt, ...)
{
	va_list ap;
	char *str;
	int base;
	int has_long;
	int alt_form;
	unsigned long long val;

	va_start(ap, fmt);

	for (; *fmt; fmt++) {
		if (*fmt != '%') {
			putc(*fmt);
			continue;
		}
		fmt++;

		if (*fmt == '#') {
			fmt++;
			alt_form = 1;
		} else {
			alt_form = 0;
		}

		if (*fmt == 'l') {
			fmt++;
			if (*fmt == 'l') {
				fmt++;
				has_long = 2;
			} else {
				has_long = 1;
			}
		} else {
			has_long = 0;
		}

		switch (*fmt) {
		case 'x':
		case 'p':
			base = 16;
			goto convert_number;
		case 'd':
		case 'i':
		case 'u':
			base = 10;
			goto convert_number;
		case 'o':
			base = 8;
			goto convert_number;

		      convert_number:
			switch (has_long) {
			case 0:
				val = va_arg(ap, unsigned int);
				break;
			case 1:
				val = va_arg(ap, unsigned long);
				break;
			case 2:
				val = va_arg(ap, unsigned long long);
				break;
			}

			if (alt_form && base == 16) {
				print_str("0x");
			}

			print_num(val, base);
			break;

		case 's':
			str = va_arg(ap, char *);
			print_str(str);
			break;
		case '%':
			putc(*fmt);
			break;
		default:
			putc('%');
			putc(*fmt);
			break;
		}
	}

	va_end(ap);
}
