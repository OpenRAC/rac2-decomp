#include "include_asm.h"

#include "common.h"
extern int g_group_count[] __attribute__((sda));
extern char *g_group_l20_member_table[] __attribute__((sda));
extern char *g_group_l20_id_lists[];
extern int g_turret_light_color __attribute__((sda));
extern void func_PAL_002A7E68(void *, int, int, int);
extern void moby_set_light_color(void *, int);
extern int math_random_int_below(int);
extern void moby_set_state(void *, int, int);
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float math_random_angle(void);

char *turret_spawn_from_group_pal(int arg0, int arg1, float *arg2, float *arg3) {
    char *idp = g_group_l20_id_lists[arg1];
    char *found = 0;

    if ((arg1 & 0xFF) == 0xFF) {
        goto end;
    }
    if (g_group_count[0] < arg1) {
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
        if ((arg1 & 0xFF) == 0xFF) {
            goto end;
        }
        if (g_group_count[0] < arg1) {
            goto end;
        }
        if (idp == 0) {
            goto end;
        }
        if (*(s16 *)(idp - 2) >= 0) {
            continue;
        }
        if (idp == g_group_l20_id_lists[arg1]) {
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
        func_PAL_002A7E68(found, 0, 0, 0xC);
        moby_set_light_color(found, g_turret_light_color);
        if (math_random_int_below(2) != 0) {
            *(u16 *)(found + 0x34) |= 0x8000;
        } else {
            *(u16 *)(found + 0x34) &= 0x7FFF;
        }
        state = *(char **)(found + 0x68);
        pos = found + 0x10;
        qcopy(pos, arg2);
        qcopy(state + 0x180, arg2);
        qcopy(state + 0x170, arg3);
        *(int *)(found + 0xB8) = arg0;
        moby_set_state(found, 2, -1);
        vec_scale_to_length(state + 0x190, arg3, math_random_float_range(20.0f, 30.0f));
        FastVecAdd(state + 0x190, state + 0x190, pos);
        *(float *)(state + 0x198) = arg2[2];
        *(float *)(state + 0x20) = (float)*(s16 *)(state + 0x24);
        *(float *)(found + 0xF8) = mat_fast_helper_a(arg3[0], arg3[1]);
        *(float *)(state + 0x1A0) = math_random_angle();
        *(float *)(state + 0x20) = (float)*(s16 *)(state + 0x24);
    }
    return found;
}
