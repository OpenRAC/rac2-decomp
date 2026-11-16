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
extern void entity_launch_member_a_pal(char *, void *, void *, char *, int);
extern void entity_launch_member_b_pal(char *, void *, void *, char *, int);
extern float ApproachValue(void *, float, float);
extern void *part_find_owned_effect_slot(char *, int, int);
extern float moby_update_aim_target_strength_pal(char *, int);
extern void part_spawn_masked_debris_pal(char *, int, void *, int, float, float, float, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char *part_spawn_blast_effect_moby_pal(char *, void *, void *, float);
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
void launcher_sequence_update_pal(char *moby_arg)
{
    static void *cases[6] = {&&c0, &&c1, &&c4, &&c2, &&c3, &&c5};
    char *moby = moby_arg;
    L07State *state;
    unsigned int state_id;

    state_id = *(unsigned char *)(moby + 0x20);
    state = *(L07State **)(moby + 0x68);
    if (state_id < 6)
        goto *D_L07_002A3380[state_id];
    goto tail;
c0:
    if (state->h24 == 0) {
        state->h24 = 0x28;
        state->f20 = 40.0f;
    }
    state->f104 = math_random_angle();
    state->f108 = math_random_angle();
    *(TI128 *)state->b0F0 = *(TI128 *)(moby + 0x10);
    moby_set_state(moby, 1, -1);
    *(int *)(moby + 0x98) = 0;
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
    goto tail;
c1:
    if (state->f90 != -1) {
        if (IsPointInCuboid(g_hero_position, state->f90))
            path_reset_follower_to_point(moby);
    }
    goto tail;
c4: {
    int i;

    if (flag_set_first_pending(moby))
        state->f124 = 0x32;
    SteerTowardTarget_pal(moby);
    i = state->idx;
    if (i >= 6 || state->ids[i + 1] == -1) {
        moby_set_state(moby, 5, -1);
    } else {
        if (moby_count_group_not_in_state(state->ids[i], -1) == 0) {
            if (math_fast_float_d(&state->f124)) {
                state->idx = state->idx + 1;
                moby_set_state(moby, 3, -1);
            }
        }
    }
    goto tail;
}
c2:
    SteerTowardTarget_pal(moby);
    if (flag_is_third_pending_set(moby))
        moby_set_state(moby, 3, -1);
    goto tail;
c3: {
    float dist;
    unsigned short *id_ptr;
    char *member;
    char buf[16];

    dist = SteerTowardTarget_pal(moby);
    if (dist < 3.0f) {
        if (state->ids[state->idx] != -1) {
            matrix_mul_vec3(buf, &g_launcher_launch_offset, moby + 0xC0);
            FastVecAdd(buf, buf, moby + 0x10);
            for (id_ptr = g_moby_l07_group_lists[state->ids[state->idx]];
                 (state->ids[state->idx] & 0xFF) != 0xFF &&
                 state->ids[state->idx] <= g_entity_group_count[0] && id_ptr != 0 &&
                 ((short)id_ptr[-1] >= 0 || id_ptr == g_moby_l07_group_lists[state->ids[state->idx]]);
                 id_ptr++) {
                member = g_moby_l07_array[0] + ((*id_ptr & 0x7FFF) << 8);
                if (member == 0)
                    break;
                if (*(unsigned char *)(member + 0x20) != 0xFE) {
                    if (*(unsigned char *)(member + 0x20) != 0xFD) {
                        switch (*(short *)(member + 0xAA)) {
                        case 0xD29:
                            PlayMobySound(0, 0, moby);
                            entity_launch_member_a_pal(member, buf, member + 0x10, moby, state->f110);
                            break;
                        case 0xD2A:
                            PlayMobySound(0, 0, moby);
                            entity_launch_member_b_pal(member, buf, member + 0x10, moby, state->f110);
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
    SteerTowardTarget_pal(moby);
    ApproachValue(&state->f114, 0.20000002f, 0.0012f);
    state->f118 += state->f114;
    if (30.0f < state->f118) {
        if (*(unsigned char *)(moby + 0x31) == 0) {
            moby_mark_spawned((int)moby);
            return;
        }
    }
}
tail:
    if (*(unsigned char *)(moby + 0x20) < 2)
        return;
    if (state->f110 != 0)
        return;
    {
        char buf2[16];
        int slot_id;
        float strength;

        slot_id = part_find_owned_effect_slot(moby, 0x10000, 0);
        strength = moby_update_aim_target_strength_pal(moby, slot_id);
        ApproachValue(&state->f20, 0.0f, strength);
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        if (state->f20 == 0.0f) {
            part_spawn_masked_debris_pal(moby, 0x7F7, state->b60, 0xFF, 5.0f, 10.0f, 5.0f, 10.0f);
            FastVecSub(buf2, g_hero_position_block, moby + 0x10);
            vec_scale_to_length(buf2, buf2, 1.0f);
            part_spawn_blast_effect_moby_pal(moby, moby + 0x10, buf2, 0.0f);
            PlayMobySound(2, 0, moby);
            moby_mark_spawned((int)moby);
        }
    }
}
