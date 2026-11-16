#include "common.h"

extern unsigned char *g_hero_l05_moby;
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);

/* When the camera is in the right mode, puts it at the given spot and turns it to look at the target. */
void ship_point_camera_at_target(void *target, void *position)
{
    unsigned char *camera = g_hero_l05_moby;
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
