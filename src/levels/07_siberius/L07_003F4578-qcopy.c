#include "include_asm.h"
#include "common.h"

/* The grouped quadword copy: the R5900 lq/sq pair with both addresses in registers. */
typedef int TI128 __attribute__((mode(TI)));

extern void func_00282CC0(u8 *a, u8 *b, u8 *c);

extern void func_00282CF0(u8 *a, u8 *b, u8 *c);

extern f32 func_00282DF0(void *a);

extern void func_00282F20(void *dst, void *src, f32 scale);

extern s32 func_002761F8(void *a, void *b, s32 c, void *d, s32 e);

extern void func_L07_003F8898(u8 *a, void *b);

extern u8 *func_L07_003F4B08(u8 *a0, u8 *a1, void *a2, void *a3, f32 a4);

extern void func_002E5CF8(s32 a, s32 b, u8 *c);

extern void func_0029FCC0(u8 *a, s32 b, void *c);

extern TI128 D_L07_001BF660;

/* The tool's own spin: the shared vector, the two sampled ones, then the shared pass. */
/* Fires a beam from the boss toward its target: works out the line, stops it at the first thing in the way, and spawns the beam object. */
void func_L07_003F8AB0(u8 *moby)
{
    TI128 beamPoints[3];
    u8 *vars;
    f32 distance;

    vars = *(u8 **)(moby + 0x68);
    PlayMobySound(1, 0, moby);
    TransformMobyJointToWorld(moby, 0, &beamPoints[0]);
    GetPositionRelativeToParent(moby, &beamPoints[2]);
    FastVecSub(&beamPoints[1], &beamPoints[2], &beamPoints[0]);
    distance = FastVecLength(&beamPoints[1]);
    vec_scale_to_length(&beamPoints[1], &beamPoints[1], distance + 2.0f);
    FastVecAdd(&beamPoints[1], &beamPoints[1], &beamPoints[0]);
    if (CollLine(&beamPoints[0], &beamPoints[1], 2, moby, 0) != 0) {
        beamPoints[1] = D_L07_001BF660;
    }
    SpawnBeamMoby(moby, *(s32 *)(vars + 0x418), &beamPoints[0], &beamPoints[1], (f32)*(u8 *)(vars + 0x34));
}
