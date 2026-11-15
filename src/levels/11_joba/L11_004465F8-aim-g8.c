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
    u8 pad138[0x35C - 0x138];
    s32 group;          /* +0x35C: index of the target id list */
} AimState;

typedef struct {
    u8 pad00[0x10];
    float position[4];  /* +0x10 */
    u8 pad20[0xE0 - 0x20];
    u8 orientation[0x18];   /* +0xE0 */
    float heading;      /* +0xF8 */
} AimObject;

/* Encoded id lists, the entity pool pointer (read absolutely) and the group count. */
extern u16 *D_L11_001FC420[];
extern u8 *D_L11_001B359C[] __attribute__((sda));
extern s32 D_L11_001B35B8 __attribute__((sda));

/* the three float tuning words of this variant (range, cone and turn angles in degrees) */
extern float D_L11_001B1BD0 __attribute__((sda));
extern float D_L11_001B1BD4 __attribute__((sda));
extern float D_L11_001B1BD8 __attribute__((sda));

extern int func_00283DB8(void *v, float r);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00283BE0(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern int func_L01_00321178(void *, void *);
extern int func_L02_003D7300(void *);

/* Finds a nearby target in front of the object and aims at it; returns 1 if one was found. */
s32 func_L11_00449C70(AimObject *obj)
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
    if (FastMathHelperA(posCopy, 128.0f) <= 0)
        return 0;
    if (state->group == -1)
        return 0;
    for (idPtr = gGroupIdLists[state->group];
         (state->group & 0xFF) != 0xFF && state->group <= D_L11_001B35B8 && idPtr != 0 &&
         ((idPtr != 0 && (s16)idPtr[-1] >= 0) || idPtr == gGroupIdLists[state->group]);
         idPtr++) {
        entity = (EntityPositionPrefix *)(gMobyTable_L11[0] + ((*idPtr & 0x7FFF) << 8));
        if (entity == 0)
            return 0;
        if (!GetMobyBusyFlag(entity))
            continue;
        if (!(vec_distance_xy(obj->position, entity->position) < D_L11_001B1BD0))
            continue;
        angleToEntity = FastMatrixHelperA(entity->position[0] - obj->position[0], entity->position[1] - obj->position[1]);
        if (!(FastDiffRots(obj->heading, angleToEntity) < D_L11_001B1BD4 * 0.017453294f))
            continue;
        if (idPtr == 0)
            return 0;
        FastVecSub(aimPoint, obj->position, entity->position);
        turnAngle = D_L11_001B1BD8 * 0.017453294f;
        angleToEntity = FastMatrixHelperA(entity->position[0] - obj->position[0], entity->position[1] - obj->position[1]);
        ApplyAxisRotationToQuaternion(aimPoint, aimPoint, obj->orientation,
                      fast_subtract_rotations(obj->heading, angleToEntity) >= 0.0f ? -turnAngle : turnAngle);
        FastVecAdd(aimPoint, aimPoint, entity->position);
        savedValue = state->f134;
        state->f134 = 0.0001f;
        TurnMobyTowardTarget(obj, aimPoint);
        state->f134 = savedValue;
        return 1;
    }
    return 0;
}
