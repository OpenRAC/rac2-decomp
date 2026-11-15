#include "common.h"
extern struct { u8 pad[0x148]; f32 x, y; } D_00138180;
extern f32 D_L03_0029BBF0[][4];
extern f32 D_L03_001B9BC0[][4];
extern void func_00283098(void *, void *, void *);
extern f32 func_00282DB0(void *, void *);
extern f32 func_00283248(f32, f32);
extern f32 func_00283C80(f32, f32);
int func_L03_003E3800(u8 *m) {
    f32 v[4] __attribute__((aligned(16)));
    u8 *p = *(u8 **)(m + 0x68);
    f32 x = -D_00138180.x;
    f32 y = -D_00138180.y;
    f32 angle, best, a, b, c, d;
    int selected, i, index;
    if (x*x + y*y < 0.9f) return 0;
    best = 1.57f;
    angle = func_00283248(x, y);
    selected = -1;
    for (i = 0; i < 8 && p[0x40+i] != 255; i++) {
        index = p[0x40+i];
        matrix_mul_vec3(v, D_L03_0029BBF0[index], m + 0xc0);
        a = FastVecDot(v, D_L03_001B9BC0[0]);
        b = FastVecDot(v, D_L03_001B9BC0[1]);
        c = func_00283248(a, b);
        d = FastDiffRots(c, angle);
        if (d < best) { selected = index; best = d; }
    }
    index = *(short *)(p+0x5c);
    if (index != *(short *)(p+0x50)) {
        matrix_mul_vec3(v, D_L03_0029BBF0[index], m + 0xc0);
        a = FastVecDot(v, D_L03_001B9BC0[0]);
        b = FastVecDot(v, D_L03_001B9BC0[1]);
        c = func_00283248(a, b);
        d = FastDiffRots(c, angle);
        if (d < best) selected = index;
    }
    if (selected != -1) { *(short *)(p+0x52) = selected; return 1; }
    return 0;
}

