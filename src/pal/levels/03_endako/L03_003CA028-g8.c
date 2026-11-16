#include "include_asm.h"

#include "common.h"
extern f32 g_rotor_spin_speed __attribute__((sda));
extern f32 g_rotor_roll_speed __attribute__((sda));
extern f32 g_rotor_speed_table[2] __attribute__((sda));
extern char g_sound_l03_slot_table[];
typedef struct { f32 scale; f32 spin; f32 wobble[2]; f32 roll; f32 fade; s32 slot; } SpinState;
extern void moby_set_state(char *object, s32 a1, s32 a2);
extern f32  FastAddRotations(f32 object, f32 a1);
extern void gfx_add_draw_callback_first(void *object, void *a1);
extern void rotor_draw(void);
extern s32  flag_is_third_pending_set(char *object);
extern f32  ApproachValue(f32 *object, f32 a1, f32 a2);
extern void snd_stop_voice(s32 object);
extern s32  PlayMobySound(s32 object, s32 a1, char *a2);

/* Updates a spinning rotor: spins and wobbles it, draws it, fades it out when hit, and loops its sound. (PAL) */
void rotor_update_pal(char *object)
{
    char *moby = object;
    SpinState *vars = *(SpinState **)(moby + 0x68);

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(f32 *)(moby + 0x2C) = *(f32 *)(*(s32 *)(moby + 0x24) + 0x24) * vars->scale;
        moby_set_state(moby, 1, -1);
        *(u16 *)(moby + 0x34) |= 1;
        *(u8 *)(moby + 0x31) = 0;
        vars->fade = 1.0f;
        break;
    case 1: {
        f32 angle_step = 0.0003490659f;
        f32 *speed_ptr = g_rotor_speed_table;
        f32 *ptr = vars->wobble;
        s32 i;

        vars->spin = FastAddRotations(vars->spin, g_rotor_spin_speed * angle_step);
        vars->roll = FastAddRotations(vars->roll, g_rotor_roll_speed * angle_step);
        for (i = 1; i >= 0; i--) {
            *ptr = FastAddRotations(*ptr, *speed_ptr * 0.0003490659f);
            ptr++;
            speed_ptr++;
        }
        gfx_add_draw_callback_first(rotor_draw, moby);
        if (flag_is_third_pending_set(moby) != 0) {
            ApproachValue(&vars->fade, 0.0f, 0.040000003f);
            if (vars->fade <= 0.0f) {
                moby_set_state(moby, 2, -1);
                *(s32 *)(moby + 0x98) = 0;
            }
        }
        break;
    }
    }
    if (*(u8 *)(moby + 0x20) == 1) {
        char *ptr = g_sound_l03_slot_table + vars->slot * 0x70;

        if (*(char **)(ptr + 0x88) != moby || *(u8 *)(ptr + 0x74) == 0)
            vars->slot = PlayMobySound(0, 4, moby);
    } else {
        s32 slot = vars->slot;

        if (slot != -1) {
            char *ptr = g_sound_l03_slot_table + slot * 0x70;

            if (*(char **)(ptr + 0x88) == moby && *(u8 *)(ptr + 0x74) != 0)
                snd_stop_voice(slot);
        }
        vars->slot = -1;
    }
}
