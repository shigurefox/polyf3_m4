#include <stdint.h>

extern void polyf3_pack_asm(uint32_t *, uint32_t *);
extern void polyf3_unpack_asm(uint32_t *, uint32_t *);
extern void polyf3_add_packed_asm(uint32_t *, uint32_t *, uint32_t *);
extern void polyf3_sub_packed_asm(uint32_t *, uint32_t *, uint32_t *);
extern void polyf3_mul_packed_asm(uint32_t *, uint32_t *, uint32_t *);

extern void bs3_mul32(uint32_t *, uint32_t *, uint32_t *);
extern void bs3_mul64(uint32_t *, uint32_t *, uint32_t *);
extern void bs3_mul128(uint32_t *, uint32_t *, uint32_t *);
extern void bs3_mul256(uint32_t *, uint32_t *, uint32_t *);
extern void bs3_j32d(int32_t, uint32_t *, uint32_t *, uint32_t *);

extern void polyf3_mul32_packed_asm(uint32_t *, uint32_t *, uint32_t *);
extern void polyf3_mul64_packed_asm(uint32_t *, uint32_t *, uint32_t *);
extern void polyf3_mul128_packed_asm(uint32_t *, uint32_t *, uint32_t *);
extern void polyf3_mul256_packed_asm(uint32_t *, uint32_t *, uint32_t *);
extern void polyf3_mul768_packed_asm(uint32_t *, uint32_t *, uint32_t *);

void polyf3_selftest_add(void);
void polyf3_selftest_sub(void);
void polyf3_selftest_mul(void);
void polyf3_selftest_mmuls(void);

void polyf3_pack(uint32_t *, uint32_t *);
void polyf3_unpack(uint32_t *,uint32_t *);
void polyf3_add_packed(uint32_t *, uint32_t *, uint32_t *);
void polyf3_sub_packed(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mul_packed(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mul_scalar_packed(uint32_t *, uint32_t[2], uint32_t *);

void polyf3_pack_fast(uint32_t *, uint32_t *);
void polyf3_unpack_fast(uint32_t *, uint32_t *);
void polyf3_add_packed_fast(uint32_t *, uint32_t *, uint32_t *);
void polyf3_sub_packed_fast(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mul_packed_fast(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mul_scalar_packed_fast(uint32_t *, uint32_t[2], uint32_t *);

void bs3_add32(uint32_t *, uint32_t *, uint32_t *);
void bs3_add64(uint32_t *, uint32_t *, uint32_t *);
void bs3_add128(uint32_t *, uint32_t *, uint32_t *);
void bs3_add256(uint32_t *, uint32_t *, uint32_t *);
void bs3_add512(uint32_t *, uint32_t *, uint32_t *);
void bs3_add768(uint32_t *, uint32_t *, uint32_t *);
void bs3_sub32(uint32_t *, uint32_t *, uint32_t *);
void bs3_sub64(uint32_t *, uint32_t *, uint32_t *);
void bs3_sub128(uint32_t *, uint32_t *, uint32_t *);
void bs3_sub256(uint32_t *, uint32_t *, uint32_t *);
void bs3_sub512(uint32_t *, uint32_t *, uint32_t *);
void bs3_sub768(uint32_t *, uint32_t *, uint32_t *);
void bs3_mul256x512(uint32_t *, uint32_t *, uint32_t *);
void bs3_mul768(uint32_t *, uint32_t *, uint32_t *);

void polyf3_divstep(int32_t, uint32_t *, uint32_t *);
void polyf3_j17d(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void polyf3_j32d(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void polyf3_j64d(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void polyf3_j128d(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void polyf3_j256d(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void polyf3_j512d(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void polyf3_j768d(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void polyf3_j1521d(int32_t *, uint32_t *, uint32_t *, uint32_t *);

void bs3_jump17divsteps(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_jump32divsteps(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_jump49divsteps(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_jump64divsteps(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_jump128divsteps(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_jump256divsteps(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_jump512divsteps(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_jump753divsteps(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_jump768divsteps(int32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_jump1521divsteps(int32_t *, uint32_t *, uint32_t *, uint32_t *);

// mxn_2x2_x_2x2 : 2x2 matrix of entry length n multiplied by another matrix of entry length m
void bs3_polymul_32x32_2x2_x_2x2(uint32_t *, uint32_t *, uint32_t *);
void bs3_polymul_64x64_2x2_x_2x2(uint32_t *, uint32_t *, uint32_t *);
void bs3_polymul_128x128_2x2_x_2x2(uint32_t *, uint32_t *, uint32_t *);
void bs3_polymul_256x256_2x2_x_2x2(uint32_t *, uint32_t *, uint32_t *);
void bs3_polymul_256x512_2x2_x_2x2(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mmul32s(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mmul64s(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mmul128s(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mmul256s(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mmul256x512s(uint32_t *, uint32_t *, uint32_t *);

// mxn_2x2_x2p2 : 1x2 vector of entry length n multiplied by 2x2 matrix of entry length m
void bs3_polymul_32x32_2x2_x2p2(uint32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_polymul_64x64_2x2_x2p2(uint32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_polymul_128x128_2x2_x2p2(uint32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_polymul_256x256_2x2_x2p2(uint32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_polymul_256x512_2x2_x2p2(uint32_t *, uint32_t *, uint32_t *, uint32_t *);
void bs3_polymul_512x256_2x2_x2p2(uint32_t *, uint32_t *, uint32_t *, uint32_t *);

void polyf3_lsr(uint32_t *);
void polyf3_lsl(uint32_t *);
void polyf3_lsl1536(uint32_t *);
void polyf3_lsr_fast(uint32_t *);
void polyf3_lsl_fast(uint32_t *);

void polyf3_rol32_negc(uint32_t *, int);
void polyf3_rol64_negc(uint32_t *, int);
void polyf3_rol32_negc_fast(uint32_t *);
void polyf3_rol64_negc_fast(uint32_t *);

void polyf3_butterfly32_CT(uint32_t *, uint32_t *, int k);
void polyf3_butterfly32_GS(uint32_t *, uint32_t *, int k);
void polyf3_butterfly64_CT(uint32_t *, uint32_t *, int k);
void polyf3_butterfly64_GS(uint32_t *, uint32_t *, int k);
