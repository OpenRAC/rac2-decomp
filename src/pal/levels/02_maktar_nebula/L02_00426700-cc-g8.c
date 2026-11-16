#include "names.h"
/* func_PAL_L02_00426700, the PAL copy of func_L02_004216F0: the same C, where scale func_00283CF0(D_L02_001B1FA4 / step). */

/* func_PAL_L02_00426700 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it;
   -g gives the two nops retail has before its `div.s` (a -g unit's line labels). */

typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));

extern void *CreateMoby(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern void moby_rebuild_frame_from_transform(u8 *);
extern int PlayMobySound(int, int, void *);
extern char g_hero_state_block[];
extern float g_projectile_start_value __attribute__((sda));
extern float g_projectile_l02_speed __attribute__((sda));
extern float g_projectile_range __attribute__((sda));

/* Creates a projectile moby at the given position, flying along the direction, and plays its launch sound. (PAL: 50 Hz speed scale) */
u8 *projectile_l02_spawn_pal(u8 *position, int target_id, u8 *direction, float damage) {
    u8 *projectile = CreateMoby(0xD08);
    u8 *vars;
    int frame_count;
    float step;

    if (projectile != 0) {
        *(u8 *)(projectile + 0x20) = 0;
        *(u8 *)(projectile + 0x30) = 0xFF;
        step = g_projectile_l02_speed * 0.020000001f;
        vars = *(u8 **)(projectile + 0x68);
        *(float *)(vars + 0x64) = damage;
        vec_scale_to_length(vars + 0x40, direction, step);
        *(TI128 *)(projectile + 0x10) = *(TI128 *)position;
        *(TI128 *)(projectile + 0xC0) = *(TI128 *)(vars + 0x40);
        FastVecCross(projectile + 0xD0, projectile + 0xC0, g_hero_state_block);
        vec_scale_to_length(projectile + 0xD0, projectile + 0xD0, -1.0f);
        FastVecCross(projectile + 0xE0, projectile + 0xD0, projectile + 0xC0);
        step = g_projectile_l02_speed * 0.020000001f;
        frame_count = (((int)(FloatToInt(g_projectile_range / step)) * 5 + 2) / 6);
        *(int *)(vars + 0x58) = frame_count;
        *(float *)(vars + 0x5C) = 1.0f / IntToFloat(frame_count);
        *(int *)(vars + 0x50) = target_id;
        *(u8 *)(projectile + 0x20) = 0;
        *(float *)(vars + 0x60) = g_projectile_start_value;
        moby_rebuild_frame_from_transform(projectile);
        PlayMobySound(1, 0, projectile);
    }
    return projectile;
}
