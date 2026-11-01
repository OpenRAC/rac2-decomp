#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    u8 reserved00[0x10];
    float position[4];
} EntityPositionPrefix;
typedef struct {
    u8 pad00[0x134];
    float f134;
    u8 pad138[0x2C0 - 0x138];
    s32 group;           
} AimState;
typedef struct {
    u8 pad00[0x10];
    float position[4];   
    u8 pad20[0xE0 - 0x20];
    u8 orientation[0x18];    
    float heading;       
} AimObject;
extern u16 *D_L11_001FC420[];
extern u8 *D_L11_001B359C[] __attribute__((sda));
extern s32 D_L11_001B35B8 __attribute__((sda));
extern float D_L11_001B1D28 __attribute__((sda));
extern float D_L11_001B1D2C __attribute__((sda));
extern float D_L11_001B1D30 __attribute__((sda));
extern int func_00283DB8(void *v, float r);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00283BE0(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern int func_PAL_L01_00323068(void *, void *);
extern int func_L02_003D7300(void *);

s32 func_PAL_L11_00458CB0(AimObject *obj)
{
    AimState *state = *(AimState **)((u8 *)obj + 0x68);
    float copy[4];
    float vec[4];
    u16 *p;
    EntityPositionPrefix *e;
    float saved;
    float a;
    float b;

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
    for (p = D_L11_001FC420[state->group];
         (state->group & 0xFF) != 0xFF && state->group <= D_L11_001B35B8 && p != 0 &&
         ((p != 0 && (s16)p[-1] >= 0) || p == D_L11_001FC420[state->group]);
         p++) {
        e = (EntityPositionPrefix *)(D_L11_001B359C[0] + ((*p & 0x7FFF) << 8));
        if (e == 0)
            return 0;
        if (!func_L02_003D7300(e))
            continue;
        if (!(func_00282E80(obj->position, e->position) < D_L11_001B1D28))
            continue;
        a = func_00283248(e->position[0] - obj->position[0], e->position[1] - obj->position[1]);
        if (!(func_00283C80(obj->heading, a) < D_L11_001B1D2C * 0.017453294f))
            continue;
        if (p == 0)
            return 0;
        func_00282CF0(vec, obj->position, e->position);
        b = D_L11_001B1D30 * 0.017453294f;
        a = func_00283248(e->position[0] - obj->position[0], e->position[1] - obj->position[1]);
        func_002ACEC0(vec, vec, obj->orientation,
                      func_00283BE0(obj->heading, a) >= 0.0f ? -b : b);
        func_00282CC0(vec, vec, e->position);
        saved = state->f134;
        state->f134 = 0.0001f;
        func_PAL_L01_00323068(obj, vec);
        state->f134 = saved;
        return 1;
    }
    return 0;
}
