#include "include_asm.h"

#include "common.h"
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
void func_PAL_L00_003E2B68(char *object)
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
    func_00282F20(offset, D_L00_001B2B30, D_L00_001B0448 + D_L00_001B0448);
    points = D_L00_00247880;
    out = points;
    count = 0;
    for (i = 0; i < 8; i++) {
        float *probe = probes[order.index[i]];
        func_00282CC0(a, probe, offset);
        if (func_002761F8(probe, a, 18, object, 0)) {
            hit = 1;
            if (func_00300540(func_00278E78())) {
                object[0x20] = 9;
                *(int *)(state + 0x20) = 8;
                continue;
            }
            func_00282D30(b, D_L00_001BF240, 0.0009765625f);
            func_00282F20(b, b, 1.0f);
            func_00282F20(c, D_L00_001B2B30, -1.0f);
            if (func_00282C30(func_00282DB0(b, c) > 0.5f) || D_L00_001B2B44) {
                qcopy(out, D_L00_001BF220);
                ++out;
                func_00282CC0(center, center, D_L00_001BF220);
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
            inv = 1.0f / func_00283CE0(count);
            for (i = 0; i < count; ++i) {
                func_00282CF0(a, hits[i], moby + 0x10);
                func_00282CF0(b, hits[i + 1 == count ? 0 : i + 1], moby + 0x10);
                func_00282F20(a, a, 1.0f);
                func_00282F20(b, b, 1.0f);
                func_00282DD8(edges[i], b, a);
                func_00282F20(edges[i], edges[i], 1.0f);
                func_00282CC0(normal, normal, edges[i]);
            }
            func_00282D30(normal, normal, inv);
            func_00282F20(a, normal, 1.0f);
            func_00282F20(c, moby + 0xE0, 1.0f);
            func_00282F20(b, a, 1.0f);
            func_00282DD8(axis, c, b);
            angle = func_00282DB0(c, b) * (D_L00_001B0474 * 0.5f);
            func_00282D30(b, axis, func_00283198(angle));
            b[3] = func_00283180(angle);
            func_00283958(b, matrix);
            func_00283738(moby + 0xC0, matrix, moby + 0xC0);
            func_00282D30(center, center, inv);
            func_00282CF0(target, center, moby + 0x10);
            func_00282D30(target, D_L00_001B2B30, func_00282DB0(target, D_L00_001B2B30));
            func_00282CC0(target, target, moby + 0x10);
            func_00282D08(moby + 0x10, moby + 0x10, target, D_L00_001B0470);
        }
        func_00282F20(a, moby + 0xE0, 0.15f);
        func_00282CC0(a, moby + 0x10, a);
        if (!grounded) {
            moby[0x20] = 4;
            func_00282F20(vars, moby + 0xC0, *(float *)(vars + 0x18));
        }
    }
}
