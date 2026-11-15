#include "common.h"

extern unsigned char *D_L05_001B9710;
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);

/* When the camera is in the right mode, puts it at the given spot and turns it to look at the target. */
void func_L05_00445B58(void *target, void *position)
{
    unsigned char *camera = D_L05_001B9710;
    float up[4];
    if (*(short *)(camera + 0x86) == 25) {
        qcopy(camera + 0x30, position);
        FastVecSub(camera, target, camera + 0x30);
        vec_scale_to_length(camera, camera, 1.0f);
        qcopy(up, camera + 0x20);
        FastVecCross(camera + 0x10, camera, up);
        vec_scale_to_length(camera + 0x10, camera + 0x10, 1.0f);
        FastVecCross(camera + 0x20, camera + 0x10, camera);
        vec_scale_to_length(camera + 0x20, camera + 0x20, 1.0f);
        *(float *)(camera + 0x3C) = 1.0f;
        *(float *)(camera + 0xC) = *(float *)(camera + 0x1C) =
            *(float *)(camera + 0x2C) = 0.0f;
    }
}
