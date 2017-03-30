#include "cp15.h"

static void isb(void)
{
	__asm__("isb");
}

unsigned long cr_get(void)
{
	unsigned long t;
	__asm__ volatile ("mrc p15, 0, %[t], c1, c0, 0"
			: /* outputs  */ [t] "=r" (t)
			: /* inputs   */
			: /* clobbers */ "cc"
			);
	return t;
}

void cr_set(unsigned long v)
{
	__asm__ volatile ("mcr p15, 0, %[v], c1, c0, 0"
			: /* outputs  */
			: /* inputs   */ [v] "r" (v)
			: /* clobbers */ "cc"
			);
	isb();
}

unsigned int auxcr_get(void)
{
	unsigned int t;
	__asm__ volatile ("mrc p15, 0, %[t], c1, c0, 1"
			: /* outputs  */ [t] "=r" (t)
			: /* inputs   */
			: /* clobbers */
			);
	return t;
}

void auxcr_set(unsigned int v)
{
	__asm__ volatile ("mcr p15, 0, %[v], c1, c0, 1"
			: /* outputs  */
			: /* inputs   */ [v] "r" (v)
			: /* clobbers */
			);
	isb();
}

int cpuid_get(void)
{
	int cpu;
	__asm__ volatile ("mrc p15, 0, %[cpu], c0, c0, 5; "
			  "and %[cpu], %[cpu], #15"
			: /* outputs  */ [cpu] "=r" (cpu)
			: /* inputs   */
			: /* clobbers */
			);
	return cpu;
}
