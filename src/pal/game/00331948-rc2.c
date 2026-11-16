#include "names.h"
/* func_PAL_00331948, the PAL copy of func_0032FDD0: the same C, where the first
 * read is negated only while the byte at D_PAL_001A7ACC is clear. */
#include "common.h"

extern void vec_clear_128(f32 *v);
extern f32 FastVecLength(f32 *v);
extern s8 g_hero_state[];
extern f32 g_stick_length;
extern u8 g_pal_enable_flag;

/* Reads the left stick into the vehicle state, clamped to -1..1, and stores its length. */
void pad_read_clamped_stick_pal(s8 *object) {
    s8 *hero;
    s8 *hero2;
    s8 *vars;
    f32 vec[2];

    vars = *(s8 **)(object + 0x68);
    if (g_pal_enable_flag != 0) {
        hero = g_hero_state;
        (*(f32 *)((s8 *)(vars) + (0x54))) = (*(f32 *)((s8 *)(hero) + (0x1FB0)));
    } else {
        hero = g_hero_state;
        (*(f32 *)((s8 *)(vars) + (0x54))) = -(*(f32 *)((s8 *)(hero) + (0x1FB0)));
    }
    hero2 = g_hero_state;
    (*(f32 *)((s8 *)(vars) + (0x50))) = -(*(f32 *)((s8 *)(hero2) + (0x1FB4)));
    if ((*(f32 *)((s8 *)(vars) + (0x54))) > 1.0f) {
        (*(f32 *)((s8 *)(vars) + (0x54))) = 1.0f;
    } else if ((*(f32 *)((s8 *)(vars) + (0x54))) < -1.0f) {
        (*(f32 *)((s8 *)(vars) + (0x54))) = -1.0f;
    }
    if ((*(f32 *)((s8 *)(vars) + (0x50))) > 1.0f) {
        (*(f32 *)((s8 *)(vars) + (0x50))) = 1.0f;
    } else if ((*(f32 *)((s8 *)(vars) + (0x50))) < -1.0f) {
        (*(f32 *)((s8 *)(vars) + (0x50))) = -1.0f;
    }
    vec_clear_128(vec);
    vec[0] = (*(f32 *)((s8 *)(vars) + (0x50)));
    vec[1] = (*(f32 *)((s8 *)(vars) + (0x54)));
    g_stick_length = FastVecLength(vec);
}
