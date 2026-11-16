#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int TI128 __attribute__((mode(TI)));
extern char *part_find_owned_effect_slot(char *, int, int);
extern float moby_update_aim_target_strength_pal(char *, void *);
extern void vec_resolve_direction(char *, char *, char *, char *);
extern void moby_init_launched_object_pal(char *, char *, int, int, int, float);
extern void anim_start_blended_pal(char *, int, int, int);
extern void SetDeathBits_pal(char *, int, int);
extern void gfx_start_color_fade_pal(char *, char *);
extern void gfx_update_color_fade_pal(char *, char *);

/* One step of an object that can be hit: it takes damage from what touches it, and when its health runs out it switches to its defeated state and plays that animation. */
void destructible_update_pal(char *moby, char *vars_in)
{
    char *vars = vars_in;
    char *hit;
    struct { TI128 in; float out[4]; } aim;
    float health;
    float strength;

    if (*(u8 *)(moby + 0x20) == 4)
        return;
    hit = part_find_owned_effect_slot(moby, 0xC30000, 0);
    strength = moby_update_aim_target_strength_pal(moby, hit);
    if (0.0f < strength) {
        health = *(float *)(vars + 0x20) - *(float *)(hit + 0x2C);
        *(float *)(vars + 0x20) = health;
        if (0.0f < health) {
            *(float *)(vars + 0x78) = 0.16000001f;
            *(float *)(vars + 0x7C) = 0.14000002f;
            aim.in = *(TI128 *)(hit + 0x10);
            vec_resolve_direction((char *)&aim.in, (char *)aim.out, vars + 0x78, vars + 0x7C);
            moby_init_launched_object_pal(moby, vars + 0x60, 3, 1, 0, aim.out[0]);
            if (1.0f <= strength) {
                *(u8 *)(vars + 0x57) = 0x78;
                *(u8 *)(moby + 0x20) = 3;
                anim_start_blended_pal(moby, 2, 0, 0);
            } else {
                *(u8 *)(vars + 0x57) = 0x78;
            }
        } else {
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            *(u8 *)(vars + 0x57) = 0xFA;
            *(u8 *)(moby + 0x20) = 4;
            *(float *)(vars + 0x78) = 0.22000001f;
            *(float *)(vars + 0x7C) = 0.14000002f;
            aim.in = *(TI128 *)(hit + 0x10);
            vec_resolve_direction((char *)&aim.in, (char *)(aim.out + 1), vars + 0x78, vars + 0x7C);
            moby_init_launched_object_pal(moby, vars + 0x60, 3, 1, 0, aim.out[1]);
            *(float *)(vars + 0xB0) = 5.0f;
            *(float *)(vars + 0xB4) = 10.0f;
            if (*(u8 *)(moby + 0x43) != 3)
                anim_start_blended_pal(moby, 3, 0, 0);
            SetDeathBits_pal(moby, 0, 3);
        }
        gfx_start_color_fade_pal(moby, vars + 0x50);
    }
    *(u8 *)(moby + 0xA8) = 0xFF;
    gfx_update_color_fade_pal(moby, vars + 0x50);
}

