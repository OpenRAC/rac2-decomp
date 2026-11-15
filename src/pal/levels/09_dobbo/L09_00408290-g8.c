/* func_PAL_L09_00408290, the PAL copy of func_L09_00403398: the same C, where 0.033333335f becomes
   0.040000003f; 0.087266475f becomes 0.10471977f; 0.026179943f becomes 0.031415932f. */
#include "common.h"

extern s32 D_L09_001B2878 __attribute__((sda));
extern u8 *D_L09_001B285C MACRO_ADDR;
extern u16 *D_L09_001FB560[];

extern f32 D_L09_001B13B8 __attribute__((sda));
extern f32 D_L09_001B13BC __attribute__((sda));
extern f32 D_L09_001B13C4 __attribute__((sda));
extern f32 D_L09_001B13C8 __attribute__((sda));
extern f32 D_L09_001B13CC __attribute__((sda));
extern f32 D_L09_001B13D0 __attribute__((sda));
extern u8 *g_hero_moby NOT_SDA;

extern void FastVecSub(void *, void *, void *);
extern f32 FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern f32 math_square(f32);
extern void math_update_wrapped_angle_offset(u8 *, void *, void *, f32, f32, f32);
extern void moby_scale_owner_words_by_angles(u8 *, void *, void *, f32, f32, f32);

void func_PAL_L09_00408290(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    f32 P[4] __attribute__((aligned(16)));
    f32 B[4] __attribute__((aligned(16)));
    f32 C[4] __attribute__((aligned(16)));
    u8 *t;
    u16 *p;
    u8 *e;
    f32 f0, f2, len, w;
    f32 height;

    *(f32 *)(state + 0x288) = *(f32 *)(a0 + 0x18);
    if (a0[0x20] != 9 && a0[0x20] != 4) {
        height = *(f32 *)(state + 0x294) - 0.040000003f;
        *(f32 *)(state + 0x294) = height;
        qcopy(P, a0 + 0x10);
        P[2] = height + (D_L09_001B13C4 - D_L09_001B13BC);
        t = *(u8 **)(state + 0x188);
        if (t == 0 || (t != g_hero_moby && *(s16 *)(t + 0xAA) != 0xD57 &&
                       *(s16 *)(*(u8 **)(t + 0x24) + 0x46) >= 11)) {
            f0 = *(f32 *)(state + 0x288) + D_L09_001B13BC;
            f2 = *(f32 *)(state + 0x294);
            if (f2 < f0)
                *(f32 *)(state + 0x294) = f2 + (f0 - f2) * D_L09_001B13C8;
        }
        f0 = *(f32 *)(state + 0x264) + D_L09_001B13BC;
        f2 = *(f32 *)(state + 0x294);
        if (f2 < f0)
            *(f32 *)(state + 0x294) = f2 + (f0 - f2) * D_L09_001B13C8;
        if (a0[0x20] >= 6 && a0[0x20] <= 8) {
            f0 = *(f32 *)(*(u8 **)(state + 0x230) + 0x18) + D_L09_001B13B8;
            f2 = *(f32 *)(state + 0x294);
            if (f2 < f0)
                *(f32 *)(state + 0x294) = f2 + (f0 - f2) * D_L09_001B13CC;
        }
        *(f32 *)(a0 + 0x18) = *(f32 *)(state + 0x294);
        qzero_nc(B);
        p = D_L09_001FB560[a0[0x21]];
        for (;
             a0[0x21] != 0xFF && a0[0x21] <= D_L09_001B2878 && p != 0 &&
             ((p != 0 && (s16)p[-1] >= 0) || p == D_L09_001FB560[a0[0x21]]);
             p++) {
            e = D_L09_001B285C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            FastVecSub(C, a0 + 0x10, e + 0x10);
            len = FastVecLength(C);
            if (len > D_L09_001B13D0)
                len = D_L09_001B13D0;
            else if (len < 0.0f)
                len = 0.0f;
            w = 1.0f - len / D_L09_001B13D0;
            math_square(w);
            vec_scale_to_length(C, C, len * w);
            FastVecAdd(B, B, C);
        }
        FastVecAdd(a0 + 0x10, a0 + 0x10, B);
        math_update_wrapped_angle_offset(a0, state + 0x278, state + 0x27C, 0.1f, 0.10471977f, *(f32 *)(a0 + 0x18));
        moby_scale_owner_words_by_angles(a0, state + 0x280, state + 0x284, 0.13962635f, 0.031415932f, 0.031415932f);
    } else {
        *(f32 *)(state + 0x294) = *(f32 *)(a0 + 0x18);
    }
}
