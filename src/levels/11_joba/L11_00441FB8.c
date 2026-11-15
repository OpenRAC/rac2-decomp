#include "common.h"
typedef struct { s32 field00; u8 remainder[12]; } JobaPolygonHeaderView;
extern JobaPolygonHeaderView *D_L11_001FF580[];
extern u8 *arena_get_center_point(u8 *);
extern s32 point_in_path_xy(float *, float *, s32);
extern s32 coll_point_inside_record_volume(void *, s32);
extern u8 *g_hero_moby;

/* Rejects a target using the state polygons and class-dependent height limits. */
/* Says whether a target should be ignored because it is outside the arena or too low. */
s32 arena_is_target_outside(u8 *controller, u8 *target, s32 skip_outer_zone) {
    float pos[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(controller + 0x68);
    s16 result = !coll_point_inside_record_volume(target + 0x10, *(s32 *)(state + 0x1E4));
    if (*(s16 *)(target + 0xAA) != 0 && (*(u16 *)(target + 0x34) & 2)) return 0;
    if (result) return result;
    if (!skip_outer_zone) {
        if (*(s16 *)(target + 0xAA) == 0xD4B /* moby class 3403 */) {
            qcopy(pos, target + 0x10);
            pos[2] -= 0.8f;
            result = (s16)coll_point_inside_record_volume(pos, *(s32 *)(state + 0x160));
        } else result = (s16)coll_point_inside_record_volume(target + 0x10, *(s32 *)(state + 0x160));
    }
    if (result) return result;
    if (*(s16 *)(state + 0x1FA) == 3) {
        float *height = (float *)arena_get_center_point(controller);
        result = (s16)(*(float *)(target + 0x18) < height[2] + (target == g_hero_moby ? 0.5f : 3.0f));
    }
    if (result) return result;
    if (*(s16 *)(state + 0x1FA) == 2 || *(s16 *)(state + 0x1FA) == 4) {
        u8 *poly = (u8 *)D_L11_001FF580[*(s32 *)(state + 0x1C8)];
        if (*(float *)(target + 0x18) < ((float *)arena_get_center_point(controller))[2] + 0.5f)
            result = !point_in_path_xy((float *)(target + 0x10), (float *)(poly + 0x10), *(s32 *)poly);
    }
    return result;
}

