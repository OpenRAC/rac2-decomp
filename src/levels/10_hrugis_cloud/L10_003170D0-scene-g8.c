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
extern Scene D_L10_001BD380;
extern u8 D_L10_00296E90[];
extern u8 D_L10_00296EB0[];
extern u8 D_L10_001A93E0[64] __attribute__((sda));
extern u8 D_L10_001B9680[];
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);

/* In the level 10 story scenes, finds the scene object and moves four marker points to
   sit around it. The scene ends when its frame runs out. */
void hrugis_update_scene_markers(void) {
    f32 tmp[4] __attribute__((aligned(16)));
    s32 low, high, slot, i, j;
    u8 *target;
    u8 *dst, *src;

    if (g_current_map_index != 10) {
        return;
    }
    low = -1;
    high = 9999;
    slot = 0;
    if (D_L10_001BD380.mode == 1) {
        low = 1;
        high = 1240;
        slot = 3;
    } else if (D_L10_001BD380.mode == 2) {
        low = 1;
        high = 400;
        slot = 3;
    }
    if (low == -1) {
        return;
    }
    if (D_L10_001BD380.frame >= low && D_L10_001BD380.frame <= high) {
        D_L10_001BD380.target = D_L10_00296E90;
        target = 0;
        for (i = 0; i < D_L10_001BD380.count; i++) {
            u8 *candidate = D_L10_001BD380.objects[i];
            if (*(s16 *)(candidate + 0xAA) == 0xD54 /* moby class 3412 */) {
                target = candidate;
                break;
            }
        }
        if (target) {
            dst = D_L10_00296EB0;
            src = D_L10_001A93E0;
            for (j = 0; j < 4; j++) {
                u8 *point = dst + j * 16;
                matrix_mul_vec3(point, src + j * 16, target + 0xC0);
                FastVecAdd(point, point, target + 0x10);
                FastVecSub(tmp, D_L10_001B9680, point);
                vec_scale_to_length(tmp, tmp, 0.15f);
                FastVecAdd(point, point, tmp);
            }
        }
        *(u8 **)(D_L10_001BD380.target + 0x68) = D_L10_001BD380.objects[slot];
    } else {
        D_L10_001BD380.target = 0;
    }
}
