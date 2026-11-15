#include "common.h"

typedef struct { u8 pad00[0x86]; s16 state; } Moby_271E88;
typedef struct {
    u8 pad000[0x140];
    f32 pos[4];
    u8 pad150[0x190 - 0x150];
    Moby_271E88 *moby;
    u8 pad194[0x400 - 0x194];
    s32 grounded;
} Cam_271E88;

extern Cam_271E88 D_001B5200;
extern s32 D_001A8BB0 __attribute__((sda));
extern f32 D_001BAFA0[4];
extern s32 func_002761F8(void *, void *, s32, void *, s32);
extern int func_00278E78(void);
extern float func_002A90F8(float *, void *);

/* Probe down from the camera target for up to six hits; grounded when a floor is within reach. */
void func_00271E88(void)
{
    f32 top[4] __attribute__((aligned(16)));
    f32 bottom[4] __attribute__((aligned(16)));
    int i;

    if (D_001B5200.moby->state == 6 || D_001A8BB0 != 0) {
        D_001B5200.grounded = 0;
        return;
    }
    qcopy(top, D_001B5200.pos);
    qcopy(bottom, D_001B5200.pos);
    top[2] += 0.75f;
    bottom[2] -= 0.75f;
    for (i = 0; i < 6 && CollLine(top, bottom, 0x12, 0, 0); i++) {
        if (GetCollHitMaterial() == 0) {
            f32 h = func_002A90F8(D_001BAFA0, 0) + 0.04f;
            if (D_001B5200.pos[2] < h) {
                D_001B5200.grounded = 1;
            } else {
                D_001B5200.grounded = 0;
            }
            return;
        }
        qcopy(top, D_001BAFA0);
        top[2] -= 0.01f;
    }
}
