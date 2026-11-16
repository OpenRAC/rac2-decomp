#include "names.h"
/* func_PAL_00331948, the PAL copy of func_0032FDD0: the same C, where the first
 * read is negated only while the byte at D_PAL_001A7ACC is clear. */
#include "common.h"

extern void vec_clear_128(f32 *v);
extern f32 FastVecLength(f32 *v);
extern s8 g_hero_state[];
extern f32 g_stick_length;
extern u8 g_pal_enable_flag;

void func_PAL_00331948(s8 *a0) {
    s8 *base;
    s8 *base2;
    s8 *obj;
    f32 vec[2];

    obj = *(s8 **)(a0 + 0x68);
    if (g_pal_enable_flag != 0) {
        base = g_hero_state;
        (*(f32 *)((s8 *)(obj) + (0x54))) = (*(f32 *)((s8 *)(base) + (0x1FB0)));
    } else {
        base = g_hero_state;
        (*(f32 *)((s8 *)(obj) + (0x54))) = -(*(f32 *)((s8 *)(base) + (0x1FB0)));
    }
    base2 = g_hero_state;
    (*(f32 *)((s8 *)(obj) + (0x50))) = -(*(f32 *)((s8 *)(base2) + (0x1FB4)));
    if ((*(f32 *)((s8 *)(obj) + (0x54))) > 1.0f) {
        (*(f32 *)((s8 *)(obj) + (0x54))) = 1.0f;
    } else if ((*(f32 *)((s8 *)(obj) + (0x54))) < -1.0f) {
        (*(f32 *)((s8 *)(obj) + (0x54))) = -1.0f;
    }
    if ((*(f32 *)((s8 *)(obj) + (0x50))) > 1.0f) {
        (*(f32 *)((s8 *)(obj) + (0x50))) = 1.0f;
    } else if ((*(f32 *)((s8 *)(obj) + (0x50))) < -1.0f) {
        (*(f32 *)((s8 *)(obj) + (0x50))) = -1.0f;
    }
    vec_clear_128(vec);
    vec[0] = (*(f32 *)((s8 *)(obj) + (0x50)));
    vec[1] = (*(f32 *)((s8 *)(obj) + (0x54)));
    g_stick_length = FastVecLength(vec);
}
