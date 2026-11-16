#include "include_asm.h"

#include "common.h"
extern f32 g_rotor_spin_speed __attribute__((sda));
extern f32 g_rotor_roll_speed __attribute__((sda));
extern f32 g_rotor_speed_table[2] __attribute__((sda));
extern char g_sound_l03_slot_table[];
typedef struct { f32 scale; f32 spin; f32 wobble[2]; f32 roll; f32 fade; s32 slot; } SpinState;
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern f32  FastAddRotations(f32 a0, f32 a1);
extern void gfx_add_draw_callback_first(void *a0, void *a1);
extern void rotor_draw(void);
extern s32  flag_is_third_pending_set(char *a0);
extern f32  ApproachValue(f32 *a0, f32 a1, f32 a2);
extern void snd_stop_voice(s32 a0);
extern s32  PlayMobySound(s32 a0, s32 a1, char *a2);

void func_PAL_L03_003CA028(char *a0)
{
    char *s1 = a0;
    SpinState *s2 = *(SpinState **)(s1 + 0x68);

    switch (*(u8 *)(s1 + 0x20)) {
    case 0:
        *(f32 *)(s1 + 0x2C) = *(f32 *)(*(s32 *)(s1 + 0x24) + 0x24) * s2->scale;
        moby_set_state(s1, 1, -1);
        *(u16 *)(s1 + 0x34) |= 1;
        *(u8 *)(s1 + 0x31) = 0;
        s2->fade = 1.0f;
        break;
    case 1: {
        f32 k = 0.0003490659f;
        f32 *c = g_rotor_speed_table;
        f32 *p = s2->wobble;
        s32 i;

        s2->spin = FastAddRotations(s2->spin, g_rotor_spin_speed * k);
        s2->roll = FastAddRotations(s2->roll, g_rotor_roll_speed * k);
        for (i = 1; i >= 0; i--) {
            *p = FastAddRotations(*p, *c * 0.0003490659f);
            p++;
            c++;
        }
        gfx_add_draw_callback_first(rotor_draw, s1);
        if (flag_is_third_pending_set(s1) != 0) {
            ApproachValue(&s2->fade, 0.0f, 0.040000003f);
            if (s2->fade <= 0.0f) {
                moby_set_state(s1, 2, -1);
                *(s32 *)(s1 + 0x98) = 0;
            }
        }
        break;
    }
    }
    if (*(u8 *)(s1 + 0x20) == 1) {
        char *p = g_sound_l03_slot_table + s2->slot * 0x70;

        if (*(char **)(p + 0x88) != s1 || *(u8 *)(p + 0x74) == 0)
            s2->slot = PlayMobySound(0, 4, s1);
    } else {
        s32 v = s2->slot;

        if (v != -1) {
            char *p = g_sound_l03_slot_table + v * 0x70;

            if (*(char **)(p + 0x88) == s1 && *(u8 *)(p + 0x74) != 0)
                snd_stop_voice(v);
        }
        s2->slot = -1;
    }
}
