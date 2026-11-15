#include "include_asm.h"
#include "common.h"

typedef int TI __attribute__((mode(TI)));

extern int D_001B53A0[];

extern TI hero_copy_vector_to_out(int, TI *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern float FastVecLength(void *);
extern float math_fast_angle_helper(float);

/* Works out how far, as a signed angle, a point in front of the camera is turned away from the object. */
float cam_compute_signed_angle_to_point(u8 *moby, float distance) {
    float base[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float toPoint[4] __attribute__((aligned(16)));
    float projected[4] __attribute__((aligned(16)));
    int *camera = D_001B53A0;
    float alongDot;
    float sideDot;
    float length;
    float angle;

    hero_copy_vector_to_out((int)moby, (TI *)base);
    FastVecScale(offset, camera + 8, distance);
    FastVecAdd(offset, offset, base);
    FastVecSub(toPoint, offset, moby + 0x30);
    alongDot = FastVecDot(toPoint, moby + 0x10);
    FastVecScale(projected, moby + 0x10, alongDot);
    FastVecSub(toPoint, toPoint, projected);
    sideDot = FastVecDot(toPoint, moby);
    length = FastVecLength(toPoint);
    if (length == 0.0f) {
        return 0.0f;
    }
    angle = 1.5707964f - math_fast_angle_helper(sideDot / length);
    if (FastVecDot(toPoint, moby + 0x20) < 0.0f) {
        angle = -angle;
    }
    return angle;
}
