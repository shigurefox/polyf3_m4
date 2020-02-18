	// bitslice functions
	.p2align	2,,3
	.syntax		unified
	.text
	.global 	bs3_mul32
	.type		bs3_mul32, %function
	// void bs3_mul32(int *h, int *f, int *g);
bs3_mul32:
	push.w	{r4-r11,lr}
	ldr.w	r4, [r1], #4
	ldr.w	r5, [r1], #4
	ldr.w	r6, [r2], #4
	ldr.w	r7, [r2], #4
	and.w	r8, r4, r6, ASR #31
	eor.w	r9, r5, r7, ASR #31
	and.w	r9, r9, r8
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ubfx.w	r10, r8, #31, #1
	ubfx.w	r11, r9, #31, #1
	and.w	r12, r4, r6, ASR #31
	eor.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eor.w	r9, r12, r9, LSL #1
	eor.w	r12, r12, r8, LSL #1
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	stm.w	r0!, {r8-r11}
#ifndef __thumb__
	pop.w	{r4-r11,pc}
#else
	pop.w	{r4-r11,pc}
#endif
	// bitslice functions
	.p2align	2,,3
	.syntax		unified
	.text
	.global 	bs3_mul32s
	.type		bs3_mul32s, %function
	// void bs3_mul32s(int *h, int *f, int *g);
bs3_mul32s:
	push.w	{r4-r11,lr}
	ldr.w	r4, [r1], #4
	ldr.w	r5, [r1], #4
	ldr.w	r6, [r2], #4
	ldr.w	r7, [r2], #4
	and.w	r8, r4, r6, ASR #31
	eor.w	r9, r5, r7, ASR #31
	and.w	r9, r9, r8
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ubfx.w	r10, r8, #31, #1
	ubfx.w	r11, r9, #31, #1
	and.w	r12, r4, r6, ASR #31
	eor.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eor.w	r9, r12, r9, LSL #1
	eor.w	r12, r12, r8, LSL #1
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	lsls.w	r8, r8, #1
	adc.w	r9, r9, r9
	lsls.w	r10, r10, #1
	adc.w	r11, r11, r11
	stm.w	r0!, {r8-r11}
#ifndef __thumb__
	pop.w	{r4-r11,pc}
#else
	pop.w	{r4-r11,pc}
#endif
	// bitslice functions
	.p2align	2,,3
	.syntax		unified
	.text
	.global 	bs3_mul32_negc
	.type		bs3_mul32_negc, %function
	// void bs3_mul32_negc(int *h, int *f, int *g);
bs3_mul32_negc:
	push.w	{r4-r11,lr}
	ldr.w	r4, [r1], #4
	ldr.w	r5, [r1], #4
	ldr.w	r6, [r2], #4
	ldr.w	r7, [r2], #4
	and.w	r8, r4, r6, ASR #31
	eor.w	r9, r5, r7, ASR #31
	and.w	r9, r9, r8
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r11, r8, #(1<<31)
	eors.w	r9, r9, r11
	ands.w	r10, r4, r6, ASR #31
	eors.w	r11, r5, r7, ASR #31
	ands.w	r11, r11, r10
	eor.w	r9, r10, r9, ROR #31
	eor.w	r10, r10, r8, ROR #31
	eor.w	r8, r11, r8, ROR #31
	eors.w	r11, r11, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r10, r11
	strd.w	r8, r9, [r0], #8
#ifndef __thumb__
	pop.w	{r4-r11,pc}
#else
	pop.w	{r4-r11,pc}
#endif
	// bitslice functions
	.p2align	2,,3
	.syntax		unified
	.text
	.global 	bs3_mul64_negc
	.type		bs3_mul64_negc, %function
	// void bs3_mul64_negc(int *h, int *f, int *g);
bs3_mul64_negc:
	push.w	{r4-r11,lr}
	ldr.w	r4, [r1]
	ldr.w	r5, [r1, #4]
	ldr.w	r6, [r2]
	ldr.w	r7, [r2, #4]
	ldr.w	r8, [r1, #8]
	ldr.w	r9, [r1, #12]
	ldr.w	r10, [r2, #8]
	ldr.w	r11, [r2, #12]
	eor.w	r5, r5, r8	// (a1^b0)
	eor.w	r8, r8, r4	// (a0^b0)
	eor.w	r4, r4, r9	// (a0^b1)
	eor.w	r9, r9, r5	// (b1^(a1^b0))
	and.w	r5, r5, r4	// c1=(a1^b0)&(a0^b1)
	orr.w	r4, r8, r9	// c0=(a0^b0)|(b1^(a1^b0))
	eor.w	r7, r7, r10	// (a1^b0)
	eor.w	r10, r10, r6	// (a0^b0)
	eor.w	r6, r6, r11	// (a0^b1)
	eor.w	r11, r11, r7	// (b1^(a1^b0))
	and.w	r7, r7, r6	// c1=(a1^b0)&(a0^b1)
	orr.w	r6, r10, r11	// c0=(a0^b0)|(b1^(a1^b0))
	and.w	r8, r4, r6, ASR #31
	eor.w	r9, r5, r7, ASR #31
	and.w	r9, r9, r8
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ubfx.w	r10, r8, #31, #1
	ubfx.w	r11, r9, #31, #1
	and.w	r12, r4, r6, ASR #31
	eor.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eor.w	r9, r12, r9, LSL #1
	eor.w	r12, r12, r8, LSL #1
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	vmov.w	s0, r8		// save c01l0
	vmov.w	s1, r9		// save c01l1
	vmov.w	s2, r10		// save c01h0
	vmov.w	s3, r11		// save c01h1
	ldr.w	r4, [r1, #8]
	ldr.w	r5, [r1, #12]
	ldr.w	r6, [r2, #8]
	ldr.w	r7, [r2, #12]
	and.w	r8, r4, r6, ASR #31
	eor.w	r9, r5, r7, ASR #31
	and.w	r9, r9, r8
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ubfx.w	r10, r8, #31, #1
	ubfx.w	r11, r9, #31, #1
	and.w	r12, r4, r6, ASR #31
	eor.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eor.w	r9, r12, r9, LSL #1
	eor.w	r12, r12, r8, LSL #1
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	vmov.w	s4, r8		// save c1l0
	vmov.w	s5, r9		// save c1l1
	vmov.w	s6, r10		// save c1h0
	vmov.w	s7, r11		// save c1h1
	ldr.w	r5, [r1, #4]
	ldr.w	r4, [r1], #16
	ldr.w	r7, [r2, #4]
	ldr.w	r6, [r2], #16
	and.w	r8, r4, r6, ASR #31
	eor.w	r9, r5, r7, ASR #31
	and.w	r9, r9, r8
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ubfx.w	r10, r8, #31, #1
	ubfx.w	r11, r9, #31, #1
	and.w	r12, r4, r6, ASR #31
	eor.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eor.w	r9, r12, r9, LSL #1
	eor.w	r12, r12, r8, LSL #1
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	rors.w	r6, r6, #31
	rors.w	r7, r7, #31
	ands.w	r12, r4, r6, ASR #31
	eors.w	r14, r5, r7, ASR #31
	ands.w	r14, r14, r12
	eors.w	r9, r12, r9, LSL #1
	adc.w	r11, r11, r11	// RLX
	eors.w	r12, r12, r8, LSL #1
	adc.w	r10, r10, r10	// RLX
	eor.w	r8, r14, r8, LSL #1
	eors.w	r14, r14, r9
	ands.w	r9, r9, r8
	orrs.w	r8, r12, r14
	vmov.w	r4, s4		// load c1l0
	vmov.w	r5, s5		// load c1l1
	vmov.w	r6, s6		// load c1h0
	vmov.w	r7, s7		// load c1h1
	eor.w	r9, r9, r6	// (a1^b0)
	eor.w	r6, r6, r8	// (a0^b0)
	eor.w	r8, r8, r7	// (a0^b1)
	eor.w	r7, r7, r9	// (b1^(a1^b0))
	and.w	r9, r9, r8	// c1=(a1^b0)&(a0^b1)
	orr.w	r8, r6, r7	// c0=(a0^b0)|(b1^(a1^b0))
	eors.w	r10, r10, r4	// (a0^b0)
	eors.w	r4, r4, r11	// (a1^b0)
	eors.w	r11, r11, r5	// (a1^b1)
	eors.w	r5, r5, r10	// (b1^(a0^b0))
	orrs.w	r10, r10, r11	// c0=(a0^b0)|(a1^b1)
	and.w	r11, r4, r5	// c1=(a1^b0)&(b1^(a0^b0))
	eor.w	r6, r10, r8	// (a0^b0)
	eor.w	r7, r8, r11	// (a1^b0)
	eor.w	r8, r11, r9	// (a1^b1)
	eor.w	r11, r10, r9	// (a0^b1)
	eor.w	r10, r9, r7	// (b1^(a1^b0))
	eor.w	r9, r9, r6	// (b1^(a0^b0))
	orr.w	r10, r10, r6	// c0=(a0^b0)|(b1^(a1^b0))
	and.w	r11, r11, r7	// c1=(a1^b0)&(a0^b1)
	orr.w	r8, r8, r6	// d0=(a0^b0)|(a1^b1)
	and.w	r9, r9, r7	// d1=(a1^b0)&(b1^(a0^b0))
	vmov.w	r4, s0		// load c01l0
	vmov.w	r5, s1		// load c01l1
	vmov.w	r6, s2		// load c01h0
	vmov.w	r7, s3		// load c01h1
	eor.w	r9, r9, r4	// (a1^b0)
	eor.w	r4, r4, r8	// (a0^b0)
	eor.w	r8, r8, r5	// (a0^b1)
	eor.w	r5, r5, r9	// (b1^(a1^b0))
	and.w	r9, r9, r8	// c1=(a1^b0)&(a0^b1)
	orr.w	r8, r4, r5	// c0=(a0^b0)|(b1^(a1^b0))
	eors.w	r10, r10, r6	// (a0^b0)
	eors.w	r6, r6, r11	// (a1^b0)
	eors.w	r11, r11, r7	// (a1^b1)
	eors.w	r7, r7, r10	// (b1^(a0^b0))
	orrs.w	r10, r10, r11	// c0=(a0^b0)|(a1^b1)
	and.w	r11, r6, r7	// c1=(a1^b0)&(b1^(a0^b0))
	str.w	r10, [r0], #4
	str.w	r11, [r0], #4
	str.w	r8, [r0], #4
	str.w	r9, [r0], #4
#ifndef __thumb__
	pop.w	{r4-r11,pc}
#else
	pop.w	{r4-r11,pc}
#endif
