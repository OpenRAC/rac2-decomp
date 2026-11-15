#include "common.h"

extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, float, int, void *);
extern float D_001BAF80[], D_001BAFA0[], D_001BAFB0[];
extern float func_002A8A20(void *);
extern float func_00282C48(float);
extern float func_00282E80(void *, void *);
extern void func_001290E0(void *, void *);
extern void func_00282D30(void *, void *, float);

/* Keeps a proposed movement over ground and resolves steep walls and spheres. */
/* Keeps a proposed movement over ground and resolves steep walls and spheres. */
int func_002A7EA0(void *o, float *old, float *pos, int flags,
                  float height, float radius, float maxstep, float slope)
{
    float delta[4] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    union {
        int q __attribute__((mode(TI)));
        float f[4];
    } up __attribute__((aligned(16)));
    float probe[4] __attribute__((aligned(16)));
    float z, dot, angle, offset;
    int mask = flags & 2;
    int result = 1, i;

    pos[2] += height;
    z = GetGroundHeightUnderObject(pos);
    pos[2] -= height;
    if (maxstep < FloatAbs(z - old[2])) {
        if ((((flags ^ 1) & 1) && z < old[2]) || old[2] < z) {
            qcopy(pos, old);
            result = 0;
        }
    }
    FastVecSub(delta, pos, old);
    vec_scale_to_length(scaled, delta, radius * 1.2f);
    up.q = 0;
    up.f[2] = height;
    FastVecAdd(start, old, &up);
    FastVecAdd(end, start, scaled);
    if (result && CollLine(start, end, mask | 0x24, o, 0)) {
        float *hit = gCollisionHit;
        if (((int *)hit)[7] > 0) {
            angle = FastMatrixHelperA(hit[18], vec_length_xy(hit + 16));
            if (slope <= angle) {
                hit[18] = 0;
                func_001290E0(hit + 16, hit + 16);
                dot = (-delta[0]) * hit[16] - delta[1] * hit[17];
                if (dot > 0) {
                    FastVecScale(hit + 16, hit + 16, dot);
                    result = 0;
                    FastVecAdd(delta, delta, hit + 16);
                }
            }
            FastVecAdd(pos, old, delta);
        }
    }
    if (!(flags & 2)) {
        float *point = D_001BAFA0;
        float *hit = point - 8;
        offset = height + radius;
        i = 0;
        do {
            qcopy(probe, pos);
            probe[2] += offset;
            if (!TestPointAgainstCollision(probe, radius, 0x24, o))
                break;
            angle = FastMatrixHelperA(vec_distance_xy(pos, point), hit[10] - pos[2]);
            if (((int *)hit)[6] != 0 || slope < angle) {
                qcopy(pos, D_001BAFB0);
                pos[2] -= offset;
                result = 0;
            }
            i++;
        } while (i < 6);
    }
    pos[2] += height;
    z = GetGroundHeightUnderObject(pos);
    pos[2] -= height;
    if (maxstep < FloatAbs(z - old[2])) {
        if ((((flags ^ 1) & 1) && z < old[2]) || old[2] < z) {
            qcopy(pos, old);
            result = 0;
        }
    }
    old[0] = pos[0];
    old[1] = pos[1];
    return result;
}
