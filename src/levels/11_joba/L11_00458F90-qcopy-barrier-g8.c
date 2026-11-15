#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));
extern void *func_0029EFD0(int);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern void func_L02_004224C8(u8 *);
extern char D_0018A0E0[];
extern float D_L11_001B1FD0 __attribute__((sda));
extern float D_L11_001B1FD8 __attribute__((sda));
extern float D_L11_001B1FDC __attribute__((sda));

/* Same body as func_L02_004216F0, minus the final call; this level's own data. */
u8 *func_L11_00458F90(u8 *position, int owner, u8 *direction, float speed) {
    u8 *moby = CreateMoby(0xE2D /* moby class 3629 */);
    u8 *vars;
    int frameCount;
    float frameTime;

    if (moby != 0) {
        *(u8 *)(moby + 0x20) = 0;
        *(u8 *)(moby + 0x30) = 0xFF;
        frameTime = D_L11_001B1FD8 * 0.016666668f;
        vars = *(u8 **)(moby + 0x68);
        *(float *)(vars + 0x64) = speed;
        vec_scale_to_length(vars + 0x40, direction, frameTime);
        *(TI128 *)(moby + 0x10) = *(TI128 *)position;
        *(TI128 *)(moby + 0xC0) = *(TI128 *)(vars + 0x40);
        FastVecCross(moby + 0xD0, moby + 0xC0, D_0018A0E0);
        vec_scale_to_length(moby + 0xD0, moby + 0xD0, -1.0f);
        FastVecCross(moby + 0xE0, moby + 0xD0, moby + 0xC0);
        frameTime = D_L11_001B1FD8 * 0.016666668f;
        frameCount = FloatToInt(D_L11_001B1FDC / frameTime);
        *(int *)(vars + 0x58) = frameCount;
        *(float *)(vars + 0x5C) = 1.0f / IntToFloat(frameCount);
        *(int *)(vars + 0x50) = owner;
        *(u8 *)(moby + 0x20) = 0;
        *(float *)(vars + 0x60) = D_L11_001B1FD0;
        RebuildFrameFromTransform(moby);
    }
    return moby;
}
