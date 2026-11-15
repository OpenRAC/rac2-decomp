#include "common.h"

/* Puts the object back on its rail: resets the flags, the state block and the
   animation, then places it on the rail point at the current angle. */

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
extern int part_spawn_damage_debris(char *, char *, char *);
extern f32 math_fast_sin_or_cos_a(f32 a0);
extern f32 math_fast_sin_or_cos_b(f32 a0);
extern f32 FastAddRotations(f32 a0, f32 a1);
extern void euler_rotation_basis(void *a0, void *a1);
extern f32 *arena_get_center_point(s32 a0);

extern f32 D_L11_001B0558 __attribute__((sda));
extern f32 D_L11_001B0540 __attribute__((sda));

/* Puts the Joba rail object back on its rail at angle zero and resets its state. */
void joba_rail_reset(u8 *moby_bytes) {
    L11Moby *moby = (L11Moby *)moby_bytes;
    u8 *vars = *(u8 **)(moby_bytes + 0x68);
    f32 *rail_point;
    f32 trig;
    f32 new_y;
    u32 model_word;

    *(f32 *)(vars + 0x20) = (f32)*(s16 *)(vars + 0x24);
    model_word = *(u32 *)(moby->model + 0x10);
    moby->flags &= 0xFFFE;
    moby->b31 = 1;
    moby->w98 = model_word;
    *(u8 *)(vars + 0x2E) = 1;
    moby->b7F = 0;
    moby->flags = (moby->flags & 0xFFB9) | 0x1000;
    *(s32 *)(vars + 0x60) = 0;
    part_spawn_damage_debris((char *)moby, (char *)(vars + 0x50), (char *)(vars + 0x20));
    if (*(s16 *)(vars + 0x70) != 0) {
        *(s16 *)(vars + 0x70) = 0;
        set_moby_color(moby, *(u32 *)(vars + 0x280), *(u32 *)(vars + 0x284),
                      *(u32 *)(vars + 0x288));
        *(s16 *)(vars + 0x72) = 1;
    }
    moby_set_state(moby_bytes, 2, 2);
    *(s32 *)(vars + 0x250) = 0;
    trig = math_fast_sin_or_cos_a(*(f32 *)(vars + 0x250));
    rail_point = arena_get_center_point(moby->slot);
    moby->x = D_L11_001B0558 * trig + rail_point[0];
    trig = math_fast_sin_or_cos_b(*(f32 *)(vars + 0x250));
    rail_point = arena_get_center_point(moby->slot);
    new_y = D_L11_001B0558 * trig + rail_point[1];
    moby->z = D_L11_001B0540;
    moby->rotX = -1.5707965f;
    moby->rotW = 0;
    moby->y = new_y;
    moby->rotZ = FastAddRotations(3.1415927f, *(f32 *)(vars + 0x250));
    euler_rotation_basis(moby->mtx, &moby->rotW);
}
