/* func_PAL_L03_003DDB50, the PAL copy of func_L03_003D9820: the same C with the 90-frame timer
   becomes 75. */
#include "common.h"

typedef struct {
    f32 velocity[4];
    s16 timer;
    s16 count;
    u8 *owner;
    s32 value;
} SpawnVars;

extern u8 *CreateMoby(s32);
extern void moby_init_child_from_parent(u8 *, u8 *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 vec_length_xy(void *);
extern f32 g_spark_shot_speed_scale __attribute__((sda));

u8 *func_PAL_L03_003DDB50(u8 *owner, void *position, f32 *velocity, s32 value)
{
    u8 *object = CreateMoby(0xA72);
    SpawnVars *vars;
    if (object != 0) {
        vars = *(SpawnVars **)(object + 0x68);
        moby_init_child_from_parent(object, owner);
        qcopy(object + 0x10, position);
        *(f32 *)(object + 0xF8) = mat_fast_helper_a(velocity[0], velocity[1]);
        *(f32 *)(object + 0xF4) = -mat_fast_helper_a(vec_length_xy(velocity), velocity[2]);
        qcopy(vars, velocity);
        vars->value = value;
        vars->timer = 0x4B;
        vars->owner = owner;
        vars->count = 0;
        *(f32 *)(object + 0x2C) = *(f32 *)(*(u8 **)(object + 0x24) + 0x24) * g_spark_shot_speed_scale;
    }
    return object;
}
