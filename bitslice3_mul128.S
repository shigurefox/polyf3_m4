
// N=128 requires 288 storage
	.p2align	2,,3
	.syntax		unified
	.text
KA_128:
	.word	128
	.word	192
	.word	288
	.p2align	2,,3	
	.syntax		unified
	.text
// void bs3_mul128 (int32_t *h, int32_t *f, int32_t *g);
	.global bs3_mul128
	.type	bs3_mul128, %function
bs3_mul128:
	push.w	{r4-r11,lr}
	sub.w	sp, sp, #288	// subtract M
		// ff=[sp], gg=[sp,#72], hh=[sp,#144]
	vmov.w	s0, r0		// save h
	add.w	r3, sp, #0	// load ff pointer
	add.w	r0, sp, #72	// load gg pointer
KA128_mv_loop:	// r0 = gg, r1 = f, r2 = g, r3 = ff
	ldm.w	r1!, {r4-r11}
	stm.w	r3!, {r4-r11}
	ldm.w	r2!, {r4-r11}
	stm.w	r0!, {r4-r11}
KA128_exp:	// ff @ sp, gg @ sp + M/4, M/4 @ r12
	add.w	r0, sp, #0	// load ff
	add.w	r1, sp, #72	// load gg
	ldr.w	r3, =KA_128
	vmov.w	s1, r3		// save list of multiplication sizes pointer
	mov.w	r2, #16		// N0/8 = r2 = N/8
KA128_exp_loop1:		// loop on N0(/8)
	cmp.w	r2, #4		// while (N0>B)
	beq.w	KA128_exp_end1
KA128_exp_adds:
/*
  for (j=0; j<N1; j+=N0) {
    for (k=0; k<N0/2; k+=32) {
     add3(ff+(j+k+N1)/4,ff+(2*j+k)/4,ff+(2*j+k+N0/2)/4);
     add3(gg+(j+k+N1)/4,gg+(2*j+k)/4,gg+(2*j+k+N0/2)/4);
    }
*/
	ldr.w	r4, [r3], #4		// load N1=KA_terms(N,N0)
	add.w	r5, r0, r4, LSR #2	// r5 = ff + N1/4
	add.w	r6, r1, r4, LSR #2	// r6 = gg + N1/4
	add.w	r0, r0, r2		// r0 = ff + N0/8
	add.w	r1, r1, r2		// r1 = gg + N0/8
	rsb.w	r2, r2, #0		// r2 = -N0/8
	mov.w	r12, r2
KA128_exp_adds1:
	ldr.w	r8, [r0, r2]
	ldr.w	r10, [r0], #4
	ldr.w	r9, [r0, r2]
	ldr.w	r11, [r0], #4
	eor.w	r9, r9, r10	// (a1^b0)
	eor.w	r10, r10, r8	// (a0^b0)
	eor.w	r8, r8, r11	// (a0^b1)
	eor.w	r11, r11, r9	// (b1^(a1^b0))
	and.w	r9, r9, r8	// c1=(a1^b0)&(a0^b1)
	orr.w	r8, r10, r11	// c0=(a0^b0)|(b1^(a1^b0))
	strd.w	r8, r9, [r5], #8
	ldr.w	r8, [r1, r2]
	ldr.w	r10, [r1], #4
	ldr.w	r9, [r1, r2]
	ldr.w	r11, [r1], #4
	eor.w	r9, r9, r10	// (a1^b0)
	eor.w	r10, r10, r8	// (a0^b0)
	eor.w	r8, r8, r11	// (a0^b1)
	eor.w	r11, r11, r9	// (b1^(a1^b0))
	and.w	r9, r9, r8	// c1=(a1^b0)&(a0^b1)
	orr.w	r8, r10, r11	// c0=(a0^b0)|(b1^(a1^b0))
	strd.w	r8, r9, [r6], #8
	subs.w	r4, r4, #64	// total of N1/64 pairs
	beq.w	KA128_exp_end
	adds.w	r12, r12, #8	// from N0/8 each time 8
	nop.n
	ittt	eq		// divisible by N0/2?
	subeq.w	r0, r0, r2	// then add N0/8!
	subeq.w	r1, r1, r2	// then add N0/8!
	moveq.w	r12, r2		// reload with N0/8
	b.w	KA128_exp_adds1
KA128_exp_end:
	rsb.w	r2, r2, #0	// back to + N0/8
	add.w	r0, sp, #0	// reload ff
	add.w	r1, sp, #72	// reload gg

	lsr.w	r2, #1 		// N0 /= 2
	b.w	KA128_exp_loop1	// loop
KA128_exp_end1:

KA128_mul:
	vmov.w	s1, r3		// save N1 list pointer
	ldr.w	r3, [r3]	// r3 = N1
	add.w	r2, sp, #144	// load r2 = hh
KA128_muls1:
	ldr.w	r4, [r0], #4
	ldr.w	r5, [r0], #4
	ldr.w	r6, [r1], #4
	ldr.w	r7, [r1], #4
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
	stm.w	r2!, {r8-r11}
	subs.w	r3, #32
	bne.w	KA128_muls1
KA128_collect:
	add.w	r2, sp, #144	// reload hh
KA128_col_32_add:			// KA collection
	vmov.w	r3, s1		// reload N1 list
	ldr.w	r14, [r3, #-4]!	// N1
	vmov.w	s1, r3		// save N1 list
	add.w	r12, r2, r14, LSR #1	// points into array
	mov.w	r1, r2		// copy of hh
	mov.w	r11, #32	// N0
KA128_col_32_add1:	// beginning of KA collect
	ldrd.w	r4, r5, [r1, #8]
	ldrd.w	r6, r7, [r1, #16]
	eor.w	r4, r4, r6	// (a0^b0)
	eor.w	r6, r6, r5	// (a1^b0)
	eor.w	r5, r5, r7	// (a1^b1)
	eor.w	r7, r7, r4	// (b1^(a0^b0))
	orr.w	r4, r4, r5	// c0=(a0^b0)|(a1^b1)
	and.w	r5, r6, r7	// c1=(a1^b0)&(b1^(a0^b0))
	ldrd.w	r6, r7, [r1, #24]
	eor.w	r9, r5, r6	// (a1^b0)
	eor.w	r6, r6, r4	// (a0^b0)
	eor.w	r8, r4, r7	// (a0^b1)
	eor.w	r7, r7, r9	// (b1^(a1^b0))
	and.w	r9, r9, r8	// c1=(a1^b0)&(a0^b1)
	orr.w	r8, r6, r7	// c0=(a0^b0)|(b1^(a1^b0))
	ldrd.w	r6, r7, [r1]
	eor.w	r4, r4, r6	// (a0^b0)
	eor.w	r6, r6, r5	// (a1^b0)
	eor.w	r5, r5, r7	// (a1^b1)
	eor.w	r7, r7, r4	// (b1^(a0^b0))
	orr.w	r4, r4, r5	// c0=(a0^b0)|(a1^b1)
	and.w	r5, r6, r7	// c1=(a1^b0)&(b1^(a0^b0))
	ldrd.w	r6, r7, [r12, #8]
	eor.w	r6, r6, r8	// (a0^b0)
	eor.w	r8, r8, r7	// (a1^b0)
	eor.w	r7, r7, r9	// (a1^b1)
	eor.w	r9, r9, r6	// (b1^(a0^b0))
	orr.w	r6, r6, r7	// c0=(a0^b0)|(a1^b1)
	and.w	r7, r8, r9	// c1=(a1^b0)&(b1^(a0^b0))
	ldrd.w	r8, r9, [r12], #8	// shift r12
	strd.w	r6, r7, [r1, #16]
	eor.w	r5, r5, r8	// (a1^b0)
	eor.w	r8, r8, r4	// (a0^b0)
	eor.w	r4, r4, r9	// (a0^b1)
	eor.w	r9, r9, r5	// (b1^(a1^b0))
	and.w	r5, r5, r4	// c1=(a1^b0)&(a0^b1)
	orr.w	r4, r8, r9	// c0=(a0^b0)|(b1^(a1^b0))
	strd.w	r4, r5, [r1, #8]
	add.w	r1, r1, #8
	subs.w	r14, r14, #64
	beq.w	KA128_col_32_end
	subs.w	r11, r11, #32
	nop.n
	ittt	eq	// no, then next set
	addeq.w	r1, r1, #24
	addeq.w	r12, r12, #8
	moveq.w	r11, #32	// N0
	b.w	KA128_col_32_add1
KA128_col_32_end:
KA128_col_64_add:			// KA collection
	vmov.w	r3, s1		// reload N1 list
	ldr.w	r14, [r3, #-4]!	// N1
	vmov.w	s1, r3		// save N1 list
	add.w	r12, r2, r14, LSR #1	// points into array
	mov.w	r1, r2		// copy of hh
	mov.w	r11, #64	// N0
KA128_col_64_add1:	// beginning of KA collect
	ldrd.w	r4, r5, [r1, #16]
	ldrd.w	r6, r7, [r1, #32]
	eor.w	r4, r4, r6	// (a0^b0)
	eor.w	r6, r6, r5	// (a1^b0)
	eor.w	r5, r5, r7	// (a1^b1)
	eor.w	r7, r7, r4	// (b1^(a0^b0))
	orr.w	r4, r4, r5	// c0=(a0^b0)|(a1^b1)
	and.w	r5, r6, r7	// c1=(a1^b0)&(b1^(a0^b0))
	ldrd.w	r6, r7, [r1, #48]
	eor.w	r9, r5, r6	// (a1^b0)
	eor.w	r6, r6, r4	// (a0^b0)
	eor.w	r8, r4, r7	// (a0^b1)
	eor.w	r7, r7, r9	// (b1^(a1^b0))
	and.w	r9, r9, r8	// c1=(a1^b0)&(a0^b1)
	orr.w	r8, r6, r7	// c0=(a0^b0)|(b1^(a1^b0))
	ldrd.w	r6, r7, [r1]
	eor.w	r4, r4, r6	// (a0^b0)
	eor.w	r6, r6, r5	// (a1^b0)
	eor.w	r5, r5, r7	// (a1^b1)
	eor.w	r7, r7, r4	// (b1^(a0^b0))
	orr.w	r4, r4, r5	// c0=(a0^b0)|(a1^b1)
	and.w	r5, r6, r7	// c1=(a1^b0)&(b1^(a0^b0))
	ldrd.w	r6, r7, [r12, #16]
	eor.w	r6, r6, r8	// (a0^b0)
	eor.w	r8, r8, r7	// (a1^b0)
	eor.w	r7, r7, r9	// (a1^b1)
	eor.w	r9, r9, r6	// (b1^(a0^b0))
	orr.w	r6, r6, r7	// c0=(a0^b0)|(a1^b1)
	and.w	r7, r8, r9	// c1=(a1^b0)&(b1^(a0^b0))
	ldrd.w	r8, r9, [r12], #8	// shift r12
	strd.w	r6, r7, [r1, #32]
	eor.w	r5, r5, r8	// (a1^b0)
	eor.w	r8, r8, r4	// (a0^b0)
	eor.w	r4, r4, r9	// (a0^b1)
	eor.w	r9, r9, r5	// (b1^(a1^b0))
	and.w	r5, r5, r4	// c1=(a1^b0)&(a0^b1)
	orr.w	r4, r8, r9	// c0=(a0^b0)|(b1^(a1^b0))
	strd.w	r4, r5, [r1, #16]
	add.w	r1, r1, #8
	subs.w	r14, r14, #64
	beq.w	KA128_col_64_end
	subs.w	r11, r11, #32
	nop.n
	ittt	eq	// no, then next set
	addeq.w	r1, r1, #48
	addeq.w	r12, r12, #16
	moveq.w	r11, #64	// N0
	b.w	KA128_col_64_add1
KA128_col_64_end:
KA128_mv_back:			// hh still =r2
	vmov.w	r0, s0		// reload h
	mov.w	r14, #128
KA128_mv_back_loop:
	ldm.w	r2!, {r4-r11}	// 4 pairs = 128 trits
	stm.w	r0!, {r4-r11}
	subs.w	r14, #64
	bne.w	KA128_mv_back_loop
KA128_end:
	add.w	sp, sp, #288
	pop.w	{r4-r11,pc}

