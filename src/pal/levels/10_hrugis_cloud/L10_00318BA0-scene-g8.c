#include "include_asm.h"

#include "common.h"
typedef struct Scene {
    u8 pad00[0x30];
    s32 mode;
    s32 frame;
    u8 pad38[12];
    s16 count;
    u8 pad46[10];
    u8 *target;
    u8 pad54[0x138];
    u8 *objects[0];
} Scene;
extern s32 g_current_map_index;
extern Scene g_scene_marker_state;
extern u8 g_scene_target_data[];
extern u8 g_scene_marker_dest[];
extern u8 g_scene_marker_data[64] __attribute__((sda));
extern u8 g_view_origin_vec[];
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);

/* During the cutscene frames, moves the four scene markers onto the marker object and points the camera target at the scene object (PAL copy of hrugis_update_scene_markers). */
void hrugis_update_scene_markers_pal(void) {
    f32 to_view[4] __attribute__((aligned(16)));
    s32 low, high, slot, i, j;
    u8 *obj;
    u8 *dst, *src;

    if (g_current_map_index != 10) {
        return;
    }
    low = -1;
    high = 9999;
    slot = 0;
    if (g_scene_marker_state.mode == 1) {
        low = 1;
        high = 1033;
        slot = 3;
    } else if (g_scene_marker_state.mode == 2) {
        low = 1;
        high = 333;
        slot = 3;
    }
    if (low == -1) {
        return;
    }
    if (g_scene_marker_state.frame >= low && g_scene_marker_state.frame <= high) {
        g_scene_marker_state.target = g_scene_target_data;
        obj = 0;
        for (i = 0; i < g_scene_marker_state.count; i++) {
            u8 *p = g_scene_marker_state.objects[i];
            if (*(s16 *)(p + 0xAA) == 0xD54) {
                obj = p;
                break;
            }
        }
        if (obj) {
            dst = g_scene_marker_dest;
            src = g_scene_marker_data;
            for (j = 0; j < 4; j++) {
                u8 *out = dst + j * 16;
                matrix_mul_vec3(out, src + j * 16, obj + 0xC0);
                FastVecAdd(out, out, obj + 0x10);
                FastVecSub(to_view, g_view_origin_vec, out);
                vec_scale_to_length(to_view, to_view, 0.15f);
                FastVecAdd(out, out, to_view);
            }
        }
        *(u8 **)(g_scene_marker_state.target + 0x68) = g_scene_marker_state.objects[slot];
    } else {
        g_scene_marker_state.target = 0;
    }
}
