#include "include_asm.h"
#include "names.h"

/* func_L07_003EE708 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern void moby_mark_spawned(int);
extern float math_random_angle();
extern void moby_set_state(char *, int, int);
extern int IsPointInCuboid(char *, int);
extern void path_reset_follower_to_point(char *);
extern int flag_set_first_pending(char *);
extern float SteerTowardTarget(char *);
extern int moby_count_group_not_in_state(int, int);
extern int math_fast_float_d(void *);
extern int flag_is_third_pending_set(char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int PlayMobySound(int, int, char *);
extern void entity_launch_member_a(char *, void *, void *, char *, int);
extern void entity_launch_member_b(char *, void *, void *, char *, int);
extern float ApproachValue(void *, float, float);
extern int part_find_owned_effect_slot(char *, int, int);
extern float moby_update_aim_target_strength(char *, int);
extern void part_spawn_masked_debris(char *, int, void *, int, float, float, float, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void part_spawn_blast_effect_moby(char *, void *, void *, float);

extern char g_hero_position[];
extern char D_L07_001B9200[];
extern int D_L07_001B0C50 __attribute__((sda));
extern unsigned short *g_moby_l07_group_lists[];
extern char *g_moby_l07_array[] __attribute__((sda));
extern int D_L07_001B22F8[] __attribute__((sda));
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
/* Per-frame update for moby class 3396: steps through its list of linked objects, throws
   launchers at them and fades out when hurt. */
void launcher_sequence_update(char *mobyArg)
{
    static void *cases[6] = {&&c0, &&c1, &&c4, &&c2, &&c3, &&c5};
    char *moby = mobyArg;
    L07State *vars;
    unsigned int state;

    state = *(unsigned char *)(moby + 0x20);
    vars = *(L07State **)(moby + 0x68);
    if (state < 6)
        goto *D_L07_002A3380[state];
    goto tail;
c0:
    if (vars->h24 == 0) {
        vars->h24 = 0x28;
        vars->f20 = 40.0f;
    }
    vars->f104 = math_random_angle();
    vars->f108 = math_random_angle();
    *(TI128 *)vars->b0F0 = *(TI128 *)(moby + 0x10);
    moby_set_state(moby, 1, -1);
    *(int *)(moby + 0x98) = 0;
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
    goto tail;
c1:
    if (vars->f90 != -1) {
        if (IsPointInCuboid(g_hero_position, vars->f90))
            path_reset_follower_to_point(moby);
    }
    goto tail;
c4: {
    int i;

    if (flag_set_first_pending(moby))
        vars->f124 = 0x3C;
    SteerTowardTarget(moby);
    i = vars->idx;
    if (i >= 6 || vars->ids[i + 1] == -1) {
        moby_set_state(moby, 5, -1);
    } else {
        if (moby_count_group_not_in_state(vars->ids[i], -1) == 0) {
            if (math_fast_float_d(&vars->f124)) {
                vars->idx = vars->idx + 1;
                moby_set_state(moby, 3, -1);
            }
        }
    }
    goto tail;
}
c2:
    SteerTowardTarget(moby);
    if (flag_is_third_pending_set(moby))
        moby_set_state(moby, 3, -1);
    goto tail;
c3: {
    float distance;
    unsigned short *p;
    char *member;
    char launchPos[16];

    distance = SteerTowardTarget(moby);
    if (distance < 3.0f) {
        if (vars->ids[vars->idx] != -1) {
            matrix_mul_vec3(launchPos, &D_L07_001B0C50, moby + 0xC0);
            FastVecAdd(launchPos, launchPos, moby + 0x10);
            for (p = g_moby_l07_group_lists[vars->ids[vars->idx]];
                 (vars->ids[vars->idx] & 0xFF) != 0xFF &&
                 vars->ids[vars->idx] <= D_L07_001B22F8[0] && p != 0 &&
                 ((short)p[-1] >= 0 || p == g_moby_l07_group_lists[vars->ids[vars->idx]]);
                 p++) {
                member = g_moby_l07_array[0] + ((*p & 0x7FFF) << 8);
                if (member == 0)
                    break;
                if (*(unsigned char *)(member + 0x20) != 0xFE) {
                    if (*(unsigned char *)(member + 0x20) != 0xFD) {
                        switch (*(short *)(member + 0xAA)) {
                        case 0xD29 /* moby class 3369 */:
                            PlayMobySound(0, 0, moby);
                            entity_launch_member_a(member, launchPos, member + 0x10, moby, vars->f110);
                            break;
                        case 0xD2A /* moby class 3370 */:
                            PlayMobySound(0, 0, moby);
                            entity_launch_member_b(member, launchPos, member + 0x10, moby, vars->f110);
                            break;
                        }
                    }
                }
            }
        }
        moby_set_state(moby, 4, -1);
    }
    goto tail;
}
c5: {
    SteerTowardTarget(moby);
    ApproachValue(&vars->f114, 0.16666667f, 0.00083333335f);
    vars->f118 += vars->f114;
    if (30.0f < vars->f118) {
        if (*(unsigned char *)(moby + 0x31) == 0) {
            moby_mark_spawned((int)moby);
            return;
        }
    }
}
tail:
    if (*(unsigned char *)(moby + 0x20) < 2)
        return;
    if (vars->f110 != 0)
        return;
    {
        char awayDir[16];
        int hitId;
        float damage;

        hitId = part_find_owned_effect_slot(moby, 0x10000, 0);
        damage = moby_update_aim_target_strength(moby, hitId);
        ApproachValue(&vars->f20, 0.0f, damage);
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        if (vars->f20 == 0.0f) {
            part_spawn_masked_debris(moby, 0x7F7, vars->b60, 0xFF, 5.0f, 10.0f, 5.0f, 10.0f);
            FastVecSub(awayDir, D_L07_001B9200, moby + 0x10);
            vec_scale_to_length(awayDir, awayDir, 1.0f);
            part_spawn_blast_effect_moby(moby, moby + 0x10, awayDir, 0.0f);
            PlayMobySound(2, 0, moby);
            moby_mark_spawned((int)moby);
        }
    }
}
