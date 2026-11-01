#include "include_asm.h"

#include "common.h"
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
extern u16 *D_L11_001FC420[];
extern Entity *D_L11_001B359C[] __attribute__((sda));
extern s32 D_L11_001B35B8 __attribute__((sda));
extern float D_L11_001B1D94 __attribute__((sda));
extern float D_L11_001B1D98 __attribute__((sda));
extern float D_L11_001B1D9C __attribute__((sda));
extern int func_00283DB8(void *vec, float radius);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00283BE0(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern int func_PAL_L11_0045BC60(void *, void *);
extern int func_L02_003D7300(void *);

/* Looks for an entity of the object's group that is in range and inside its view cone, and if
   found turns the object toward it and runs the follow-up call with a tiny turn rate. */
s32 func_PAL_L11_0045C2B0(AimObject *obj)
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
    if (func_00283DB8(copy, 128.0f) <= 0)
        return 0;
    if (state->group == -1)
        return 0;

    for (ids = D_L11_001FC420[state->group];
         (state->group & 0xFF) != 0xFF && state->group <= D_L11_001B35B8 && ids != 0 &&
         ((ids != 0 && (s16)ids[-1] >= 0) || ids == D_L11_001FC420[state->group]);
         ids++) {
        entity = D_L11_001B359C[0] + (*ids & 0x7FFF);
        if (entity == 0)
            return 0;
        if (!func_L02_003D7300(entity))
            continue;
        if (!(func_00282E80(obj->position, entity->position) < D_L11_001B1D94))
            continue;

        angle = func_00283248(entity->position[0] - obj->position[0],
                              entity->position[1] - obj->position[1]);
        if (!(func_00283C80(obj->heading, angle) < D_L11_001B1D98 * 0.017453294f))
            continue;
        if (ids == 0)
            return 0;

        func_00282CF0(vec, obj->position, entity->position);
        turn = D_L11_001B1D9C * 0.017453294f;
        angle = func_00283248(entity->position[0] - obj->position[0],
                              entity->position[1] - obj->position[1]);
        func_002ACEC0(vec, vec, obj->axis,
                      func_00283BE0(obj->heading, angle) >= 0.0f ? -turn : turn);
        func_00282CC0(vec, vec, entity->position);

        savedTurnRate = state->turnRate;
        state->turnRate = 0.0001f;
        func_PAL_L11_0045BC60(obj, vec);
        state->turnRate = savedTurnRate;
        return 1;
    }
    return 0;
}
