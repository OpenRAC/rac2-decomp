#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern void moby_mark_spawned(int);
extern float math_random_angle();
extern void moby_set_state(char *, int, int);
extern int IsPointInCuboid(char *, int);
extern void path_reset_follower_to_point(char *);
extern int flag_set_first_pending(char *);
extern float SteerTowardTarget_pal(char *);
extern int moby_count_group_not_in_state(int, int);
extern int math_fast_float_d(void *);
extern int flag_is_third_pending_set(char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int PlayMobySound(int, int, char *);
extern void func_PAL_L07_003EB648(char *, void *, void *, char *, int);
extern void func_PAL_L07_003EFFD0(char *, void *, void *, char *, int);
extern float ApproachValue(void *, float, float);
extern void *part_find_owned_effect_slot(char *, int, int);
extern float moby_update_aim_target_strength_pal(char *, int);
extern void func_PAL_002B15D8(char *, int, void *, int, float, float, float, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char *func_PAL_0032F3B8(char *, void *, void *, float);
extern char g_hero_position[];
extern char g_hero_position_block[];
extern int g_launcher_launch_offset __attribute__((sda));
extern unsigned short *g_moby_l07_group_lists[];
extern char *g_moby_l07_array[] __attribute__((sda));
extern int g_entity_group_count[] __attribute__((sda));
extern void *D_L07_002A3380[];
typedef struct {
    char pad00[0x20];
    float f20;
    short h24;
    char pad26[0x60 - 0x26];
    char b60[0x30];
    int f90;
    char pad94[0x9C - 0x94];
    int ids[7];
    char padB8[0xF0 - 0xB8];
    char b0F0[0x10];
    char pad100[0x104 - 0x100];
    float f104;
    float f108;
    char pad10C[0x110 - 0x10C];
    int f110;
    float f114;
    float f118;
    char pad11C[0x120 - 0x11C];
    int idx;
    int f124;
} L07State;

/* The object's six states, state 0 to 5 (anything above only runs the tail). The dispatch reads the
   level's own jump table (six code addresses in the level's data at 0x2A3380: the bodies come in
   the order 0, 1, 4, 2, 3, 5); `cases` only keeps the labels alive. */
void launcher_sequence_update_pal(char *a0)
{
    static void *cases[6] = {&&c0, &&c1, &&c4, &&c2, &&c3, &&c5};
    char *s1 = a0;
    L07State *s3;
    unsigned int sel;

    sel = *(unsigned char *)(s1 + 0x20);
    s3 = *(L07State **)(s1 + 0x68);
    if (sel < 6)
        goto *D_L07_002A3380[sel];
    goto tail;
c0:
    if (s3->h24 == 0) {
        s3->h24 = 0x28;
        s3->f20 = 40.0f;
    }
    s3->f104 = math_random_angle();
    s3->f108 = math_random_angle();
    *(TI128 *)s3->b0F0 = *(TI128 *)(s1 + 0x10);
    moby_set_state(s1, 1, -1);
    *(int *)(s1 + 0x98) = 0;
    *(unsigned short *)(s1 + 0x34) = (*(unsigned short *)(s1 + 0x34) | 0x41) & 0xEFFF;
    goto tail;
c1:
    if (s3->f90 != -1) {
        if (IsPointInCuboid(g_hero_position, s3->f90))
            path_reset_follower_to_point(s1);
    }
    goto tail;
c4: {
    int i;

    if (flag_set_first_pending(s1))
        s3->f124 = 0x32;
    SteerTowardTarget_pal(s1);
    i = s3->idx;
    if (i >= 6 || s3->ids[i + 1] == -1) {
        moby_set_state(s1, 5, -1);
    } else {
        if (moby_count_group_not_in_state(s3->ids[i], -1) == 0) {
            if (math_fast_float_d(&s3->f124)) {
                s3->idx = s3->idx + 1;
                moby_set_state(s1, 3, -1);
            }
        }
    }
    goto tail;
}
c2:
    SteerTowardTarget_pal(s1);
    if (flag_is_third_pending_set(s1))
        moby_set_state(s1, 3, -1);
    goto tail;
c3: {
    float f;
    unsigned short *p;
    char *e;
    char buf[16];

    f = SteerTowardTarget_pal(s1);
    if (f < 3.0f) {
        if (s3->ids[s3->idx] != -1) {
            matrix_mul_vec3(buf, &g_launcher_launch_offset, s1 + 0xC0);
            FastVecAdd(buf, buf, s1 + 0x10);
            for (p = g_moby_l07_group_lists[s3->ids[s3->idx]];
                 (s3->ids[s3->idx] & 0xFF) != 0xFF &&
                 s3->ids[s3->idx] <= g_entity_group_count[0] && p != 0 &&
                 ((short)p[-1] >= 0 || p == g_moby_l07_group_lists[s3->ids[s3->idx]]);
                 p++) {
                e = g_moby_l07_array[0] + ((*p & 0x7FFF) << 8);
                if (e == 0)
                    break;
                if (*(unsigned char *)(e + 0x20) != 0xFE) {
                    if (*(unsigned char *)(e + 0x20) != 0xFD) {
                        switch (*(short *)(e + 0xAA)) {
                        case 0xD29:
                            PlayMobySound(0, 0, s1);
                            func_PAL_L07_003EB648(e, buf, e + 0x10, s1, s3->f110);
                            break;
                        case 0xD2A:
                            PlayMobySound(0, 0, s1);
                            func_PAL_L07_003EFFD0(e, buf, e + 0x10, s1, s3->f110);
                            break;
                        }
                    }
                }
            }
        }
        moby_set_state(s1, 4, -1);
    }
    goto tail;
}
c5: {
    SteerTowardTarget_pal(s1);
    ApproachValue(&s3->f114, 0.20000002f, 0.0012f);
    s3->f118 += s3->f114;
    if (30.0f < s3->f118) {
        if (*(unsigned char *)(s1 + 0x31) == 0) {
            moby_mark_spawned((int)s1);
            return;
        }
    }
}
tail:
    if (*(unsigned char *)(s1 + 0x20) < 2)
        return;
    if (s3->f110 != 0)
        return;
    {
        char buf2[16];
        int t;
        float f2;

        t = part_find_owned_effect_slot(s1, 0x10000, 0);
        f2 = moby_update_aim_target_strength_pal(s1, t);
        ApproachValue(&s3->f20, 0.0f, f2);
        *(unsigned char *)(s1 + 0xA8) = 0xFF;
        if (s3->f20 == 0.0f) {
            func_PAL_002B15D8(s1, 0x7F7, s3->b60, 0xFF, 5.0f, 10.0f, 5.0f, 10.0f);
            FastVecSub(buf2, g_hero_position_block, s1 + 0x10);
            vec_scale_to_length(buf2, buf2, 1.0f);
            func_PAL_0032F3B8(s1, s1 + 0x10, buf2, 0.0f);
            PlayMobySound(2, 0, s1);
            moby_mark_spawned((int)s1);
        }
    }
}
