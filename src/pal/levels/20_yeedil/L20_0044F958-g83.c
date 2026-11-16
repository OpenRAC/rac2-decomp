#include "include_asm.h"

#include "common.h"
extern int g_group_count[] __attribute__((sda));
extern char *g_group_l20_member_table[] __attribute__((sda));
extern char *g_group_l20_id_lists[];
extern int g_turret_light_color __attribute__((sda));
extern void anim_start_blended_pal(void *, int, int, int);
extern void moby_set_light_color(void *, int);
extern int math_random_int_below(int);
extern void moby_set_state(void *, int, int);
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float math_random_angle(void);

/* Wakes an idle turret from a group of objects, places it at a position facing a direction, and returns it (or null if none is free). */
char *turret_spawn_from_group_pal(int parent, int group_index, float *position, float *direction) {
    char *idp = g_group_l20_id_lists[group_index];
    char *found = 0;

    if ((group_index & 0xFF) == 0xFF) {
        goto end;
    }
    if (g_group_count[0] < group_index) {
        goto end;
    }
    if (idp == 0) {
        goto end;
    }
    for (;;) {
        char *moby = g_group_l20_member_table[0] + ((*(u16 *)idp & 0x7FFF) << 8);

        if (moby == 0) {
            goto end;
        }
        if (*(u8 *)(moby + 0x20) == 1) {
            found = moby;
            goto end;
        }
        idp += 2;
        if ((group_index & 0xFF) == 0xFF) {
            goto end;
        }
        if (g_group_count[0] < group_index) {
            goto end;
        }
        if (idp == 0) {
            goto end;
        }
        if (*(s16 *)(idp - 2) >= 0) {
            continue;
        }
        if (idp == g_group_l20_id_lists[group_index]) {
            continue;
        }
        break;
    }
end:
    if (found != 0) {
        char *state;
        char *pos;

        *(u16 *)(found + 0x34) = (*(u16 *)(found + 0x34) & 0xFFBE) | 0x1000;
        *(int *)(found + 0x98) = *(int *)(*(char **)(found + 0x24) + 0x10);
        anim_start_blended_pal(found, 0, 0, 0xC);
        moby_set_light_color(found, g_turret_light_color);
        if (math_random_int_below(2) != 0) {
            *(u16 *)(found + 0x34) |= 0x8000;
        } else {
            *(u16 *)(found + 0x34) &= 0x7FFF;
        }
        state = *(char **)(found + 0x68);
        pos = found + 0x10;
        qcopy(pos, position);
        qcopy(state + 0x180, position);
        qcopy(state + 0x170, direction);
        *(int *)(found + 0xB8) = parent;
        moby_set_state(found, 2, -1);
        vec_scale_to_length(state + 0x190, direction, math_random_float_range(20.0f, 30.0f));
        FastVecAdd(state + 0x190, state + 0x190, pos);
        *(float *)(state + 0x198) = position[2];
        *(float *)(state + 0x20) = (float)*(s16 *)(state + 0x24);
        *(float *)(found + 0xF8) = mat_fast_helper_a(direction[0], direction[1]);
        *(float *)(state + 0x1A0) = math_random_angle();
        *(float *)(state + 0x20) = (float)*(s16 *)(state + 0x24);
    }
    return found;
}
