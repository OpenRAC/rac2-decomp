#include "include_asm.h"
#include "common.h"

/* func_L00_003DE950 needs -g (the division keeps its line label, retail's nop
   pair) on top of the -G8 small data, so it has a unit of its own. */

/* Retail copies the probe order {0, 4, 1, 7, 3, 5, 2, 6} to its stack. */
typedef struct { int index[8]; } GroundProbeOrder;
extern const GroundProbeOrder D_L00_001B0478;

extern float D_L00_00247800[8][4];
extern float D_L00_00247880[8][4];
extern float D_L00_001B2B30[4] __attribute__((sda));
extern float D_L00_001BF220[4];
extern float D_L00_001BF240[4] __attribute__((sda));
extern int D_L00_001B2B44;
extern float D_L00_001B0448 __attribute__((sda));
extern float D_L00_001B0474 __attribute__((sda));
extern float D_L00_001B0470 __attribute__((sda));
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern int func_00300540(int);
extern int func_00282C30(int);
extern float func_00283CE0(int);
extern float func_00283198(float), func_00283180(float);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);

/* Casts the eight ground probes in a fixed order. A hit on a surface that
   func_00300540 accepts sets states 9/10 instead; otherwise the hit point
   (D_L00_001BF220) is kept when its normal (D_L00_001BF240) passes the slope test
   or D_L00_001B2B44 is set. Then turns the orientation matrix (+0xC0) so its
   third row (+0xE0) follows the mean normal of the kept points and eases
   the position (+0x10) toward their centre along D_L00_001B2B30. Without any
   hit it sets state 4 and a velocity along the first row. */
void func_L00_003DE950(char *object)
{
    float (*probes)[4] = D_L00_00247800;
    float edges[8][4];
    float offset[4], center[4], normal[4];
    char *state = *(char **)(object + 0x68);
    GroundProbeOrder order = D_L00_001B0478;
    float a[4], b[4], c[4], axis[4], matrix[12];
    float target[4];
    int count, hit, i;
    float (*points)[4];
    float (*out)[4];
    float inv, angle;
    char *vehicle = object;

    func_00282C88(center);
    hit = 0;
    func_00282C88(normal);
    vec_scale_to_length(offset, D_L00_001B2B30, D_L00_001B0448 + D_L00_001B0448);
    points = D_L00_00247880;
    out = points;
    count = 0;
    for (i = 0; i < 8; i++) {
        float *probe = probes[order.index[i]];
        FastVecAdd(a, probe, offset);
        if (CollLine(probe, a, 18, object, 0)) {
            hit = 1;
            if (func_00300540(GetCollHitMaterial())) {
                object[0x20] = 9;
                *(int *)(state + 0x20) = 10;
                continue;
            }
            FastVecScale(b, D_L00_001BF240, 0.0009765625f);
            vec_scale_to_length(b, b, 1.0f);
            vec_scale_to_length(c, D_L00_001B2B30, -1.0f);
            if (subtract_integer_with_clamp(FastVecDot(b, c) > 0.5f) || D_L00_001B2B44) {
                qcopy(out, D_L00_001BF220);
                ++out;
                FastVecAdd(center, center, D_L00_001BF220);
                ++count;
            }
        }
    }

    /* The settling step reads its inputs through local copies. GCSE copy
       propagation goes one copy deep per pass, so PRE still sees moby's
       offsets based on vehicle, and the copies set the size of PRE's hash
       table; together they give the order of the registers PRE creates, which
       is the order of the six spill slots at 0x158..0x16C. */
    {
        char *moby = vehicle;
        char *vars = state;
        float (*hits)[4] = points;
        int grounded = hit;

        if (count) {
            inv = 1.0f / IntToFloat(count);
            for (i = 0; i < count; ++i) {
                FastVecSub(a, hits[i], moby + 0x10);
                FastVecSub(b, hits[i + 1 == count ? 0 : i + 1], moby + 0x10);
                vec_scale_to_length(a, a, 1.0f);
                vec_scale_to_length(b, b, 1.0f);
                FastVecCross(edges[i], b, a);
                vec_scale_to_length(edges[i], edges[i], 1.0f);
                FastVecAdd(normal, normal, edges[i]);
            }
            FastVecScale(normal, normal, inv);
            vec_scale_to_length(a, normal, 1.0f);
            vec_scale_to_length(c, moby + 0xE0, 1.0f);
            vec_scale_to_length(b, a, 1.0f);
            FastVecCross(axis, c, b);
            angle = FastVecDot(c, b) * (D_L00_001B0474 * 0.5f);
            FastVecScale(b, axis, func_00283198(angle));
            b[3] = func_00283180(angle);
            quaternion_to_rotation_basis(b, matrix);
            multiply_matrix3x3(moby + 0xC0, matrix, moby + 0xC0);
            FastVecScale(center, center, inv);
            FastVecSub(target, center, moby + 0x10);
            FastVecScale(target, D_L00_001B2B30, FastVecDot(target, D_L00_001B2B30));
            FastVecAdd(target, target, moby + 0x10);
            lerp_vector(moby + 0x10, moby + 0x10, target, D_L00_001B0470);
        }
        vec_scale_to_length(a, moby + 0xE0, 0.15f);
        FastVecAdd(a, moby + 0x10, a);
        if (!grounded) {
            moby[0x20] = 4;
            vec_scale_to_length(vars, moby + 0xC0, *(float *)(vars + 0x18));
        }
    }
}
