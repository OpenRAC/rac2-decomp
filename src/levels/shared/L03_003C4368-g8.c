#include "common.h"
extern int func_002AD0B0(u8 *);
extern float func_00282C48(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002AC9F8(float *, float);
extern float D_L03_001AFF08 __attribute__((sda));
extern float D_L03_001AFF04 __attribute__((sda));

/* Pushes the object toward a target point by adding a scaled offset to its drift velocity. */
void func_L03_003C4368(u8 *object, void *target)
{
    float delta[4];
    u8 *state;
    u8 *attachment;
    if (object[0x20] != 4 && object[0x20] != 2)
        return;
    state = *(u8 **)(object + 0x68);
    if (*(u8 **)(state + 0x198) != 0) {
        attachment = (u8 *)GetMobyPrivateValue2(*(u8 **)(state + 0x198));
        if (attachment != 0 && 0.0016666668234393f < FloatAbs(*(float *)(attachment + 0x18)))
            return;
    }
    FastVecSub(delta, object + 0x10, target);
    delta[2] = 0.0f;
    vec_scale_to_length(delta, delta, (D_L03_001AFF08 + D_L03_001AFF08) * 0.00027777778f);
    FastVecAdd(state + 0x1B0, state + 0x1B0, delta);
    ClampVectorLength((float *)(state + 0x1B0), D_L03_001AFF04 * 0.016666668f);
}
