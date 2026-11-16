#include "include_asm.h"
#include "names.h"

typedef short s16;
typedef int s32;
extern s32 func_002F3220(char *, float);
extern int math_fast_float_d(void *);
extern s32 func_003D77F8(char *);
extern s32 moby_is_state_two_no_children(char *);
extern s32 arena_start_announcer_message(char *, s32);
typedef int TI128 __attribute__((mode(TI)));
extern int g_frame_l02_counter __attribute__((sda));
extern float g_sway_angle_range[2] __attribute__((sda));
extern char *g_sway_piece_table __attribute__((sda));
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float ApproachValue(float *, float, float);
extern void euler_rotation_basis(float *, float *);
extern void mat_multiply_rotation(char *, char *, float *);
extern s32 arena_register_spawned_enemy(char *, char *);
extern s32 g_group_max_index[] __attribute__((sda));
extern s32 g_group_max_index[] __attribute__((sda));
extern s16 moby_get_vars_counter(char *);
extern s32 moby_get_busy_flag(char *);

/* Runs func_L02_003F5430 first when bit 0 of D_L02_001B30C8 is set. The angle at +0x88 is stepped
   (func_002AA2E8, 0.05 degree) towards the target at +0x8C when func_00282948 reports the timer at
   +0x90 idle or just run out, and towards zero while it is still counting down. When the target lies
   between zero and the angle, the timer gets a random 30..90 and the target a random size with the
   opposite sign. The angle is then the third word of a vector func_002833F0 turns into a matrix,
   which multiplies the 64-byte records of D_L02_001B3B00 that the entries of the list at +0x40 name,
   for each bit set in the mask at +0x84. */
void func_PAL_L02_003F9B50(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    float m[12];
    float b[4];
    float a[4];
    s32 i;
    s16 *s2;

    if (g_frame_l02_counter & 1)
        sway_update_piece_mask(a0);
    if (math_fast_float_d(state + 0x90) != 0) {
        ApproachValue((float *)(state + 0x88), *(float *)(state + 0x8C), 0.0012566373f);
        if ((*(float *)(state + 0x88) >= *(float *)(state + 0x8C) && *(float *)(state + 0x8C) >= 0.0f) ||
            (*(float *)(state + 0x88) <= *(float *)(state + 0x8C) && *(float *)(state + 0x8C) <= 0.0f)) {
            *(s32 *)(state + 0x90) = ((s32)(math_random_int_range(0x1E, 0x5A)) * 5 + 2) / 6;
            if (0.0f < *(float *)(state + 0x8C))
                *(float *)(state + 0x8C) =
                    -(math_random_float_range(g_sway_angle_range[0], g_sway_angle_range[1]) * 0.0003490659f);
            else
                *(float *)(state + 0x8C) =
                    math_random_float_range(g_sway_angle_range[0], g_sway_angle_range[1]) * 0.0003490659f;
        }
    } else {
        ApproachValue((float *)(state + 0x88), 0.0f, 0.0012566373f);
    }
    *(TI128 *)a = 0;
    a[2] = *(float *)(state + 0x88);
    *(TI128 *)b = *(TI128 *)a;
    euler_rotation_basis(m, b);
    for (i = 0; i < *(s32 *)(state + 0x80); i++) {
        char *rec;
        s32 skip;

        s2 = (s16 *)(state + 0x40 + i * 2);
        skip = ((*(s32 *)(state + 0x84) >> i) & 1) == 0;
        if (skip)
            continue;
        rec = g_sway_piece_table + *s2 * 64;
        mat_multiply_rotation(rec, rec, m);
    }
}


