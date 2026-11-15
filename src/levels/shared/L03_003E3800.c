#include "common.h"
extern struct { u8 pad[0x148]; f32 x, y; } D_00138180;
extern f32 D_L03_0029BBF0[][4];
extern f32 D_L03_001B9BC0[][4];
extern void func_00283098(void *, void *, void *);
extern f32 func_00282DB0(void *, void *);
extern f32 func_00283248(f32, f32);
extern f32 func_00283C80(f32, f32);
/* Reads the stick direction and picks the open node that lies closest to it; returns 1 when one was chosen. */
int func_L03_003E3800(u8 *moby) {
    f32 nodeDir[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 x = -gPadState.x;
    f32 y = -gPadState.y;
    f32 angle, best, dotX, dotY, nodeAngle, angleDiff;
    int selected, i, index;
    if (x*x + y*y < 0.9f) return 0;
    best = 1.57f;
    angle = FastMatrixHelperA(x, y);
    selected = -1;
    for (i = 0; i < 8 && vars[0x40+i] != 255; i++) {
        index = vars[0x40+i];
        matrix_mul_vec3(nodeDir, D_L03_0029BBF0[index], moby + 0xc0);
        dotX = FastVecDot(nodeDir, D_L03_001B9BC0[0]);
        dotY = FastVecDot(nodeDir, D_L03_001B9BC0[1]);
        nodeAngle = FastMatrixHelperA(dotX, dotY);
        angleDiff = FastDiffRots(nodeAngle, angle);
        if (angleDiff < best) { selected = index; best = angleDiff; }
    }
    index = *(short *)(vars+0x5c);
    if (index != *(short *)(vars+0x50)) {
        matrix_mul_vec3(nodeDir, D_L03_0029BBF0[index], moby + 0xc0);
        dotX = FastVecDot(nodeDir, D_L03_001B9BC0[0]);
        dotY = FastVecDot(nodeDir, D_L03_001B9BC0[1]);
        nodeAngle = FastMatrixHelperA(dotX, dotY);
        angleDiff = FastDiffRots(nodeAngle, angle);
        if (angleDiff < best) selected = index;
    }
    if (selected != -1) { *(short *)(vars+0x52) = selected; return 1; }
    return 0;
}

