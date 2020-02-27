#include "libopencm3/cm3/dwt.h"
#include "my-mod3.h"
#include "cmsis.h"
#include <stdio.h>

#define start_timer() dwt_enable_cycle_counter()
#define get_timer() dwt_read_cycle_counter()
#define stop_timer() *((volatile uint32_t*)0xE0001000) = 0x40000000

extern void polyf3_pack_asm(uint32_t *, uint32_t *);
extern void polyf3_unpack_asm(uint32_t *, uint32_t *);
extern void polyf3_add_packed_asm(uint32_t *, uint32_t *, uint32_t *);
extern void polyf3_sub_packed_asm(uint32_t *, uint32_t *, uint32_t *);
extern void polyf3_mul_packed_asm(uint32_t *, uint32_t *, uint32_t *);

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

void polyf3_swap768(uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r2, r3, r4, r5, r6, r7, r8, r9;
    uint32_t *readOp1 = tritIn1, *readOp2 = tritIn2, *writeOp1 = tritIn2, *writeOp2 = tritIn1;
    for (int i = 0; i < 12; i++) {
        r2 = *(readOp1++);
        r3 = *(readOp1++);
        r4 = *(readOp1++);
        r5 = *(readOp1++);
        r6 = *(readOp2++);
        r7 = *(readOp2++);
        r8 = *(readOp2++);
        r9 = *(readOp2++);
        /*
        r2 = r2 ^ r6;
        r6 = r2 ^ r6;
        r2 = r2 ^ r6;
        r3 = r3 ^ r7;
        r7 = r3 ^ r7;
        r3 = r3 ^ r7;
        r4 = r4 ^ r8;
        r8 = r4 ^ r8;
        r4 = r4 ^ r8;
        r5 = r5 ^ r9;
        r9 = r5 ^ r9;
        r5 = r5 ^ r9;
        */
        *(writeOp1++) = r2;
        *(writeOp1++) = r3;
        *(writeOp1++) = r4;
        *(writeOp1++) = r5;
        *(writeOp2++) = r6;
        *(writeOp2++) = r7;
        *(writeOp2++) = r8;
        *(writeOp2++) = r9;
    }
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


extern void polyf3_lsr_asm(uint32_t *);
extern void polyf3_lsl_asm(uint32_t *);

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

extern void polyf3_rol1_32_asm(uint32_t *);
extern void polyf3_rol1_64_asm(uint32_t *);

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
// TODO: extract update of f and g to another function
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
            swapptr(&tritIn1, &tritIn2);
            polyf3_swap768(u, r);
            polyf3_swap768(v, s);
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
        polyf3_sub_packed_fast(tritIn2, tritIn2, tritTmp);
        polyf3_lsr(tritIn2);

        // r = (r - c*u)
        polyf3_mul_scalar_packed_fast(tritTmp, r4, u);
        polyf3_sub_packed_fast(r, r, tritTmp);

        // s = (s - c*v)
        polyf3_mul_scalar_packed_fast(tritTmp, r4, v);
        polyf3_sub_packed_fast(s, s, tritTmp);

        // TODO: lsl should be omitted in the last iteration
        if (i > 1) {
            polyf3_lsl_fast(u);
            polyf3_lsl_fast(v);
        }
    }

    *d = delta;
}

void polyf3_j64d768(int32_t *d, uint32_t *tritIn1, uint32_t *tritIn2, uint32_t uvrs[192]) {
    int delta = *d;
    uint32_t uvrs1[192] = {[0] = 1, [144] = 1}, uvrs2[192] = {[0] = 1, [144] = 1};

    polyf3_j32d768(&delta, tritIn1, tritIn2, uvrs1);
    polyf3_j32d768(&delta, tritIn1, tritIn2, uvrs2);
    polyf3_mmul32(uvrs, uvrs1, uvrs2);

    //polyf3_update(tritIn1, tritIn2, uvrs);
    *d = delta;
}

void polyf3_j128d768(int32_t *d, uint32_t *tritIn1, uint32_t *tritIn2, uint32_t uvrs[192]) {
    int delta = *d;
    uint32_t uvrs1[192] = {[0] = 1, [144] = 1}, uvrs2[192] = {[0] = 1, [144] = 1};

    polyf3_j64d768(&delta, tritIn1, tritIn2, uvrs1);
    polyf3_j64d768(&delta, tritIn1, tritIn2, uvrs2);
    polyf3_mmul64(uvrs, uvrs1, uvrs2);

    //polyf3_update(tritIn1, tritIn2, uvrs);
    *d = delta;
}

void polyf3_j256d768(int32_t *d, uint32_t *tritIn1, uint32_t *tritIn2, uint32_t uvrs[192]) {
    int delta = *d;
    uint32_t uvrs1[192] = {[0] = 1, [144] = 1}, uvrs2[192] = {[0] = 1, [144] = 1};

    polyf3_j128d768(&delta, tritIn1, tritIn2, uvrs1);
    polyf3_j128d768(&delta, tritIn1, tritIn2, uvrs2);
    polyf3_mmul128(uvrs, uvrs1, uvrs2);

    //polyf3_update(tritIn1, tritIn2, uvrs);
    *d = delta;
}

extern void bs3_mul32(uint32_t *, uint32_t *, uint32_t *);
extern void bs3_mul64(uint32_t *, uint32_t *, uint32_t *);
extern void bs3_mul128(uint32_t *, uint32_t *, uint32_t *);
extern void bs3_mul256(uint32_t *, uint32_t *, uint32_t *);

// 2x2 matrix multiplications
void polyf3_mmul32(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 48, *r1 = a + 96, *s1 = a + 144;
    uint32_t *u2 = b, *v2 = b + 48, *r2 = b + 96, *s2 = b + 144;
    uint32_t *ures = c, *vres = c + 48, *rres = c + 96, *sres = c + 144;
    uint32_t temp[192];

    bs3_mul32(ures, u2, u1);
    bs3_mul32(vres, u2, v1);
    bs3_mul32(rres, r2, u1);
    bs3_mul32(sres, r2, v1);
    bs3_mul32(temp, v2, r1);
    bs3_mul32(temp+48, v2, s1);
    bs3_mul32(temp+96, s2, r1);
    bs3_mul32(temp+144, s2, s1);

    polyf3_lsl_fast(c);
    polyf3_add_packed_fast(c, c, temp);
}

void polyf3_mmul64(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 48, *r1 = a + 96, *s1 = a + 144;
    uint32_t *u2 = b, *v2 = b + 48, *r2 = b + 96, *s2 = b + 144;
    uint32_t *ures = c, *vres = c + 48, *rres = c + 96, *sres = c + 144;

    bs3_mul64(ures, u2, u1);
    bs3_mul64(vres, u2, v1);
    bs3_mul64(rres, r2, u1);
    bs3_mul64(sres, r2, v1);
    bs3_mul64(temp, v2, r1);
    bs3_mul64(temp+48, v2, s1);
    bs3_mul64(temp+96, s2, r1);
    bs3_mul64(temp+144, s2, s1);

    polyf3_lsl_fast(c);
    polyf3_add_packed_fast(c, c, temp);
}

void polyf3_mmul128(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 48, *r1 = a + 96, *s1 = a + 144;
    uint32_t *u2 = b, *v2 = b + 48, *r2 = b + 96, *s2 = b + 144;
    uint32_t *ures = c, *vres = c + 48, *rres = c + 96, *sres = c + 144;

    bs3_mul128(ures, u2, u1);
    bs3_mul128(vres, u2, v1);
    bs3_mul128(rres, r2, u1);
    bs3_mul128(sres, r2, v1);
    bs3_mul128(temp, v2, r1);
    bs3_mul128(temp+48, v2, s1);
    bs3_mul128(temp+96, s2, r1);
    bs3_mul128(temp+144, s2, s1);

    polyf3_lsl_fast(c);
    polyf3_add_packed_fast(c, c, temp);
}

void polyf3_mmul256(uint32_t *c, uint32_t *a, uint32_t *b) {
    uint32_t *u1 = a, *v1 = a + 48, *r1 = a + 96, *s1 = a + 144;
    uint32_t *u2 = b, *v2 = b + 48, *r2 = b + 96, *s2 = b + 144;
    uint32_t *ures = c, *vres = c + 48, *rres = c + 96, *sres = c + 144;

    bs3_mul256(ures, u2, u1);
    bs3_mul256(vres, u2, v1);
    bs3_mul256(rres, r2, u1);
    bs3_mul256(sres, r2, v1);
    bs3_mul256(temp, v2, r1);
    bs3_mul256(temp+48, v2, s1);
    bs3_mul256(temp+96, s2, r1);
    bs3_mul256(temp+144, s2, s1);

    polyf3_lsl_fast(c);
    polyf3_add_packed_fast(c, c, temp);
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
