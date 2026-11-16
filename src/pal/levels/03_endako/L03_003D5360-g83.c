#include "include_asm.h"

#include "common.h"
extern char *CreateMoby(s32);
extern void moby_init_child_from_parent(char *, char *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 vec_length_xy(f32 *);
extern f32 g_trail_projectile_scale __attribute__((sda));

/* Spawns a trail projectile from a parent object at the given position, with the given velocity
   and damage, aimed along its velocity. Returns the new moby or 0. */
char *trail_projectile_spawn_pal(char *parent, char *position, f32 *velocity, s32 damage)
{
    char *moby = CreateMoby(0xA02);
    char *vars;

    if (moby != 0) {
        vars = *(char **)(moby + 0x68);
        moby_init_child_from_parent(moby, parent);
        qcopy(moby + 0x10, position);
        qcopy(vars, velocity);
        *(f32 *)(moby + 0xF8) = mat_fast_helper_a(velocity[0], velocity[1]);
        {
            f32 xy_length = vec_length_xy(velocity);
            f32 angle = -mat_fast_helper_a(xy_length, velocity[2]);
            f32 scale = g_trail_projectile_scale;

            *(f32 *)(moby + 0xF4) = angle;
            *(s32 *)(vars + 0x30) = 0x64;
            *(s32 *)(vars + 0x38) = damage;
            *(f32 *)(moby + 0x2C) = *(f32 *)(*(u32 *)(moby + 0x24) + 0x24)
                * scale;
        }
    }
    return moby;
}
