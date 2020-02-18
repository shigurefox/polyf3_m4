.p2align 2,,3
.syntax unified
.text

.global polyf3_mul32_packed_asm
.type polyf3_mul32_packed_asm, %function
@ 32x32 0-layer bit-sliced Karatsuba
@ void polyf3_mul32_packed_asm(uint32_t *h, uint32_t *c, uint32_t *f)
polyf3_mul32_packed_asm:
  push.w {r4-r12, lr}
  ldr.w r3, [r1], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r2], #4
  ldr.w r6, [r2], #4
  and.w r9, r3, r5, asr #31
  eor.w r10, r4, r6, asr #31
  and.w r10, r10, r9
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  ubfx.w r7, r9, #31, #1
  ubfx.w r8, r10, #31, #1
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eor.w r10, r11, r10, lsl #1
  eor.w r11, r11, r9, lsl #1
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  ror.w r5, r5, #31
  ror.w r6, r6, #31
  and.w r11, r3, r5, asr #31
  eor.w r12, r4, r6, asr #31
  and.w r12, r12, r11
  eors.w r10, r11, r10, lsl #1
  adc.w r8, r8, r8
  eors.w r11, r11, r9, lsl #1
  adc.w r7, r7, r7
  eor.w r9, r12, r9, lsl #1
  eor.w r12, r12, r10
  and.w r10, r10, r9
  orr.w r9, r11, r12
  str.w r9, [r0], #4
  str.w r10, [r0], #4
  str.w r7, [r0], #4
  str.w r8, [r0], #4
  pop.w {r4-r12, pc}
