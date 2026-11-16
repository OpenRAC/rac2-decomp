#include "names.h"
/* func_PAL_L06_00401AA0, the PAL copy of func_L06_003FDEB8: the same C, where expr 0.016666668f becomes 0.020000001f; wrap state (((int)({e}) * 5 + 2) / 6); rewrap func_002A7820(D_L06_001AFC58, D_L06_001AFC5C). */
/* Path group setup, motion and spacing update. This unit needs -g for division padding. */
#include "common.h"
extern float math_random_float_range(float, float);
extern unsigned short *g_group_l06_id_lists[];
typedef struct { char prefix[0x68]; char *state; char tail[0x94]; } PathMoby;
extern PathMoby *g_moby_l06_table;
extern char *g_path_list[];
/* Tuning ranges, read only here. The upper bounds are read-only declarations: retail schedules
   their loads ahead of the stores before them and keeps them absolute; the lower bounds go to
   the call slots, where the assembler addresses them through $gp. */
extern int g_spawn_timer_min;
extern const int g_spawn_timer_max;
extern float g_spawn_spin_min;
extern const float g_spawn_spin_max;
extern float fast_vec_dist(void *, void *);
extern float math_random_signed_float_range(float, float);
extern float IntToFloat(int);
extern void vec_clear_128(void *);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);

/* Space the group's objects around a path and initialize their movement. */
void func_PAL_L06_00401AA0(int group)
{
    unsigned short *entry = g_group_l06_id_lists[group];
    char *path, *state, *last;
    float reciprocal, pathLength;
    int count, reverse, closed;
    if (!entry)
        return;
    state = g_moby_l06_table[*entry & 0x7FFF].state;
    path = g_path_list[*(int *)state];
    count = 0;
    reciprocal = fast_vec_dist(path + 0x10, path + 0x20);
    reciprocal = 1.0f / reciprocal;
    pathLength = (float)*(int *)path;
    closed = 1;
    if (!(fast_vec_dist(path + 0x10, path + (*(int *)path << 4)) < 5.0f))
        closed = 0;
    do {
        last = (char *)&g_moby_l06_table[*entry & 0x7FFF];
        count++;
    } while ((short)*entry++ >= 0);
    entry = g_group_l06_id_lists[group];
    reverse = count - 1;
    do {
        char *moby = (char *)&g_moby_l06_table[*entry & 0x7FFF];
        float position;
        state = *(char **)(moby + 0x68);
        *(float *)(state + 0x14) = (reciprocal * (0.020000001f)) *
                                  math_random_float_range(*(float *)(state + 8), *(float *)(state + 0xC));
        *(float *)(state + 0x18) = (reciprocal * 0.00040000002f) *
                                  (*(float *)(state + 0xC) - *(float *)(state + 8));
        position = IntToFloat(reverse);
        reverse--;
        position = position / IntToFloat(count);
        position *= pathLength;
        *(char **)(state + 0x34) = last;
        *(float *)(state + 0x60) = reciprocal;
        *(char **)(state + 0x30) = path;
        *(int *)(state + 0x40) = closed;
        *(float *)(state + 0x38) = *(float *)(state + 0x14);
        *(float *)(state + 0x5C) = *(float *)(state + 0x14);
        *(float *)(state + 0x1C) = reciprocal * 3.5f;
        *(float *)(state + 0x10) = position;
        vec_clear_128(state + 0x20);
        *(float *)(state + 0x20) = math_random_signed_float_range(0.0f, *(float *)(state + 4));
        *(float *)(state + 0x28) = math_random_signed_float_range(0.0f, *(float *)(state + 4));
        *(int *)(state + 0x48) = (((int)(math_random_int_range(g_spawn_timer_min, g_spawn_timer_max)) * 5 + 2) / 6);
        *(float *)(state + 0x4C) = math_random_angle();
        *(float *)(state + 0x50) = math_random_signed_float_range(g_spawn_spin_min, g_spawn_spin_max) * 0.0003490659f;
        *(unsigned char *)(moby + 0x20) = 1;
        *(unsigned short *)(moby + 0x32) = 0xFF;
        *(int *)(state + 0x54) = -1;
        last = moby;
    } while ((short)*entry++ >= 0);
}

/* Advance a moving object's path and keep its spacing from the next object. */
