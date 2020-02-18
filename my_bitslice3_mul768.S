.p2align 2,,3
.syntax unified
.text

.global polyf3_mul768_packed_asm
.type polyf3_mul768_packed_asm, %function
@ 768x768 bit-sliced three-way Karatsuba
@ void polyf3_mul768_packed_asm(uint32_t *h, uint32_t *c, uint32_t *f)
polyf3_mul768_packed_asm:
  push.w {r4-r12, lr}
  vmov.w s0, r0
  sub.w sp, sp, #1152
  mov.w r0, sp
  add.w lr, r0, #64
polyf3_mul768_packed_asm_extend_input_f_unit:
  ldr.w r7, [r2, #128]
  ldr.w r5, [r2, #64]
  ldr.w r3, [r2], #4
  ldr.w r8, [r2, #128]
  ldr.w r6, [r2, #64]
  ldr.w r4, [r2], #4
  eor.w r10, r6, r7
  eor.w r11, r5, r7
  eor.w r9, r5, r8
  eor.w r12, r10, r8
  and.w r10, r9, r10
  orr.w r9, r11, r12
  eor.w r8, r8, r3
  eor.w r11, r7, r3
  eor.w r7, r7, r4
  eor.w r12, r8, r4
  and.w r8, r7, r8
  orr.w r7, r11, r12
  eor.w r6, r6, r3
  eor.w r11, r5, r3
  eor.w r5, r5, r4
  eor.w r12, r6, r4
  and.w r6, r5, r6
  orr.w r5, r11, r12
  str.w r9, [r0, #128]
  str.w r7, [r0, #64]
  str.w r5, [r0], #4
  str.w r10, [r0, #128]
  str.w r8, [r0, #64]
  str.w r6, [r0], #4
  cmp.w r0, lr
  bne.w polyf3_mul768_packed_asm_extend_input_f_unit
  sub.w r2, r2, #64
  add.w r0, r0, #128
  add.w lr, r0, #64
polyf3_mul768_packed_asm_extend_input_c_unit:
  ldr.w r7, [r1, #128]
  ldr.w r5, [r1, #64]
  ldr.w r3, [r1], #4
  ldr.w r8, [r1, #128]
  ldr.w r6, [r1, #64]
  ldr.w r4, [r1], #4
  eor.w r10, r6, r7
  eor.w r11, r5, r7
  eor.w r9, r5, r8
  eor.w r12, r10, r8
  and.w r10, r9, r10
  orr.w r9, r11, r12
  eor.w r8, r8, r3
  eor.w r11, r7, r3
  eor.w r7, r7, r4
  eor.w r12, r8, r4
  and.w r8, r7, r8
  orr.w r7, r11, r12
  eor.w r6, r6, r3
  eor.w r11, r5, r3
  eor.w r5, r5, r4
  eor.w r12, r6, r4
  and.w r6, r5, r6
  orr.w r5, r11, r12
  str.w r9, [r0, #128]
  str.w r7, [r0, #64]
  str.w r5, [r0], #4
  str.w r10, [r0, #128]
  str.w r8, [r0, #64]
  str.w r6, [r0], #4
  cmp.w r0, lr
  bne.w polyf3_mul768_packed_asm_extend_input_c_unit
  sub.w r1, r1, #64
  add.w r0, r0, #128
  vmov.w r4, s0
  mov.w r5, r0
  mov.w r6, r1
  mov.w r7, r2
  bl.w bs3_mul256
  add.w r0, r5, 128
  add.w r1, r6, 64
  add.w r2, r7, 64
  bl.w bs3_mul256
  add.w r0, r5, 256
  add.w r1, r6, 128
  add.w r2, r7, 128
  bl.w bs3_mul256
  add.w r0, r5, 384
  sub.w r1, r5, 192
  sub.w r2, r5, 384
  bl.w bs3_mul256
  add.w r0, r5, 512
  sub.w r1, r5, 128
  sub.w r2, r5, 320
  bl.w bs3_mul256
  add.w r0, r5, 640
  sub.w r1, r5, 64
  sub.w r2, r5, 256
  bl.w bs3_mul256
  vmov.w s0, r4
  mov.w r0, r5
  add.w lr, r0, #128
polyf3_mul768_packed_asm_compose_output_A:
  ldr.w r11, [r0, #640]
  ldr.w r7, [r0, #384]
  ldr.w r5, [r0, #256]
  ldr.w r3, [r0, #128]
  ldr.w r1, [r0], #4
  ldr.w r12, [r0, #640]
  ldr.w r8, [r0, #384]
  ldr.w r6, [r0, #256]
  ldr.w r4, [r0, #128]
  ldr.w r2, [r0], #4
  eor.w r7, r7, r1
  eor.w r9, r8, r1
  eor.w r8, r8, r2
  eor.w r10, r7, r2
  orr.w r7, r7, r8
  and.w r8, r9, r10
  eor.w r7, r7, r3
  eor.w r9, r8, r3
  eor.w r8, r8, r4
  eor.w r10, r7, r4
  orr.w r7, r7, r8
  and.w r8, r9, r10
  eor.w r11, r11, r3
  eor.w r9, r12, r3
  eor.w r12, r12, r4
  eor.w r10, r11, r4
  orr.w r11, r11, r12
  and.w r12, r9, r10
  eor.w r11, r11, r5
  eor.w r9, r12, r5
  eor.w r12, r12, r6
  eor.w r10, r11, r6
  orr.w r11, r11, r12
  and.w r12, r9, r10
  eor.w r3, r3, r5
  eor.w r9, r4, r5
  eor.w r4, r4, r6
  eor.w r10, r3, r6
  orr.w r3, r3, r4
  and.w r4, r9, r10
  eor.w r3, r3, r1
  eor.w r9, r4, r1
  eor.w r4, r4, r2
  eor.w r10, r3, r2
  orr.w r3, r3, r4
  and.w r4, r9, r10
  ldr.w r9, [r0, #504]
  ldr.w r10, [r0, #508]
  eor.w r4, r4, r9
  eor.w r9, r3, r9
  eor.w r3, r3, r10
  eor.w r10, r4, r10
  and.w r4, r3, r4
  orr.w r3, r9, r10
  str.w r11, [r0, #632]
  str.w r7, [r0, #376]
  str.w r3, [r0, #120]
  str.w r12, [r0, #636]
  str.w r8, [r0, #380]
  str.w r4, [r0, #124]
  cmp.w r0, lr
  bne.w polyf3_mul768_packed_asm_compose_output_A
  add.w lr, r0, #64
  sub.w r0, r0, #64
polyf3_mul768_packed_asm_compose_output_B:
  ldr.w r11, [r0, #576]
  ldr.w r7, [r0, #320]
  ldr.w r5, [r0, #128]
  ldr.w r3, [r0], #4
  ldr.w r12, [r0, #576]
  ldr.w r8, [r0, #320]
  ldr.w r6, [r0, #128]
  ldr.w r4, [r0], #4
  eor.w r4, r4, r7
  eor.w r7, r3, r7
  eor.w r3, r3, r8
  eor.w r8, r4, r8
  and.w r4, r3, r4
  orr.w r3, r7, r8
  eor.w r6, r6, r11
  eor.w r11, r5, r11
  eor.w r5, r5, r12
  eor.w r12, r6, r12
  and.w r6, r5, r6
  orr.w r5, r11, r12
  str.w r5, [r0, #120]
  str.w r3, [r0, #-8]
  str.w r6, [r0, #124]
  str.w r4, [r0, #-4]
  cmp.w r0, lr
  bne.w polyf3_mul768_packed_asm_compose_output_B
  sub.w r0, r0, #192
  vmov.w lr, s0
  add.w r1, r0, #352
polyf3_mul768_packed_asm_copy_output_body:
  ldm.w r0!, {r2-r12}
  stm.w lr!, {r2-r12}
  cmp.w r0, r1
  bne.w polyf3_mul768_packed_asm_copy_output_body
  ldr.w r2, [r0], #4
  ldr.w r3, [r0], #4
  ldr.w r4, [r0], #4
  ldr.w r5, [r0], #4
  ldr.w r6, [r0], #4
  ldr.w r7, [r0], #4
  ldr.w r8, [r0], #4
  ldr.w r9, [r0], #4
  str.w r2, [lr], #4
  str.w r3, [lr], #4
  str.w r4, [lr], #4
  str.w r5, [lr], #4
  str.w r6, [lr], #4
  str.w r7, [lr], #4
  str.w r8, [lr], #4
  str.w r9, [lr], #4
  add.w sp, sp, #1152
  pop.w {r4-r12, pc}
