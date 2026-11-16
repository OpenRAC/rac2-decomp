#include "names.h"
/* func_L20_00449338: mode 0 records the start position, mode 1 waits for a trigger,
 * mode 2 moves z up by state[0x80] over state[0x84] updates, then mode 3.  An object
 * already triggered in mode 0 goes straight to the end position.  The trigger is flag
 * 0x80 of the object's entry (byte 0xB0) in the current level's row of D_0019B2E8, or
 * func_L00_00329520 on D_00189EA0 and index state[0x88].
 * Built -G8 (D_001A79F0 through $gp).  The entry byte is read at each use rather than
 * kept in a variable: that is what gives the row sum retail's register. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern s32 g_current_map_index __attribute__((sda));

extern u8 g_moby_group_flags[][16] __attribute__((nosda));

extern u32 g_hero_position[] __attribute__((nosda));

extern int coll_point_inside_region(void *, int);

extern int flag_is_third_pending_set(void *);

extern void mat_combine_and_store(void *, void *, void *, void *);
extern void moby_set_state(char *, int, int);
extern void FastVecSub(void *, void *, void *);

/* Update handler for moby class 4739: lifts the object upward when it is triggered, then holds it at the top. */
void rising_l20_platform_update(char *moby) {
    char *state = *(char **)(moby + 0x68);
    TI128 old_pos, old_rot, move_delta;

    qcopy(&old_pos, moby + 0x10);
    qcopy(&old_rot, moby + 0xF0);
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(float *)(state + 0x90) = 0.0f;
        qcopy(state + 0x60, moby + 0x10);
        qcopy(state + 0x70, moby + 0xF0);
        if ((*(u8 *)(moby + 0xB0) != 0xFF && *(u32 *)(state + 0x8C) != 0
             && (g_moby_group_flags[g_current_map_index][*(u8 *)(moby + 0xB0)] & 0x80))
            || (*(int *)(state + 0x88) != -1
                && coll_point_inside_region(g_hero_position, *(int *)(state + 0x88)) != 0)) {
            float base = *(float *)(state + 0x68);
            float rise = *(float *)(state + 0x80);

            *(u16 *)(moby + 0x34) |= 2;
            *(float *)(moby + 0x18) = base + rise;
            moby_set_state(moby, 3, -1);
        } else {
            moby_set_state(moby, 1, -1);
        }
        break;
    case 1:
        if (*(u8 *)(moby + 0xBC) != 0 || flag_is_third_pending_set(moby) != 0
            || (*(u8 *)(moby + 0xB0) != 0xFF && *(u32 *)(state + 0x8C) != 0
                && (g_moby_group_flags[g_current_map_index][*(u8 *)(moby + 0xB0)] & 0x80))
            || (*(int *)(state + 0x88) != -1
                && coll_point_inside_region(g_hero_position, *(int *)(state + 0x88)) != 0)) {
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2: {
        float step, progress, amplitude, baseline;
        step = 1.0f / *(float *)(state + 0x84);
        *(float *)(state + 0x90) += step;
        if (*(float *)(state + 0x90) > 1.0f) *(float *)(state + 0x90) = 1.0f;
        progress = *(float *)(state + 0x90);
        amplitude = *(float *)(state + 0x80);
        baseline = *(float *)(state + 0x68);
        progress *= amplitude;
        baseline += progress;
        *(float *)(moby + 0x18) = baseline;
        if (*(float *)(state + 0x90) >= 1.0f)
            moby_set_state(moby, 3, -1);
        break;
    }
    }
    if (*(u8 *)(moby + 0x20) < 3) {
        FastVecSub(&move_delta, moby + 0x10, &old_pos);
        mat_combine_and_store(state + 0x20, &move_delta, &old_rot, moby + 0xF0);
    }
}
