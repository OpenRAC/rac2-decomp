#include "common.h"

/* Split out of L11_00453358.c: this unit needs -frac2-zero-ti-por (the por/sq clear of the
 * vector at 0($sp)) and -frac2-keep-block-order. The list-pointer guard in front of the aim
 * code is deleted by the null-pointer-check pass (ids was just dereferenced); without the
 * block merge it leaves the CSE block boundary that keeps the second saved copy of the target
 * position and the 0x80 frame. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 pad20[0xE0];
} Entity;

typedef struct {
    u8 pad000[0x134];
    float turnRate;
    u8 pad138[0x244 - 0x138];
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

/* Encoded entity id lists per group, the entity pool pointer and the group count. */
extern u16 *g_group_id_lists[];
extern Entity *g_moby_l11_table[] __attribute__((sda));
extern s32 D_L11_001B35B8 __attribute__((sda));

/* Range, cone angle and turn angle (degrees) of this variant. */
extern float D_L11_001B1D94 __attribute__((sda));
extern float D_L11_001B1D98 __attribute__((sda));
extern float D_L11_001B1D9C __attribute__((sda));

extern int math_fast_helper_a(void *vec, float radius);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern int joba_fighter_walk_dust(void *, void *);
extern int moby_get_busy_flag(void *);

/* Looks for an entity of the object's group that is in range and inside its view cone, and if
   found turns the object toward it and runs the follow-up call with a tiny turn rate. */
s32 joba_turn_toward_group_entity(AimObject *obj)
{
    AimState *state = obj->state;
    float copy[4];
    float vec[4];
    u16 *ids;
    Entity *entity;
    float savedTurnRate;
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
         (state->group & 0xFF) != 0xFF && state->group <= D_L11_001B35B8 && ids != 0 &&
         ((ids != 0 && (s16)ids[-1] >= 0) || ids == g_group_id_lists[state->group]);
         ids++) {
        entity = g_moby_l11_table[0] + (*ids & 0x7FFF);
        if (entity == 0)
            return 0;
        if (!moby_get_busy_flag(entity))
            continue;
        if (!(vec_distance_xy(obj->position, entity->position) < D_L11_001B1D94))
            continue;

        angle = mat_fast_helper_a(entity->position[0] - obj->position[0],
                              entity->position[1] - obj->position[1]);
        if (!(FastDiffRots(obj->heading, angle) < D_L11_001B1D98 * 0.017453294f))
            continue;
        if (ids == 0)
            return 0;

        FastVecSub(vec, obj->position, entity->position);
        turn = D_L11_001B1D9C * 0.017453294f;
        angle = mat_fast_helper_a(entity->position[0] - obj->position[0],
                              entity->position[1] - obj->position[1]);
        math_apply_axis_rotation_to_quat(vec, vec, obj->axis,
                      fast_subtract_rotations(obj->heading, angle) >= 0.0f ? -turn : turn);
        FastVecAdd(vec, vec, entity->position);

        savedTurnRate = state->turnRate;
        state->turnRate = 0.0001f;
        joba_fighter_walk_dust(obj, vec);
        state->turnRate = savedTurnRate;
        return 1;
    }
    return 0;
}
