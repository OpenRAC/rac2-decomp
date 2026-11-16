#include "include_asm.h"
#include "names.h"

extern void *part_find_owned_effect_slot(char *obj, int state, int a2);
extern float moby_update_aim_target_strength(char *obj, int state);
extern void gfx_start_color_fade(char *obj, char *state);
extern void SetDeathBits(char *obj, int state, int a2);
extern void gfx_update_color_fade(char *obj, char *state);

/* runs a moby's timer down and picks the dying or the revived path from what is left */
void spawner_update_damage_timer_pal(char *obj, char *state)
{
    float strength = moby_update_aim_target_strength(obj, part_find_owned_effect_slot(obj, 0xC30000, 0));

    if (strength > 0.0f) {
        float left = *(float *)(state + 0x20) - strength;

        *(float *)(state + 0x20) = left;
        if (left > 0.0f) {
            *(unsigned char *)(state + 0x57) = 0x5A;
            gfx_start_color_fade(obj, state + 0x50);
        } else {
            SetDeathBits(obj, 0, 3);
            *(unsigned char *)(obj + 0x20) = 2;
            *(unsigned char *)(state + 0x57) = 0x78;
            gfx_start_color_fade(obj, state + 0x50);
        }
    }
    *(unsigned char *)(obj + 0xA8) = 0xFF;
    gfx_update_color_fade(obj, state + 0x50);
}

