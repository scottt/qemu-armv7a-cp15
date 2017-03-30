	.section .text
	.global _start
_start:
	mrc p15, 0, r0, c0, c0, 5
	and r0, r0, #15
	add r0, r0, #1

	lsl r0, r0, #20
	ldr r1, =text_end
	add r0, r0, r1
	mov sp, r0
	bl main
	wfi
