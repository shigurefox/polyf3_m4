#include <stdint.h>

void polyf3_pack(uint32_t *, uint32_t *);
void polyf3_unpack(uint32_t *,uint32_t *);
void polyf3_pack_fast(uint32_t *, uint32_t *);
void polyf3_unpack_fast(uint32_t *, uint32_t *);
void polyf3_add_packed_fast(uint32_t *, uint32_t *, uint32_t *);
void polyf3_sub_packed_fast(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mul_packed_fast(uint32_t *, uint32_t *, uint32_t *);
void polyf3_mul_scalar_packed_fast(uint32_t *, uint32_t[2], uint32_t *);

void hybrid_mult_32x32(int32_t *, uint32_t *, uint32_t *);
void polyf3_divstep(int32_t, uint32_t *, uint32_t *);
void polyf3_jump32divsteps(int32_t, uint32_t *, uint32_t *, uint32_t *);

void polyf3_ror(uint32_t *);
void polyf3_ror_fast(uint32_t *);
void polyf3_ror767_adcs(uint32_t *);
void polyf3_ror767_bfi(uint32_t *);
void polyf3_ror767_fast(uint32_t *);

void polyf3_jump32divsteps768(int32_t, uint32_t *, uint32_t *, uint32_t *);
