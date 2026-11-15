#include "common.h"

typedef union { u8 b[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; } Hero;

typedef struct {
    u8 pad000[0x1C8];
    f32 cam[9];
    f32 f1EC;
    u8 pad1F0[0x220 - 0x1F0];
    f32 home[4];
    u8 pad230[0x260 - 0x230];
    u8 *target;
} Vars_L07_003E5910;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 pad20[0x68 - 0x20];
    Vars_L07_003E5910 *vars;
    u8 pad6C[0xC0 - 0x6C];
    f32 rot[4];
} Moby_L07_003E5910;

extern char D_00189E20[];
extern f32 D_L07_001B0AA0 __attribute__((sda));
extern f32 D_L07_001B0AA4 __attribute__((sda));
extern f32 D_L07_001B0AA8 __attribute__((sda));
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_002A89A8(void *, int, float);
extern void func_002AAC80(void *, float, float, float, float);
extern int func_002B4FF0(void *, float *, float);

/* Follow the camera height between the moby's home and the hero, never under the floor. */
float func_L07_003E5910(Moby_L07_003E5910 *m, float *arg1, float arg2)
{
    f32 pos[4] __attribute__((aligned(16)));
    Vars_L07_003E5910 *v = m->vars;
    f32 lo, hi, h, floor;

    if (v->target != 0) {
        matrix_mul_vec3(pos, v->home, m->rot);
        FastVecAdd(pos, pos, v->target + 0x10);
    } else {
        qcopy(pos, v->home);
    }
    lo = pos[2] - 2.0f;
    hi = lo + 5.0f;
    h = ((Hero *)D_00189E20)->f[0x2D8 / 4] + D_L07_001B0AA8;
    if (hi < h) h = hi;
    else if (h < lo) h = lo;
    floor = func_002A89A8(m->pos, 0, 0.5f) + D_L07_001B0AA8;
    if (h < floor) h = floor;
    func_002AAC80(v->cam, h - m->pos[2], D_L07_001B0AA0 * 0.000277777785f, D_L07_001B0AA0 * 0.000277777785f,
                  D_L07_001B0AA4 * 0.0166666675f);
    func_002B4FF0(m, arg1, arg2);
    return v->f1EC;
}
