.p2align 2,,3
.syntax unified
.text

.global polyf3_pack_asm
.type polyf3_pack_asm, %function
@ void polyf3_pack_asm(uint32_t* tritOut, uint32_t* mod3In)
polyf3_pack_asm:
  push.w {r4-r12, lr}
  add.w r2, r0, #192
unit_pack:
  ldr.w r3, [r1], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r1], #4
  ldr.w r7, [r1], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r1], #4
  ldr.w r11, [r1], #4
  bfi.w r12, r3, #0, #2
  lsr.w r3, r3, #16
  bfi.w lr, r3, #0, #2
  bfi.w r12, r4, #2, #2
  lsr.w r4, r4, #16
  bfi.w lr, r4, #2, #2
  bfi.w r12, r5, #4, #2
  lsr.w r5, r5, #16
  bfi.w lr, r5, #4, #2
  bfi.w r12, r6, #6, #2
  lsr.w r6, r6, #16
  bfi.w lr, r6, #6, #2
  bfi.w r12, r7, #8, #2
  lsr.w r7, r7, #16
  bfi.w lr, r7, #8, #2
  bfi.w r12, r8, #10, #2
  lsr.w r8, r8, #16
  bfi.w lr, r8, #10, #2
  bfi.w r12, r9, #12, #2
  lsr.w r9, r9, #16
  bfi.w lr, r9, #12, #2
  bfi.w r12, r10, #14, #2
  lsr.w r10, r10, #16
  bfi.w lr, r10, #14, #2
  bfi.w r12, r11, #16, #2
  lsr.w r11, r11, #16
  bfi.w lr, r11, #16, #2
  ldr.w r3, [r1], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r1], #4
  ldr.w r7, [r1], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  bfi.w r12, r3, #18, #2
  lsr.w r3, r3, #16
  bfi.w lr, r3, #18, #2
  bfi.w r12, r4, #20, #2
  lsr.w r4, r4, #16
  bfi.w lr, r4, #20, #2
  bfi.w r12, r5, #22, #2
  lsr.w r5, r5, #16
  bfi.w lr, r5, #22, #2
  bfi.w r12, r6, #24, #2
  lsr.w r6, r6, #16
  bfi.w lr, r6, #24, #2
  bfi.w r12, r7, #26, #2
  lsr.w r7, r7, #16
  bfi.w lr, r7, #26, #2
  bfi.w r12, r8, #28, #2
  lsr.w r8, r8, #16
  bfi.w lr, r8, #28, #2
  bfi.w r12, r9, #30, #2
  lsr.w r9, r9, #16
  bfi.w lr, r9, #30, #2
  and.w r3, r12, #0xaaaaaaaa
  and.w r12, r12, #0x55555555
  and.w r4, lr, #0x55555555
  and.w lr, lr, #0xaaaaaaaa
  orr.w r12, r12, r4, lsl #1
  orr.w lr, lr, r3, lsr #1
  str.w r12, [r0], #4
  str.w lr, [r0], #4
  cmp.w r0, r2
  bne.w unit_pack
  pop.w {r4-r12, pc}

.global polyf3_unpack_asm
.type polyf3_unpack_asm, %function
@ void polyf3_unpack_asm(uint32_t* mod3Out, uint32_t* tritIn)
polyf3_unpack_asm:
  push.w {r4-r12, lr}
  add.w r2, r1, #192
unit_unpack:
  ldr.w r3, [r1], #4
  ldr.w r4, [r1], #4
  sbfx.w r5, r4, #0, #1
  and.w r6, r3, #0x1
  orr.w r5, r5, r6
  sbfx.w r6, r4, #1, #1
  and.w r7, r3, #0x2
  orr.w r6, r6, r7, lsr #1
  pkhbt.w r5, r5, r6, lsl #16
  sbfx.w r6, r4, #2, #1
  and.w r7, r3, #0x4
  orr.w r6, r6, r7, lsr #2
  sbfx.w r7, r4, #3, #1
  and.w r8, r3, #0x8
  orr.w r7, r7, r8, lsr #3
  pkhbt.w r6, r6, r7, lsl #16
  sbfx.w r7, r4, #4, #1
  and.w r8, r3, #0x10
  orr.w r7, r7, r8, lsr #4
  sbfx.w r8, r4, #5, #1
  and.w r9, r3, #0x20
  orr.w r8, r8, r9, lsr #5
  pkhbt.w r7, r7, r8, lsl #16
  sbfx.w r8, r4, #6, #1
  and.w r9, r3, #0x40
  orr.w r8, r8, r9, lsr #6
  sbfx.w r9, r4, #7, #1
  and.w r10, r3, #0x80
  orr.w r9, r9, r10, lsr #7
  pkhbt.w r8, r8, r9, lsl #16
  sbfx.w r9, r4, #8, #1
  and.w r10, r3, #0x100
  orr.w r9, r9, r10, lsr #8
  sbfx.w r10, r4, #9, #1
  and.w r11, r3, #0x200
  orr.w r10, r10, r11, lsr #9
  pkhbt.w r9, r9, r10, lsl #16
  sbfx.w r10, r4, #10, #1
  and.w r11, r3, #0x400
  orr.w r10, r10, r11, lsr #10
  sbfx.w r11, r4, #11, #1
  and.w r12, r3, #0x800
  orr.w r11, r11, r12, lsr #11
  pkhbt.w r10, r10, r11, lsl #16
  sbfx.w r11, r4, #12, #1
  and.w r12, r3, #0x1000
  orr.w r11, r11, r12, lsr #12
  sbfx.w r12, r4, #13, #1
  and.w lr, r3, #0x2000
  orr.w r12, r12, lr, lsr #13
  pkhbt.w r11, r11, r12, lsl #16
  str.w r5, [r0], #4
  str.w r6, [r0], #4
  str.w r7, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  str.w r10, [r0], #4
  str.w r11, [r0], #4
  sbfx.w r5, r4, #14, #1
  and.w r6, r3, #0x4000
  orr.w r5, r5, r6, lsr #14
  sbfx.w r6, r4, #15, #1
  and.w r7, r3, #0x8000
  orr.w r6, r6, r7, lsr #15
  pkhbt.w r5, r5, r6, lsl #16
  sbfx.w r6, r4, #16, #1
  and.w r7, r3, #0x10000
  orr.w r6, r6, r7, lsr #16
  sbfx.w r7, r4, #17, #1
  and.w r8, r3, #0x20000
  orr.w r7, r7, r8, lsr #17
  pkhbt.w r6, r6, r7, lsl #16
  sbfx.w r7, r4, #18, #1
  and.w r8, r3, #0x40000
  orr.w r7, r7, r8, lsr #18
  sbfx.w r8, r4, #19, #1
  and.w r9, r3, #0x80000
  orr.w r8, r8, r9, lsr #19
  pkhbt.w r7, r7, r8, lsl #16
  sbfx.w r8, r4, #20, #1
  and.w r9, r3, #0x100000
  orr.w r8, r8, r9, lsr #20
  sbfx.w r9, r4, #21, #1
  and.w r10, r3, #0x200000
  orr.w r9, r9, r10, lsr #21
  pkhbt.w r8, r8, r9, lsl #16
  sbfx.w r9, r4, #22, #1
  and.w r10, r3, #0x400000
  orr.w r9, r9, r10, lsr #22
  sbfx.w r10, r4, #23, #1
  and.w r11, r3, #0x800000
  orr.w r10, r10, r11, lsr #23
  pkhbt.w r9, r9, r10, lsl #16
  sbfx.w r10, r4, #24, #1
  and.w r11, r3, #0x1000000
  orr.w r10, r10, r11, lsr #24
  sbfx.w r11, r4, #25, #1
  and.w r12, r3, #0x2000000
  orr.w r11, r11, r12, lsr #25
  pkhbt.w r10, r10, r11, lsl #16
  sbfx.w r11, r4, #26, #1
  and.w r12, r3, #0x4000000
  orr.w r11, r11, r12, lsr #26
  sbfx.w r12, r4, #27, #1
  and.w lr, r3, #0x8000000
  orr.w r12, r12, lr, lsr #27
  pkhbt.w r11, r11, r12, lsl #16
  str.w r5, [r0], #4
  str.w r6, [r0], #4
  str.w r7, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  str.w r10, [r0], #4
  str.w r11, [r0], #4
  sbfx.w r5, r4, #28, #1
  and.w r6, r3, #0x10000000
  orr.w r5, r5, r6, lsr #28
  sbfx.w r6, r4, #29, #1
  and.w r7, r3, #0x20000000
  orr.w r6, r6, r7, lsr #29
  pkhbt.w r5, r5, r6, lsl #16
  sbfx.w r6, r4, #30, #1
  and.w r7, r3, #0x40000000
  orr.w r6, r6, r7, lsr #30
  sbfx.w r7, r4, #31, #1
  and.w r8, r3, #0x80000000
  orr.w r7, r7, r8, lsr #31
  pkhbt.w r6, r6, r7, lsl #16
  str.w r5, [r0], #4
  str.w r6, [r0], #4
  cmp.w r1, r2
  bne.w unit_unpack
  pop.w {r4-r12, pc}

.global polyf3_add_packed_asm
.type polyf3_add_packed_asm, %function
@ void polyf3_add_packed_asm(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2)
polyf3_add_packed_asm:
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r5, r6
  eor.w r5, r4, r7
  and.w r5, r5, r12
  eor.w r12, r12, r7
  eor.w r4, r4, r6
  orr.w r4, r4, r12
  eor.w r12, r9, r10
  eor.w r9, r8, r11
  and.w r9, r9, r12
  push.w {r4-r12, lr}
  eor.w r12, r12, r11
  eor.w r8, r8, r10
  orr.w r8, r8, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r5, r6
  eor.w r5, r4, r7
  and.w r5, r5, r12
  eor.w r12, r12, r7
  eor.w r4, r4, r6
  orr.w r4, r4, r12
  eor.w r12, r9, r10
  eor.w r9, r8, r11
  and.w r9, r9, r12
  push.w {r4-r12, lr}
  eor.w r12, r12, r11
  eor.w r8, r8, r10
  orr.w r8, r8, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r5, r6
  eor.w r5, r4, r7
  and.w r5, r5, r12
  eor.w r12, r12, r7
  eor.w r4, r4, r6
  orr.w r4, r4, r12
  eor.w r12, r9, r10
  eor.w r9, r8, r11
  and.w r9, r9, r12
  push.w {r4-r12, lr}
  eor.w r12, r12, r11
  eor.w r8, r8, r10
  orr.w r8, r8, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r5, r6
  eor.w r5, r4, r7
  and.w r5, r5, r12
  eor.w r12, r12, r7
  eor.w r4, r4, r6
  orr.w r4, r4, r12
  eor.w r12, r9, r10
  eor.w r9, r8, r11
  and.w r9, r9, r12
  push.w {r4-r12, lr}
  eor.w r12, r12, r11
  eor.w r8, r8, r10
  orr.w r8, r8, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r5, r6
  eor.w r5, r4, r7
  and.w r5, r5, r12
  eor.w r12, r12, r7
  eor.w r4, r4, r6
  orr.w r4, r4, r12
  eor.w r12, r9, r10
  eor.w r9, r8, r11
  and.w r9, r9, r12
  push.w {r4-r12, lr}
  eor.w r12, r12, r11
  eor.w r8, r8, r10
  orr.w r8, r8, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r5, r6
  eor.w r5, r4, r7
  and.w r5, r5, r12
  eor.w r12, r12, r7
  eor.w r4, r4, r6
  orr.w r4, r4, r12
  eor.w r12, r9, r10
  eor.w r9, r8, r11
  and.w r9, r9, r12
  push.w {r4-r12, lr}
  eor.w r12, r12, r11
  eor.w r8, r8, r10
  orr.w r8, r8, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r5, r6
  eor.w r5, r4, r7
  and.w r5, r5, r12
  eor.w r12, r12, r7
  eor.w r4, r4, r6
  orr.w r4, r4, r12
  eor.w r12, r9, r10
  eor.w r9, r8, r11
  and.w r9, r9, r12
  push.w {r4-r12, lr}
  eor.w r12, r12, r11
  eor.w r8, r8, r10
  orr.w r8, r8, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r5, r6
  eor.w r5, r4, r7
  and.w r5, r5, r12
  eor.w r12, r12, r7
  eor.w r4, r4, r6
  orr.w r4, r4, r12
  eor.w r12, r9, r10
  eor.w r9, r8, r11
  and.w r9, r9, r12
  push.w {r4-r12, lr}
  eor.w r12, r12, r11
  eor.w r8, r8, r10
  orr.w r8, r8, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r5, r6
  eor.w r5, r4, r7
  and.w r5, r5, r12
  eor.w r12, r12, r7
  eor.w r4, r4, r6
  orr.w r4, r4, r12
  eor.w r12, r9, r10
  eor.w r9, r8, r11
  and.w r9, r9, r12
  push.w {r4-r12, lr}
  eor.w r12, r12, r11
  eor.w r8, r8, r10
  orr.w r8, r8, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r5, r6
  eor.w r5, r4, r7
  and.w r5, r5, r12
  eor.w r12, r12, r7
  eor.w r4, r4, r6
  orr.w r4, r4, r12
  eor.w r12, r9, r10
  eor.w r9, r8, r11
  and.w r9, r9, r12
  push.w {r4-r12, lr}
  eor.w r12, r12, r11
  eor.w r8, r8, r10
  orr.w r8, r8, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r5, r6
  eor.w r5, r4, r7
  and.w r5, r5, r12
  eor.w r12, r12, r7
  eor.w r4, r4, r6
  orr.w r4, r4, r12
  eor.w r12, r9, r10
  eor.w r9, r8, r11
  and.w r9, r9, r12
  push.w {r4-r12, lr}
  eor.w r12, r12, r11
  eor.w r8, r8, r10
  orr.w r8, r8, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r5, r6
  eor.w r5, r4, r7
  and.w r5, r5, r12
  eor.w r12, r12, r7
  eor.w r4, r4, r6
  orr.w r4, r4, r12
  eor.w r12, r9, r10
  eor.w r9, r8, r11
  and.w r9, r9, r12
  push.w {r4-r12, lr}
  eor.w r12, r12, r11
  eor.w r8, r8, r10
  orr.w r8, r8, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  pop.w {r4-r12, pc}

.global polyf3_sub_packed_asm
.type polyf3_sub_packed_asm, %function
@ void polyf3_sub_packed_asm(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2)
polyf3_sub_packed_asm:
  push.w {r4-r12, lr}
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r4, r6
  eor.w r4, r5, r7
  orr.w r4, r4, r12
  eor.w r12, r12, r7
  eor.w r5, r5, r6
  and.w r5, r5, r12
  eor.w r12, r8, r10
  eor.w r8, r9, r11
  orr.w r8, r8, r12
  eor.w r12, r12, r11
  eor.w r9, r9, r10
  and.w r9, r9, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r4, r6
  eor.w r4, r5, r7
  orr.w r4, r4, r12
  eor.w r12, r12, r7
  eor.w r5, r5, r6
  and.w r5, r5, r12
  eor.w r12, r8, r10
  eor.w r8, r9, r11
  orr.w r8, r8, r12
  eor.w r12, r12, r11
  eor.w r9, r9, r10
  and.w r9, r9, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r4, r6
  eor.w r4, r5, r7
  orr.w r4, r4, r12
  eor.w r12, r12, r7
  eor.w r5, r5, r6
  and.w r5, r5, r12
  eor.w r12, r8, r10
  eor.w r8, r9, r11
  orr.w r8, r8, r12
  eor.w r12, r12, r11
  eor.w r9, r9, r10
  and.w r9, r9, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r4, r6
  eor.w r4, r5, r7
  orr.w r4, r4, r12
  eor.w r12, r12, r7
  eor.w r5, r5, r6
  and.w r5, r5, r12
  eor.w r12, r8, r10
  eor.w r8, r9, r11
  orr.w r8, r8, r12
  eor.w r12, r12, r11
  eor.w r9, r9, r10
  and.w r9, r9, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r4, r6
  eor.w r4, r5, r7
  orr.w r4, r4, r12
  eor.w r12, r12, r7
  eor.w r5, r5, r6
  and.w r5, r5, r12
  eor.w r12, r8, r10
  eor.w r8, r9, r11
  orr.w r8, r8, r12
  eor.w r12, r12, r11
  eor.w r9, r9, r10
  and.w r9, r9, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r4, r6
  eor.w r4, r5, r7
  orr.w r4, r4, r12
  eor.w r12, r12, r7
  eor.w r5, r5, r6
  and.w r5, r5, r12
  eor.w r12, r8, r10
  eor.w r8, r9, r11
  orr.w r8, r8, r12
  eor.w r12, r12, r11
  eor.w r9, r9, r10
  and.w r9, r9, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r4, r6
  eor.w r4, r5, r7
  orr.w r4, r4, r12
  eor.w r12, r12, r7
  eor.w r5, r5, r6
  and.w r5, r5, r12
  eor.w r12, r8, r10
  eor.w r8, r9, r11
  orr.w r8, r8, r12
  eor.w r12, r12, r11
  eor.w r9, r9, r10
  and.w r9, r9, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r4, r6
  eor.w r4, r5, r7
  orr.w r4, r4, r12
  eor.w r12, r12, r7
  eor.w r5, r5, r6
  and.w r5, r5, r12
  eor.w r12, r8, r10
  eor.w r8, r9, r11
  orr.w r8, r8, r12
  eor.w r12, r12, r11
  eor.w r9, r9, r10
  and.w r9, r9, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r4, r6
  eor.w r4, r5, r7
  orr.w r4, r4, r12
  eor.w r12, r12, r7
  eor.w r5, r5, r6
  and.w r5, r5, r12
  eor.w r12, r8, r10
  eor.w r8, r9, r11
  orr.w r8, r8, r12
  eor.w r12, r12, r11
  eor.w r9, r9, r10
  and.w r9, r9, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r4, r6
  eor.w r4, r5, r7
  orr.w r4, r4, r12
  eor.w r12, r12, r7
  eor.w r5, r5, r6
  and.w r5, r5, r12
  eor.w r12, r8, r10
  eor.w r8, r9, r11
  orr.w r8, r8, r12
  eor.w r12, r12, r11
  eor.w r9, r9, r10
  and.w r9, r9, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r4, r6
  eor.w r4, r5, r7
  orr.w r4, r4, r12
  eor.w r12, r12, r7
  eor.w r5, r5, r6
  and.w r5, r5, r12
  eor.w r12, r8, r10
  eor.w r8, r9, r11
  orr.w r8, r8, r12
  eor.w r12, r12, r11
  eor.w r9, r9, r10
  and.w r9, r9, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r1], #4
  ldr.w r6, [r2], #4
  ldr.w r7, [r2], #4
  ldr.w r8, [r1], #4
  ldr.w r9, [r1], #4
  ldr.w r10, [r2], #4
  ldr.w r11, [r2], #4
  eor.w r12, r4, r6
  eor.w r4, r5, r7
  orr.w r4, r4, r12
  eor.w r12, r12, r7
  eor.w r5, r5, r6
  and.w r5, r5, r12
  eor.w r12, r8, r10
  eor.w r8, r9, r11
  orr.w r8, r8, r12
  eor.w r12, r12, r11
  eor.w r9, r9, r10
  and.w r9, r9, r12
  str.w r4, [r0], #4
  str.w r5, [r0], #4
  str.w r8, [r0], #4
  str.w r9, [r0], #4
  pop.w {r4-r12, pc}

.global polyf3_mul_packed_asm
.type polyf3_mul_packed_asm, %function
@ void polyf3_mul_packed_asm(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2)
polyf3_mul_packed_asm:
  push.w {r4-r12, lr}
  add.w r3, r0, #16
  vmov.w s0, r3
unit_mul:
  ldr.w r3, [r1], #4
  ldr.w r4, [r1], #4
  ldr.w r5, [r2], #4
  ldr.w r6, [r2], #4
  sbfx.w r7, r3, #0, #1
  sbfx.w r8, r4, #0, #1
  and.w r7, r7, r5
  eor.w r8, r8, r6
  and.w r8, r8, r7
  bfi.w r9, r7, #0, #1
  bfi.w r10, r8, #0, #1
  sbfx.w r11, r3, #1, #1
  sbfx.w r12, r4, #1, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #1, #1
  bfi.w r10, r8, #1, #1
  sbfx.w r11, r3, #2, #1
  sbfx.w r12, r4, #2, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #2, #1
  bfi.w r10, r8, #2, #1
  sbfx.w r11, r3, #3, #1
  sbfx.w r12, r4, #3, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #3, #1
  bfi.w r10, r8, #3, #1
  sbfx.w r11, r3, #4, #1
  sbfx.w r12, r4, #4, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #4, #1
  bfi.w r10, r8, #4, #1
  sbfx.w r11, r3, #5, #1
  sbfx.w r12, r4, #5, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #5, #1
  bfi.w r10, r8, #5, #1
  sbfx.w r11, r3, #6, #1
  sbfx.w r12, r4, #6, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #6, #1
  bfi.w r10, r8, #6, #1
  sbfx.w r11, r3, #7, #1
  sbfx.w r12, r4, #7, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #7, #1
  bfi.w r10, r8, #7, #1
  sbfx.w r11, r3, #8, #1
  sbfx.w r12, r4, #8, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #8, #1
  bfi.w r10, r8, #8, #1
  sbfx.w r11, r3, #9, #1
  sbfx.w r12, r4, #9, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #9, #1
  bfi.w r10, r8, #9, #1
  sbfx.w r11, r3, #10, #1
  sbfx.w r12, r4, #10, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #10, #1
  bfi.w r10, r8, #10, #1
  sbfx.w r11, r3, #11, #1
  sbfx.w r12, r4, #11, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #11, #1
  bfi.w r10, r8, #11, #1
  sbfx.w r11, r3, #12, #1
  sbfx.w r12, r4, #12, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #12, #1
  bfi.w r10, r8, #12, #1
  sbfx.w r11, r3, #13, #1
  sbfx.w r12, r4, #13, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #13, #1
  bfi.w r10, r8, #13, #1
  sbfx.w r11, r3, #14, #1
  sbfx.w r12, r4, #14, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #14, #1
  bfi.w r10, r8, #14, #1
  sbfx.w r11, r3, #15, #1
  sbfx.w r12, r4, #15, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #15, #1
  bfi.w r10, r8, #15, #1
  sbfx.w r11, r3, #16, #1
  sbfx.w r12, r4, #16, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #16, #1
  bfi.w r10, r8, #16, #1
  sbfx.w r11, r3, #17, #1
  sbfx.w r12, r4, #17, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #17, #1
  bfi.w r10, r8, #17, #1
  sbfx.w r11, r3, #18, #1
  sbfx.w r12, r4, #18, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #18, #1
  bfi.w r10, r8, #18, #1
  sbfx.w r11, r3, #19, #1
  sbfx.w r12, r4, #19, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #19, #1
  bfi.w r10, r8, #19, #1
  sbfx.w r11, r3, #20, #1
  sbfx.w r12, r4, #20, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #20, #1
  bfi.w r10, r8, #20, #1
  sbfx.w r11, r3, #21, #1
  sbfx.w r12, r4, #21, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #21, #1
  bfi.w r10, r8, #21, #1
  sbfx.w r11, r3, #22, #1
  sbfx.w r12, r4, #22, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #22, #1
  bfi.w r10, r8, #22, #1
  sbfx.w r11, r3, #23, #1
  sbfx.w r12, r4, #23, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #23, #1
  bfi.w r10, r8, #23, #1
  sbfx.w r11, r3, #24, #1
  sbfx.w r12, r4, #24, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #24, #1
  bfi.w r10, r8, #24, #1
  sbfx.w r11, r3, #25, #1
  sbfx.w r12, r4, #25, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #25, #1
  bfi.w r10, r8, #25, #1
  sbfx.w r11, r3, #26, #1
  sbfx.w r12, r4, #26, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #26, #1
  bfi.w r10, r8, #26, #1
  sbfx.w r11, r3, #27, #1
  sbfx.w r12, r4, #27, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #27, #1
  bfi.w r10, r8, #27, #1
  sbfx.w r11, r3, #28, #1
  sbfx.w r12, r4, #28, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #28, #1
  bfi.w r10, r8, #28, #1
  sbfx.w r11, r3, #29, #1
  sbfx.w r12, r4, #29, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #29, #1
  bfi.w r10, r8, #29, #1
  sbfx.w r11, r3, #30, #1
  sbfx.w r12, r4, #30, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #30, #1
  bfi.w r10, r8, #30, #1
  sbfx.w r11, r3, #31, #1
  sbfx.w r12, r4, #31, #1
  and.w r11, r11, r5
  eor.w r12, r12, r6
  and.w r12, r12, r11
  eor.w lr, r11, r8, lsr #1
  eor.w r8, r12, r7, lsr #1
  and.w r8, r8, lr
  eor.w lr, lr, r12
  eor.w r7, r11, r7, lsr #1
  orr.w r7, r7, lr
  bfi.w r9, r7, #31, #1
  bfi.w r10, r8, #31, #1
  lsr.w r7, r7, #1
  lsr.w r8, r8, #1
  str.w r9, [r0], #4
  str.w r10, [r0], #4
  str.w r7, [r0], #4
  str.w r8, [r0], #4
  vmov.w r3, s0
  cmp.w r0, r3
  bne.w unit_mul
  pop.w {r4-r12, pc}

.global polyf3_ror767_asm
.type polyf3_ror767_asm, %function
@ void polyf3_ror767_asm(uint32_t *tritIn)
polyf3_ror767_asm:
  push {r4-r12, lr}
  adds r3, #0
  ldr r3, [r0, #0]
  ldr r4, [r0, #8]
  ldr r5, [r0, #16]
  ldr r6, [r0, #24]
  ldr r7, [r0, #32]
  ldr r8, [r0, #40]
  ldr r9, [r0, #48]
  ldr r10, [r0, #56]
  adcs r3, r3
  adcs r4, r4
  adcs r5, r5
  adcs r6, r6
  adcs r7, r7
  adcs r8, r8
  adcs r9, r9
  adcs r10, r10
  str r3, [r0, #0]
  str r4, [r0, #8]
  str r5, [r0, #16]
  str r6, [r0, #24]
  str r7, [r0, #32]
  str r8, [r0, #40]
  str r9, [r0, #48]
  str r10, [r0, #56]
  ldr r3, [r0, #64]
  ldr r4, [r0, #72]
  ldr r5, [r0, #80]
  ldr r6, [r0, #88]
  ldr r7, [r0, #96]
  ldr r8, [r0, #104]
  ldr r9, [r0, #112]
  ldr r10, [r0, #120]
  adcs r3, r3
  adcs r4, r4
  adcs r5, r5
  adcs r6, r6
  adcs r7, r7
  adcs r8, r8
  adcs r9, r9
  adcs r10, r10
  str r3, [r0, #64]
  str r4, [r0, #72]
  str r5, [r0, #80]
  str r6, [r0, #88]
  str r7, [r0, #96]
  str r8, [r0, #104]
  str r9, [r0, #112]
  str r10, [r0, #120]
  ldr r3, [r0, #128]
  ldr r4, [r0, #136]
  ldr r5, [r0, #144]
  ldr r6, [r0, #152]
  ldr r7, [r0, #160]
  ldr r8, [r0, #168]
  ldr r9, [r0, #176]
  ldr r10, [r0, #184]
  adcs r3, r3
  adcs r4, r4
  adcs r5, r5
  adcs r6, r6
  adcs r7, r7
  adcs r8, r8
  adcs r9, r9
  adcs r10, r10
  str r3, [r0, #128]
  str r4, [r0, #136]
  str r5, [r0, #144]
  str r6, [r0, #152]
  str r7, [r0, #160]
  str r8, [r0, #168]
  str r9, [r0, #176]
  str r10, [r0, #184]
  adds r3, #0
  ldr r3, [r0, #4]
  ldr r4, [r0, #12]
  ldr r5, [r0, #20]
  ldr r6, [r0, #28]
  ldr r7, [r0, #36]
  ldr r8, [r0, #44]
  ldr r9, [r0, #52]
  ldr r10, [r0, #60]
  adcs r3, r3
  adcs r4, r4
  adcs r5, r5
  adcs r6, r6
  adcs r7, r7
  adcs r8, r8
  adcs r9, r9
  adcs r10, r10
  str r3, [r0, #4]
  str r4, [r0, #12]
  str r5, [r0, #20]
  str r6, [r0, #28]
  str r7, [r0, #36]
  str r8, [r0, #44]
  str r9, [r0, #52]
  str r10, [r0, #60]
  ldr r3, [r0, #68]
  ldr r4, [r0, #76]
  ldr r5, [r0, #84]
  ldr r6, [r0, #92]
  ldr r7, [r0, #100]
  ldr r8, [r0, #108]
  ldr r9, [r0, #116]
  ldr r10, [r0, #124]
  adcs r3, r3
  adcs r4, r4
  adcs r5, r5
  adcs r6, r6
  adcs r7, r7
  adcs r8, r8
  adcs r9, r9
  adcs r10, r10
  str r3, [r0, #68]
  str r4, [r0, #76]
  str r5, [r0, #84]
  str r6, [r0, #92]
  str r7, [r0, #100]
  str r8, [r0, #108]
  str r9, [r0, #116]
  str r10, [r0, #124]
  ldr r3, [r0, #132]
  ldr r4, [r0, #140]
  ldr r5, [r0, #148]
  ldr r6, [r0, #156]
  ldr r7, [r0, #164]
  ldr r8, [r0, #172]
  ldr r9, [r0, #180]
  ldr r10, [r0, #188]
  adcs r3, r3
  adcs r4, r4
  adcs r5, r5
  adcs r6, r6
  adcs r7, r7
  adcs r8, r8
  adcs r9, r9
  adcs r10, r10
  str r3, [r0, #132]
  str r4, [r0, #140]
  str r5, [r0, #148]
  str r6, [r0, #156]
  str r7, [r0, #164]
  str r8, [r0, #172]
  str r9, [r0, #180]
  str r10, [r0, #188]
  pop {r4-r12, pc}

