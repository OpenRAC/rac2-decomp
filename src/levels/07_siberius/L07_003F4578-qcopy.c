#include "include_asm.h"
#include "common.h"

/* The grouped quadword copy: the R5900 lq/sq pair with both addresses in registers. */
typedef int TI128 __attribute__((mode(TI)));

extern void func_00282CC0(u8 *a, u8 *b, u8 *c);

extern void func_00282CF0(u8 *a, u8 *b, u8 *c);

extern f32 func_00282DF0(void *a);

extern void func_00282F20(void *dst, void *src, f32 scale);

extern s32 func_002761F8(void *a, void *b, s32 c, void *d, s32 e);

extern void func_L07_003F8898(u8 *a, void *b);

extern u8 *func_L07_003F4B08(u8 *a0, u8 *a1, void *a2, void *a3, f32 a4);

extern void func_002E5CF8(s32 a, s32 b, u8 *c);

extern void func_0029FCC0(u8 *a, s32 b, void *c);

extern TI128 D_L07_001BF660;

/* The tool's own spin: the shared vector, the two sampled ones, then the shared pass. */
void func_L07_003F8AB0(u8 *a0)
{
    TI128 v[3];
    u8 *s3;
    f32 len;

    s3 = *(u8 **)(a0 + 0x68);
    PlayMobySound(1, 0, a0);
    func_0029FCC0(a0, 0, &v[0]);
    func_L07_003F8898(a0, &v[2]);
    FastVecSub(&v[1], &v[2], &v[0]);
    len = FastVecLength(&v[1]);
    vec_scale_to_length(&v[1], &v[1], len + 2.0f);
    FastVecAdd(&v[1], &v[1], &v[0]);
    if (CollLine(&v[0], &v[1], 2, a0, 0) != 0) {
        v[1] = D_L07_001BF660;
    }
    func_L07_003F4B08(a0, *(s32 *)(s3 + 0x418), &v[0], &v[1], (f32)*(u8 *)(s3 + 0x34));
}
