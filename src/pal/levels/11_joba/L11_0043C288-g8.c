/* func_PAL_L11_0043C288, the PAL copy of func_L11_00436D08: the same C, where func_L01_00321178
   becomes func_PAL_L01_00323068. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 pad20[0xE0];
} Entity;

typedef struct {
    u8 pad000[0x134];
    float turn_rate;
    u8 pad138[0x278 - 0x138];
    s32 group;
} AimState;

typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 pad20[0x48];
    AimState *state;
    u8 pad6C[0xE0 - 0x6C];
    float axis[4];
    u8 padF0[8];
    float heading;
} AimObject;

extern u16 *g_group_id_lists[];
extern Entity *g_moby_l11_table[] __attribute__((sda));
extern s32 g_tribe_group_limit __attribute__((sda));

extern float g_enemy_aim_max_distance __attribute__((sda));
extern float g_enemy_l11_aim_cone_degrees __attribute__((sda));
extern float g_enemy_aim_turn_degrees __attribute__((sda));

extern int math_fast_helper_a(void *vec, float radius);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern int moby_l01_turn_toward_target_pal(void *, void *);
extern int moby_get_busy_flag(void *);

/* Looks for an entity of the object's group that is in range and inside its view cone, and if
   found turns the object toward it and runs the follow-up call with a tiny turn rate. */
s32 enemy_aim_at_group_entity_in_cone_short_pal(AimObject *obj)
{
    AimState *state = obj->state;
    float copy[4];
    float vec[4];
    u16 *ids;
    Entity *entity;
    float saved_turn_rate;
    float angle;
    float turn;

    *(TI128 *)vec = 0;
    vec[0] = obj->position[0];
    vec[1] = obj->position[1];
    vec[2] = obj->position[2];
    vec[3] = 2.0f;
    *(TI128 *)copy = *(TI128 *)vec;
    if (math_fast_helper_a(copy, 128.0f) <= 0)
        return 0;
    if (state->group == -1)
        return 0;

    for (ids = g_group_id_lists[state->group];
         (state->group & 0xFF) != 0xFF && state->group <= g_tribe_group_limit && ids != 0 &&
         ((ids != 0 && (s16)ids[-1] >= 0) || ids == g_group_id_lists[state->group]);
         ids++) {
        entity = g_moby_l11_table[0] + (*ids & 0x7FFF);
        if (entity == 0)
            return 0;
        if (!moby_get_busy_flag(entity))
            continue;
        if (!(vec_distance_xy(obj->position, entity->position) < g_enemy_aim_max_distance))
            continue;

        angle = mat_fast_helper_a(entity->position[0] - obj->position[0],
                              entity->position[1] - obj->position[1]);
        if (!(FastDiffRots(obj->heading, angle) < g_enemy_l11_aim_cone_degrees * 0.017453294f))
            continue;
        if (ids == 0)
            return 0;

        FastVecSub(vec, obj->position, entity->position);
        turn = g_enemy_aim_turn_degrees * 0.017453294f;
        angle = mat_fast_helper_a(entity->position[0] - obj->position[0],
                              entity->position[1] - obj->position[1]);
        math_apply_axis_rotation_to_quat(vec, vec, obj->axis,
                      fast_subtract_rotations(obj->heading, angle) >= 0.0f ? -turn : turn);
        FastVecAdd(vec, vec, entity->position);

        saved_turn_rate = state->turn_rate;
        state->turn_rate = 0.0001f;
        moby_l01_turn_toward_target_pal(obj, vec);
        state->turn_rate = saved_turn_rate;
        return 1;
    }
    return 0;
}
