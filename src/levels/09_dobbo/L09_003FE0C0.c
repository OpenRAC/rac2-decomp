#include "common.h"

extern int func_00283DB8(void *, float);
extern float func_00282E80(void *, void *);
extern void func_00282CF0(float *, const float *, const float *);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern int func_00277F48(void *, int, void *, void *, float);
extern void func_0029FC20(char *, int, void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L09_003FD7D0(void *);
extern unsigned char *D_L09_001C3EC0[];

/* Unit of its own for -fno-gcse: with gcse, cprop carries the copy's destination into the
   ray call's argument and keeps it in a saved register (548 bytes).

   When the object is within twice its 0x32 range of the sub-object's 0x140 point: refreshes
   the sub-object's 0x340 block, aims its 0x278/0x3DC and 0x274/0x3E0 angles along the
   0x370 to 0x390 direction, copies 0x390 to 0x330, optionally registers func_L09_003FD7D0
   when the 1.4 * 0x434 sphere test hits, and records in 0x3AC/0x44C the last hit whose
   type is 0xCB, 0x76C or 0xEB0. Returns whether it was in range. */
int func_L09_003FE0C0(unsigned char *moby, int registerOverlay) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float vec[8] __attribute__((aligned(16)));
    int done = 0;
    int count;
    int i;
    unsigned char *hit;

    if (vec_distance_xy(moby + 0x10, vars + 0x140) <
        (float)*(short *)(moby + 0x32) * 2.0f) {
        unsigned char *targetPoint;
        unsigned char *hitPoint;
        float yaw;
        float pitch;
        float angle;

        TransformMobyJointPoint((char *)moby, 1, vars + 0x340);
        done = 1;
        targetPoint = vars + 0x390;
        FastVecSub(vec, (float *)targetPoint, (float *)(vars + 0x370));
        yaw = FastMatrixHelperA(vec[0], vec[1]);
        pitch = -FastMatrixHelperA(vec_length_xy(vec), vec[2]);
        angle = fast_subtract_rotations(yaw, *(float *)(moby + 0xF8));
        *(float *)(vars + 0x278) = angle;
        *(float *)(vars + 0x3DC) = angle;
        angle = fast_subtract_rotations(pitch, *(float *)(moby + 0xF4));
        *(float *)(vars + 0x274) = angle;
        *(float *)(vars + 0x3E0) = angle;
        qcopy(vars + 0x330, targetPoint);
        hitPoint = vars + 0x330;
        if (registerOverlay != 0) {
            qcopy(vec + 4, hitPoint);
            vec[7] = *(float *)(vars + 0x434) * 1.4f;
            if (FastMathHelperA(vec + 4, (float)*(short *)(moby + 0x32)) != -1) {
                AddDrawCallbackToList3(DrawGroundTargetMarker, moby);
            }
        }
        count = ProcessCollisionHit(hitPoint, 0, 0, 0, *(float *)(vars + 0x434) * 0.9f);
        if (count > 0) {
            for (i = 0; i < count; i++) {
                if (D_L09_001C3EC0[i] != 0) {
                    if (*(short *)(D_L09_001C3EC0[i] + 0xAA) == 0xCB /* Decoy */ ||
                        *(short *)(D_L09_001C3EC0[i] + 0xAA) == 0x76C /* moby class 1900 */ ||
                        *(short *)(D_L09_001C3EC0[i] + 0xAA) == 0xEB0 /* Dark Sheep */) {
                        hit = D_L09_001C3EC0[i];
                        *(unsigned char **)(vars + 0x3AC) = hit;
                        *(int *)(vars + 0x44C) = *(short *)(hit + 0xAA);
                    }
                }
            }
        }
        if (registerOverlay != 0) {
            *(int *)(vars + 0x42C) |= 2;
        }
    }
    return done;
}
