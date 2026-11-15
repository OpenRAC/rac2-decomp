#include "names.h"
/* Moves an object using its controller; vector fields cover complete quadwords.
 * The two volatile reads at controller +0x90 reproduce distinct retail accesses.
 * AAA00 returns float even though this caller ignores it. Its declaration keeps
 * the observed EE argument banks; native ports must use a consistent interface.
 */

/* The object (a0) and its controller state (a1); only the fields this function reads or writes. */
typedef struct {
    char pad0[0x10];
    float pos[4];                       /* 0x10 */
    char pad1[0xF8 - 0x20];
    float heading;                      /* 0xF8 */
} Self_002B52A0;

typedef struct {
    char pad0[0x14];
    float f14, f18, f1C, f20, f24, f28, f2C, f30, f34;      /* 0x14 .. 0x34 */
    unsigned flags38;                   /* 0x38 */
    char pad1[0x50 - 0x3C];
    float v50[4];                       /* 0x50 */
    float f60, f64;                     /* 0x60 */
    char pad3[0x80 - 0x68];
    int w80;                            /* 0x80 */
    char pad4[0x90 - 0x84];
    volatile float f90; /* Retail reads this field for the comparison and reloads it for the final damping call. */
    unsigned flags94;                   /* 0x94 */
    char pad5[0x9C - 0x98];
    int flags9C;                        /* 0x9C */
    float vel[4];                       /* 0xA0 */
    float speed;                        /* 0xB0 */
    float fB4;                          /* 0xB4 */
    char pad7[0xC0 - 0xB8];
    short hC0, hC2;                     /* 0xC0 */
    char pad8[0xCC - 0xC4];
    float fCC;                          /* 0xCC */
} Ctl_002B52A0;

extern float D_001AA108 __attribute__((sda));

/* The float argument is the second declared parameter: that order fixes the instruction order of the call setup. */
extern float func_002AAA00(void *, float, void *, int, float, float, float);
extern float func_00283C80(float, float);
extern void func_00282C88(void *);
extern float func_00282E80(void *, void *);
extern float func_00282C10(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_002AC9F8(void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E20(void *);
extern void func_002AAC80(void *, float, float, float, float);

/* Works out the speed of an object from its controller: it speeds up toward the target or slows down, and rises or falls with gravity. */
void func_002B52A0(Self_002B52A0 *self, Ctl_002B52A0 *ctl, void *target, float x)
{
    float local[4] __attribute__((aligned(16)));
    float local2[4] __attribute__((aligned(16)));
    float h, scale, dist, dot, len, len2, diff, g90;

    if (!(ctl->flags38 & 0x10))
        ApproachTargetWithDirectionMode(&self->heading, x, &ctl->fB4, 0, ctl->f14, ctl->f18, ctl->f1C);
    h = FastDiffRots(self->heading, x);
    if (!(ctl->flags38 & 0x10) && ctl->f30 < h) {
        ClearVector128(local);
        if (h - ctl->f30 > ctl->fB4 * 30.0f)
            ctl->flags9C |= 2;
    } else {
        ctl->flags9C &= ~2;
        dist = vec_distance_xy(self->pos, target);
        ctl->fCC = dist;
        if (dist <= ctl->f34) {
            ClearVector128(local);
        } else {
            scale = square_root(2.0f * (dist - ctl->f34) * ctl->f24);
            if (ctl->f28 < scale)
                scale = ctl->f28;
            h = x;
            if (ctl->w80 != 0) {
                x = FastAddRotations(FastMatrixHelperA(ctl->f60 - self->pos[0], ctl->f64 - self->pos[1]), 3.14159f);
                h = fast_subtract_rotations(h, x);
                if (D_001AA108 < h)
                    h = D_001AA108;
                else if (h < -D_001AA108)
                    h = -D_001AA108;
                h = FastAddRotations(h, x);
            }
            local[0] = FastSinOrCosA(h) * scale;
            local[1] = FastSinOrCosB(h) * scale;
            local[2] = 0;
        }
    }
    FastVecSub(local2, local, ctl->vel);
    local2[2] = 0;
    dot = FastVecDot(local, ctl->vel);
    if (0.0f < dot)
        ClampVectorLength(local2, ctl->f20);
    else
        ClampVectorLength(local2, ctl->f24);
    FastVecAdd(ctl->vel, ctl->vel, local2);
    len = vec_length_xy(ctl->vel);
    ctl->speed = len;
    if (ctl->flags38 & 4)
        return;
    g90 = ctl->f90;
    if (g90 < self->pos[2]) {
        if (ctl->hC2 < 2) {
            if (self->pos[2] - g90 < 0.15f) {
                len2 = vec_length_xy(ctl->v50);
                if (0.087266475f < FastMatrixHelperA(ctl->v50[2], len2)) {
                    if (-FastVecDot(ctl->vel, ctl->v50) < ctl->vel[2])
                        ctl->vel[2] = -FastVecDot(ctl->vel, ctl->v50);
                }
            }
        }
        ctl->vel[2] = ctl->vel[2] - ctl->f2C;
        if (ctl->hC0 == 0)
            ctl->flags94 |= 0x20;
    } else {
        diff = g90 - self->pos[2];
        if (diff < ctl->vel[2])
            ctl->vel[2] = diff;
        else if (ctl->vel[2] < 0.0f)
            ctl->vel[2] = 0.0f;
        ApproachTargetWithBraking(&ctl->vel[2], ctl->f90 - self->pos[2], 0.011111111f, 0.011111111f, 1.0f);
    }
}
