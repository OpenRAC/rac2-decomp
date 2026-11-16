#include "include_asm.h"

#include "common.h"
typedef int quad __attribute__((mode(TI)));
extern char g_aim_target_position[];
extern f32 g_shockwave_growth_rate __attribute__((sda));
extern f32 g_shockwave_radius_limit __attribute__((sda));
extern void FastVecAdd(char *, char *, char *);
extern void part_spawn_spinning_fragment_pal(char *);
extern s32 CollLine(char *, char *, s32, s32, s32);
extern void moby_set_state(char *, s32, s32);
extern char *SpawnExplosion_pal(char *, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern int coll_sweep_from_object(char *, char *, f32, f32, u32, s32, s32, s32, f32);
extern s32 flag_set_first_pending(char *);
extern f32 ApproachValue(f32 *, f32, f32);
extern void moby_mark_spawned(char *);
extern void SweepAndDrawRibbonRing(char *);
extern void gfx_add_draw_callback_first(void (*)(char *), char *);

/* Moves a fragment until impact and runs its fading shock-wave effect. */
void fragment_shockwave_update_pal(char *self) {
    quad previous;
    char *vars = *(char **)(self + 0x68);

    switch (*(u8 *)(self + 0x20)) {
    case 0: {
        char *old = (char *)&previous;
        char *position = self + 16;
        qcopy(old,position);
        FastVecAdd(position, position, vars);
        *(f32 *)(vars + 8) -= *(f32 *)(vars + 0x24);
        part_spawn_spinning_fragment_pal(self);
        if (CollLine(old, position, 0, *(s32 *)(self + 0xB8), 0)) {
            qcopy(position ,g_aim_target_position);
            if (*(s32 *)(vars + 0x20)) moby_set_state(self, 2, -1);
            else moby_set_state(self, 1, -1);
        }
        break;
    }
    case 1: {
        char *position = self + 16;
        SpawnExplosion_pal(position, 1.0f, 20.0f, 0, 25, 20, 20, 20, 45, 1, 1, 0, 0, 0);
        coll_sweep_from_object(self, position, 2.0f, 6.0f, 0x10001, 0, 1, 0, 1.0f);
        moby_mark_spawned(self);
        break;
    }
    case 2:
        if (flag_set_first_pending(self)) {
            SpawnExplosion_pal(self + 16, 0.6660000085830688f, 20.0f, 0, 20, 15, 15, 15, 35, 1, 1, 0, 0, 0);
            *(s32 *)(self + 0x98) = 0;
            *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) | 0x41) & 0xEFFF;
            *(f32 *)(self + 0x18) += 0.5f;
            *(f32 *)(vars + 0x30) = 1.0f;
        }
        *(f32 *)(vars + 0x34) += 0.080000006f;
        if (*(f32 *)(vars + 0x34) > 1.0f) *(f32 *)(vars + 0x34) -= 1.0f;
        { f32 radius = *(f32 *)(vars + 0x2C);
          f32 growth = g_shockwave_growth_rate * 0.020000001f;
          f32 limit = g_shockwave_radius_limit;
          radius += growth;
          *(f32 *)(vars + 0x2C) = radius;
        if (radius >= limit) ApproachValue((f32 *)(vars + 0x30), 0.0f, 0.080000006f);
        }
        if (*(f32 *)(vars + 0x30) <= 0.0f) moby_mark_spawned(self);
        else gfx_add_draw_callback_first(SweepAndDrawRibbonRing, self);
        break;
    }
}
