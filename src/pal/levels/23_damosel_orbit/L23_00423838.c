#include "include_asm.h"



#include "common.h"
extern void cam_compute_view_direction(void *, void *, int);
extern char *CreateMoby(int);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecCross(float *, float *, float *);
extern void FastVecCross(float *, float *, float *);
extern void vec_scale_to_length(float *, float *, float);

/* func_L23_0041E5B0 is defined in its dedicated source unit. */

char *func_PAL_L23_00427920(char *pos, char *dir, float *damage) {
    char axis[16];
    char scaled[16];
    char *obj;
    char *state;
    cam_compute_view_direction(pos, axis, 1);
    obj = CreateMoby(0x118E);
    if (obj) {
        state = *(char **)(obj + 0x68);
        *(float *)(state + 0x1C) = *damage;
        *(int *)(state + 0x10) = 0x32;
        *(u8 *)(obj + 0x30) = 0xFF;
        *(u16 *)(obj + 0x32) = 0xFF;
        *(u8 *)(obj + 0x20) = 0;
        qcopy(obj + 0x10, pos);
        qcopy(state, dir);
        *(int *)(state + 0x18) = 0;
        *(int *)(state + 0x14) = 0;
        vec_scale_to_length((float *)scaled, (float *)dir, 1.0f);
        qcopy(obj + 0xC0, scaled);
        FastVecCross((float *)(obj + 0xD0), (float *)(obj + 0xC0), (float *)axis);
        vec_scale_to_length((float *)(obj + 0xD0), (float *)(obj + 0xD0), 1.0f);
        FastVecCross((float *)(obj + 0xE0), (float *)(obj + 0xD0), (float *)(obj + 0xC0));
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
    }
    return obj;
}


