#include "names.h"
/* func_PAL_002C0078, the PAL copy of func_002BF390: the same C, where each D_001AA36x - 1.0f is scaled by 1.2f. */
#include "common.h"

typedef int TI __attribute__((mode(TI)));
extern s32 FastDecTimer();
extern void FastVecAdd();
extern void FastVecSub();
extern void FastVecScale(void *, void *, f32);
extern f32 fast_vec_dist();
extern void part_kill();
extern f32 g_tether_scale_a __attribute__((sda));
extern f32 g_tether_scale_b __attribute__((sda));

void part_update_tethered_pal(s32 particle) {
    s32 offset[4];
    TI target;
    s32 parent;
    u8 parent_state;
    s32 point_b;
    s32 point_a;

    parent = (*(s32 *)((s8 *)(particle) + (0x30)));
    if (parent == 0 || (parent_state = (*(u8 *)((s8 *)(parent) + (0x20))), parent_state == 0xFE) || parent_state == 0xFD || FastDecTimer(particle + 0xA) != 0) {
        part_kill(particle);
        return;
    }
    point_a = particle + 0x10;
    FastVecSub(&target, (*(s32 *)((s8 *)(particle) + (0x30))) + 0x10, point_a);
    point_b = particle + 0x20;
    *(TI *)offset = target;
    FastVecScale(offset, offset, (g_tether_scale_a - 1.0f) * 1.2f + 1.0f);
    FastVecAdd(&target, offset, (*(s32 *)((s8 *)(particle) + (0x30))) + 0x10);
    (*(TI *)((s8 *)(particle) + (0x10))) = target;
    FastVecSub(&target, (*(s32 *)((s8 *)(particle) + (0x30))) + 0x10, point_b);
    *(TI *)offset = target;
    FastVecScale(offset, offset, (g_tether_scale_b - 1.0f) * 1.2f + 1.0f);
    FastVecAdd(&target, offset, (*(s32 *)((s8 *)(particle) + (0x30))) + 0x10);
    (*(TI *)((s8 *)(particle) + (0x20))) = target;
    if (fast_vec_dist(point_a, point_b) < 0.1f || fast_vec_dist(point_a, (*(s32 *)((s8 *)(particle) + (0x30))) + 0x10) < 1.0f) {
        part_kill(particle);
    }
}
