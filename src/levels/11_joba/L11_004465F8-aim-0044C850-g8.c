#include "common.h"

/* Aims the object at the first entity of its target group that is in range and inside its
 * view cone and hands a turned aim point to func_L01_00321178. Returns 1 if one was found.
 *
 * The unit needs -frac2-zero-ti-por (the por/sq clear of the vector at 0($sp)) and
 * -frac2-keep-block-order. The list-pointer guard before the aim code is deleted by the
 * null-pointer-check pass (p was just dereferenced); without the block merge it leaves the CSE
 * block boundary that keeps the second saved copy of the target position and the 0x80 frame. */

typedef int TI128 __attribute__((mode(TI)));

/* Observed prefix only; entity indexing uses the 0x100-byte stride. */
typedef struct {
    u8 reserved00[0x10];
    float position[4];
} EntityPositionPrefix;

typedef struct {
    u8 pad00[0x134];
    float f134;
    u8 pad138[0x4C0 - 0x138];
    s32 group;          /* +0x4C0: index of the target id list */
} AimState;

typedef struct {
    u8 pad00[0x10];
    float position[4];  /* +0x10 */
    u8 pad20[0xE0 - 0x20];
    u8 orientation[0x18];   /* +0xE0 */
    float heading;      /* +0xF8 */
} AimObject;

/* Encoded id lists, the entity pool pointer (read absolutely) and the group count. */
extern u16 *g_group_id_lists[];
extern u8 *g_moby_l11_table[] __attribute__((sda));
extern s32 D_L11_001B35B8 __attribute__((sda));

/* the three float tuning words of this variant (range, cone and turn angles in degrees) */
extern float D_L11_001B1C58 __attribute__((sda));
extern float D_L11_001B1C5C __attribute__((sda));
extern float D_L11_001B1C60 __attribute__((sda));

extern int math_fast_helper_a(void *v, float r);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern int moby_l01_turn_toward_target(void *, void *);
extern int moby_get_busy_flag(void *);

/* Finds a nearby target in front of the object and aims at it; returns 1 if one was found. */
s32 enemy_aim_at_group_entity_in_cone_b(AimObject *obj)
{
    AimState *state = *(AimState **)((u8 *)obj + 0x68);
    float posCopy[4];
    float aimPoint[4];
    u16 *idPtr;
    EntityPositionPrefix *entity;
    float savedValue;
    float angleToEntity;
    float turnAngle;

    *(TI128 *)aimPoint = 0;
    aimPoint[0] = obj->position[0];
    aimPoint[1] = obj->position[1];
    aimPoint[2] = obj->position[2];
    aimPoint[3] = 2.0f;
    *(TI128 *)posCopy = *(TI128 *)aimPoint;
    if (math_fast_helper_a(posCopy, 128.0f) <= 0)
        return 0;
    if (state->group == -1)
        return 0;
    for (idPtr = g_group_id_lists[state->group];
         (state->group & 0xFF) != 0xFF && state->group <= D_L11_001B35B8 && idPtr != 0 &&
         ((idPtr != 0 && (s16)idPtr[-1] >= 0) || idPtr == g_group_id_lists[state->group]);
         idPtr++) {
        entity = (EntityPositionPrefix *)(g_moby_l11_table[0] + ((*idPtr & 0x7FFF) << 8));
        if (entity == 0)
            return 0;
        if (!moby_get_busy_flag(entity))
            continue;
        if (!(vec_distance_xy(obj->position, entity->position) < D_L11_001B1C58))
            continue;
        angleToEntity = mat_fast_helper_a(entity->position[0] - obj->position[0], entity->position[1] - obj->position[1]);
        if (!(FastDiffRots(obj->heading, angleToEntity) < D_L11_001B1C5C * 0.017453294f))
            continue;
        if (idPtr == 0)
            return 0;
        FastVecSub(aimPoint, obj->position, entity->position);
        turnAngle = D_L11_001B1C60 * 0.017453294f;
        angleToEntity = mat_fast_helper_a(entity->position[0] - obj->position[0], entity->position[1] - obj->position[1]);
        math_apply_axis_rotation_to_quat(aimPoint, aimPoint, obj->orientation,
                      fast_subtract_rotations(obj->heading, angleToEntity) >= 0.0f ? -turnAngle : turnAngle);
        FastVecAdd(aimPoint, aimPoint, entity->position);
        savedValue = state->f134;
        state->f134 = 0.0001f;
        moby_l01_turn_toward_target(obj, aimPoint);
        state->f134 = savedValue;
        return 1;
    }
    return 0;
}
