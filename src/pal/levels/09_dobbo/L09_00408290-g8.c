#include "names.h"
/* func_PAL_L09_00408290, the PAL copy of func_L09_00403398: the same C, where 0.033333335f becomes
   0.040000003f; 0.087266475f becomes 0.10471977f; 0.026179943f becomes 0.031415932f. */
#include "common.h"

extern s32 g_max_l09_group_id __attribute__((sda));
extern u8 *g_moby_record_table MACRO_ADDR;
extern u16 *g_track_entry_table[];

extern f32 g_dobbo_height_limit_offset __attribute__((sda));
extern f32 g_dobbo_height_base_offset __attribute__((sda));
extern f32 g_dobbo_height_top_offset __attribute__((sda));
extern f32 g_dobbo_height_blend_up __attribute__((sda));
extern f32 g_dobbo_height_blend_down __attribute__((sda));
extern f32 g_dobbo_separation_range __attribute__((sda));
extern u8 *g_hero_moby NOT_SDA;

extern void FastVecSub(void *, void *, void *);
extern f32 FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern f32 math_square(f32);
extern void math_update_wrapped_angle_offset(u8 *, void *, void *, f32, f32, f32);
extern void moby_scale_owner_words_by_angles(u8 *, void *, void *, f32, f32, f32);

void dobbo_update_height_separation_pal(u8 *a0)
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
        P[2] = height + (g_dobbo_height_top_offset - g_dobbo_height_base_offset);
        t = *(u8 **)(state + 0x188);
        if (t == 0 || (t != g_hero_moby && *(s16 *)(t + 0xAA) != 0xD57 &&
                       *(s16 *)(*(u8 **)(t + 0x24) + 0x46) >= 11)) {
            f0 = *(f32 *)(state + 0x288) + g_dobbo_height_base_offset;
            f2 = *(f32 *)(state + 0x294);
            if (f2 < f0)
                *(f32 *)(state + 0x294) = f2 + (f0 - f2) * g_dobbo_height_blend_up;
        }
        f0 = *(f32 *)(state + 0x264) + g_dobbo_height_base_offset;
        f2 = *(f32 *)(state + 0x294);
        if (f2 < f0)
            *(f32 *)(state + 0x294) = f2 + (f0 - f2) * g_dobbo_height_blend_up;
        if (a0[0x20] >= 6 && a0[0x20] <= 8) {
            f0 = *(f32 *)(*(u8 **)(state + 0x230) + 0x18) + g_dobbo_height_limit_offset;
            f2 = *(f32 *)(state + 0x294);
            if (f2 < f0)
                *(f32 *)(state + 0x294) = f2 + (f0 - f2) * g_dobbo_height_blend_down;
        }
        *(f32 *)(a0 + 0x18) = *(f32 *)(state + 0x294);
        qzero_nc(B);
        p = g_track_entry_table[a0[0x21]];
        for (;
             a0[0x21] != 0xFF && a0[0x21] <= g_max_l09_group_id && p != 0 &&
             ((p != 0 && (s16)p[-1] >= 0) || p == g_track_entry_table[a0[0x21]]);
             p++) {
            e = g_moby_record_table + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            FastVecSub(C, a0 + 0x10, e + 0x10);
            len = FastVecLength(C);
            if (len > g_dobbo_separation_range)
                len = g_dobbo_separation_range;
            else if (len < 0.0f)
                len = 0.0f;
            w = 1.0f - len / g_dobbo_separation_range;
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
