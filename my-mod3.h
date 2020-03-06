#include <stdint.h>

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

void polyf3_add32(uint32_t *, uint32_t *, uint32_t *);
void polyf3_add64(uint32_t *, uint32_t *, uint32_t *);
void polyf3_add128(uint32_t *, uint32_t *, uint32_t *);
void polyf3_add256(uint32_t *, uint32_t *, uint32_t *);
void polyf3_add512(uint32_t *, uint32_t *, uint32_t *);
void polyf3_sub32(uint32_t *, uint32_t *, uint32_t *);
void polyf3_sub64(uint32_t *, uint32_t *, uint32_t *);
void polyf3_sub128(uint32_t *, uint32_t *, uint32_t *);
void polyf3_sub256(uint32_t *, uint32_t *, uint32_t *);
void polyf3_sub512(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mul256x512(uint32_t *, uint32_t *, uint32_t *);

void polyf3_divstep(int32_t, uint32_t *, uint32_t *);
void polyf3_j32d(int32_t, uint32_t *, uint32_t *, uint32_t *); // for prototype
void polyf3_j32d768(int32_t *, uint32_t *, uint32_t *, uint32_t [192]);
void polyf3_j64d768(int32_t *, uint32_t *, uint32_t *, uint32_t [192]);
void polyf3_j128d768(int32_t *, uint32_t *, uint32_t *, uint32_t [192]);
void polyf3_j256d768(int32_t *, uint32_t *, uint32_t *, uint32_t [192]);
void polyf3_j512d768(int32_t *, uint32_t *, uint32_t *, uint32_t [192]);

void polyf3_mmul32(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mmul64(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mmul128(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mmul256(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mmul32s(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mmul64s(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mmul128s(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mmul256s(uint32_t *, uint32_t *, uint32_t *);

void polyf3_update32(uint32_t *, uint32_t *, uint32_t *);
void polyf3_update64(uint32_t *, uint32_t *, uint32_t *);
void polyf3_update128(uint32_t *, uint32_t *, uint32_t *);
void polyf3_update256(uint32_t *, uint32_t *, uint32_t *);

void polyf3_lsr(uint32_t *);
void polyf3_lsl(uint32_t *);
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
