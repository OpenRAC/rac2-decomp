#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern s32 g_current_map_index __attribute__((sda));
extern u8 *D_L20_001B2F9C __attribute__((sda));
extern u8 D_0019B2E8[][16] __attribute__((nosda));
extern u32 g_hero_position[] __attribute__((nosda));
extern struct { u8 header[0x464]; u8 collected[0]; } D_L20_0021EFB0;
typedef struct { u8 pad[0x30]; TI128 pos; u8 pad2[0x30]; TI128 rot; } PathPoint;
extern PathPoint *D_L20_001B308C;
extern int coll_point_inside_region(void *, int);
extern int flag_is_third_pending_set(void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void moby_set_state(char *, int, int);
extern void moby_mark_table_entry_flagged(int);
extern void moby_mark_spawned(void *);
extern void func_PAL_L20_002C59B0(s32);
extern float math_fast_sin_or_cos_a(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

void func_PAL_L20_0044D4B8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    TI128 v0, v1, v2;

    qcopy(&v0, arg0 + 0x10);
    qcopy(&v1, arg0 + 0xF0);
    switch (*(u8 *)(arg0 + 0x20)) {
    case 0:
        if (*(int *)(state + 0x80) == -1) {
            *(u16 *)(arg0 + 0x34) |= 2;
            moby_set_state(arg0, 4, -1);
            return;
        }
        *(float *)(state + 0x88) = 0.0f;
        *(int *)(state + 0x5C) |= 1;
        qcopy(state + 0x60, arg0 + 0x10);
        qcopy(state + 0x70, arg0 + 0xF0);
        *(u16 *)(arg0 + 0x34) |= 0x100;
        if (D_L20_0021EFB0.collected[*(int *)(state + 0x8C)] != 0
            || (*(u8 *)(arg0 + 0xB0) != 0xFF && *(u8 *)(state + 0x92) != 0
                && (D_0019B2E8[g_current_map_index][*(u8 *)(arg0 + 0xB0)] & 0x80))
            || (*(int *)(state + 0x98) != -1
                && coll_point_inside_region(g_hero_position, *(int *)(state + 0x98)) != 0)) {
            /* Already triggered: snap to the end of the path. */
            qcopy_nc(arg0 + 0x10, &D_L20_001B308C[*(int *)(state + 0x80)].pos);
            qcopy_nc(arg0 + 0xF0, &D_L20_001B308C[*(int *)(state + 0x80)].rot);
            moby_mark_spawned(arg0);
            return;
        }
        moby_set_state(arg0, 1, -1);
        break;
    case 1:
        if (*(u8 *)(arg0 + 0xBC) != 0 || flag_is_third_pending_set(arg0) != 0
            || *(int *)(state + 0x8C) == -1
            || D_L20_001B2F9C[(*(int *)(state + 0x8C) << 8) + 0x20] == 0xFE
            || D_L20_001B2F9C[(*(int *)(state + 0x8C) << 8) + 0x20] == 0xFD
            || (*(u8 *)(arg0 + 0xB0) != 0xFF && *(u8 *)(state + 0x92) != 0
                && (D_0019B2E8[g_current_map_index][*(u8 *)(arg0 + 0xB0)] & 0x80))
            || (*(int *)(state + 0x98) != -1
                && coll_point_inside_region(g_hero_position, *(int *)(state + 0x98)) != 0)) {
            if (*(int *)(state + 0x94) != -1) {
                D_L20_001B2F9C[(*(int *)(state + 0x94) << 8) + 0xBC] = 1;
            }
            if (*(u8 *)(state + 0x93) != 0) {
                moby_mark_table_entry_flagged(*(u8 *)(arg0 + 0xB0));
            }
            moby_set_state(arg0, 2, -1);
        }
        break;
    case 2: {
        float t, ease;

        *(float *)(state + 0x88) += 1.0f / *(float *)(state + 0x84);
        if (*(float *)(state + 0x88) > 1.0f) {
            *(float *)(state + 0x88) = 1.0f;
        }
        t = *(float *)(state + 0x88);
        ease = (1.0f - math_fast_sin_or_cos_a(t * 3.1415927f)) * 0.5f;
        vec_scale_to_length(arg0 + 0xE0, arg0 + 0xE0, 1.0f - ease);
        FastVecSub(&v2, &D_L20_001B308C[*(int *)(state + 0x80)].pos, state + 0x60);
        FastVecScale(&v2, &v2, ease);
        FastVecAdd(arg0 + 0x10, state + 0x60, &v2);
        if (*(float *)(state + 0x88) >= 1.0f) {
            moby_set_state(arg0, 3, -1);
        }
        break;
    }
    case 3:
        if (*(int *)(state + 0x94) == -1
            || D_L20_001B2F9C[(*(int *)(state + 0x94) << 8) + 0xBC] == 0) {
            if (*(u8 *)(state + 0x90) != 0) {
                func_PAL_L20_002C59B0(0);
            }
            moby_mark_spawned(arg0);
            return;
        }
        break;
    }
    if (*(u8 *)(arg0 + 0x20) < 3) {
        FastVecSub(&v2, arg0 + 0x10, &v0);
        mat_combine_and_store(state + 0x20, &v2, &v1, arg0 + 0xF0);
    }
}
