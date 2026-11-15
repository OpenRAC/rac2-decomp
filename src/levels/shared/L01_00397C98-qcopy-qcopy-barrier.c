#include "names.h"

typedef unsigned int Quadword __attribute__((mode(TI)));
typedef union { Quadword whole; float f[4]; } Vector;
extern float moby_get_anim_value(char *);
extern float FastAddRotations(float, float), fast_subtract_rotations(float, float);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *), vec_clear_128(void *);
extern void lerp_vector(void *, void *, void *, float);
extern void object_copy_vector_to_selected(void *), cam_set_state_rotation(void *);
extern char *D_L01_001B264C __attribute__((sda));
extern struct { unsigned char prefix[0x80]; Vector position; unsigned char unused90[8]; float heading; } g_hero_state;

/* Blend the configured cameras, or orbit the player when either endpoint is absent. */
/* Same body as func_L01_00416E78, with this function's own callees. */
void cam_blend_moby_update(char *object)
{
    int *state = *(int **)(object + 0x68);
    Vector position, rotation, first, second;
    float weight, heading, value;
    if (*(unsigned char *)(object + 0x42) == 1)
        value = moby_get_anim_value(object);
    else
        value = 170.0f;
    weight = value * 0.0058823530562222003937f;
    if (state[1] == -1 || state[2] == -1) {
        heading = FastAddRotations(weight * 0.69813179969787597656f - 0.34906589984893798828f, g_hero_state.heading);
        position.f[0] = math_fast_sin_or_cos_a(heading) * 5.0f;
        position.f[1] = math_fast_sin_or_cos_b(heading) * 5.0f;
        position.f[2] = 0;
        FastVecAdd(&position, &position, &g_hero_state.position);
        position.f[2] += 1.0f;
        vec_clear_128(&rotation);
        rotation.f[2] = FastAddRotations(heading, 3.141590118408203125f);
        rotation.f[1] = weight * -0.17000000178813934326f;
    } else {
        lerp_vector(&position, D_L01_001B264C + state[1] * 0x80 + 0x30, D_L01_001B264C + state[2] * 0x80 + 0x30, weight);
        first.whole = ((Vector *)(D_L01_001B264C + state[1] * 0x80 + 0x70))->whole;
        second.whole = ((Vector *)(D_L01_001B264C + state[2] * 0x80 + 0x70))->whole;
        rotation.f[2] = FastAddRotations(fast_subtract_rotations(second.f[2], first.f[2]) * weight, first.f[2]);
        rotation.f[1] = FastAddRotations(fast_subtract_rotations(second.f[1], first.f[1]) * weight, first.f[1]);
        rotation.f[0] = FastAddRotations(fast_subtract_rotations(second.f[0], first.f[0]) * weight, first.f[0]);
    }
    object_copy_vector_to_selected(&position);
    cam_set_state_rotation(&rotation);
}
