#include "include_asm.h"

#include "common.h"
extern float D_L20_001B2168 __attribute__((sda));
extern float D_L20_001B216C __attribute__((sda));
extern float D_L20_001B2170 __attribute__((sda));
extern void *CreateMoby(int);
extern void moby_init_child_from_parent(char *, char *);
extern void euler_rotation_basis(char *, char *);
extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecCross(char *, char *, char *);
extern float math_fast_sin_or_cos_b(float);
extern void vec_set_direction_with_complement(float *, float *, float);
extern float weapon_compute_shot_launch_speed(char *, char *, float *, float, float);
extern int FloatToInt(float);
extern void tumbling_debris_update(char *);

char *func_PAL_L20_004491F0(char *arg0, int arg1, char *arg2) {
    char *obj = (char *)CreateMoby(arg1);
    char *state;
    char *p;
    float f20;
    float f21;
    float local;
    unsigned short flags;

    if (obj != 0) {
        moby_init_child_from_parent(obj, arg0);
        qcopy(obj + 0xF0, arg0 + 0xF0);
        euler_rotation_basis(obj + 0xC0, obj + 0xF0);
        flags = *(unsigned short *)(obj + 0x34);
        flags |= 0x100;
        flags &= 0xEFDF;
        state = *(char **)(obj + 0x68);
        f20 = D_L20_001B2168 * 0.020000001f;
        f21 = D_L20_001B216C * 0.00040000002f;
        p = state + 0x10;
        *(unsigned short *)(obj + 0x34) = flags;
        local = 0.0f;
        FastVecSub(state, arg2, obj + 0x10);
        *(float *)(state + 8) = 0.0f;
        vec_scale_to_length(state, state, f20);
        FastVecCross(p, state, obj + 0xE0);
        vec_set_direction_with_complement((float *)p, (float *)p, math_fast_sin_or_cos_b(D_L20_001B2170 * 0.0003490659f));
        *(float *)(state + 8) = weapon_compute_shot_launch_speed(obj + 0x10, arg2, &local, f20, -f21);
        *(float *)(state + 0x20) = f21;
        *(int *)(state + 0x24) = FloatToInt(local);
        *(void (**)(char *))(obj + 0x64) = tumbling_debris_update;
    }
    return obj;
}
