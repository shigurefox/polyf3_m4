#include "my-mod3.h"
#include "cmsis.h"

// assert input size = 768
// TODO: the possibility to exploit "signs"
// TODO: the possibility to exploit BFI
void polyf3_pack_fast(uint32_t* tritOut, uint32_t* mod3In) {
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
void polyf3_unpack_fast(uint32_t* mod3Out, uint32_t* tritIn) {
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
void polyf3_add_packed_fast(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
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
void polyf3_sub_packed_fast(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
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
void polyf3_mul_packed_fast(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
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


void polyf3_mul_scalar_packed_fast(uint32_t *tritOut, uint32_t *tritIn1, uint32_t *tritIn2) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8;
    uint32_t *readOp1, *readOp2, *writeSum, *bndry;

    readOp1 = tritIn1;
    readOp2 = tritIn2;
    writeSum = tritOut;
    bndry = writeSum + 48;
    r0 = *(readOp1++);
    r1 = *(readOp1++);
    r2 = __SBFX(r0, 0, 1);
    r3 = __SBFX(r1, 0, 1);

    while (writeSum != bndry) {
        r4 = *(readOp2++);
        r5 = *(readOp2++);

        r6 = r2 & r4;
        r7 = r3 ^ r5;
        r8 = r6 & r7;

        *(writeSum++) = r6;
        *(writeSum++) = r8;
    }
}

void hybrid_mult_32x32(int32_t *cf, uint32_t *c_from1, uint32_t *f_from1) {
  uint32_t r0, r1, r2, r3;
  int32_t ir0, ir1, ir2, ir3, ir4, ir5, ir6;

    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    ir0 = __SMULBB(r0, r2);
    ir2 = __SMULBB(r0, r3);
    ir1 = __SMUADX(r0, r2);
    ir3 = __SMUADX(r0, r3);
    ir5 = __SMUADX(r1, r3);
    ir4 = __SMULTT(r1, r2);
    ir6 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    *(cf++) = ir0;
    *(cf++) = ir1;
    *(cf++) = ir2;
    *(cf++) = ir3;
    r1 = *(c_from1 + 1);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMUADX(r0, r3);
    ir1 = __SMUADX(r1, r3);
    ir0 = __SMULTT(r1, r2);
    ir2 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r0 = *(c_from1 - 1);
    r1 = *(c_from1++);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r0 = *(c_from1 - 2);
    *(cf++) = ir4;
    *(cf++) = ir5;
    *(cf++) = ir6;
    *(cf++) = ir3;
    r3 = *(f_from1 + 1);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMUADX(r0, r3);
    ir5 = __SMUADX(r1, r3);
    ir4 = __SMULTT(r1, r2);
    ir6 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r2 = *(f_from1 - 1);
    r3 = *(f_from1++);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    *(cf++) = ir0;
    *(cf++) = ir1;
    *(cf++) = ir2;
    *(cf++) = ir3;
    r1 = *(c_from1 + 1);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMUADX(r0, r3);
    ir1 = __SMUADX(r1, r3);
    ir0 = __SMULTT(r1, r2);
    ir2 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r0 = *(c_from1 - 1);
    r1 = *(c_from1++);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r0 = *(c_from1 - 2);
    *(cf++) = ir4;
    *(cf++) = ir5;
    *(cf++) = ir6;
    *(cf++) = ir3;
    r3 = *(f_from1 + 1);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMUADX(r0, r3);
    ir5 = __SMUADX(r1, r3);
    ir4 = __SMULTT(r1, r2);
    ir6 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r2 = *(f_from1 - 1);
    r3 = *(f_from1++);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    *(cf++) = ir0;
    *(cf++) = ir1;
    *(cf++) = ir2;
    *(cf++) = ir3;
    r1 = *(c_from1 + 1);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMUADX(r0, r3);
    ir1 = __SMUADX(r1, r3);
    ir0 = __SMULTT(r1, r2);
    ir2 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r0 = *(c_from1 - 1);
    r1 = *(c_from1++);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r0 = *(c_from1 - 2);
    *(cf++) = ir4;
    *(cf++) = ir5;
    *(cf++) = ir6;
    *(cf++) = ir3;
    r3 = *(f_from1 + 1);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMUADX(r0, r3);
    ir5 = __SMUADX(r1, r3);
    ir4 = __SMULTT(r1, r2);
    ir6 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r2 = *(f_from1 - 1);
    r3 = *(f_from1++);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    *(cf++) = ir0;
    *(cf++) = ir1;
    *(cf++) = ir2;
    *(cf++) = ir3;
    r1 = *(c_from1 + 1);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMUADX(r0, r3);
    ir1 = __SMUADX(r1, r3);
    ir0 = __SMULTT(r1, r2);
    ir2 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r3 = *(f_from1 + 1);
    r2 = *(f_from1--);
    r0 = *(c_from1 - 1);
    r1 = *(c_from1++);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    *(cf++) = ir4;
    *(cf++) = ir5;
    *(cf++) = ir6;
    *(cf++) = ir3;
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMUADX(r0, r3);
    ir5 = __SMUADX(r1, r3);
    ir4 = __SMULTT(r1, r2);
    ir6 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r1 = *(c_from1 + 1);
    r0 = *(c_from1--);
    r2 = *(f_from1 - 1);
    r3 = *(f_from1++);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1 + 1);
    *(cf++) = ir0;
    *(cf++) = ir1;
    *(cf++) = ir2;
    *(cf++) = ir3;
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMUADX(r0, r3);
    ir1 = __SMUADX(r1, r3);
    ir0 = __SMULTT(r1, r2);
    ir2 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r3 = *(f_from1 + 1);
    r2 = *(f_from1--);
    r0 = *(c_from1 - 1);
    r1 = *(c_from1++);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    *(cf++) = ir4;
    *(cf++) = ir5;
    *(cf++) = ir6;
    *(cf++) = ir3;
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMUADX(r0, r3);
    ir5 = __SMUADX(r1, r3);
    ir4 = __SMULTT(r1, r2);
    ir6 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r1 = *(c_from1 + 1);
    r0 = *(c_from1--);
    r2 = *(f_from1 - 1);
    r3 = *(f_from1++);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1 + 1);
    *(cf++) = ir0;
    *(cf++) = ir1;
    *(cf++) = ir2;
    *(cf++) = ir3;
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMUADX(r0, r3);
    ir1 = __SMUADX(r1, r3);
    ir0 = __SMULTT(r1, r2);
    ir2 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r1 = *(c_from1--);
    r0 = *(c_from1--);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r3 = *(f_from1 + 1);
    r2 = *(f_from1--);
    r0 = *(c_from1 - 1);
    r1 = *(c_from1++);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    *(cf++) = ir4;
    *(cf++) = ir5;
    *(cf++) = ir6;
    *(cf++) = ir3;
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMUADX(r0, r3);
    ir5 = __SMUADX(r1, r3);
    ir4 = __SMULTT(r1, r2);
    ir6 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    r3 = *(f_from1--);
    r2 = *(f_from1--);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r1 = *(c_from1 + 1);
    r0 = *(c_from1--);
    r2 = *(f_from1 - 1);
    r3 = *(f_from1++);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMLADX(r0, r3, ir3);
    ir5 = __SMLADX(r1, r3, ir5);
    ir4 = __SMLATT(r1, r2, ir4);
    ir6 = __SMLATT(r1, r3, ir6);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    r0 = *(c_from1 + 1);
    *(cf++) = ir0;
    *(cf++) = ir1;
    *(cf++) = ir2;
    *(cf++) = ir3;
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMUADX(r0, r3);
    ir1 = __SMUADX(r1, r3);
    ir0 = __SMULTT(r1, r2);
    ir2 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    r2 = *(f_from1++);
    r3 = *(f_from1++);
    r0 = *(c_from1 - 1);
    r1 = *(c_from1++);
    ir4 = __SMLABB(r0, r2, ir4);
    ir6 = __SMLABB(r0, r3, ir6);
    ir5 = __SMLADX(r0, r2, ir5);
    ir3 = __SMLADX(r0, r3, ir3);
    ir1 = __SMLADX(r1, r3, ir1);
    ir0 = __SMLATT(r1, r2, ir0);
    ir2 = __SMLATT(r1, r3, ir2);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir6 = __SMLAD(r0, r2, ir6);
    ir0 = __SMLAD(r0, r3, ir0);
    *(cf++) = ir4;
    *(cf++) = ir5;
    *(cf++) = ir6;
    *(cf++) = ir3;
    r0 = *(c_from1++);
    r1 = *(c_from1++);
    ir0 = __SMLABB(r0, r2, ir0);
    ir2 = __SMLABB(r0, r3, ir2);
    ir1 = __SMLADX(r0, r2, ir1);
    ir3 = __SMUADX(r0, r3);
    ir5 = __SMUADX(r1, r3);
    ir4 = __SMULTT(r1, r2);
    ir6 = __SMULTT(r1, r3);
    ir3 = __SMLADX(r1, r2, ir3);
    r0 = __PKHBT(r1, r0, 0);
    ir2 = __SMLAD(r0, r2, ir2);
    ir4 = __SMLAD(r0, r3, ir4);
    *(cf++) = ir0;
    *(cf++) = ir1;
    *(cf++) = ir2;
    *(cf++) = ir3;
    *(cf++) = ir4;
    *(cf++) = ir5;
    *(cf++) = ir6;
    *(cf++) = 0;
}

static inline void swapptr(uint32_t **ptr1, uint32_t **ptr2) {
    void *tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
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
void polyf3_jump32divsteps(int32_t d, uint32_t *tritIn1, uint32_t *tritIn2, uint32_t **uvrs) {
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10;
    uint32_t *readOp1, *readOp2, *writeOp, *u, *v, *r, *s;
    readOp1 = tritIn1;
    readOp2 = tritIn2;
    r0 = *(readOp1); // a0
    r1 = *(readOp1+1); // a1
    r2 = *(readOp2); // b0
    r3 = *(readOp2+1); // b1
    u = uvrs[0];
    v = uvrs[1];
    r = uvrs[2];
    s = uvrs[3];

    int delta = d;
    for (int i = 32; i > 0; i--) {
        if ((delta > 0) && ((r2 & 1) != 0)) {
            swapptr(&tritIn1, &tritIn2);
            swapptr(&uvrs[0], &uvrs[2]);
            swapptr(&uvrs[1], &uvrs[3]);
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

        // update
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
