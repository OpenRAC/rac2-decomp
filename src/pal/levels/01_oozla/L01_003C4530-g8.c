#include "common.h"

extern int func_001163B0(void);
extern int math_random_int_range(int, int);
extern void moby_set_state(void *, int, int);
extern void moby_set_animation_and_speed(void *, int, int, int);

/* Small data reached through $gp: this is only one instruction at -G8. */
extern int g_swamp_monster_attack_b_value __attribute__((sda));

typedef struct L01_003C06E8_OWNED {
    char pad0[0x2DC];
    unsigned short f2DC;
} L01_003C06E8_OWNED;

typedef struct L01_003C06E8_OBJ {
    char pad0[0x68];
    L01_003C06E8_OWNED *f68;
} L01_003C06E8_OBJ;

/* func_PAL_L01_003C4530, the PAL copy of func_L01_003C06E8: the same C, with the stored time
 * scaled for 50 Hz. */
void swamp_monster_start_claw_attack_pal(L01_003C06E8_OBJ *moby)
{
    L01_003C06E8_OBJ *self = moby;
    L01_003C06E8_OWNED *vars = self->f68;
    int anim = (func_001163B0() & 1) + 6;
    int blend_frames = math_random_int_range(10, 15);

    moby_set_animation_and_speed(self, anim, 0, blend_frames);
    moby_set_state(self, 1, 3);
    vars->f2DC = (g_swamp_monster_attack_b_value * 5 + 2) / 6;
}
