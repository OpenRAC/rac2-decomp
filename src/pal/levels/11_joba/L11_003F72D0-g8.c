#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad0[0x10];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[0x8];
    u8 *model;
    u8 pad28[0x9];
    u8 b31;
    u8 pad32[2];
    u16 flags;
    u8 pad36[0x49];
    u8 b7F;
    u8 pad80[0x18];
    u32 w98;
    u8 pad9C[0x1C];
    s32 slot;
    u8 padBC[0x4];
    u8 mtx[0x30];
    s32 rotW;
    f32 rotX;
    f32 rotZ;
} L11Moby;
extern void moby_set_state(u8 *arg0, s32 arg1, s32 arg2);
extern void set_moby_color(void *, int, int, int);
extern int part_spawn_damage_debris_pal(char *, char *, char *);
extern f32 math_fast_sin_or_cos_a(f32 a0);
extern f32 math_fast_sin_or_cos_b(f32 a0);
extern f32 FastAddRotations(f32 a0, f32 a1);
extern void euler_rotation_basis(void *a0, void *a1);
extern f32 *arena_get_center_point(s32 a0);
extern f32 g_joba_orbit_radius __attribute__((sda));
extern f32 g_orbit_enemy_start_z __attribute__((sda));

/* Resets a Joba enemy to full health and its starting state, then puts it on the orbit circle
   in the arena (PAL: v1.01 joba_rail_reset). */
void joba_rail_reset_pal(u8 *moby) {
    L11Moby *m = (L11Moby *)moby;
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 *center;
    f32 trig_value;
    f32 orbit_y;
    u32 model_value;

    *(f32 *)(vars + 0x20) = (f32)*(s16 *)(vars + 0x24);
    model_value = *(u32 *)(m->model + 0x10);
    m->flags &= 0xFFFE;
    m->b31 = 1;
    m->w98 = model_value;
    *(u8 *)(vars + 0x2E) = 1;
    m->b7F = 0;
    m->flags = (m->flags & 0xFFB9) | 0x1000;
    *(s32 *)(vars + 0x60) = 0;
    part_spawn_damage_debris_pal((char *)m, (char *)(vars + 0x50), (char *)(vars + 0x20));
    if (*(s16 *)(vars + 0x70) != 0) {
        *(s16 *)(vars + 0x70) = 0;
        set_moby_color(m, *(u32 *)(vars + 0x280), *(u32 *)(vars + 0x284),
                      *(u32 *)(vars + 0x288));
        *(s16 *)(vars + 0x72) = 1;
    }
    moby_set_state(moby, 2, 2);
    *(s32 *)(vars + 0x250) = 0;
    trig_value = math_fast_sin_or_cos_a(*(f32 *)(vars + 0x250));
    center = arena_get_center_point(m->slot);
    m->x = g_joba_orbit_radius * trig_value + center[0];
    trig_value = math_fast_sin_or_cos_b(*(f32 *)(vars + 0x250));
    center = arena_get_center_point(m->slot);
    orbit_y = g_joba_orbit_radius * trig_value + center[1];
    m->z = g_orbit_enemy_start_z;
    m->rotX = -1.5707965f;
    m->rotW = 0;
    m->y = orbit_y;
    m->rotZ = FastAddRotations(3.1415927f, *(f32 *)(vars + 0x250));
    euler_rotation_basis(m->mtx, &m->rotW);
}
