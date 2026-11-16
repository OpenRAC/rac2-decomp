#include "include_asm.h"
#include "names.h"

extern void *part_find_owned_effect_slot(char *a0, int a1, int a2);
extern float moby_update_aim_target_strength(char *a0, int a1);
extern void gfx_start_color_fade(char *a0, char *a1);
extern void SetDeathBits(char *a0, int a1, int a2);
extern void gfx_update_color_fade(char *a0, char *a1);

/* runs a moby's timer down and picks the dying or the revived path from what is left */
void spawner_update_damage_timer_pal(char *a0, char *a1)
{
    float t = moby_update_aim_target_strength(a0, part_find_owned_effect_slot(a0, 0xC30000, 0));

    if (t > 0.0f) {
        float left = *(float *)(a1 + 0x20) - t;

        *(float *)(a1 + 0x20) = left;
        if (left > 0.0f) {
            *(unsigned char *)(a1 + 0x57) = 0x5A;
            gfx_start_color_fade(a0, a1 + 0x50);
        } else {
            SetDeathBits(a0, 0, 3);
            *(unsigned char *)(a0 + 0x20) = 2;
            *(unsigned char *)(a1 + 0x57) = 0x78;
            gfx_start_color_fade(a0, a1 + 0x50);
        }
    }
    *(unsigned char *)(a0 + 0xA8) = 0xFF;
    gfx_update_color_fade(a0, a1 + 0x50);
}

