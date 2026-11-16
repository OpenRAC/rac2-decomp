#include "names.h"
/* func_PAL_L02_0032D5F8, the PAL copy of func_L02_0032B468: the same C, where expr 0.016666668f becomes 0.020000001f; wrap func_002A7878(60.0f, 120.0f) (({e}) * 5.0f + 2.0f) * 0.. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vec4;
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern char *CreateMoby(int kind);
extern void euler_rotation_basis(void *, void *);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern float FastVecLength(void *);
extern void vec_random_direction(void *, float, float);
extern void FastVecScale(void *, void *, float);
extern void func_002A0F48(void *);

/* Spawns one flying fragment copied from a source object. It sets size, lifetime, speed, spin and bounds, picking random values when the caller passes zeros (PAL: 50 Hz scaling). */
char *part_spawn_flying_fragment_pal(char *source, int kind, TI128 *position, void *rotation,
                      int lifetime, int flags, TI128 *velocity, TI128 *spin,
                      TI128 *bounds, float speed) {
    Vec4 temporary;
    unsigned char *object = (unsigned char *)CreateMoby(kind);
    char *state;
    float scale, angle, radial;
    if (object) {
    scale = *(float *)(source + 0x2C) / *(float *)(*(char **)(source + 0x24) + 0x24);
    *(float *)(object + 0x2C) = *(float *)(*(char **)(object + 0x24) + 0x24) * scale;
    *(char *)(object + 0x31) = 1;
    *(unsigned short *)(object + 0x34) |= 0x100;
    state = *(char **)(object + 0x68);
    *(long long *)(object + 0x38) = *(long long *)(source + 0x38);
    object[0x20] = 1;
    qcopy(object + 0x10, position);
    euler_rotation_basis(object + 0xC0, rotation);
    object[0x30] = 0xFF;
    *(short *)(object + 0x32) = 0x80;
    *(int *)(object + 0x98) = 0;
    if (!lifetime) *(int *)(state + 0x30) = FloatToInt(((math_random_float_range(60.0f, 120.0f)) * 5.0f + 2.0f) * 0.16666667f);
    else *(int *)(state + 0x30) = lifetime;
    *(int *)(state + 0x34) = flags;
    if (*(float *)(state + 0x38) == 0.0f)
        *(float *)(state + 0x38) = math_random_float_range(10.0f, 15.0f) * 0.00040000002f;
    else *(float *)(state + 0x38) = speed;
    if (FastVecLength(velocity) == 0.0f) {
        angle = math_random_angle();
        radial = math_random_float_range(2.0f, 4.0f) * (0.020000001f);
        temporary.f[0] = math_fast_sin_or_cos_a(angle) * radial;
        temporary.f[1] = math_fast_sin_or_cos_b(angle) * radial;
        temporary.f[2] = 0.0f;
        temporary.f[2] = math_random_float_range(5.0f, 8.0f) * (0.020000001f);
        qcopy(state, &temporary);
    } else qcopy(state, velocity);
    if (FastVecLength(spin) == 0.0f) {
        vec_random_direction(&temporary, 0.062831864f, 0.12566373f);
        qcopy(state + 0x10, &temporary);
    } else qcopy(state + 0x10, spin);
    if (FastVecLength(bounds) == 0.0f && ((float *)bounds)[3] == 0.0f) {
        qcopy(&temporary, *(char **)(object + 0x24) + 0x30);
        {
            float boundsScale = *(float *)(object + 0x2C) * 0.0009765625f;
            FastVecScale(&temporary, &temporary, boundsScale);
            temporary.f[3] *= boundsScale;
        }
        qcopy(state + 0x20, &temporary);
    } else qcopy(state + 0x20, bounds);
    func_002A0F48(object);
    }
    return object;
}
