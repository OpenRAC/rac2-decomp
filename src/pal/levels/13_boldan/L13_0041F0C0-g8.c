#include "names.h"
/*
 * func_PAL_L13_0041F0C0, the PAL copy of func_L13_0041A398: the same C, with the
 * 50 Hz scale on the two timers stored at state + 0x10, and 4 where v1.01 has 5.
 */
#include "common.h"

extern s32 g_lightning_beam_countdown __attribute__((sda));
extern s32 g_lightning_beam_machine_flag __attribute__((sda));
extern s32 g_streak_fade_end __attribute__((sda));
extern s32 g_lightning_beam_machine_blocked __attribute__((sda));
extern s32 math_fast_helper_a(void *a0, f32 f12);
extern s32 FastDecTimer(void *a0);
extern void lightning_beam_build_pal(u8 *a0);
extern void streak_effect_update(u8 *a0);
extern void gfx_add_draw_callback_third(void *a0, u8 *a1);
extern u8 gfx_draw_electric_beam[];

typedef struct {
    f32 f[4];
} __attribute__((aligned(16))) L13_Quad;

/* Lightning beam machine: builds a new beam on a timer and, while its beam is alive, updates the streak and draws the electric beam. */
void lightning_beam_machine_update_pal(u8 *self)
{
    u8 *state;
    s32 one;
    L13_Quad v;

    state = *(u8 **)(self + 0x68);
    if (self[0x20] != 0) {
        qcopy(&v, self + 0x10);
        v.f[3] = *(f32 *)(state + 0x624);
        if (math_fast_helper_a(&v, 52.0f) < 0)
            return;
    }
    if (*(s32 *)(state + 0x628) == 0)
        return;
    one = 1;
    switch (self[0x20]) {
    case 0:
        lightning_beam_build_pal(self);
        *(u16 *)(state + 0x10) = (*(s32 *)(state + 0xC) * 5 + 2) / 6;
        self[0x20] = 2;
        *(f32 *)(state + 0x624) = 2.5f;
        *(s16 *)(state + 8) = one;
        *(s16 *)(state + 0xA) = one;
        break;
    case 1:
        if (g_lightning_beam_countdown != 0 && *(s16 *)(state + 0x12) == 0) {
            g_lightning_beam_countdown = g_lightning_beam_countdown - 1;
            lightning_beam_build_pal(self);
        }
        break;
    case 2:
        if (FastDecTimer(state + 0x10) != 0) {
            self[0x20] = 3;
            *(u16 *)(state + 0x10) = ((int)(*(s16 *)(state + 4)) * 5 + 2) / 6;
            lightning_beam_build_pal(self);
        }
        break;
    case 3:
        if (FastDecTimer(state + 0x10) != 0) {
            if (*(s16 *)(state + 6) != 0)
                self[0x20] = 2;
            *(s16 *)(state + 0x10) = 4;
        } else if (*(s16 *)(state + 0x12) == 0) {
            lightning_beam_build_pal(self);
        }
        break;
    }
    if (*(s16 *)(state + 0x12) != 0) {
        if (g_lightning_beam_machine_flag == 0)
            streak_effect_update(self);
        if (g_streak_fade_end < *(s16 *)(state + 0x12) && g_lightning_beam_machine_blocked == 0)
            gfx_add_draw_callback_third(gfx_draw_electric_beam, self);
    }
}
