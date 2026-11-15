#include "common.h"

typedef union { int q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern void moby_set_state(u8 *, s32, s32);
extern s32 flag_is_third_pending_set(u8 *);
extern void anim_start_immediate(u8 *, s32, s32);
extern void anim_start_blended(u8 *, s32, s32, s32);
extern void FastVecAdd(void *, void *, void *);
extern void door_spawn_debris_piece(u8 *, void *, void *, s32);
extern s32 math_fast_float_d(void *);
extern void moby_mark_spawned(u8 *);

/* Updates a door (Factory Door and similar, moby class 4933 too). It opens and closes with animations and throws out small pieces of itself each time. The pieces fly off and are then removed. */
void factory_door_update(u8 *object)
{
    Vector position, velocity;
    f32 scale;
    u8 *vars;
    switch (object[0x20]) {
    case 0:
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (flag_is_third_pending_set(object) != 0) {
            f32 initial;
            moby_set_state(object, 2, -1);
            anim_start_immediate(object, 1, 0);
            *(s32 *)(object + 0x98) = 0;
            initial = *(f32 *)(object + 0x2C) / *(f32 *)(*(u8 **)(object + 0x24) + 0x24);
            position.q = 0;
            position.f[2] = initial * 0.05833333730697632f;
            door_spawn_debris_piece(object, object + 0x10, &position, 0x3C);
        }
        break;
    case 2:
        if ((object[0x60] & 2) != 0) {
            moby_set_state(object, 3, -1);
            if (object[0x43] != 2)
                anim_start_blended(object, 2, 0, 1);
        }
        break;
    case 3:
        if (flag_is_third_pending_set(object) == 0) {
            moby_set_state(object, 4, -1);
            anim_start_immediate(object, 3, 0);
            scale = *(f32 *)(object + 0x2C) / *(f32 *)(*(u8 **)(object + 0x24) + 0x24);
            position.q = 0;
            position.f[2] = scale * 3.5f;
            FastVecAdd(&position, &position, object + 0x10);
            velocity.q = 0;
            scale *= 0.05833333730697632f;
            velocity.f[2] = scale;
            door_spawn_debris_piece(object, &position, &velocity, 0x3C);
            *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
        }
        break;
    case 4:
        if ((object[0x60] & 2) != 0) {
            moby_set_state(object, 1, -1);
            if (object[0x43] != 0)
                anim_start_blended(object, 0, 0, 1);
        }
        break;
    case 5:
        vars = *(u8 **)(object + 0x68);
        FastVecAdd(object + 0x10, object + 0x10, vars);
        if (math_fast_float_d(vars + 0x10) != 0)
            moby_mark_spawned(object);
        break;
    }
}
