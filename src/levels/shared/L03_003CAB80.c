#include "common.h"

extern void func_L03_003CAAF0(u8 *, void *, void *);
extern s32 func_L03_00419BD8(u32, u8 *, u8 *);
extern s32 func_L03_00419C58(u32, void *);
extern f32 func_00282E80(void *, void *);
extern f32 func_002A89A8(void *, s32, f32);
extern u8 D_00189EA0[];

/* Picks one of two candidate points near the object's route and writes it to output, raised a little off the ground. */
void func_L03_003CAB80(u8 *object, void *unused, f32 *output)
{
    f32 first[4] __attribute__((aligned(16)));
    f32 second[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(object + 0x68);
    s32 region;
    f32 distance;
    ComputeOppositePoints(object, first, second);
    if (CheckPointsOnRouteGraph(*(u32 *)(vars + 0x64), (u8 *)first, gHeroPosition) != 0) {
        qcopy(output, first);
    } else if (CheckPointsOnRouteGraph(*(u32 *)(vars + 0x64), (u8 *)second, gHeroPosition) != 0) {
        qcopy(output, second);
    } else {
        region = FindRouteNodeIndex(*(u32 *)(vars + 0x64), first);
        if (region != -1) {
            qcopy(output, first);
        } else if (FindRouteNodeIndex(*(u32 *)(vars + 0x64), second) != region) {
            qcopy(output, second);
        } else {
            distance = vec_distance_xy(gHeroPosition, first);
            if (distance < vec_distance_xy(gHeroPosition, second))
                qcopy(output, first);
            else
                qcopy(output, second);
        }
    }
    output[2] += 0.5f;
    output[2] = ProbeGroundHeightBelow(output, 0, 0.5f);
}
