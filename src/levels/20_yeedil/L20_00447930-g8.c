#include "names.h"
/* func_L20_00447930 (UpdateMoby_4687): a platform that eases from its start
 * position to path point state[0x80] of D_L20_001B308C.  Mode 0 records the start
 * (or, when already triggered, jumps straight to the end and retires the moby),
 * mode 1 waits for a trigger, mode 2 eases along a half cosine, mode 3 waits for the
 * linked moby state[0x94] to release it.  Same family as func_L20_00449338.
 * Built -G8 (D_001A79F0 and D_L20_001B2F9C through $gp).
 * The end-of-path copies use qcopy_nc: the only accesses around them read the path
 * table pointer and state[0x80], never the moby's position/rotation being written,
 * and retail keeps the table base and the scaled index across the first copy. */
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
extern void hero_exit_vehicle_mode(s32);
extern float math_fast_sin_or_cos_a(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

/* Moves a platform (moby class 4687) smoothly from its start to the end of a path once it is triggered, then removes it. */
void eased_platform_update(char *moby) {
    char *state = *(char **)(moby + 0x68);
    TI128 start_pos, start_rot, offset;

    qcopy(&start_pos, moby + 0x10);
    qcopy(&start_rot, moby + 0xF0);
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        if (*(int *)(state + 0x80) == -1) {
            *(u16 *)(moby + 0x34) |= 2;
            moby_set_state(moby, 4, -1);
            return;
        }
        *(float *)(state + 0x88) = 0.0f;
        *(int *)(state + 0x5C) |= 1;
        qcopy(state + 0x60, moby + 0x10);
        qcopy(state + 0x70, moby + 0xF0);
        *(u16 *)(moby + 0x34) |= 0x100;
        if (D_L20_0021EFB0.collected[*(int *)(state + 0x8C)] != 0
            || (*(u8 *)(moby + 0xB0) != 0xFF && *(u8 *)(state + 0x92) != 0
                && (D_0019B2E8[g_current_map_index][*(u8 *)(moby + 0xB0)] & 0x80))
            || (*(int *)(state + 0x98) != -1
                && coll_point_inside_region(g_hero_position, *(int *)(state + 0x98)) != 0)) {
            /* Already triggered: snap to the end of the path. */
            qcopy_nc(moby + 0x10, &D_L20_001B308C[*(int *)(state + 0x80)].pos);
            qcopy_nc(moby + 0xF0, &D_L20_001B308C[*(int *)(state + 0x80)].rot);
            moby_mark_spawned(moby);
            return;
        }
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (*(u8 *)(moby + 0xBC) != 0 || flag_is_third_pending_set(moby) != 0
            || *(int *)(state + 0x8C) == -1
            || D_L20_001B2F9C[(*(int *)(state + 0x8C) << 8) + 0x20] == 0xFE
            || D_L20_001B2F9C[(*(int *)(state + 0x8C) << 8) + 0x20] == 0xFD
            || (*(u8 *)(moby + 0xB0) != 0xFF && *(u8 *)(state + 0x92) != 0
                && (D_0019B2E8[g_current_map_index][*(u8 *)(moby + 0xB0)] & 0x80))
            || (*(int *)(state + 0x98) != -1
                && coll_point_inside_region(g_hero_position, *(int *)(state + 0x98)) != 0)) {
            if (*(int *)(state + 0x94) != -1) {
                D_L20_001B2F9C[(*(int *)(state + 0x94) << 8) + 0xBC] = 1;
            }
            if (*(u8 *)(state + 0x93) != 0) {
                moby_mark_table_entry_flagged(*(u8 *)(moby + 0xB0));
            }
            moby_set_state(moby, 2, -1);
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
        vec_scale_to_length(moby + 0xE0, moby + 0xE0, 1.0f - ease);
        FastVecSub(&offset, &D_L20_001B308C[*(int *)(state + 0x80)].pos, state + 0x60);
        FastVecScale(&offset, &offset, ease);
        FastVecAdd(moby + 0x10, state + 0x60, &offset);
        if (*(float *)(state + 0x88) >= 1.0f) {
            moby_set_state(moby, 3, -1);
        }
        break;
    }
    case 3:
        if (*(int *)(state + 0x94) == -1
            || D_L20_001B2F9C[(*(int *)(state + 0x94) << 8) + 0xBC] == 0) {
            if (*(u8 *)(state + 0x90) != 0) {
                hero_exit_vehicle_mode(0);
            }
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
    if (*(u8 *)(moby + 0x20) < 3) {
        FastVecSub(&offset, moby + 0x10, &start_pos);
        mat_combine_and_store(state + 0x20, &offset, &start_rot, moby + 0xF0);
    }
}
