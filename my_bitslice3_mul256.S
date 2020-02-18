.p2align 2,,3
.syntax unified
.text

.global polyf3_mul256_packed_asm
.type polyf3_mul256_packed_asm, %function
@ 256x256 3-layer bit-sliced Karatsuba
@ void polyf3_mul256_packed_asm(uint32_t *h, uint32_t *c, uint32_t *f)
polyf3_mul256_packed_asm:
  push.w {r4-r12, lr}
  vmov.w s0, r0
  sub.w sp, sp, #864
  mov.w r0, sp
  ldm.w r2!, {r3-r12, lr}
  stm.w r0!, {r3-r12, lr}
  ldm.w r2!, {r3-r7}
  stm.w r0!, {r3-r7}
  sub.w r12, r0, #64
  add.w lr, r12, #32
polyf3_mul256_packed_asm_extend_input_f_0_unit:
  ldr.w r8, [r12, #32]
  ldr.w r4, [r12], #4
  ldr.w r9, [r12, #32]
  ldr.w r5, [r12], #4
  ldr.w r10, [r12, #32]
  ldr.w r6, [r12], #4
  ldr.w r11, [r12, #32]
  ldr.w r7, [r12], #4
  eor.w r5, r5, r8
  eor.w r8, r8, r4
  eor.w r4, r4, r9
  eor.w r9, r9, r5
  and.w r5, r5, r4
  orr.w r4, r8, r9
  eor.w r7, r7, r10
  eor.w r10, r10, r6
  eor.w r6, r6, r11
  eor.w r11, r11, r7
  and.w r7, r7, r6
  orr.w r6, r10, r11
  stm.w r0!, {r4-r7}
  cmp.w r12, lr
  bne.w polyf3_mul256_packed_asm_extend_input_f_0_unit
  sub.w r12, r0, #96
  mov.w r3, r0
polyf3_mul256_packed_asm_extend_input_f_1_body:
  ldr.w r8, [r12, #16]
  ldr.w r4, [r12], #4
  ldr.w r9, [r12, #16]
  ldr.w r5, [r12], #4
  ldr.w r10, [r12, #16]
  ldr.w r6, [r12], #4
  ldr.w r11, [r12, #16]
  ldr.w r7, [r12], #4
  eor.w r5, r5, r8
  eor.w r8, r8, r4
  eor.w r4, r4, r9
  eor.w r9, r9, r5
  and.w r5, r5, r4
  orr.w r4, r8, r9
  eor.w r7, r7, r10
  eor.w r10, r10, r6
  eor.w r6, r6, r11
  eor.w r11, r11, r7
  and.w r7, r7, r6
  orr.w r6, r10, r11
  stm.w r0!, {r4-r7}
  add.w r12, r12, #16
  cmp.w r12, r3
  bne.w polyf3_mul256_packed_asm_extend_input_f_1_body
  sub.w r12, r0, #144
  mov.w r3, r0
polyf3_mul256_packed_asm_extend_input_f_2_body:
  ldr.w r6, [r12, #8]
  ldr.w r4, [r12], #4
  ldr.w r7, [r12, #8]
  ldr.w r5, [r12], #4
  eor.w r5, r5, r6
  eor.w r6, r6, r4
  eor.w r4, r4, r7
  eor.w r7, r7, r5
  and.w r5, r5, r4
  orr.w r4, r6, r7
  stm.w r0!, {r4-r5}
  add.w r12, r12, #8
  cmp.w r12, r3
  bne.w polyf3_mul256_packed_asm_extend_input_f_2_body
  ldm.w r1!, {r2-r12, lr}
  stm.w r0!, {r2-r12, lr}
  ldm.w r1!, {r2-r5}
  stm.w r0!, {r2-r5}
  sub.w r12, r0, #64
  add.w lr, r12, #32
polyf3_mul256_packed_asm_extend_input_c_0_unit:
  ldr.w r8, [r12, #32]
  ldr.w r4, [r12], #4
  ldr.w r9, [r12, #32]
  ldr.w r5, [r12], #4
  ldr.w r10, [r12, #32]
  ldr.w r6, [r12], #4
  ldr.w r11, [r12, #32]
  ldr.w r7, [r12], #4
  eor.w r5, r5, r8
  eor.w r8, r8, r4
  eor.w r4, r4, r9
  eor.w r9, r9, r5
  and.w r5, r5, r4
  orr.w r4, r8, r9
  eor.w r7, r7, r10
  eor.w r10, r10, r6
  eor.w r6, r6, r11
  eor.w r11, r11, r7
  and.w r7, r7, r6
  orr.w r6, r10, r11
  stm.w r0!, {r4-r7}
  cmp.w r12, lr
  bne.w polyf3_mul256_packed_asm_extend_input_c_0_unit
  sub.w r12, r0, #96
  mov.w r3, r0
polyf3_mul256_packed_asm_extend_input_c_1_body:
  ldr.w r8, [r12, #16]
  ldr.w r4, [r12], #4
  ldr.w r9, [r12, #16]
  ldr.w r5, [r12], #4
  ldr.w r10, [r12, #16]
  ldr.w r6, [r12], #4
  ldr.w r11, [r12, #16]
  ldr.w r7, [r12], #4
  eor.w r5, r5, r8
  eor.w r8, r8, r4
  eor.w r4, r4, r9
  eor.w r9, r9, r5
  and.w r5, r5, r4
  orr.w r4, r8, r9
  eor.w r7, r7, r10
  eor.w r10, r10, r6
  eor.w r6, r6, r11
  eor.w r11, r11, r7
  and.w r7, r7, r6
  orr.w r6, r10, r11
  stm.w r0!, {r4-r7}
  add.w r12, r12, #16
  cmp.w r12, r3
  bne.w polyf3_mul256_packed_asm_extend_input_c_1_body
  sub.w r12, r0, #144
  mov.w r3, r0
polyf3_mul256_packed_asm_extend_input_c_2_body:
  ldr.w r6, [r12, #8]
  ldr.w r4, [r12], #4
  ldr.w r7, [r12, #8]
  ldr.w r5, [r12], #4
  eor.w r5, r5, r6
  eor.w r6, r6, r4
  eor.w r4, r4, r7
  eor.w r7, r7, r5
  and.w r5, r5, r4
  orr.w r4, r6, r7
  stm.w r0!, {r4-r5}
  add.w r12, r12, #8
  cmp.w r12, r3
  bne.w polyf3_mul256_packed_asm_extend_input_c_2_body
  add.w lr, r0, #432
  sub.w r1, r0, #216
  sub.w r2, r1, #216
polyf3_mul256_packed_asm_mul32_body:
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
  cmp.w r0, lr
  bne.w polyf3_mul256_packed_asm_mul32_body
  sub.w r0, r0, #424
  add.w r12, r0, #288
polyf3_mul256_packed_asm_compose_output_0_body:
  ldr.w r1, [r0, #0]
  ldr.w r3, [r0, #8]
  ldr.w r2, [r0, #4]
  ldr.w r4, [r0, #12]
  eor.w r3, r3, r1
  eor.w r1, r4, r1
  eor.w r4, r4, r2
  eor.w r2, r3, r2
  and.w r2, r1, r2
  orr.w r1, r3, r4
  stm.w r0!, {r1-r2}
  ldr.w r3, [r0, #-4]!
  ldr.w r1, [r0, #16]
  ldr.w r4, [r0, #-4]!
  ldr.w r2, [r0, #16]
  eor.w r2, r2, r4
  eor.w r4, r1, r4
  eor.w r1, r1, r3
  eor.w r3, r2, r3
  orr.w r2, r2, r1
  and.w r1, r4, r3
  str.w r1, [r0, #12]
  str.w r2, [r0, #8]
  ldr.w r3, [r0, #-4]!
  ldr.w r1, [r0, #8]
  ldr.w r4, [r0, #-4]!
  ldr.w r2, [r0, #8]
  eor.w r1, r1, r4
  eor.w r4, r2, r4
  eor.w r2, r2, r3
  eor.w r3, r1, r3
  and.w r1, r2, r1
  orr.w r2, r4, r3
  str.w r1, [r0, #12]
  str.w r2, [r0, #8]
  add.w r0, r0, #40
  cmp.w r0, r12
  bne.w polyf3_mul256_packed_asm_compose_output_0_body
  sub.w r12, r0, #288
  sub.w lr, r0, #8
polyf3_mul256_packed_asm_compose_output_0_jump:
  ldm.w r12, {r1-r4}
  ldm.w lr!, {r5-r8}
  eor.w r5, r5, r1
  eor.w r1, r6, r1
  eor.w r6, r6, r2
  eor.w r2, r5, r2
  and.w r2, r1, r2
  orr.w r1, r5, r6
  eor.w r7, r7, r3
  eor.w r3, r8, r3
  eor.w r8, r8, r4
  eor.w r4, r7, r4
  and.w r4, r3, r4
  orr.w r3, r7, r8
  stm.w r12!, {r1-r4}
  add.w r12, r12, #16
  cmp.w r12, r0
  bne.w polyf3_mul256_packed_asm_compose_output_0_jump
  sub.w r0, r12, #16
  sub.w r0, r0, #264
  add.w r12, r0, #192
polyf3_mul256_packed_asm_compose_output_1_body:
  ldr.w r1, [r0, #0]
  ldr.w r5, [r0, #16]
  ldr.w r2, [r0, #4]
  ldr.w r6, [r0, #20]
  ldr.w r3, [r0, #8]
  ldr.w r7, [r0, #24]
  ldr.w r4, [r0, #12]
  ldr.w r8, [r0, #28]
  eor.w r5, r5, r1
  eor.w r1, r6, r1
  eor.w r6, r6, r2
  eor.w r2, r5, r2
  and.w r2, r1, r2
  orr.w r1, r5, r6
  eor.w r7, r7, r3
  eor.w r3, r8, r3
  eor.w r8, r8, r4
  eor.w r4, r7, r4
  and.w r4, r3, r4
  orr.w r3, r7, r8
  stm.w r0!, {r1-r4}
  ldr.w r5, [r0, #-4]!
  ldr.w r1, [r0, #32]
  ldr.w r6, [r0, #-4]!
  ldr.w r2, [r0, #32]
  ldr.w r7, [r0, #-4]!
  ldr.w r3, [r0, #32]
  ldr.w r8, [r0, #-4]!
  ldr.w r4, [r0, #32]
  eor.w r2, r2, r6
  eor.w r6, r1, r6
  eor.w r1, r1, r5
  eor.w r5, r2, r5
  orr.w r2, r2, r1
  and.w r1, r6, r5
  eor.w r4, r4, r8
  eor.w r8, r3, r8
  eor.w r3, r3, r7
  eor.w r7, r4, r7
  orr.w r4, r4, r3
  and.w r3, r8, r7
  str.w r1, [r0, #28]
  str.w r2, [r0, #24]
  str.w r3, [r0, #20]
  str.w r4, [r0, #16]
  ldr.w r5, [r0, #-4]!
  ldr.w r1, [r0, #16]
  ldr.w r6, [r0, #-4]!
  ldr.w r2, [r0, #16]
  ldr.w r7, [r0, #-4]!
  ldr.w r3, [r0, #16]
  ldr.w r8, [r0, #-4]!
  ldr.w r4, [r0, #16]
  eor.w r1, r1, r6
  eor.w r6, r2, r6
  eor.w r2, r2, r5
  eor.w r5, r1, r5
  and.w r1, r2, r1
  orr.w r2, r6, r5
  eor.w r3, r3, r8
  eor.w r8, r4, r8
  eor.w r4, r4, r7
  eor.w r7, r3, r7
  and.w r3, r4, r3
  orr.w r4, r8, r7
  str.w r1, [r0, #28]
  str.w r2, [r0, #24]
  str.w r3, [r0, #20]
  str.w r4, [r0, #16]
  add.w r0, r0, #80
  cmp.w r0, r12
  bne.w polyf3_mul256_packed_asm_compose_output_1_body
  sub.w r12, r0, #192
  sub.w lr, r0, #16
polyf3_mul256_packed_asm_compose_output_1_jump:
  add.w r11, r12, #32
polyf3_mul256_packed_asm_compose_output_D_1:
  ldm.w r12, {r1-r4}
  ldm.w lr!, {r5-r8}
  eor.w r5, r5, r1
  eor.w r1, r6, r1
  eor.w r6, r6, r2
  eor.w r2, r5, r2
  and.w r2, r1, r2
  orr.w r1, r5, r6
  eor.w r7, r7, r3
  eor.w r3, r8, r3
  eor.w r8, r8, r4
  eor.w r4, r7, r4
  and.w r4, r3, r4
  orr.w r3, r7, r8
  stm.w r12!, {r1-r4}
  cmp.w r12, r11
  bne.w polyf3_mul256_packed_asm_compose_output_D_1
  add.w r12, r12, #32
  cmp.w r12, r0
  bne.w polyf3_mul256_packed_asm_compose_output_1_jump
  sub.w r0, r12, #32
  sub.w r0, r0, #144
  add.w lr, r0, #32
polyf3_mul256_packed_asm_compose_output_A_2:
  ldr.w r1, [r0, #0]
  ldr.w r5, [r0, #32]
  ldr.w r2, [r0, #4]
  ldr.w r6, [r0, #36]
  ldr.w r3, [r0, #8]
  ldr.w r7, [r0, #40]
  ldr.w r4, [r0, #12]
  ldr.w r8, [r0, #44]
  eor.w r5, r5, r1
  eor.w r1, r6, r1
  eor.w r6, r6, r2
  eor.w r2, r5, r2
  and.w r2, r1, r2
  orr.w r1, r5, r6
  eor.w r7, r7, r3
  eor.w r3, r8, r3
  eor.w r8, r8, r4
  eor.w r4, r7, r4
  and.w r4, r3, r4
  orr.w r3, r7, r8
  stm.w r0!, {r1-r4}
  cmp.w r0, lr
  bne.w polyf3_mul256_packed_asm_compose_output_A_2
  sub.w lr, lr, #32
polyf3_mul256_packed_asm_compose_output_B_2:
  ldr.w r5, [r0, #-4]!
  ldr.w r1, [r0, #64]
  ldr.w r6, [r0, #-4]!
  ldr.w r2, [r0, #64]
  ldr.w r7, [r0, #-4]!
  ldr.w r3, [r0, #64]
  ldr.w r8, [r0, #-4]!
  ldr.w r4, [r0, #64]
  eor.w r2, r2, r6
  eor.w r6, r1, r6
  eor.w r1, r1, r5
  eor.w r5, r2, r5
  orr.w r2, r2, r1
  and.w r1, r6, r5
  eor.w r4, r4, r8
  eor.w r8, r3, r8
  eor.w r3, r3, r7
  eor.w r7, r4, r7
  orr.w r4, r4, r3
  and.w r3, r8, r7
  str.w r1, [r0, #44]
  str.w r2, [r0, #40]
  str.w r3, [r0, #36]
  str.w r4, [r0, #32]
  cmp.w r0, lr
  bne.w polyf3_mul256_packed_asm_compose_output_B_2
  sub.w lr, lr, #32
polyf3_mul256_packed_asm_compose_output_C_2:
  ldr.w r5, [r0, #-4]!
  ldr.w r1, [r0, #32]
  ldr.w r6, [r0, #-4]!
  ldr.w r2, [r0, #32]
  ldr.w r7, [r0, #-4]!
  ldr.w r3, [r0, #32]
  ldr.w r8, [r0, #-4]!
  ldr.w r4, [r0, #32]
  eor.w r1, r1, r6
  eor.w r6, r2, r6
  eor.w r2, r2, r5
  eor.w r5, r1, r5
  and.w r1, r2, r1
  orr.w r2, r6, r5
  eor.w r3, r3, r8
  eor.w r8, r4, r8
  eor.w r4, r4, r7
  eor.w r7, r3, r7
  and.w r3, r4, r3
  orr.w r4, r8, r7
  str.w r1, [r0, #44]
  str.w r2, [r0, #40]
  str.w r3, [r0, #36]
  str.w r4, [r0, #32]
  cmp.w r0, lr
  bne.w polyf3_mul256_packed_asm_compose_output_C_2
  add.w r0, r0, #160
  sub.w r12, r0, #128
  sub.w lr, r0, #32
  add.w r11, r12, #64
polyf3_mul256_packed_asm_compose_output_D_2:
  ldm.w r12, {r1-r4}
  ldm.w lr!, {r5-r8}
  eor.w r5, r5, r1
  eor.w r1, r6, r1
  eor.w r6, r6, r2
  eor.w r2, r5, r2
  and.w r2, r1, r2
  orr.w r1, r5, r6
  eor.w r7, r7, r3
  eor.w r3, r8, r3
  eor.w r8, r8, r4
  eor.w r4, r7, r4
  and.w r4, r3, r4
  orr.w r3, r7, r8
  stm.w r12!, {r1-r4}
  cmp.w r12, r11
  bne.w polyf3_mul256_packed_asm_compose_output_D_2
  sub.w r0, r12, #96
  vmov.w lr, s0
  add.w r1, r0, #88
polyf3_mul256_packed_asm_copy_output_body:
  ldm.w r0!, {r2-r12}
  stm.w lr!, {r2-r12}
  cmp.w r0, r1
  bne.w polyf3_mul256_packed_asm_copy_output_body
  ldr.w r2, [r0], #4
  ldr.w r3, [r0], #4
  ldr.w r4, [r0], #4
  ldr.w r5, [r0], #4
  ldr.w r6, [r0], #4
  ldr.w r7, [r0], #4
  ldr.w r8, [r0], #4
  ldr.w r9, [r0], #4
  ldr.w r10, [r0], #4
  ldr.w r11, [r0], #4
  str.w r2, [lr], #4
  str.w r3, [lr], #4
  str.w r4, [lr], #4
  str.w r5, [lr], #4
  str.w r6, [lr], #4
  str.w r7, [lr], #4
  str.w r8, [lr], #4
  str.w r9, [lr], #4
  str.w r10, [lr], #4
  str.w r11, [lr], #4
  add.w sp, sp, #864
  pop.w {r4-r12, pc}
