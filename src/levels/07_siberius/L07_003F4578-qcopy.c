#include "include_asm.h"
#include "common.h"

/* The grouped quadword copy: the R5900 lq/sq pair with both addresses in registers. */
typedef int TI128 __attribute__((mode(TI)));

extern void FastVecAdd(u8 *a, u8 *b, u8 *c);

extern void FastVecSub(u8 *a, u8 *b, u8 *c);

extern f32 FastVecLength(void *a);

extern void vec_scale_to_length(void *dst, void *src, f32 scale);

extern s32 CollLine(void *a, void *b, s32 c, void *d, s32 e);

extern void moby_get_pos_rel_parent(u8 *a, void *b);

extern u8 *beam_spawn(u8 *a0, u8 *a1, void *a2, void *a3, f32 a4);

extern void PlayMobySound(s32 a, s32 b, u8 *c);

extern void moby_transform_joint_to_world(u8 *a, s32 b, void *c);

extern TI128 D_L07_001BF660;

/* The tool's own spin: the shared vector, the two sampled ones, then the shared pass. */
/* Fires a beam from the boss toward its target: works out the line, stops it at the first thing in the way, and spawns the beam object. */
void boss_fire_beam_attack(u8 *moby)
{
    TI128 beamPoints[3];
    u8 *vars;
    f32 distance;

    vars = *(u8 **)(moby + 0x68);
    PlayMobySound(1, 0, moby);
    moby_transform_joint_to_world(moby, 0, &beamPoints[0]);
    moby_get_pos_rel_parent(moby, &beamPoints[2]);
    FastVecSub(&beamPoints[1], &beamPoints[2], &beamPoints[0]);
    distance = FastVecLength(&beamPoints[1]);
    vec_scale_to_length(&beamPoints[1], &beamPoints[1], distance + 2.0f);
    FastVecAdd(&beamPoints[1], &beamPoints[1], &beamPoints[0]);
    if (CollLine(&beamPoints[0], &beamPoints[1], 2, moby, 0) != 0) {
        beamPoints[1] = D_L07_001BF660;
    }
    beam_spawn(moby, *(s32 *)(vars + 0x418), &beamPoints[0], &beamPoints[1], (f32)*(u8 *)(vars + 0x34));
}
