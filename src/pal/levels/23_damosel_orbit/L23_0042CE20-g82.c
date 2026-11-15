#include "include_asm.h"

#include "common.h"
extern u8 *g_mothership_boss_moby __attribute__((sda));
extern s32 D_L23_001B1694 __attribute__((sda));
extern s32 g_hero_moby __attribute__((nosda));
extern float D_L23_001B36FC;
extern char D_L23_001BA500[];
extern u8 *part_find_owned_effect_slot(u8 *, s32, s32);
extern void FastDecTimer(u8 *);
extern s32 mothership_is_attack_state(void);
extern s32 mothership_is_held(void);
extern void func_PAL_L23_00423838(void);
extern void func_PAL_002AC290(u8 *, u8 *);
extern void func_PAL_002AC3C0(u8 *, u8 *);
extern void func_PAL_L23_004217B0(u8 *);
extern float math_random_signed_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern u8 *func_PAL_002735D0(u8 *, s32, s32, s32, u8 *, u8 *, float *, float, float, s32);
extern void func_PAL_003120C0(void);

/* Hit handler of the object: takes the damage of the object that hit it (unless the shield state
   or the hit filter rejects the hit), then spawns one particle per set bit of the mask word, at
   most ten, fewer the more of the timer is left. */
void func_PAL_L23_0042CE20(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *hit;
    s32 n;
    s32 i;
    float vec[3];

    hit = part_find_owned_effect_slot(moby, 0x30000, 1);
    moby[0xA8] = 0xFF;
    FastDecTimer(vars + 0x26);
    if (hit != 0) {
        if (mothership_is_attack_state() == 0 || *(s16 *)(vars + 0x26) != 0 ||
            (g_mothership_boss_moby != 0 && mothership_is_held() != 0) ||
            (*(s32 *)(hit + 0x20) == g_hero_moby && D_L23_001B1694 < 0)) {
            if (mothership_is_held() != 0)
                func_PAL_L23_00423838();
            hit = 0;
        }
    }
    if (hit != 0) {
        *(float *)(vars + 0x20) = *(float *)(vars + 0x20) - *(float *)(hit + 0x2C);
        if (*(float *)(vars + 0x20) > 0.0f) {
            vars[0x147] = 0xFF;
            func_PAL_002AC290(moby, vars + 0x140);
            func_PAL_L23_004217B0(*(u8 **)(hit + 0x20));
            if (*(s16 *)(*(u8 **)(hit + 0x20) + 0xAA) != 0x118F)
                *(s16 *)(vars + 0x26) = 0x11;
            if (*(u16 *)(moby + 0x7C) != 0) {
                float f;

                f = *(float *)(vars + 0x20) / D_L23_001B36FC;
                n = 10 - (s32)(f * 10.0f);
                for (i = 0; i < n; i++) {
                    s32 mask = *(u16 *)(moby + 0x7C);

                    if ((mask >> i) & 1) {
                        float angle, speed;
                        u8 *p;
                        u8 *base = (u8 *)D_L23_001BA500;
                        float spread = 90.0f;
                        float per_tick = 0.020000001f;
                        float to_rad = 0.017453294f;

                        *(u16 *)(moby + 0x7C) = mask & ~(1 << i);
                        angle = FastAddRotations(math_random_signed_float_range(spread, 120.0f) * to_rad,
                                              *(float *)(base + 0x158));
                        speed = math_random_float_range(2.0f, 4.0f) * per_tick;
                        vec[0] = math_fast_sin_or_cos_a(angle) * speed;
                        vec[1] = math_fast_sin_or_cos_b(angle) * speed;
                        vec[2] = 0.0f;
                        vec[2] = math_random_float_range(5.0f, 8.0f) * per_tick;
                        p = func_PAL_002735D0(moby, 1, *(s16 *)(moby + 0xAA), i, moby + 0x10, moby + 0xF0,
                                          vec, spread, 15.0f, 0xFF);
                        if (p != 0)
                            *(void (**)(void))(p + 0x64) = func_PAL_003120C0;
                    }
                }
            }
        }
    }
    func_PAL_002AC3C0(moby, vars + 0x140);
}
