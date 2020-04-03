#include "libopencm3/cm3/dwt.h"
#include "my-mod3.h"
#include "cmsis.h"
#include <stdio.h>

#define start_timer() dwt_enable_cycle_counter()
#define get_timer() dwt_read_cycle_counter()
#define stop_timer() *((volatile uint32_t*)0xE0001000) = 0x40000000


void polyf3_selftest_add() {
    start_timer();
    uint32_t f[48] = {1}, g[48] = {0}, h[96] = {0};
    uint32_t t0, t1;

    t0 = get_timer();
    bs3_add32(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_add32: %ld\n", t1-t0);

    t0 = get_timer();
    bs3_add64(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_add64: %ld\n", t1-t0);

    t0 = get_timer();
    bs3_add128(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_add128: %ld\n", t1-t0);

    t0 = get_timer();
    bs3_add256(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_add256: %ld\n", t1-t0);

    t0 = get_timer();
    bs3_add512(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_add512: %ld\n", t1-t0);

    stop_timer();
}

void polyf3_selftest_sub() {
    start_timer();
    uint32_t f[48] = {1}, g[48] = {0}, h[96] = {0};
    uint32_t t0, t1;

    t0 = get_timer();
    bs3_sub32(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_sub32: %ld\n", t1-t0);

    t0 = get_timer();
    bs3_sub64(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_sub64: %ld\n", t1-t0);

    t0 = get_timer();
    bs3_sub128(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_sub128: %ld\n", t1-t0);

    t0 = get_timer();
    bs3_sub256(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_sub256: %ld\n", t1-t0);

    t0 = get_timer();
    bs3_sub512(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_sub512: %ld\n", t1-t0);

    stop_timer();
}

void polyf3_selftest_mul() {
    start_timer();
    uint32_t f[48] = {1}, g[48] = {0}, h[96] = {0};
    uint32_t t0, t1;

    t0 = get_timer();
    bs3_mul32(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_mul32: %ld\n", t1-t0);

    t0 = get_timer();
    bs3_mul64(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_mul64: %ld\n", t1-t0);

    t0 = get_timer();
    bs3_mul128(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_mul128: %ld\n", t1-t0);

    t0 = get_timer();
    bs3_mul256(h, f, g);
    t1 = get_timer();
    printf("Elapsed cycles for bs3_mul256: %ld\n", t1-t0);

    stop_timer();
}

void polyf3_selftest_mmuls() {
    start_timer();
    uint32_t f[48] = {1}, g[48] = {0}, h[96] = {0};
    uint32_t t0, t1;
    uint32_t uvrs[192] = {[0] = 1, [144] = 1};
	uint32_t uvrs1[192] = {[0] = 1, [144] = 1}, uvrs2[192] = {[0] = 1, [144] = 1};

    t0 = get_timer();
    polyf3_mmul32s(uvrs, uvrs1, uvrs2);
    t1 = get_timer();
    printf("Elapsed cycles for mmul32s: %ld\n", t1-t0);

    t0 = get_timer();
    polyf3_mmul64s(uvrs, uvrs1, uvrs2);
    t1 = get_timer();
    printf("Elapsed cycles for mmul64s: %ld\n", t1-t0);

    t0 = get_timer();
    polyf3_mmul128s(uvrs, uvrs1, uvrs2);
    t1 = get_timer();
    printf("Elapsed cycles for mmul128s: %ld\n", t1-t0);

    t0 = get_timer();
    polyf3_mmul256s(uvrs, uvrs1, uvrs2);
    t1 = get_timer();
    printf("Elapsed cycles for mmul256s: %ld\n", t1-t0);

    stop_timer();
}

void polyf3_pack_fast(uint32_t *tritOut, uint32_t *mod3In) {
    polyf3_pack_asm(tritOut, mod3In);
}

void polyf3_unpack_fast(uint32_t *mod3Out, uint32_t *tritIn) {
    polyf3_unpack_asm(mod3Out, tritIn);
}

void polyf3_add_packed_fast(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    polyf3_add_packed_asm(tritOut, tritIn1, tritIn2);
}

void polyf3_sub_packed_fast(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    polyf3_sub_packed_asm(tritOut, tritIn1, tritIn2);
}

void polyf3_mul_packed_fast(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    polyf3_mul_packed_asm(tritOut, tritIn1, tritIn2);
}

// assert input size = 768
// TODO: the possibility to exploit "signs"
// TODO: the possibility to exploit BFI
void polyf3_pack(uint32_t *tritOut, uint32_t *mod3In) {
  uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
  uint32_t *writeTrit, *readMod3, *bndry;

  readMod3 = mod3In;
  writeTrit = tritOut;
  bndry = writeTrit + 48;
  while (writeTrit != bndry) {
    r0 = *(readMod3++);
    r1 = *(readMod3++);
    r2 = *(readMod3++);
    r3 = *(readMod3++);
    r4 = *(readMod3++);

    r5 = r0 & 0x00000001;
    r6 = r0 & 0x00000002;
    r7 = r0 & 0x00010000;
    r8 = r0 & 0x00020000;

    r9 = r1 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r1 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r1 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r1 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r9 = r2 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r2 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r2 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r2 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r9 = r3 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r3 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r3 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r3 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r9 = r4 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r4 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r4 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r4 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r0 = *(readMod3++);
    r1 = *(readMod3++);
    r2 = *(readMod3++);
    r3 = *(readMod3++);
    r4 = *(readMod3++);

    r9 = r0 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r0 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r0 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r0 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r9 = r1 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r1 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r1 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r1 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r9 = r2 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r2 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r2 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r2 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r9 = r3 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r3 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r3 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r3 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r9 = r4 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r4 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r4 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r4 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r0 = *(readMod3++);
    r1 = *(readMod3++);
    r2 = *(readMod3++);
    r3 = *(readMod3++);
    r4 = *(readMod3++);

    r9 = r0 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r0 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r0 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r0 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r9 = r1 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r1 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r1 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r1 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r9 = r2 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r2 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r2 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r2 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r9 = r3 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r3 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r3 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r3 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r9 = r4 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r4 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r4 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r4 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r0 = *(readMod3++);

    r9 = r0 & 0x00000001;
    r5 = __ORR_ROR(r9, r5, 30);
    r9 = r0 & 0x00000002;
    r6 = __ORR_ROR(r9, r6, 30);
    r9 = r0 & 0x00010000;
    r7 = __ORR_ROR(r9, r7, 30);
    r9 = r0 & 0x00020000;
    r8 = __ORR_ROR(r9, r8, 30);

    r5 = __ROR(r5, 31);
    r5 = __ORR_ROR(r5, r7, 16);
    r6 = __ORR_ROR(r6, r8, 17);
    *(writeTrit++) = r5;
    *(writeTrit++) = r6;
  }
}

// assert input size = 768
void polyf3_unpack(uint32_t *mod3Out, uint32_t *tritIn) {
  uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
  uint32_t *readTrit, *writeMod3, *bndry;

  readTrit = tritIn;
  bndry = readTrit + 48;
  writeMod3 = mod3Out;
  while (readTrit != bndry) {
    r0 = *(readTrit++);
    r1 = *(readTrit++);

    r2 = __SBFX(r1, 31, 1);
    r3 = r0 & 0x80000000;
    r2 = __ORR_LSR(r2, r3, 31);
    r3 = __SBFX(r1, 30, 1);
    r4 = r0 & 0x40000000;
    r3 = __ORR_LSR(r3, r4, 30);
    r2 = __PKHBT(r2, r3, 16);

    r3 = __SBFX(r1, 29, 1);
    r4 = r0 & 0x20000000;
    r3 = __ORR_LSR(r3, r4, 29);
    r4 = __SBFX(r1, 28, 1);
    r5 = r0 & 0x10000000;
    r4 = __ORR_LSR(r4, r5, 28);
    r3 = __PKHBT(r3, r4, 16);

    r4 = __SBFX(r1, 27, 1);
    r5 = r0 & 0x08000000;
    r4 = __ORR_LSR(r4, r5, 27);
    r5 = __SBFX(r1, 26, 1);
    r6 = r0 & 0x04000000;
    r5 = __ORR_LSR(r5, r6, 26);
    r4 = __PKHBT(r4, r5, 16);

    r5 = __SBFX(r1, 25, 1);
    r6 = r0 & 0x02000000;
    r5 = __ORR_LSR(r5, r6, 25);
    r6 = __SBFX(r1, 24, 1);
    r7 = r0 & 0x01000000;
    r6 = __ORR_LSR(r6, r7, 24);
    r5 = __PKHBT(r5, r6, 16);

    r6 = __SBFX(r1, 23, 1);
    r7 = r0 & 0x00800000;
    r6 = __ORR_LSR(r6, r7, 23);
    r7 = __SBFX(r1, 22, 1);
    r8 = r0 & 0x00400000;
    r7 = __ORR_LSR(r7, r8, 22);
    r6 = __PKHBT(r6, r7, 16);

    r7 = __SBFX(r1, 21, 1);
    r8 = r0 & 0x00200000;
    r7 = __ORR_LSR(r7, r8, 21);
    r8 = __SBFX(r1, 20, 1);
    r9 = r0 & 0x00100000;
    r8 = __ORR_LSR(r8, r9, 20);
    r7 = __PKHBT(r7, r8, 16);

    *(writeMod3++) = r2;
    *(writeMod3++) = r3;
    *(writeMod3++) = r4;
    *(writeMod3++) = r5;
    *(writeMod3++) = r6;
    *(writeMod3++) = r7;

    r2 = __SBFX(r1, 19, 1);
    r3 = r0 & 0x00080000;
    r2 = __ORR_LSR(r2, r3, 19);
    r3 = __SBFX(r1, 18, 1);
    r4 = r0 & 0x00040000;
    r3 = __ORR_LSR(r3, r4, 18);
    r2 = __PKHBT(r2, r3, 16);

    r3 = __SBFX(r1, 17, 1);
    r4 = r0 & 0x00020000;
    r3 = __ORR_LSR(r3, r4, 17);
    r4 = __SBFX(r1, 16, 1);
    r5 = r0 & 0x00010000;
    r4 = __ORR_LSR(r4, r5, 16);
    r3 = __PKHBT(r3, r4, 16);

    r4 = __SBFX(r1, 15, 1);
    r5 = r0 & 0x00008000;
    r4 = __ORR_LSR(r4, r5, 15);
    r5 = __SBFX(r1, 14, 1);
    r6 = r0 & 0x00004000;
    r5 = __ORR_LSR(r5, r6, 14);
    r4 = __PKHBT(r4, r5, 16);

    r5 = __SBFX(r1, 13, 1);
    r6 = r0 & 0x00002000;
    r5 = __ORR_LSR(r5, r6, 13);
    r6 = __SBFX(r1, 12, 1);
    r7 = r0 & 0x00001000;
    r6 = __ORR_LSR(r6, r7, 12);
    r5 = __PKHBT(r5, r6, 16);

    r6 = __SBFX(r1, 11, 1);
    r7 = r0 & 0x00000800;
    r6 = __ORR_LSR(r6, r7, 11);
    r7 = __SBFX(r1, 10, 1);
    r8 = r0 & 0x00000400;
    r7 = __ORR_LSR(r7, r8, 10);
    r6 = __PKHBT(r6, r7, 16);

    r7 = __SBFX(r1, 9, 1);
    r8 = r0 & 0x00000200;
    r7 = __ORR_LSR(r7, r8, 9);
    r8 = __SBFX(r1, 8, 1);
    r9 = r0 & 0x00000100;
    r8 = __ORR_LSR(r8, r9, 8);
    r7 = __PKHBT(r7, r8, 16);

    *(writeMod3++) = r2;
    *(writeMod3++) = r3;
    *(writeMod3++) = r4;
    *(writeMod3++) = r5;
    *(writeMod3++) = r6;
    *(writeMod3++) = r7;

    r2 = __SBFX(r1, 7, 1);
    r3 = r0 & 0x00000080;
    r2 = __ORR_LSR(r2, r3, 7);
    r3 = __SBFX(r1, 6, 1);
    r4 = r0 & 0x00000040;
    r3 = __ORR_LSR(r3, r4, 6);
    r2 = __PKHBT(r2, r3, 16);

    r3 = __SBFX(r1, 5, 1);
    r4 = r0 & 0x00000020;
    r3 = __ORR_LSR(r3, r4, 5);
    r4 = __SBFX(r1, 4, 1);
    r5 = r0 & 0x00000010;
    r4 = __ORR_LSR(r4, r5, 4);
    r3 = __PKHBT(r3, r4, 16);

    r4 = __SBFX(r1, 3, 1);
    r5 = r0 & 0x00000008;
    r4 = __ORR_LSR(r4, r5, 3);
    r5 = __SBFX(r1, 2, 1);
    r6 = r0 & 0x00000004;
    r5 = __ORR_LSR(r5, r6, 2);
    r4 = __PKHBT(r4, r5, 16);

    r5 = __SBFX(r1, 1, 1);
    r6 = r0 & 0x00000002;
    r5 = __ORR_LSR(r5, r6, 1);
    r6 = __SBFX(r1, 0, 1);
    r7 = r0 & 0x00000001;
    r6 = __ORR_LSR(r6, r7, 0);
    r5 = __PKHBT(r5, r6, 16);

    *(writeMod3++) = r2;
    *(writeMod3++) = r3;
    *(writeMod3++) = r4;
    *(writeMod3++) = r5;
  }
}

// assert input size = 768
void polyf3_add_packed(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
    uint32_t *readOp1, *readOp2, *writeSum, *bndry;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;
    bndry = writeSum + 48;
    while (writeSum != bndry) {
        r0 = *(readOp1++); // a0
        r1 = *(readOp1++); // a1
        r2 = *(readOp2++); // b0
        r3 = *(readOp2++); // b1

        r4 = *(readOp1++); // a0
        r5 = *(readOp1++); // a1
        r6 = *(readOp2++); // b0
        r7 = *(readOp2++); // b1

        r8 = r1 ^ r2;
        r1 = r0 ^ r3;
        r1 = r1 & r8;
        r8 = r8 ^ r3;
        r0 = r0 ^ r2;
        r0 = r0 | r8;

        r8 = r5 ^ r6;
        r5 = r4 ^ r7;
        r5 = r5 & r8;
        r8 = r8 ^ r7;
        r4 = r4 ^ r6;
        r4 = r4 | r8;

        *(writeSum++) = r0;
        *(writeSum++) = r1;
        *(writeSum++) = r4;
        *(writeSum++) = r5;
    }
}

// assert input size = 768
void polyf3_sub_packed(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
  uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
  uint32_t *readOp1, *readOp2, *writeSum, *bndry;

  readOp1 = tritIn1;
  readOp2 = tritIn2;
  writeSum = tritOut;
  bndry = writeSum + 48;
  while (writeSum != bndry) {
    r0 = *(readOp1++); // a0
    r1 = *(readOp1++); // a1
    r2 = *(readOp2++); // b0
    r3 = *(readOp2++); // b1

    r4 = *(readOp1++); // a0
    r5 = *(readOp1++); // a1
    r6 = *(readOp2++); // b0
    r7 = *(readOp2++); // b1

    r8 = r0 ^ r2;
    r0 = r1 ^ r3;
    r0 = r0 | r8;
    r8 = r8 ^ r3;
    r1 = r1 ^ r2;
    r1 = r1 & r8;

    r8 = r4 ^ r6;
    r4 = r5 ^ r7;
    r4 = r4 | r8;
    r8 = r8 ^ r7;
    r5 = r5 ^ r6;
    r5 = r5 & r8;

    *(writeSum++) = r0;
    *(writeSum++) = r1;
    *(writeSum++) = r4;
    *(writeSum++) = r5;
  }
}

// assert input size = 32
void polyf3_mul_packed(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
  uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10;
  uint32_t *readOp1, *readOp2, *writeSum, *bndry;

  readOp1 = tritIn1;
  readOp2 = tritIn2;
  writeSum = tritOut;
  bndry = writeSum + 4;
  while (writeSum != bndry) {
    r0 = *(readOp1++);
    r1 = *(readOp1++);
    r2 = *(readOp2++);
    r3 = *(readOp2++);

    r4 = __SBFX(r0, 0, 1);
    r5 = __SBFX(r1, 0, 1);
    r4 = r4 & r2;
    r5 = r5 ^ r3;
    r5 = r5 & r4;
    r6 = __BFI(r6, r4, 0, 1);
    r7 = __BFI(r7, r5, 0, 1);

    r8 = __SBFX(r0, 1, 1);
    r9 = __SBFX(r1, 1, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 1, 1);
    r7 = __BFI(r7, r5, 1, 1);

    r8 = __SBFX(r0, 2, 1);
    r9 = __SBFX(r1, 2, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 2, 1);
    r7 = __BFI(r7, r5, 2, 1);

    r8 = __SBFX(r0, 3, 1);
    r9 = __SBFX(r1, 3, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 3, 1);
    r7 = __BFI(r7, r5, 3, 1);

    r8 = __SBFX(r0, 4, 1);
    r9 = __SBFX(r1, 4, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 4, 1);
    r7 = __BFI(r7, r5, 4, 1);

    r8 = __SBFX(r0, 5, 1);
    r9 = __SBFX(r1, 5, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 5, 1);
    r7 = __BFI(r7, r5, 5, 1);

    r8 = __SBFX(r0, 6, 1);
    r9 = __SBFX(r1, 6, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 6, 1);
    r7 = __BFI(r7, r5, 6, 1);

    r8 = __SBFX(r0, 7, 1);
    r9 = __SBFX(r1, 7, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 7, 1);
    r7 = __BFI(r7, r5, 7, 1);

    r8 = __SBFX(r0, 8, 1);
    r9 = __SBFX(r1, 8, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 8, 1);
    r7 = __BFI(r7, r5, 8, 1);

    r8 = __SBFX(r0, 9, 1);
    r9 = __SBFX(r1, 9, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 9, 1);
    r7 = __BFI(r7, r5, 9, 1);

    r8 = __SBFX(r0, 10, 1);
    r9 = __SBFX(r1, 10, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 10, 1);
    r7 = __BFI(r7, r5, 10, 1);

    r8 = __SBFX(r0, 11, 1);
    r9 = __SBFX(r1, 11, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 11, 1);
    r7 = __BFI(r7, r5, 11, 1);

    r8 = __SBFX(r0, 12, 1);
    r9 = __SBFX(r1, 12, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 12, 1);
    r7 = __BFI(r7, r5, 12, 1);

    r8 = __SBFX(r0, 13, 1);
    r9 = __SBFX(r1, 13, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 13, 1);
    r7 = __BFI(r7, r5, 13, 1);

    r8 = __SBFX(r0, 14, 1);
    r9 = __SBFX(r1, 14, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 14, 1);
    r7 = __BFI(r7, r5, 14, 1);

    r8 = __SBFX(r0, 15, 1);
    r9 = __SBFX(r1, 15, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 15, 1);
    r7 = __BFI(r7, r5, 15, 1);

    r8 = __SBFX(r0, 16, 1);
    r9 = __SBFX(r1, 16, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 16, 1);
    r7 = __BFI(r7, r5, 16, 1);

    r8 = __SBFX(r0, 17, 1);
    r9 = __SBFX(r1, 17, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 17, 1);
    r7 = __BFI(r7, r5, 17, 1);

    r8 = __SBFX(r0, 18, 1);
    r9 = __SBFX(r1, 18, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 18, 1);
    r7 = __BFI(r7, r5, 18, 1);

    r8 = __SBFX(r0, 19, 1);
    r9 = __SBFX(r1, 19, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 19, 1);
    r7 = __BFI(r7, r5, 19, 1);

    r8 = __SBFX(r0, 20, 1);
    r9 = __SBFX(r1, 20, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 20, 1);
    r7 = __BFI(r7, r5, 20, 1);

    r8 = __SBFX(r0, 21, 1);
    r9 = __SBFX(r1, 21, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 21, 1);
    r7 = __BFI(r7, r5, 21, 1);

    r8 = __SBFX(r0, 22, 1);
    r9 = __SBFX(r1, 22, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 22, 1);
    r7 = __BFI(r7, r5, 22, 1);

    r8 = __SBFX(r0, 23, 1);
    r9 = __SBFX(r1, 23, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 23, 1);
    r7 = __BFI(r7, r5, 23, 1);

    r8 = __SBFX(r0, 24, 1);
    r9 = __SBFX(r1, 24, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 24, 1);
    r7 = __BFI(r7, r5, 24, 1);

    r8 = __SBFX(r0, 25, 1);
    r9 = __SBFX(r1, 25, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 25, 1);
    r7 = __BFI(r7, r5, 25, 1);

    r8 = __SBFX(r0, 26, 1);
    r9 = __SBFX(r1, 26, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 26, 1);
    r7 = __BFI(r7, r5, 26, 1);

    r8 = __SBFX(r0, 27, 1);
    r9 = __SBFX(r1, 27, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 27, 1);
    r7 = __BFI(r7, r5, 27, 1);

    r8 = __SBFX(r0, 28, 1);
    r9 = __SBFX(r1, 28, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 28, 1);
    r7 = __BFI(r7, r5, 28, 1);

    r8 = __SBFX(r0, 29, 1);
    r9 = __SBFX(r1, 29, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 29, 1);
    r7 = __BFI(r7, r5, 29, 1);

    r8 = __SBFX(r0, 30, 1);
    r9 = __SBFX(r1, 30, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;
    r6 = __BFI(r6, r4, 30, 1);
    r7 = __BFI(r7, r5, 30, 1);

    r8 = __SBFX(r0, 31, 1);
    r9 = __SBFX(r1, 31, 1);
    r8 = r8 & r2;
    r9 = r9 ^ r3;
    r9 = r9 & r8;

    r10 = __EOR_LSR(r8, r5, 1);
    r5 = __EOR_LSR(r9, r4, 1);
    r5 = r5 & r10;
    r10 = r10 ^ r9;
    r4 = __EOR_LSR(r8, r4, 1);
    r4 = r4 | r10;

    r6 <<= 1;
    r7 <<= 1;
    *(writeSum++) = r4;
    *(writeSum++) = r5;
    *(writeSum++) = r6;
    *(writeSum++) = r7;
  }
}

// assert input size = 768, the scalar trit c to multiply is trit-extended
void polyf3_mul_scalar_packed_fast(uint32_t *tritOut, uint32_t tritIn1[2], uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8;
    uint32_t *readOp1, *readOp2, *writeSum, *bndry;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;
    bndry = writeSum + 48;
    r0 = *(readOp1++);
    r1 = *(readOp1++);

    while (writeSum != bndry) {
        r2 = *(readOp2++);
        r3 = *(readOp2++);

        r4 = r0 & r2;
        r6 = r1 ^ r3;
        r5 = r4 & r6;

        *(writeSum++) = r4;
        *(writeSum++) = r5;
    }
}

void bs3_add32(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r8;
    uint32_t *readOp1, *readOp2, *writeSum;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;
    r0 = *(readOp1++); // a0
    r1 = *(readOp1++); // a1
    r2 = *(readOp2++); // b0
    r3 = *(readOp2++); // b1

    r8 = r1 ^ r2;
    r1 = r0 ^ r3;
    r1 = r1 & r8;
    r8 = r8 ^ r3;
    r0 = r0 ^ r2;
    r0 = r0 | r8;

    *(writeSum++) = r0;
    *(writeSum++) = r1;
}

void bs3_add64(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
    uint32_t *readOp1, *readOp2, *writeSum, *bndry;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;
    r0 = *(readOp1++); // a0
    r1 = *(readOp1++); // a1
    r2 = *(readOp2++); // b0
    r3 = *(readOp2++); // b1

    r4 = *(readOp1++); // a0
    r5 = *(readOp1++); // a1
    r6 = *(readOp2++); // b0
    r7 = *(readOp2++); // b1

    r8 = r1 ^ r2;
    r1 = r0 ^ r3;
    r1 = r1 & r8;
    r8 = r8 ^ r3;
    r0 = r0 ^ r2;
    r0 = r0 | r8;

    r8 = r5 ^ r6;
    r5 = r4 ^ r7;
    r5 = r5 & r8;
    r8 = r8 ^ r7;
    r4 = r4 ^ r6;
    r4 = r4 | r8;

    *(writeSum++) = r0;
    *(writeSum++) = r1;
    *(writeSum++) = r4;
    *(writeSum++) = r5;
}

void bs3_add128(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
    uint32_t *readOp1, *readOp2, *writeSum;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;

    for (int i = 0; i < 2; i++) {
        r0 = *(readOp1++); // a0
        r1 = *(readOp1++); // a1
        r2 = *(readOp2++); // b0
        r3 = *(readOp2++); // b1

        r4 = *(readOp1++); // a0
        r5 = *(readOp1++); // a1
        r6 = *(readOp2++); // b0
        r7 = *(readOp2++); // b1

        r8 = r1 ^ r2;
        r1 = r0 ^ r3;
        r1 = r1 & r8;
        r8 = r8 ^ r3;
        r0 = r0 ^ r2;
        r0 = r0 | r8;

        r8 = r5 ^ r6;
        r5 = r4 ^ r7;
        r5 = r5 & r8;
        r8 = r8 ^ r7;
        r4 = r4 ^ r6;
        r4 = r4 | r8;

        *(writeSum++) = r0;
        *(writeSum++) = r1;
        *(writeSum++) = r4;
        *(writeSum++) = r5;
    }
}

void bs3_add256(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
    uint32_t *readOp1, *readOp2, *writeSum;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;
    for (int i = 0; i < 4; i++) {
        r0 = *(readOp1++); // a0
        r1 = *(readOp1++); // a1
        r2 = *(readOp2++); // b0
        r3 = *(readOp2++); // b1

        r4 = *(readOp1++); // a0
        r5 = *(readOp1++); // a1
        r6 = *(readOp2++); // b0
        r7 = *(readOp2++); // b1

        r8 = r1 ^ r2;
        r1 = r0 ^ r3;
        r1 = r1 & r8;
        r8 = r8 ^ r3;
        r0 = r0 ^ r2;
        r0 = r0 | r8;

        r8 = r5 ^ r6;
        r5 = r4 ^ r7;
        r5 = r5 & r8;
        r8 = r8 ^ r7;
        r4 = r4 ^ r6;
        r4 = r4 | r8;

        *(writeSum++) = r0;
        *(writeSum++) = r1;
        *(writeSum++) = r4;
        *(writeSum++) = r5;
    }
}

void bs3_add512(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
    uint32_t *readOp1, *readOp2, *writeSum;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;
    for (int i = 0; i < 8; i++) {
        r0 = *(readOp1++); // a0
        r1 = *(readOp1++); // a1
        r2 = *(readOp2++); // b0
        r3 = *(readOp2++); // b1

        r4 = *(readOp1++); // a0
        r5 = *(readOp1++); // a1
        r6 = *(readOp2++); // b0
        r7 = *(readOp2++); // b1

        r8 = r1 ^ r2;
        r1 = r0 ^ r3;
        r1 = r1 & r8;
        r8 = r8 ^ r3;
        r0 = r0 ^ r2;
        r0 = r0 | r8;

        r8 = r5 ^ r6;
        r5 = r4 ^ r7;
        r5 = r5 & r8;
        r8 = r8 ^ r7;
        r4 = r4 ^ r6;
        r4 = r4 | r8;

        *(writeSum++) = r0;
        *(writeSum++) = r1;
        *(writeSum++) = r4;
        *(writeSum++) = r5;
    }
}

void bs3_add768(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
    uint32_t *readOp1, *readOp2, *writeSum;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;
    for (int i = 0; i < 12; i++) {
        r0 = *(readOp1++); // a0
        r1 = *(readOp1++); // a1
        r2 = *(readOp2++); // b0
        r3 = *(readOp2++); // b1

        r4 = *(readOp1++); // a0
        r5 = *(readOp1++); // a1
        r6 = *(readOp2++); // b0
        r7 = *(readOp2++); // b1

        r8 = r1 ^ r2;
        r1 = r0 ^ r3;
        r1 = r1 & r8;
        r8 = r8 ^ r3;
        r0 = r0 ^ r2;
        r0 = r0 | r8;

        r8 = r5 ^ r6;
        r5 = r4 ^ r7;
        r5 = r5 & r8;
        r8 = r8 ^ r7;
        r4 = r4 ^ r6;
        r4 = r4 | r8;

        *(writeSum++) = r0;
        *(writeSum++) = r1;
        *(writeSum++) = r4;
        *(writeSum++) = r5;
    }
}

void bs3_sub32(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r8;
    uint32_t *readOp1, *readOp2, *writeSum;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;

    r0 = *(readOp1++); // a0
    r1 = *(readOp1++); // a1
    r2 = *(readOp2++); // b0
    r3 = *(readOp2++); // b1

    r8 = r0 ^ r2;
    r0 = r1 ^ r3;
    r0 = r0 | r8;
    r8 = r8 ^ r3;
    r1 = r1 ^ r2;
    r1 = r1 & r8;

    *(writeSum++) = r0;
    *(writeSum++) = r1;
}

void bs3_sub64(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8;
    uint32_t *readOp1, *readOp2, *writeSum;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;

    r0 = *(readOp1++); // a0
    r1 = *(readOp1++); // a1
    r2 = *(readOp2++); // b0
    r3 = *(readOp2++); // b1

    r4 = *(readOp1++); // a0
    r5 = *(readOp1++); // a1
    r6 = *(readOp2++); // b0
    r7 = *(readOp2++); // b1

    r8 = r0 ^ r2;
    r0 = r1 ^ r3;
    r0 = r0 | r8;
    r8 = r8 ^ r3;
    r1 = r1 ^ r2;
    r1 = r1 & r8;

    r8 = r4 ^ r6;
    r4 = r5 ^ r7;
    r4 = r4 | r8;
    r8 = r8 ^ r7;
    r5 = r5 ^ r6;
    r5 = r5 & r8;

    *(writeSum++) = r0;
    *(writeSum++) = r1;
    *(writeSum++) = r4;
    *(writeSum++) = r5;
}

void bs3_sub128(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8;
    uint32_t *readOp1, *readOp2, *writeSum;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;

    for (int i = 0; i < 2; i++) {
        r0 = *(readOp1++); // a0
        r1 = *(readOp1++); // a1
        r2 = *(readOp2++); // b0
        r3 = *(readOp2++); // b1

        r4 = *(readOp1++); // a0
        r5 = *(readOp1++); // a1
        r6 = *(readOp2++); // b0
        r7 = *(readOp2++); // b1

        r8 = r0 ^ r2;
        r0 = r1 ^ r3;
        r0 = r0 | r8;
        r8 = r8 ^ r3;
        r1 = r1 ^ r2;
        r1 = r1 & r8;

        r8 = r4 ^ r6;
        r4 = r5 ^ r7;
        r4 = r4 | r8;
        r8 = r8 ^ r7;
        r5 = r5 ^ r6;
        r5 = r5 & r8;

        *(writeSum++) = r0;
        *(writeSum++) = r1;
        *(writeSum++) = r4;
        *(writeSum++) = r5;
    }
}

void bs3_sub256(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8;
    uint32_t *readOp1, *readOp2, *writeSum;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;

    for (int i = 0; i < 4; i++) {
        r0 = *(readOp1++); // a0
        r1 = *(readOp1++); // a1
        r2 = *(readOp2++); // b0
        r3 = *(readOp2++); // b1

        r4 = *(readOp1++); // a0
        r5 = *(readOp1++); // a1
        r6 = *(readOp2++); // b0
        r7 = *(readOp2++); // b1

        r8 = r0 ^ r2;
        r0 = r1 ^ r3;
        r0 = r0 | r8;
        r8 = r8 ^ r3;
        r1 = r1 ^ r2;
        r1 = r1 & r8;

        r8 = r4 ^ r6;
        r4 = r5 ^ r7;
        r4 = r4 | r8;
        r8 = r8 ^ r7;
        r5 = r5 ^ r6;
        r5 = r5 & r8;

        *(writeSum++) = r0;
        *(writeSum++) = r1;
        *(writeSum++) = r4;
        *(writeSum++) = r5;
    }
}

void bs3_sub512(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8;
    uint32_t *readOp1, *readOp2, *writeSum;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;

    for (int i = 0; i < 8; i++) {
        r0 = *(readOp1++); // a0
        r1 = *(readOp1++); // a1
        r2 = *(readOp2++); // b0
        r3 = *(readOp2++); // b1

        r4 = *(readOp1++); // a0
        r5 = *(readOp1++); // a1
        r6 = *(readOp2++); // b0
        r7 = *(readOp2++); // b1

        r8 = r0 ^ r2;
        r0 = r1 ^ r3;
        r0 = r0 | r8;
        r8 = r8 ^ r3;
        r1 = r1 ^ r2;
        r1 = r1 & r8;

        r8 = r4 ^ r6;
        r4 = r5 ^ r7;
        r4 = r4 | r8;
        r8 = r8 ^ r7;
        r5 = r5 ^ r6;
        r5 = r5 & r8;

        *(writeSum++) = r0;
        *(writeSum++) = r1;
        *(writeSum++) = r4;
        *(writeSum++) = r5;
    }
}

void bs3_sub768(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8;
    uint32_t *readOp1, *readOp2, *writeSum;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;

    for (int i = 0; i < 12; i++) {
        r0 = *(readOp1++); // a0
        r1 = *(readOp1++); // a1
        r2 = *(readOp2++); // b0
        r3 = *(readOp2++); // b1

        r4 = *(readOp1++); // a0
        r5 = *(readOp1++); // a1
        r6 = *(readOp2++); // b0
        r7 = *(readOp2++); // b1

        r8 = r0 ^ r2;
        r0 = r1 ^ r3;
        r0 = r0 | r8;
        r8 = r8 ^ r3;
        r1 = r1 ^ r2;
        r1 = r1 & r8;

        r8 = r4 ^ r6;
        r4 = r5 ^ r7;
        r4 = r4 | r8;
        r8 = r8 ^ r7;
        r5 = r5 ^ r6;
        r5 = r5 & r8;

        *(writeSum++) = r0;
        *(writeSum++) = r1;
        *(writeSum++) = r4;
        *(writeSum++) = r5;
    }
}

void bs3_mul512(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t apb[16] = {0}, cpd[16] = {0}, temp[32]= {0};
    bs3_add256(apb, tritIn1, tritIn1 + 16);
    bs3_add256(cpd, tritIn2, tritIn2 + 16);
    bs3_mul256(temp, apb, cpd); // (a+b)*(c+d)
    bs3_mul256(tritOut, tritIn1, tritIn2);
    bs3_mul256(tritOut+32, tritIn1 + 16, tritIn2 + 16);
    bs3_sub512(temp, temp, tritOut);
    bs3_sub512(temp, temp, tritOut + 32);
    bs3_add512(tritOut + 16, tritOut + 16, temp);
}

void bs3_mul256x512(uint32_t *tritOut, uint32_t *trit256, uint32_t *trit512) {
    uint32_t temp[32] = {0};

    bs3_mul256(tritOut, trit256, trit512);
    bs3_mul256(temp, trit256, trit512 + 16);
    bs3_add512(tritOut + 16, tritOut + 16, temp);
}

void bs3_mul768(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t *a0 = tritIn1, *a1 = tritIn1+16, *a2 = tritIn1+32;
    uint32_t *b0 = tritIn2, *b1 = tritIn2+16, *b2 = tritIn2+32;
    uint32_t temp[64] = {0};

    // y^0
    bs3_mul256(tritOut, a0, b0);

    // y^4
    bs3_mul256(tritOut+64, a2, b2);

    // y^2
    bs3_mul256(tritOut+32, a0, b2);
    bs3_mul256(temp, a1, b1);
    bs3_mul256(temp+32, a2, b0);
    bs3_add512(temp, temp, temp+32);
    bs3_add512(tritOut+32, tritOut+32, temp);

    // y^1
    bs3_mul256(temp, a0, b1);
    bs3_mul256(temp+32, a1, b0);
    bs3_add512(temp, temp, temp+32);
    bs3_add512(tritOut+16, tritOut+16, temp);

    // y^3
    bs3_mul256(temp, a1, b2);
    bs3_mul256(temp+32, a2, b1);
    bs3_add512(temp, temp, temp+32);
    bs3_add512(tritOut+48, tritOut+48, temp);
}

static inline void swapptr(uint32_t **ptr1, uint32_t **ptr2) {
    uint32_t *tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;

    /*
    uintptr_t a = (uintptr_t)*ptr1;
    uintptr_t b = (uintptr_t)*ptr2;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    *ptr1 = (uint32_t*)a;
    *ptr2 = (uint32_t*)b;
    */
}


void polyf3_divstep(int32_t delta, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10;
    uint32_t *readOp1, *readOp2, *writeOp;
    readOp1 = tritIn1;
    readOp2 = tritIn2;
    r0 = *(readOp1); // a0
    r1 = *(readOp1+1); // a1
    r2 = *(readOp2); // b0
    r3 = *(readOp2+1); // b1

    if ((delta > 0) && ((r2 & 1) != 0)) {
        swapptr(&tritIn1, &tritIn2);
        delta = -delta;
    }
    delta++;

    // c = f[0] * g[0]
    r4 = r0 & r2;
    r8 = r1 ^ r3;
    r5 = r4 & r8;
    r4 = __SBFX(r4, 0, 1);
    r5 = __SBFX(r5, 0, 1);

    writeOp = tritIn2;

    // g = (g - c*f)/x
    r6 = r4 & r0;
    r8 = r5 ^ r1;
    r7 = r6 & r8;

    r8 = r2 ^ r6;
    r9 = r8 ^ r7;
    r10 = r3 ^ r6;
    r2 = r9 & r10;
    r10 = r3 ^ r7;
    r3 = r8 | r10;

    // update
    *(writeOp++) = r2 >> 1;
    *(writeOp++) = r3 >> 1;
}


// assert input size = 32
/*
void polyf3_j32d(int32_t d, uint32_t *tritIn1, uint32_t *tritIn2, uint32_t uvrs[4]) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10;
    uint32_t *readOp1, *readOp2, *writeOp, *u, *v, *r, *s;
    readOp1 = tritIn1;
    readOp2 = tritIn2;
    r0 = *(readOp1); // a0
    r1 = *(readOp1+1); // a1
    r2 = *(readOp2); // b0
    r3 = *(readOp2+1); // b1
    u = uvrs;
    v = uvrs+1;
    r = uvrs+2;
    s = uvrs+3;

    int delta = d;
    for (int i = 32; i > 0; i--) {
        if ((delta > 0) && ((r2 & 1) != 0)) {
            swapptr(&tritIn1, &tritIn2);
            *u = *u ^ *r;
            *r = *u ^ *r;
            *u = *u ^ *r;
            *v = *v ^ *s;
            *s = *v ^ *s;
            *v = *v ^ *s;
            delta = -delta;
        }
        delta++;
        writeOp = tritIn2;

        // c = f[0]^(-1) * g[0] = f[0] * g[0] (mod 3)
        // duplicate with sbfx to do 32 scalar mults at a time
        r4 = r0 & r2;
        r8 = r1 ^ r3;
        r5 = r4 & r8;
        r4 = __SBFX(r4, 0, 1);
        r5 = __SBFX(r5, 0, 1);

        // g = (g - c*f)/x
        r6 = r4 & r0;
        r8 = r5 ^ r1;
        r7 = r6 & r8;

        r8 = r2 ^ r6;
        r9 = r8 ^ r7;
        r10 = r3 ^ r6;
        r2 = r9 & r10;
        r10 = r3 ^ r7;
        r3 = r8 | r10;

        // update g
        *(writeOp++) = r2 >> 1;
        *(writeOp++) = r3 >> 1;

        // r = (r - c*u)
        r6 = r4 & *u;
        r8 = r5 ^ *(u+1);
        r7 = r6 & r8;

        r8 = *r ^ r6;
        r9 = r8 ^ r7;
        r10 = *(r+1) ^ r6;
        *r = r9 & r10;
        r10 = *(r+1) ^ r7;
        *(r+1) = r8 | r10;

        // s = (s - c*v)
        r6 = r4 & *v;
        r8 = r5 ^ *(v+1);
        r7 = r6 & r8;

        r8 = *s ^ r6;
        r9 = r8 ^ r7;
        r10 = *(s+1) ^ r6;
        *s = r9 & r10;
        r10 = *(s+1) ^ r7;
        *(s+1) = r8 | r10;

        // TODO: below should be omitted in the last iteration
        if (i > 1) {
            *u <<= 1;
            *v <<= 1;
        }
    }
}
*/

extern void polyf3_lsr_asm(uint32_t *);
extern void polyf3_lsl_asm(uint32_t *);
extern void polyf3_rol1_32_asm(uint32_t *);
extern void polyf3_rol1_64_asm(uint32_t *);

void polyf3_lsr_fast(uint32_t *tritIn) {
    polyf3_lsr_asm(tritIn);
}

void polyf3_lsl_fast(uint32_t *tritIn) {
    polyf3_lsl_asm(tritIn);
}

// assert input size = 768
// serve as in-place division by x
void polyf3_lsr(uint32_t *tritIn) {
    /*
    uint32_t r0, r1, r2, r3;
    uint32_t *readOp, *writeOp, *bndry;
    readOp = tritIn;
    writeOp = tritIn;
    bndry = tritIn + 46;
    while (readOp != bndry) {
        r0 = *(readOp++);
        r1 = *(readOp++);
        r2 = *(readOp);
        r3 = *(readOp+1);
        r0 >>= 1;
        r1 >>= 1;
        r0 = __ORR_LSL(r0, r2, 31);
        r1 = __ORR_LSL(r1, r3, 31);
        *(writeOp++) = r0;
        *(writeOp++) = r1;
    }
    */

    for (int i = 0; i < 46; i += 2) {
        tritIn[i] = (tritIn[i] >> 1) | (tritIn[i+2] << 31);
        tritIn[i+1] = (tritIn[i+1] >> 1) | (tritIn[i+3] << 31);
    }
    tritIn[46] >>= 1;
    tritIn[47] >>= 1;

}

// assert input size = 768
// serve as in-place multiplication by x
void polyf3_lsl(uint32_t *tritIn) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7;
    uint32_t *readOp, *writeOp, *bndry;
    readOp = tritIn;
    writeOp = tritIn;
    bndry = tritIn + 48;

    __asm__ volatile ("adds r4, #0");

    while (writeOp != bndry) {
        r0 = *(readOp);
        readOp += 2;
        r1 = *(readOp);
        readOp += 2;
        r2 = *(readOp);
        readOp += 2;
        r3 = *(readOp);
        readOp += 2;
        r4 = *(readOp);
        readOp += 2;
        r5 = *(readOp);
        readOp += 2;
        r6 = *(readOp);
        readOp += 2;
        r7 = *(readOp);
        readOp += 2;

        r0 = __ADCS(r0, r0);
        r1 = __ADCS(r1, r1);
        r2 = __ADCS(r2, r2);
        r3 = __ADCS(r3, r3);
        r4 = __ADCS(r4, r4);
        r5 = __ADCS(r5, r5);
        r6 = __ADCS(r6, r6);
        r7 = __ADCS(r7, r7);

        *(writeOp) = r0;
        writeOp += 2;
        *(writeOp) = r1;
        writeOp += 2;
        *(writeOp) = r2;
        writeOp += 2;
        *(writeOp) = r3;
        writeOp += 2;
        *(writeOp) = r4;
        writeOp += 2;
        *(writeOp) = r5;
        writeOp += 2;
        *(writeOp) = r6;
        writeOp += 2;
        *(writeOp) = r7;
        writeOp += 2;
    }

    readOp = tritIn + 1;
    writeOp = tritIn + 1;
    bndry = tritIn + 49;

    __asm__ volatile ("adds r4, #0");

    while (writeOp != bndry) {
        r0 = *(readOp);
        readOp += 2;
        r1 = *(readOp);
        readOp += 2;
        r2 = *(readOp);
        readOp += 2;
        r3 = *(readOp);
        readOp += 2;
        r4 = *(readOp);
        readOp += 2;
        r5 = *(readOp);
        readOp += 2;
        r6 = *(readOp);
        readOp += 2;
        r7 = *(readOp);
        readOp += 2;

        r0 = __ADCS(r0, r0);
        r1 = __ADCS(r1, r1);
        r2 = __ADCS(r2, r2);
        r3 = __ADCS(r3, r3);
        r4 = __ADCS(r4, r4);
        r5 = __ADCS(r5, r5);
        r6 = __ADCS(r6, r6);
        r7 = __ADCS(r7, r7);

        *(writeOp) = r0;
        writeOp += 2;
        *(writeOp) = r1;
        writeOp += 2;
        *(writeOp) = r2;
        writeOp += 2;
        *(writeOp) = r3;
        writeOp += 2;
        *(writeOp) = r4;
        writeOp += 2;
        *(writeOp) = r5;
        writeOp += 2;
        *(writeOp) = r6;
        writeOp += 2;
        *(writeOp) = r7;
        writeOp += 2;
    }
}

void polyf3_lsl1536(uint32_t *tritIn) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7;
    uint32_t *readOp, *writeOp, *bndry;
    readOp = tritIn;
    writeOp = tritIn;
    bndry = tritIn + 96;

    __asm__ volatile ("adds r4, #0");

    while (writeOp != bndry) {
        r0 = *(readOp);
        readOp += 2;
        r1 = *(readOp);
        readOp += 2;
        r2 = *(readOp);
        readOp += 2;
        r3 = *(readOp);
        readOp += 2;
        r4 = *(readOp);
        readOp += 2;
        r5 = *(readOp);
        readOp += 2;
        r6 = *(readOp);
        readOp += 2;
        r7 = *(readOp);
        readOp += 2;

        r0 = __ADCS(r0, r0);
        r1 = __ADCS(r1, r1);
        r2 = __ADCS(r2, r2);
        r3 = __ADCS(r3, r3);
        r4 = __ADCS(r4, r4);
        r5 = __ADCS(r5, r5);
        r6 = __ADCS(r6, r6);
        r7 = __ADCS(r7, r7);

        *(writeOp) = r0;
        writeOp += 2;
        *(writeOp) = r1;
        writeOp += 2;
        *(writeOp) = r2;
        writeOp += 2;
        *(writeOp) = r3;
        writeOp += 2;
        *(writeOp) = r4;
        writeOp += 2;
        *(writeOp) = r5;
        writeOp += 2;
        *(writeOp) = r6;
        writeOp += 2;
        *(writeOp) = r7;
        writeOp += 2;
    }

    readOp = tritIn + 1;
    writeOp = tritIn + 1;
    bndry = tritIn + 97;

    __asm__ volatile ("adds r4, #0");

    while (writeOp != bndry) {
        r0 = *(readOp);
        readOp += 2;
        r1 = *(readOp);
        readOp += 2;
        r2 = *(readOp);
        readOp += 2;
        r3 = *(readOp);
        readOp += 2;
        r4 = *(readOp);
        readOp += 2;
        r5 = *(readOp);
        readOp += 2;
        r6 = *(readOp);
        readOp += 2;
        r7 = *(readOp);
        readOp += 2;

        r0 = __ADCS(r0, r0);
        r1 = __ADCS(r1, r1);
        r2 = __ADCS(r2, r2);
        r3 = __ADCS(r3, r3);
        r4 = __ADCS(r4, r4);
        r5 = __ADCS(r5, r5);
        r6 = __ADCS(r6, r6);
        r7 = __ADCS(r7, r7);

        *(writeOp) = r0;
        writeOp += 2;
        *(writeOp) = r1;
        writeOp += 2;
        *(writeOp) = r2;
        writeOp += 2;
        *(writeOp) = r3;
        writeOp += 2;
        *(writeOp) = r4;
        writeOp += 2;
        *(writeOp) = r5;
        writeOp += 2;
        *(writeOp) = r6;
        writeOp += 2;
        *(writeOp) = r7;
        writeOp += 2;
    }
}

void polyf3_rol32_negc_fast(uint32_t *tritIn) {
    polyf3_rol1_32_asm(tritIn);
}

void polyf3_rol64_negc_fast(uint32_t *tritIn) {
    polyf3_rol1_64_asm(tritIn);
}

// rotate left k trits for corresponding input size
void polyf3_rol32_negc(uint32_t *tritIn, int k) {
    uint32_t r0, r1;
    uint32_t *readOp = tritIn, *writeOp = tritIn;
    r0 = *(readOp++);
    r1 = *(readOp++);

    r0 = (r0 << k) | (r0 >> (32 - k));
    r1 = r1 ^ (r0 << (32 - k));
    r1 = (r1 << k) | (r1 >> (32 - k));

    *(writeOp++) = r0;
    *(writeOp++) = r1;
}

void polyf3_rol64_negc(uint32_t *tritIn, int k) {
    uint32_t r0, r1, r2, r3, r4, r5;
    uint32_t *readOp = tritIn, *writeOp = tritIn;
    r0 = *(readOp++);
    r1 = *(readOp++);
    r2 = *(readOp++);
    r3 = *(readOp++);

    r4 = r0;
    r5 = r1;

    r0 = (r0 << k) | (r2 >> (32 - k));
    r2 = (r2 << k) | (r4 >> (32 - k));

    r1 = r1 ^ (r2 >> (32 - k));

    r1 = (r1 << k) | (r3 >> (32 - k));
    r3 = (r3 << k) | (r5 >> (32 - k));

    *(writeOp++) = r0;
    *(writeOp++) = r1;
    *(writeOp++) = r2;
    *(writeOp++) = r3;
}

// assert input size = 768
/*
void polyf3_j32d768(int32_t *d, uint32_t *tritIn1, uint32_t *tritIn2, uint32_t uvrs[192]) {
    uint32_t r0, r1, r2, r3, r4[2], r6;
    uint32_t *u, *v, *r, *s;
    uint32_t tritTmp[48] = {0};
    r2 = *(tritIn2);
    u = uvrs;
    v = uvrs + 48;
    r = uvrs + 96;
    s = uvrs + 144;

    int delta = *d;
    for (int i = 32; i > 0; i--) {
        if ((delta > 0) && ((r2 & 1) != 0)) {
            polyf3_swap32(tritIn, tritIn2);
            polyf3_swap32(u, r);
            polyf3_swap32(v, s);
            delta = -delta;
        }
        delta++;
        r0 = *(tritIn1);
        r1 = *(tritIn1+1);
        r2 = *(tritIn2);
        r3 = *(tritIn2+1);
        // c = f[0]^(-1) * g[0] = f[0] * g[0] (mod 3)
        // duplicate with sbfx to do 32 scalar mults at a time
        r4[0] = r0 & r2;
        r6 = r1 ^ r3;
        r4[1] = r4[0] & r6;
        r4[0] = __SBFX(r4[0], 0, 1);
        r4[1] = __SBFX(r4[1], 0, 1);

        // g = (g - c*f)/x
        polyf3_mul_scalar_packed_fast(tritTmp, r4, tritIn1);
        bs3_sub768(tritIn2, tritIn2, tritTmp);
        polyf3_lsr(tritIn2);

        // r = (r - c*u)
        polyf3_mul_scalar_packed_fast(tritTmp, r4, u);
        bs3_sub768(r, r, tritTmp);

        // s = (s - c*v)
        polyf3_mul_scalar_packed_fast(tritTmp, r4, v);
        bs3_sub768(s, s, tritTmp);

        // TODO: lsl should be omitted in the last iteration
        if (i > 1) {
            polyf3_lsl_fast(u);
            polyf3_lsl_fast(v);
        }
    }

    *d = delta;
}
*/

void bs3_jump17divsteps(int32_t *d, uint32_t *f, uint32_t *g, uint32_t *M) {
    int32_t delta = *d;
    __asm__ volatile ("vmov.f32 s0, #16.0");
    bs3_j32d(delta, f, g, M);
    *d = delta;
}

void bs3_jump32divsteps(int32_t *d, uint32_t *f, uint32_t *g, uint32_t *M) {
    int32_t delta = *d;
    __asm__ volatile ("vmov.f32 s0, #31.0");
    bs3_j32d(delta, f, g, M);
    *d = delta;
}

void bs3_jump49divsteps(int32_t *d, uint32_t *f, uint32_t *g, uint32_t *M) {
    uint32_t M1[12] = {0}, M2[12] = {0}, fgnew[8] = {0};
    polyf3_j32d(d, f, g, M);
    bs3_polymul_32x32_2x2_x2p2(fgnew, f+2, g+2, M);
    polyf3_j17d(d, fgnew, fgnew+4, M2);
    bs3_polymul_32x32_2x2_x2p2(M, fgnew+2, fgnew+6, M2);

    bs3_polymul_32x32_2x2_x_2x2(M + 8, M1 + 4, M2 + 4);
}

void bs3_jump64divsteps(int32_t *d, uint32_t *f, uint32_t *g, uint32_t *M) {
    uint32_t M1[12] = {0}, M2[12] = {0}, fgnew[8] = {0};

    bs3_jump32divsteps(d, f, g, M1);
    bs3_polymul_32x32_2x2_x2p2(fgnew, f+2, g+2, M1);
    bs3_jump32divsteps(d, fgnew, fgnew+4, M2);
    bs3_polymul_32x32_2x2_x2p2(M, fgnew+2, fgnew+6, M2);

    bs3_polymul_32x32_2x2_x_2x2(M + 8, M1 + 4, M2 + 4);
}

void bs3_jump128divsteps(int32_t *d, uint32_t *f, uint32_t *g, uint32_t *M) {
    uint32_t M1[24] = {0}, M2[24] = {0}, fgnew[16] = {0};

    bs3_jump64divsteps(d, f, g, M1);
    bs3_polymul_64x64_2x2_x2p2(fgnew, f+4, g+4, M1);
    bs3_jump64divsteps(d, fgnew, fgnew+8, M2);
    bs3_polymul_64x64_2x2_x2p2(M, fgnew+4, fgnew+12, M2);

    bs3_polymul_64x64_2x2_x_2x2(M + 16, M1 + 8, M2 + 8);
}

void bs3_jump256divsteps(int32_t *d, uint32_t *f, uint32_t *g, uint32_t *M) {
    uint32_t M1[48] = {0}, M2[48] = {0}, fgnew[32] = {0};

    bs3_jump128divsteps(d, f, g, M1);
    bs3_polymul_128x128_2x2_x2p2(fgnew, f+8, g+8, M1);
    bs3_jump128divsteps(d, fgnew, fgnew+16, M2);
    bs3_polymul_128x128_2x2_x2p2(M, fgnew+8, fgnew+24, M2);

    bs3_polymul_128x128_2x2_x_2x2(M + 32, M1 + 16, M2 + 16);
}

void bs3_jump512divsteps(int32_t *d, uint32_t *f, uint32_t *g, uint32_t *M) {
    uint32_t M1[96] = {0}, M2[96] = {0}, fgnew[64] = {0};

    bs3_jump256divsteps(d, f, g, M1);
    bs3_polymul_256x256_2x2_x2p2(fgnew, f+16, g+16, M1);
    bs3_jump256divsteps(d, fgnew, fgnew+32, M2);
    bs3_polymul_256x256_2x2_x2p2(M, fgnew+16, fgnew+48, M2);

    bs3_polymul_256x256_2x2_x_2x2(M + 64, M1 + 32, M2 + 32);
}

void bs3_jump753divsteps(int32_t *d, uint32_t *f, uint32_t *g, uint32_t *M) {
    uint32_t M512[192] = {0}, fg768[96] = {0};
    uint32_t M128[48] = {0}, fg128[32] = {0};
    uint32_t M64[24] = {0}, fg64[16] = {0};
    uint32_t M32[12] = {0}, fg32[8] = {0};
    uint32_t M17[12] = {0};
    uint32_t h1[64] = {0}, h2[32] = {0}, h3[16] = {0};

    // 753 = 512 + 128 + 64 + 32 + 17
    bs3_jump512divsteps(d, f, g, M512);
    bs3_polymul_512x256_2x2_x2p2(fg768, f+32, g+32, M512);
    bs3_jump128divsteps(d, fg768, fg768+48, M128);
    bs3_polymul_128x128_2x2_x2p2(fg128, fg768+8, fg768+56, M128);
    bs3_jump64divsteps(d, fg128, fg128+16, M64);
    bs3_polymul_64x64_2x2_x2p2(fg64, fg128+4, fg128+20, M64);
    bs3_jump32divsteps(d, fg64, fg64+8, M32);
    bs3_polymul_32x32_2x2_x2p2(fg32, fg64+4, fg64+12, M32);
    bs3_jump17divsteps(d, fg32, fg32+4, M17);

    printf("After last 17 steps,\n");
    printf("delta = %ld, fp = %8lx, gp = %8lx\n", *d, M17[0], M17[2]);

    bs3_polymul_32x32_2x2_x_2x2(h3, M32+4, M17+4);
    bs3_polymul_64x64_2x2_x_2x2(h2, M64+8, h3);
    bs3_polymul_128x128_2x2_x_2x2(h1, M128+16, h2);
    bs3_polymul_256x512_2x2_x_2x2(M+96, M512+64, h1);

    M[0] = M17[0];
    M[1] = M17[1];
    M[48] = M17[2];
    M[49] = M17[3];
}

void bs3_jump768divsteps(int32_t *d, uint32_t *f, uint32_t *g, uint32_t *M) {
    uint32_t M1[192] = {0}, M2[96] = {0}, fgnew[96] = {0};

    bs3_jump512divsteps(d, f, g, M1);
    bs3_polymul_512x256_2x2_x2p2(fgnew, f+32, g+32, M1);
    bs3_jump256divsteps(d, fgnew, fgnew+48, M2);
    bs3_polymul_256x512_2x2_x2p2(M, fgnew+16, fgnew+64, M2);

    bs3_polymul_256x512_2x2_x_2x2(M + 96, M1 + 64, M2 + 32);
}

/*
void polyf3_j64d(int32_t *d, uint32_t *f, uint32_t *g, uint32_t *M) {
    uint32_t M1[12] = {0}, M2[12] = {0}, fgnew[8] = {0};

    polyf3_j32d(d, f, g, M1);
    bs3_polymul_32x32_2x2_x2p2(fgnew, f+2, g+2, M1);
    polyf3_j32d(d, fgnew, fgnew+2, M2);
    bs3_polymul_32x32_2x2_x2p2(M, fgnew+2, fgnew+6, M2);

    bs3_polymul_32x32_2x2_x_2x2(M + 8, M1 + 4, M2 + 4);
}

void polyf3_j128d(int32_t *d, uint32_t *tritIn1, uint32_t *tritIn2, uint32_t uvrs[32]) {
    uint32_t uvrs1[16] = {0}, uvrs2[16] = {0};

    polyf3_j64d(d, tritIn1, tritIn2, uvrs1);
    polyf3_j64d(d, tritIn1+4, tritIn2+4, uvrs2);

    polyf3_mmul64(uvrs, uvrs1, uvrs2);
}

void polyf3_j256d(int32_t *d, uint32_t *tritIn1, uint32_t *tritIn2, uint32_t uvrs[64]) {
    uint32_t uvrs1[32] = {0}, uvrs2[32] = {0};

    polyf3_j128d(d, tritIn1, tritIn2, uvrs1);
    polyf3_j128d(d, tritIn1+8, tritIn2+8, uvrs2);

    polyf3_mmul128(uvrs, uvrs1, uvrs2);
}

void polyf3_j512d(int32_t *d, uint32_t *tritIn1, uint32_t *tritIn2, uint32_t uvrs[128]) {
    uint32_t uvrs1[64] = {0}, uvrs2[64] = {0};

    polyf3_j256d(d, tritIn1, tritIn2, uvrs1);
    polyf3_j256d(d, tritIn1+16, tritIn2+16, uvrs2);

    polyf3_mmul256(uvrs, uvrs1, uvrs2);
}

void polyf3_j768d(int32_t *d, uint32_t *tritIn1, uint32_t *tritIn2, uint32_t uvrs[192]) {
    uint32_t uvrs1[128] = {0}, uvrs2[64] = {0};

    polyf3_j512d(d, tritIn1, tritIn2, uvrs1);
    polyf3_j256d(d, tritIn1+32, tritIn2+32, uvrs2);

    polyf3_mmul256x512(uvrs, uvrs1, uvrs2);
}
*/

void bs3_jump1521divsteps(int32_t *d, uint32_t *f, uint32_t *g, uint32_t vres[96]) {
    uint32_t M768[288] = {0}, fg768[96] = {0};
    uint32_t M753[288] = {0}, fg512[64] = {0};
    uint32_t temp[192] = {0};

    // 1521 = 768 + 753
    bs3_jump768divsteps(d, f, g, M768);
    bs3_jump753divsteps(d, M768, M768+48, M753);

    // only calculate final v
    uint32_t *v1 = M768+144, *s1 = M768+240;
    uint32_t *u2 = M753+96, *v2 = M753+144;
    uint32_t temp2[96] = {0};
    bs3_mul768(vres, u2, v1);
    polyf3_lsl1536(vres);
    bs3_mul768(temp2, v2, s1);
    bs3_add768(vres, vres, temp2);
    bs3_add768(vres+48, vres+48, temp2+48);
}


// 2x2 matrix multiplications
// C = B * A
void bs3_polymul_32x32_2x2_x_2x2(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 2, *r1 = a + 4, *s1 = a + 6;
    uint32_t *u2 = b, *v2 = b + 2, *r2 = b + 4, *s2 = b + 6;
    uint32_t *ures = c, *vres = c + 4, *rres = c + 8, *sres = c + 12;
    uint32_t temp[48];

    bs3_mul32(temp, u2, u1);
    bs3_mul32(temp+12, u2, v1);
    bs3_mul32(temp+24, r2, u1);
    bs3_mul32(temp+36, r2, v1);
    polyf3_lsl_fast(temp);
    bs3_mul32(ures, v2, r1);
    bs3_mul32(vres, v2, s1);
    bs3_mul32(rres, s2, r1);
    bs3_mul32(sres, s2, s1);

    bs3_add64(ures, ures, temp);
    bs3_add64(vres, vres, temp+12);
    bs3_add64(rres, rres, temp+24);
    bs3_add64(sres, sres, temp+36);
}

void bs3_polymul_64x64_2x2_x_2x2(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 4, *r1 = a + 8, *s1 = a + 12;
    uint32_t *u2 = b, *v2 = b + 4, *r2 = b + 8, *s2 = b + 12;
    uint32_t *ures = c, *vres = c + 8, *rres = c + 16, *sres = c + 24;
    uint32_t temp[48];

    bs3_mul64(temp, u2, u1);
    bs3_mul64(temp+12, u2, v1);
    bs3_mul64(temp+24, r2, u1);
    bs3_mul64(temp+36, r2, v1);
    polyf3_lsl_fast(temp);
    bs3_mul64(ures, v2, r1);
    bs3_mul64(vres, v2, s1);
    bs3_mul64(rres, s2, r1);
    bs3_mul64(sres, s2, s1);

    bs3_add128(ures, ures, temp);
    bs3_add128(vres, vres, temp+12);
    bs3_add128(rres, rres, temp+24);
    bs3_add128(sres, sres, temp+36);
}

void bs3_polymul_128x128_2x2_x_2x2(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 8, *r1 = a + 16, *s1 = a + 24;
    uint32_t *u2 = b, *v2 = b + 8, *r2 = b + 16, *s2 = b + 24;
    uint32_t *ures = c, *vres = c + 16, *rres = c + 32, *sres = c + 48;
    uint32_t temp[96];

    bs3_mul128(temp, u2, u1);
    bs3_mul128(temp+24, u2, v1);
    bs3_mul128(temp+48, r2, u1);
    bs3_mul128(temp+72, r2, v1);
    polyf3_lsl_fast(temp);
    polyf3_lsl_fast(temp+48);
    bs3_mul128(ures, v2, r1);
    bs3_mul128(vres, v2, s1);
    bs3_mul128(rres, s2, r1);
    bs3_mul128(sres, s2, s1);

    bs3_add256(ures, ures, temp);
    bs3_add256(vres, vres, temp+24);
    bs3_add256(rres, rres, temp+48);
    bs3_add256(sres, sres, temp+72);
}

void bs3_polymul_256x256_2x2_x_2x2(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 16, *r1 = a + 32, *s1 = a + 48;
    uint32_t *u2 = b, *v2 = b + 16, *r2 = b + 32, *s2 = b + 48;
    uint32_t *ures = c, *vres = c + 32, *rres = c + 64, *sres = c + 96;
    uint32_t temp[192];

    bs3_mul256(temp, u2, u1);
    bs3_mul256(temp+48, u2, v1);
    bs3_mul256(temp+96, r2, u1);
    bs3_mul256(temp+144, r2, v1);
    polyf3_lsl_fast(temp);
    polyf3_lsl_fast(temp+48);
    polyf3_lsl_fast(temp+96);
    polyf3_lsl_fast(temp+144);
    bs3_mul256(ures, v2, r1);
    bs3_mul256(vres, v2, s1);
    bs3_mul256(rres, s2, r1);
    bs3_mul256(sres, s2, s1);

    bs3_add512(ures, ures, temp);
    bs3_add512(vres, vres, temp+48);
    bs3_add512(rres, rres, temp+96);
    bs3_add512(sres, sres, temp+144);
}

void bs3_polymul_256x512_2x2_x_2x2(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 32, *r1 = a + 64, *s1 = a + 96;
    uint32_t *u2 = b, *v2 = b + 16, *r2 = b + 32, *s2 = b + 48;
    uint32_t *ures = c, *vres = c + 48, *rres = c + 96, *sres = c + 144;
    uint32_t temp[192];

    bs3_mul256x512(temp, u2, u1);
    bs3_mul256x512(temp+48, u2, v1);
    bs3_mul256x512(temp+96, r2, u1);
    bs3_mul256x512(temp+144, r2, v1);
    polyf3_lsl_fast(temp);
    polyf3_lsl_fast(temp+48);
    polyf3_lsl_fast(temp+96);
    polyf3_lsl_fast(temp+144);
    bs3_mul256x512(ures, v2, r1);
    bs3_mul256x512(vres, v2, s1);
    bs3_mul256x512(rres, s2, r1);
    bs3_mul256x512(sres, s2, s1);

    bs3_add768(ures, ures, temp);
    bs3_add768(vres, vres, temp+48);
    bs3_add768(rres, rres, temp+96);
    bs3_add768(sres, sres, temp+144);
}

/*
void polyf3_mmul32s(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 2, *r1 = a + 4, *s1 = a + 6;
    uint32_t *u2 = b, *v2 = b + 2, *r2 = b + 4, *s2 = b + 6;
    uint32_t *ures = c, *vres = c + 48, *rres = c + 96, *sres = c + 144;
    uint32_t temp1[96], temp2[48 * 7];
    // M1
    bs3_add32(temp1, u2, s2);
    bs3_add32(temp1+48, u1, s1);
    bs3_mul32(temp2, temp1, temp1+48);

    // M2
    bs3_add32(temp1, r2, s2);
    bs3_mul32(temp2+48, temp1, u1);

    // M3
    bs3_sub32(temp1, v1, s1);
    bs3_mul32(temp2+96, u2, temp1);

    // M4
    bs3_sub32(temp1, r1, u1);
    bs3_mul32(temp2+144, s2, temp1);

    // M5
    bs3_add32(temp1, u2, v2);
    bs3_mul32(temp2+192, temp1, s1);

    // M6
    bs3_sub32(temp1, r2, u2);
    bs3_add32(temp1+48, u1, v1);
    bs3_mul32(temp2+240, temp1, temp1+48);

    // M7
    bs3_sub32(temp1, v2, s2);
    bs3_add32(temp1+48, r1, s1);
    bs3_mul32(temp2+288, temp1, temp1+48);

    // final
    bs3_add64(ures, temp2, temp2+144);
    bs3_sub64(ures, ures, temp2+192);
    bs3_add64(ures, ures, temp2+288);

    bs3_add64(vres, temp2+96, temp2+192);

    polyf3_lsl_fast(c);

    bs3_add64(rres, temp2+48, temp2+144);

    bs3_sub64(sres, temp2, temp2+48);
    bs3_add64(sres, sres, temp2+96);
    bs3_add64(sres, sres, temp2+240);
}

void polyf3_mmul64s(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 48, *r1 = a + 96, *s1 = a + 144;
    uint32_t *u2 = b, *v2 = b + 48, *r2 = b + 96, *s2 = b + 144;
    uint32_t *ures = c, *vres = c + 48, *rres = c + 96, *sres = c + 144;
    uint32_t temp1[96], temp2[48 * 7];
    // M1
    bs3_add64(temp1, u2, s2);
    bs3_add64(temp1+48, u1, s1);
    bs3_mul64(temp2, temp1, temp1+48);

    // M2
    bs3_add64(temp1, r2, s2);
    bs3_mul64(temp2+48, temp1, u1);

    // M3
    bs3_sub64(temp1, v1, s1);
    bs3_mul64(temp2+96, u2, temp1);

    // M4
    bs3_sub64(temp1, r1, u1);
    bs3_mul64(temp2+144, s2, temp1);

    // M5
    bs3_add64(temp1, u2, v2);
    bs3_mul64(temp2+192, temp1, s1);

    // M6
    bs3_sub64(temp1, r2, u2);
    bs3_add64(temp1+48, u1, v1);
    bs3_mul64(temp2+240, temp1, temp1+48);

    // M7
    bs3_sub64(temp1, v2, s2);
    bs3_add64(temp1+48, r1, s1);
    bs3_mul64(temp2+288, temp1, temp1+48);

    // final
    bs3_add128(ures, temp2, temp2+144);
    bs3_sub128(ures, ures, temp2+192);
    bs3_add128(ures, ures, temp2+288);

    bs3_add128(vres, temp2+96, temp2+192);

    polyf3_lsl_fast(c);

    bs3_add128(rres, temp2+48, temp2+144);

    bs3_sub128(sres, temp2, temp2+48);
    bs3_add128(sres, sres, temp2+96);
    bs3_add128(sres, sres, temp2+240);
}

void polyf3_mmul128s(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 48, *r1 = a + 96, *s1 = a + 144;
    uint32_t *u2 = b, *v2 = b + 48, *r2 = b + 96, *s2 = b + 144;
    uint32_t *ures = c, *vres = c + 48, *rres = c + 96, *sres = c + 144;
    uint32_t temp1[96], temp2[48 * 7];
    // M1
    bs3_add128(temp1, u2, s2);
    bs3_add128(temp1+48, u1, s1);
    bs3_mul128(temp2, temp1, temp1+48);

    // M2
    bs3_add128(temp1, r2, s2);
    bs3_mul128(temp2+48, temp1, u1);

    // M3
    bs3_sub128(temp1, v1, s1);
    bs3_mul128(temp2+96, u2, temp1);

    // M4
    bs3_sub128(temp1, r1, u1);
    bs3_mul128(temp2+144, s2, temp1);

    // M5
    bs3_add128(temp1, u2, v2);
    bs3_mul128(temp2+192, temp1, s1);

    // M6
    bs3_sub128(temp1, r2, u2);
    bs3_add128(temp1+48, u1, v1);
    bs3_mul128(temp2+240, temp1, temp1+48);

    // M7
    bs3_sub128(temp1, v2, s2);
    bs3_add128(temp1+48, r1, s1);
    bs3_mul128(temp2+288, temp1, temp1+48);

    // final
    bs3_add256(ures, temp2, temp2+144);
    bs3_sub256(ures, ures, temp2+192);
    bs3_add256(ures, ures, temp2+288);

    bs3_add256(vres, temp2+96, temp2+192);

    polyf3_lsl_fast(c);

    bs3_add256(rres, temp2+48, temp2+144);

    bs3_sub256(sres, temp2, temp2+48);
    bs3_add256(sres, sres, temp2+96);
    bs3_add256(sres, sres, temp2+240);
}

void polyf3_mmul256s(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 48, *r1 = a + 96, *s1 = a + 144;
    uint32_t *u2 = b, *v2 = b + 48, *r2 = b + 96, *s2 = b + 144;
    uint32_t *ures = c, *vres = c + 48, *rres = c + 96, *sres = c + 144;
    uint32_t temp1[96], temp2[48 * 7];
    // M1
    bs3_add256(temp1, u2, s2);
    bs3_add256(temp1+48, u1, s1);
    bs3_mul256(temp2, temp1, temp1+48);

    // M2
    bs3_add256(temp1, r2, s2);
    bs3_mul256(temp2+48, temp1, u1);

    // M3
    bs3_sub256(temp1, v1, s1);
    bs3_mul256(temp2+96, u2, temp1);

    // M4
    bs3_sub256(temp1, r1, u1);
    bs3_mul256(temp2+144, s2, temp1);

    // M5
    bs3_add256(temp1, u2, v2);
    bs3_mul256(temp2+192, temp1, s1);

    // M6
    bs3_sub256(temp1, r2, u2);
    bs3_add256(temp1+48, u1, v1);
    bs3_mul256(temp2+240, temp1, temp1+48);

    // M7
    bs3_sub256(temp1, v2, s2);
    bs3_add256(temp1+48, r1, s1);
    bs3_mul256(temp2+288, temp1, temp1+48);

    // final
    bs3_add512(ures, temp2, temp2+144);
    bs3_sub512(ures, ures, temp2+192);
    bs3_add512(ures, ures, temp2+288);

    bs3_add512(vres, temp2+96, temp2+192);

    polyf3_lsl_fast(c);

    bs3_add512(rres, temp2+48, temp2+144);

    bs3_sub512(sres, temp2, temp2+48);
    bs3_add512(sres, sres, temp2+96);
    bs3_add512(sres, sres, temp2+240);
}

void polyf3_mmul256x512s(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 48, *r1 = a + 96, *s1 = a + 144;
    uint32_t *u2 = b, *v2 = b + 48, *r2 = b + 96, *s2 = b + 144;
    uint32_t *ures = c, *vres = c + 48, *rres = c + 96, *sres = c + 144;
    uint32_t temp1[96], temp2[48 * 7];
    // M1
    bs3_add256(temp1, u2, s2);
    bs3_add512(temp1+48, u1, s1);
    bs3_mul256x512(temp2, temp1, temp1+48);

    // M2
    bs3_add256(temp1, r2, s2);
    bs3_mul256x512(temp2+48, temp1, u1);

    // M3
    bs3_sub512(temp1, v1, s1);
    bs3_mul256x512(temp2+96, u2, temp1);

    // M4
    bs3_sub512(temp1, r1, u1);
    bs3_mul256x512(temp2+144, s2, temp1);

    // M5
    bs3_add256(temp1, u2, v2);
    bs3_mul256x512(temp2+192, temp1, s1);

    // M6
    bs3_sub256(temp1, r2, u2);
    bs3_add512(temp1+48, u1, v1);
    bs3_mul256x512(temp2+240, temp1, temp1+48);

    // M7
    bs3_sub256(temp1, v2, s2);
    bs3_add512(temp1+48, r1, s1);
    bs3_mul256x512(temp2+288, temp1, temp1+48);

    // final
    bs3_add768(ures, temp2, temp2+144);
    bs3_sub768(ures, ures, temp2+192);
    bs3_add768(ures, ures, temp2+288);
    polyf3_lsl_fast(ures);

    bs3_add768(vres, temp2+96, temp2+192);
    polyf3_lsl_fast(vres);

    bs3_add768(rres, temp2+48, temp2+144);

    bs3_sub768(sres, temp2, temp2+48);
    bs3_add768(sres, sres, temp2+96);
    bs3_add768(sres, sres, temp2+240);
}
*/

void bs3_polymul_32x32_2x2_x2p2(uint32_t *fgnew, uint32_t *fh, uint32_t *gh, uint32_t uvrs[12]) {
    uint32_t *fp = uvrs, *gp = uvrs + 2;
    uint32_t *u = uvrs + 4, *v = uvrs + 6, *r = uvrs + 8, *s = uvrs + 10;
    uint32_t temp[192];
    bs3_mul32(temp, u, fh);
    bs3_mul32(temp+24, v, gh);
    polyf3_lsl_fast(temp); // * y
    bs3_mul32(temp+96, r, fh); // r * fh
    bs3_mul32(temp+144, s, gh); // s * gh

    bs3_add64(fgnew, temp, temp+24); // (u * fh + v * gh) * y
    bs3_add64(fgnew+4, temp+96, temp+144); // (r * fh + s * gh)
    bs3_add32(fgnew, fgnew, fp);
    bs3_add32(fgnew+4, fgnew+4, gp);
}

void bs3_polymul_64x64_2x2_x2p2(uint32_t *fgnew, uint32_t *fh, uint32_t *gh, uint32_t uvrs[24]) {
    uint32_t *fp = uvrs, *gp = uvrs + 4;
    uint32_t *u = uvrs + 8, *v = uvrs + 12, *r = uvrs + 16, *s = uvrs + 20;
    uint32_t temp[192];
    bs3_mul64(temp, u, fh);
    bs3_mul64(temp+24, v, gh);
    polyf3_lsl_fast(temp); // * y
    bs3_mul64(temp+96, r, fh); // r * fh
    bs3_mul64(temp+144, s, gh); // s * gh

    bs3_add128(fgnew, temp, temp+24); // (u * fh + v * gh) * y
    bs3_add128(fgnew+8, temp+96, temp+144); // (r * fh + s * gh)
    bs3_add64(fgnew, fgnew, fp);
    bs3_add64(fgnew+8, fgnew+8, gp);
}

void bs3_polymul_128x128_2x2_x2p2(uint32_t *fgnew, uint32_t *fh, uint32_t *gh, uint32_t uvrs[48]) {
    uint32_t *fp = uvrs, *gp = uvrs + 8;
    uint32_t *u = uvrs + 16, *v = uvrs + 24, *r = uvrs + 32, *s = uvrs + 40;
    uint32_t temp[192];
    bs3_mul128(temp, u, fh);
    bs3_mul128(temp+24, v, gh);
    polyf3_lsl_fast(temp); // * y
    bs3_mul128(temp+96, r, fh); // r * fh
    bs3_mul128(temp+144, s, gh); // s * gh

    bs3_add256(fgnew, temp, temp+24); // (u * fh + v * gh) * y
    bs3_add256(fgnew+16, temp+96, temp+144); // (r * fh + s * gh)
    bs3_add128(fgnew, fgnew, fp);
    bs3_add128(fgnew+16, fgnew+16, gp);
}

void bs3_polymul_256x256_2x2_x2p2(uint32_t *fgnew, uint32_t *fh, uint32_t *gh, uint32_t uvrs[96]) {
    uint32_t *fp = uvrs, *gp = uvrs + 16;
    uint32_t *u = uvrs + 32, *v = uvrs + 48, *r = uvrs + 64, *s = uvrs + 80;
    uint32_t temp[192];
    bs3_mul256(temp, u, fh);
    bs3_mul256(temp+48, v, gh);
    polyf3_lsl_fast(temp); // * y
    polyf3_lsl_fast(temp+48); // * y
    bs3_mul256(temp+96, r, fh); // r * fh
    bs3_mul256(temp+144, s, gh); // s * gh

    bs3_add512(fgnew, temp, temp+24); // (u * fh + v * gh) * y
    bs3_add512(fgnew+32, temp+96, temp+144); // (r * fh + s * gh)
    bs3_add256(fgnew, fgnew, fp);
    bs3_add256(fgnew+32, fgnew+32, gp);
}

// entry size of matrix * entry size of vector
void bs3_polymul_256x512_2x2_x2p2(uint32_t *fgnew, uint32_t *fh, uint32_t *gh, uint32_t uvrs[96]) {
    uint32_t *fp = uvrs, *gp = uvrs + 16;
    uint32_t *u = uvrs + 32, *v = uvrs + 48, *r = uvrs + 64, *s = uvrs + 80;
    uint32_t temp[192];
    bs3_mul256x512(temp, u, fh);
    bs3_mul256x512(temp+48, v, gh);
    polyf3_lsl_fast(temp); // * y
    polyf3_lsl_fast(temp+48); // * y
    bs3_mul256x512(temp+96, r, fh); // r * fh
    bs3_mul256x512(temp+144, s, gh); // s * gh

    bs3_add768(fgnew, temp, temp+48); // (u * fh + v * gh) * y
    bs3_add768(fgnew+48, temp+96, temp+144); // (r * fh + s * gh)
    bs3_add256(fgnew, fgnew, fp);
    bs3_add256(fgnew+48, fgnew+48, gp);
}

void bs3_polymul_512x256_2x2_x2p2(uint32_t *fgnew, uint32_t *fh, uint32_t *gh, uint32_t uvrs[192]) {
    uint32_t *fp = uvrs, *gp = uvrs + 16;
    uint32_t *u = uvrs + 64, *v = uvrs + 96, *r = uvrs + 128, *s = uvrs + 160;
    uint32_t temp[192];
    bs3_mul256x512(temp, fh, u);
    bs3_mul256x512(temp+48, gh, v);
    polyf3_lsl_fast(temp); // * y
    polyf3_lsl_fast(temp+48); // * y
    bs3_mul256x512(temp+96, fh, r); // r * fh
    bs3_mul256x512(temp+144, gh, s); // s * gh

    bs3_add768(fgnew, temp, temp+48); // (u * fh + v * gh) * y
    bs3_add768(fgnew+48, temp+96, temp+144); // (r * fh + s * gh)
    bs3_add256(fgnew, fgnew, fp);
    bs3_add256(fgnew+48, fgnew+48, gp);
}

void polyf3_butterfly32_CT(uint32_t *tritIn1, uint32_t *tritIn2, int k) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
    uint32_t *readOp1 = tritIn1, *readOp2 = tritIn2, *writeOp1 = tritIn1, *writeOp2 = tritIn2;

    polyf3_rol32_negc(tritIn2, k);

    r0 = *(readOp1++);
    r1 = *(readOp1++);
    r2 = *(readOp2++);
    r3 = *(readOp2++);

    r8 = r1 ^ r2; // r8 = a1 ^ b0
    r4 = r8 ^ r3; // r4 = (a1 ^ b0) ^ b1
    r9 = r0 ^ r2; // r9 = a0 ^ b0
    r5 = r0 ^ r3; // r5 = a0 ^ b1
    r5 = r5 & r8; // r5 = (a0 ^ b1) & (a1 ^ b0)
    r7 = r9 ^ r3; // r7 = (a0 ^ b0) ^ b1
    r7 = r7 & r8; // r7 = ((a0 ^ b0) ^ b1) & (a1 ^ b0)
    r4 = r4 | r9; // r4 = ((a1 ^ b0) ^ b1) | (a0 ^ b0)
    r6 = r1 ^ r3; // r6 = a1 ^ b1
    r6 = r6 | r9; // r6 = (a0 ^ b0) | (a1 ^ b1)

    *(writeOp1++) = r4;
    *(writeOp1++) = r5;
    *(writeOp2++) = r6;
    *(writeOp2++) = r7;
}

void polyf3_butterfly32_GS(uint32_t *tritIn1, uint32_t *tritIn2, int k) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
    uint32_t *readOp1 = tritIn1, *readOp2 = tritIn2, *writeOp1 = tritIn1, *writeOp2 = tritIn2;

    r0 = *(readOp1++);
    r1 = *(readOp1++);
    r2 = *(readOp2++);
    r3 = *(readOp2++);

    r8 = r1 ^ r2; // r8 = a1 ^ b0
    r4 = r8 ^ r3; // r4 = (a1 ^ b0) ^ b1
    r9 = r0 ^ r2; // r9 = a0 ^ b0
    r5 = r0 ^ r3; // r5 = a0 ^ b1
    r5 = r5 & r8; // r5 = (a0 ^ b1) & (a1 ^ b0)
    r7 = r9 ^ r3; // r7 = (a0 ^ b0) ^ b1
    r7 = r7 & r8; // r7 = ((a0 ^ b0) ^ b1) & (a1 ^ b0)
    r4 = r4 | r9; // r4 = ((a1 ^ b0) ^ b1) | (a0 ^ b0)
    r6 = r1 ^ r3; // r6 = a1 ^ b1
    r6 = r6 | r9; // r6 = (a0 ^ b0) | (a1 ^ b1)

    *(writeOp1++) = r4;
    *(writeOp1++) = r5;
    *(writeOp2++) = r6;
    *(writeOp2++) = r7;

    polyf3_rol32_negc(tritIn2, k);
}

void polyf3_butterfly64_CT(uint32_t *tritIn1, uint32_t *tritIn2, int k) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
    uint32_t *readOp1 = tritIn1, *readOp2 = tritIn2, *writeOp1 = tritIn1, *writeOp2 = tritIn2;

    polyf3_rol64_negc(tritIn2, k);

    for (int i = 0; i < 2; i++) {
        r0 = *(readOp1++);
        r1 = *(readOp1++);
        r2 = *(readOp2++);
        r3 = *(readOp2++);

        r8 = r1 ^ r2; // r8 = a1 ^ b0
        r4 = r8 ^ r3; // r4 = (a1 ^ b0) ^ b1
        r9 = r0 ^ r2; // r9 = a0 ^ b0
        r5 = r0 ^ r3; // r5 = a0 ^ b1
        r5 = r5 & r8; // r5 = (a0 ^ b1) & (a1 ^ b0)
        r7 = r9 ^ r3; // r7 = (a0 ^ b0) ^ b1
        r7 = r7 & r8; // r7 = ((a0 ^ b0) ^ b1) & (a1 ^ b0)
        r4 = r4 | r9; // r4 = ((a1 ^ b0) ^ b1) | (a0 ^ b0)
        r6 = r1 ^ r3; // r6 = a1 ^ b1
        r6 = r6 | r9; // r6 = (a0 ^ b0) | (a1 ^ b1)

        *(writeOp1++) = r4;
        *(writeOp1++) = r5;
        *(writeOp2++) = r6;
        *(writeOp2++) = r7;
    }
}

void polyf3_butterfly64_GS(uint32_t *tritIn1, uint32_t *tritIn2, int k) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
    uint32_t *readOp1 = tritIn1, *readOp2 = tritIn2, *writeOp1 = tritIn1, *writeOp2 = tritIn2;

    for (int i = 0; i < 2; i++) {
        r0 = *(readOp1++);
        r1 = *(readOp1++);
        r2 = *(readOp2++);
        r3 = *(readOp2++);

        r8 = r1 ^ r2; // r8 = a1 ^ b0
        r4 = r8 ^ r3; // r4 = (a1 ^ b0) ^ b1
        r9 = r0 ^ r2; // r9 = a0 ^ b0
        r5 = r0 ^ r3; // r5 = a0 ^ b1
        r5 = r5 & r8; // r5 = (a0 ^ b1) & (a1 ^ b0)
        r7 = r9 ^ r3; // r7 = (a0 ^ b0) ^ b1
        r7 = r7 & r8; // r7 = ((a0 ^ b0) ^ b1) & (a1 ^ b0)
        r4 = r4 | r9; // r4 = ((a1 ^ b0) ^ b1) | (a0 ^ b0)
        r6 = r1 ^ r3; // r6 = a1 ^ b1
        r6 = r6 | r9; // r6 = (a0 ^ b0) | (a1 ^ b1)

        *(writeOp1++) = r4;
        *(writeOp1++) = r5;
        *(writeOp2++) = r6;
        *(writeOp2++) = r7;
    }

    polyf3_rol64_negc(tritIn2, k);
}
