#include "common.h"
extern char *moby_get_private_value_2(u8 *);
extern float math_fabs(float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_clamp_length(float *, float);
extern float g_moby_l03_push_scale __attribute__((sda));
extern float g_moby_push_clamp __attribute__((sda));

/* Pushes the object toward a target point by adding a scaled offset to its drift velocity. */
void moby_push_toward_target(u8 *object, void *target)
{
    float delta[4];
    u8 *state;
    u8 *attachment;
    if (object[0x20] != 4 && object[0x20] != 2)
        return;
    state = *(u8 **)(object + 0x68);
    if (*(u8 **)(state + 0x198) != 0) {
        attachment = (u8 *)moby_get_private_value_2(*(u8 **)(state + 0x198));
        if (attachment != 0 && 0.0016666668234393f < math_fabs(*(float *)(attachment + 0x18)))
            return;
    }
    FastVecSub(delta, object + 0x10, target);
    delta[2] = 0.0f;
    vec_scale_to_length(delta, delta, (g_moby_l03_push_scale + g_moby_l03_push_scale) * 0.00027777778f);
    FastVecAdd(state + 0x1B0, state + 0x1B0, delta);
    vec_clamp_length((float *)(state + 0x1B0), g_moby_push_clamp * 0.016666668f);
}
