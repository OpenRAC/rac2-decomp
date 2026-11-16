#include "include_asm.h"



#include "common.h"
extern void cam_compute_view_direction(void *, void *, int);
extern char *CreateMoby(int);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecCross(float *, float *, float *);
extern void FastVecCross(float *, float *, float *);
extern void vec_scale_to_length(float *, float *, float);

/* func_L23_0041E5B0 is defined in its dedicated source unit. */

char *directed_shot_create_pal(char *pos, char *dir, float *damage) {
    char axis[16];
    char scaled[16];
    char *shot;
    char *shot_vars;
    cam_compute_view_direction(pos, axis, 1);
    shot = CreateMoby(0x118E);
    if (shot) {
        shot_vars = *(char **)(shot + 0x68);
        *(float *)(shot_vars + 0x1C) = *damage;
        *(int *)(shot_vars + 0x10) = 0x32;
        *(u8 *)(shot + 0x30) = 0xFF;
        *(u16 *)(shot + 0x32) = 0xFF;
        *(u8 *)(shot + 0x20) = 0;
        qcopy(shot + 0x10, pos);
        qcopy(shot_vars, dir);
        *(int *)(shot_vars + 0x18) = 0;
        *(int *)(shot_vars + 0x14) = 0;
        vec_scale_to_length((float *)scaled, (float *)dir, 1.0f);
        qcopy(shot + 0xC0, scaled);
        FastVecCross((float *)(shot + 0xD0), (float *)(shot + 0xC0), (float *)axis);
        vec_scale_to_length((float *)(shot + 0xD0), (float *)(shot + 0xD0), 1.0f);
        FastVecCross((float *)(shot + 0xE0), (float *)(shot + 0xD0), (float *)(shot + 0xC0));
        *(float *)(shot + 0xCC) = *(float *)(shot + 0xDC) = *(float *)(shot + 0xEC) = 0.0f;
    }
    return shot;
}


