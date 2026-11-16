#include "common.h"

/* func_L20_0043F318 defined in L20_0043F318-g8.c. */

/* func_L20_0043F460 is defined in L20_0043ECB0-g8.c (it reaches a global through $gp). */

/* func_L20_0043F570 is defined in L20_0043F570-g8.c. */

/* func_L20_0043FC70 is defined in L20_0043F570-g8.c (it reaches data through $gp). */

/* func_L20_0043FFF0 is defined in L20_0043F570-g8.c (it reaches globals through $gp). */

/* func_L20_00440198 is defined in L20_00440198.c (its slot-table and func_002A7750 declarations conflict with this unit's). */

extern char *g_group_l20_id_lists[];

extern int g_group_count __attribute__((sda));

extern unsigned int g_group_l20_member_table __attribute__((sda));

/* Counts the objects of a group whose state byte (object + 0x20) is neither 6 nor negative.
   D_L20_001FBB20 holds a list of 16-bit object ids per group; the low 15 bits of an id index
   the 0x100-byte object records at D_L20_001B2F9C, and the last id of a list has its top bit
   set. The guards on the group and its list come before the walk and again after each record,
   as in func_L20_0039E0A0. The bound D_L20_001B2FB8 does not change in the loop, so cc1 hoists
   its repeated test into a register known to be zero, which the loop still tests (retail's
   `daddu $t0,$zero,$zero` and `bnez $t0`). */
int group_count_active_members(int group) {
    unsigned short *id_list = (unsigned short *)g_group_l20_id_lists[group];
    int count = 0;

    if ((group & 0xFF) == 0xFF) {
        goto end;
    }
    if (g_group_count < group) {
        goto end;
    }
    if (id_list == 0) {
        goto end;
    }
    for (;;) {
        char *object = (char *)g_group_l20_member_table + ((*id_list & 0x7FFF) << 8);

        if (object == 0) {
            goto end;
        }
        if (*(unsigned char *)(object + 0x20) != 6 && *(signed char *)(object + 0x20) >= 0) {
            count++;
        }
        id_list++;
        if ((group & 0xFF) == 0xFF) {
            goto end;
        }
        if (g_group_count < group) {
            goto end;
        }
        if (id_list == 0) {
            goto end;
        }
        if (*(short *)(id_list - 1) >= 0) {
            continue;
        }
        if (id_list == (unsigned short *)g_group_l20_id_lists[group]) {
            continue;
        }
        break;
    }
end:
    return count;
}

extern void moby_set_state(int, int, int);

/* Gets a moby ready for its next state: clears a counter, sets its hit value and flags, then switches to state 6. */
void moby_enter_state_six(char *moby) {
    char *state = *(char **)(moby + 0x68);

    *(unsigned short *)(state + 0x178) = 0;
    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(int *)(moby + 0x98) = 0;
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
    moby_set_state(moby, 6, 3);
}
extern void FastVecAdd(char *, char *, char *);
extern void FastVecScale(char *, char *, float);
extern int coll_sweep_from_object(char *, char *, int, int, float, float, float, int,
                          int);
extern int math_fast_float_d(char *);
extern void moby_mark_spawned(char *);

/* Moves a piece of debris along its speed, pulls it down, draws an effect and removes it when its timer runs out. */
void falling_l20_debris_update(char *moby) {
    char *q = moby + 0x10;
    char *state = *(char **)(moby + 0x68);

    FastVecAdd(q, q, state);
    *(float *)(state + 8) = *(float *)(state + 8) - *(float *)(state + 0x14);
    FastVecScale(state, state, *(float *)(state + 0x10));
    coll_sweep_from_object(*(char **)(moby + 0xB8), q, 0x10001, 0,
                  *(float *)(state + 0x18), 3.0f, 1.0f, 1, 0);
    if (math_fast_float_d(state + 0x1C) != 0) {
        moby_mark_spawned(moby);
    }
}

extern void gfx_set_clear_color_packet(int, int, int, int);

/* Starts a screen-wide effect with fixed settings. */
void gfx_start_screen_effect(void) {
    gfx_set_clear_color_packet(0, 0, 0, 0x80);
}

/* func_L20_00440598 is defined in L20_00440598-g8.c (it reaches data through $gp and needs -frac2-hazard-labels). */

/* func_L20_00441CB8 is defined in L20_00441CB8-g8.c. */

/* func_L20_004421A8 is defined in L20_004421A8-g8.c. */

/* func_L20_004424A0 is defined in L20_004424A0-helpers-g8.c. */
/* func_L20_004424A0 reads four constants through $gp: its near miss is in
   nonmatching/levels/func_L20_004424A0.c and belongs in the -G8 sibling. */

/* func_L20_00442550 is defined in L20_00442550-g8.c. */

extern int coll_sweep_from_object(char *, char *, int, int, float, float, float, int,
                          int);

extern float vec_distance_xy(char *, char *);

extern int moby_step_controller(char *, char *, float);

extern int moby_l01_turn_toward_target(char *, char *);

/* Draws an effect at the moby, then moves it toward a target if it is close enough, or uses the other approach when it is far away. */
void moby_chase_target_update(char *moby, char *target, float speed) {
    char *state = *(char **)(moby + 0x68);

    coll_sweep_from_object(moby, moby + 0x10, 0x04010000, 0,
                  *(float *)(state + 0x50) + 0.5f, 50.0f, 1.0f, 1, 0);
    if (vec_distance_xy(moby + 0x10, target) <= *(float *)(state + 0x84)) {
        moby_step_controller(moby, target, speed);
    } else {
        moby_l01_turn_toward_target(moby, target);
    }
}


/* func_L20_004429F0 is defined in L20_004429F0-g8.c. */

extern int math_random_int_range(int, int);

extern char *yeedil_boss_find_group_target(char *);

extern int math_random_int_below(int);

/* Picks the next behaviour state for an enemy based on what it did last, and remembers the choice. */
void enemy_choose_next_state(char *moby) {
    char *state = *(char **)(moby + 0x68);
    int previous_mode = *(int *)(state + 0x17F4);
    int result;

    if (previous_mode == 2) goto other;
    if (previous_mode >= 3) goto other;
    if (previous_mode != 1) goto other;
    result = yeedil_boss_find_group_target(moby);
    *(int *)(state + 0x17FC) = result;
    if (result == 0) {
        moby_set_state(moby, 0xC, 4);
    } else {
        moby_set_state(moby, 4, 2);
    }
    goto done;
other:
    result = math_random_int_below(2) + 2;
    *(int *)(state + 0x17F8) = result;
    *(int *)(state + 0x1810) = math_random_int_range(0xB4, 0x168);
    moby_set_state(moby, 3, 1);
done:
    *(int *)(state + 0x17F4) = *(unsigned char *)(moby + 0x95);
}

/* func_L20_00442CD8 is defined in L20_00442CD8-g8.c. */

/* func_L20_00442E68 is defined in L20_00442E68-g8.c (it reaches data through $gp). */

extern int moby_is_in_special_class_range(char *);

extern void moby_finish_release_child(char *);

extern void moby_reset_to_idle(char *);

/* Runs the right extra update for a moby depending on what kind of moby it is. */
void moby_run_type_update(char *moby) {
    if (moby_is_in_special_class_range(moby) != 0) {
        moby_finish_release_child(moby);
    } else if (*(short *)(moby + 0xAA) == 0x12D3) {
        moby_reset_to_idle(moby);
    }
}

/* func_L20_00442F80 is defined in L20_00442F80-g8.c. */

/* func_L20_004431E0 is defined in L20_004431E0-g8.c (it reads D_L20_001B2FB8 through $gp and needs -frac2-keep-block-order). */
/* func_L20_004431E0 reads a global through $gp: its near miss is in
   nonmatching/levels/func_L20_004431E0.c and belongs in the -G8 sibling. */

extern unsigned int g_group_l20_member_table __attribute__((sda));
extern int moby_is_first_state(char *);
/* func_L20_004499E8 is defined in L20_004499E8-g8.c. */
extern int func_L20_00449AC8(char *);

extern void func_0039BDF0(char *, char *, int, int);

/* Sets up the linked child moby at the target and returns it, or returns nothing if it is busy. */
char *moby_activate_linked_child(char *moby, char *target) {
    char *state = *(char **)(moby + 0x68);
    unsigned int child_addr = g_group_l20_member_table + (*(int *)(state + 0x238) << 8);

    if (func_L20_00449AC8((char *)child_addr) != 0) {
        moby_start_path_movement((char *)child_addr, moby, target);
        func_0039BDF0((char *)child_addr, (char *)(child_addr + 0x10), 0x168, 0);
        return (char *)child_addr;
    }
    return 0;
}
/* func_L20_004433B0 is defined in L20_004433B0-g8.c (it reaches a global through $gp). */

extern int func_0033E808(char *, int);

extern int func_003BA3F8(char *);

extern int moby_get_targeted_flag(char *);

/* Tells whether a moby is a valid thing for this enemy to target. */
int enemy_is_valid_target(char *moby, char *candidate) {
    char *state = *(char **)(moby + 0x68);
    short class_id;

    if (func_0033E808(candidate + 0x10, *(int *)(state + 0x220)) == 0) {
        goto ret0;
    }
    class_id = *(short *)(candidate + 0xAA);
    if (class_id < 0x1FF) {
        goto ret0;
    }
    if (class_id < 0x201) {
        goto other;
    }
    if (class_id != 0x12D3) {
        goto ret0;
    }
    if (func_L20_00449AC8(candidate) != 0) {
        goto ret0;
    }
    if (moby_get_targeted_flag(candidate) != 0) {
        goto ret0;
    }
    return 1;
other:
    return func_003BA3F8(candidate) == 0;
ret0:
    return 0;
}

/* func_L20_004435A0 is in L20_004435A0-g8.c. */

/* func_L20_00443790 is defined in L20_00443790-helpers-g8.c. */

typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vec4;

extern void matrix_mul_vec3(void *, void *, void *);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);

/* Moves and spins a piece of debris, pulls it down, and removes it when its timer runs out. */
void tumbling_debris_update(char *moby) {
    char *state = *(char **)(moby + 0x68);
    Vec4 v[6];

    FastVecAdd(moby + 0x10, moby + 0x10, state);
    *(float *)(state + 8) = *(float *)(state + 8) - *(float *)(state + 0x20);
    v[2].q = 0;
    v[2].f[2] = 0.5f;
    matrix_mul_vec3(&v[0], &v[2], moby + 0xC0);
    quaternion_to_rotation_basis(state + 0x10, &v[3]);
    multiply_matrix3x3(moby + 0xC0, &v[3], moby + 0xC0);
    matrix_mul_vec3(&v[1], &v[2], moby + 0xC0);
    FastVecSub(&v[2], &v[0], &v[1]);
    FastVecAdd(moby + 0x10, moby + 0x10, (char *)&v[2]);
    if (math_fast_float_d(state + 0x24) != 0) {
        moby_mark_spawned(moby);
    }
}

/* func_L20_00443A10 lives in L20_00443A10-g8.c. */

/* func_L20_00443B60 is defined in L20_00443B60-helpers.c. */

extern void yeedil_boss_compute_shot_launch(char *, char *, char *, float *);
extern u8 *ActivateGroupMemberAt(int, const float *, const float *, float);

/* Finds the group member to activate along the enemy aim and returns it. */
u8 *group_activate_member_along_aim(char *moby) {
    char *state = *(char **)(moby + 0x68);
    TI128 origin;
    TI128 direction;
    float spread;

    spread = 1.0471977f;
    yeedil_boss_compute_shot_launch(moby, (char *)&origin, (char *)&direction, &spread);
    return ActivateGroupMemberAt(*(int *)(state + 0x21C), (float *)&origin, (float *)&direction, spread);
}

extern char *yeedil_projectile_spawn(char *, char *, char *, float, int, float);

/* Fires a new projectile along the enemy aim with a random lifetime. */
char *enemy_fire_projectile_along_aim(char *moby) {
    char *state = *(char **)(moby + 0x68);
    TI128 origin;
    TI128 direction;
    float spread;
    float spread_copy;
    int lifetime;

    spread = 1.0471977f;
    yeedil_boss_compute_shot_launch(moby, (char *)&origin, (char *)&direction, &spread);
    spread_copy = spread;
    lifetime = math_random_int_range(0x12C, 0x258);
    return yeedil_projectile_spawn(moby, (char *)&origin, (char *)&direction, spread_copy, lifetime, (float)*(unsigned char *)(state + 0x36));
}

/* func_L20_00443DF0 is defined in L20_00443DF0.c (it needs -frac2-hazard-labels). */

/* func_L20_00444018 is defined in L20_00444088-g8.c (it needs this unit's -fno-schedule-insns). */

/* func_L20_00444088 is defined in L20_00444088-g8.c (it reaches a global through
   $gp and needs its own -fno-schedule-insns). */


/* func_L20_00444138 is defined in L20_00444138-g8.c (it reads a global through $gp and
   needs its own -mno-split-addresses). */

/* func_L20_004441D8 is defined in L20_004441D8-g8.c (it reaches globals through $gp and
   needs -frac2-sticky-volatile-refs). */

/* func_L20_004448A8 is defined in L20_004448A8-g8.c (it needs the -G8 profile with split addresses). */

extern float mat_fast_helper_a(float, float);

extern float fast_subtract_rotations(float, float);

/* Works out how far an enemy must turn to face a point and stores it, limited to about 60 degrees. */
void enemy_compute_aim_turn_angle(char *moby, float *target_pos) {
    char *state = *(char **)(moby + 0x68);
    float angle;

    angle = mat_fast_helper_a(target_pos[0] - *(float *)(moby + 0x10),
                      target_pos[1] - *(float *)(moby + 0x14));
    angle = fast_subtract_rotations(angle, *(float *)(moby + 0xF8));
    if (angle > 1.0471977f) {
        angle = 1.0471977f;
    } else if (angle < -1.0471977f) {
        angle = -1.0471977f;
    }
    *(float *)(state + 0x2B8) = angle;
}

/* func_L20_00444B48 is defined in L20_00444B48-g8.c. */

extern void gfx_add_draw_callback_third(void (*)(void), int);

/* Puts a moby into state 18 and queues the screen effect. */
void moby_start_screen_effect_state(int moby) {
    moby_set_state(moby, 0x12, -1);
    gfx_add_draw_callback_third(gfx_start_screen_effect, moby);
}

/* func_L20_00444CA8 is defined in L20_00444CA8.c. */

/* func_L20_004450D8 is defined in L20_004450D8-g8.c (it reads a global through $gp). */

/* func_L20_004451C0 is defined in L20_004451C0-g16.c (it reaches two 16-byte vectors through $gp). */

/* The level's own jump table (the label of the data blob at 0x002B5960). */
extern void *jtbl_002B5960[];

extern int flag_set_first_pending(char *);

extern int flag_is_third_pending_set(char *);

extern float math_step_value_toward_target(char *, char *, float, float, float, float);

extern int PlayMobySound(int, int, char *);

extern unsigned char g_moby_group_flags[];
extern int g_current_map_index MACRO_ADDR;

/* The five behaviours the object's state byte selects; the table in the level's data
   holds the address of each. */
/* Updates a platform that rises when a switch is pressed and plays a sound as it starts moving. */
void switch_platform_update(char *moby) {
    static void * volatile tab[] = { &&c0, &&c1, &&c2, &&c3, &&c4 };
    char *state;
    unsigned char sel;

    sel = *(unsigned char *)(moby + 0x20);
    state = *(char **)(moby + 0x68);
    if (sel >= 5) {
        goto end;
    }
    goto *jtbl_002B5960[sel];
c0:
    *(float *)(state + 0x10) = *(float *)(moby + 0x10);
    moby_set_state(moby, 1, -1);
    goto out;
c1:
    if ((g_moby_group_flags[((unsigned char *)moby)[0xB0] + g_current_map_index * 16] & 0x80) == 0) {
        goto end;
    }
    moby_set_state(moby, 2, -1);
    goto out;
c2:
    if (flag_set_first_pending(moby) != 0) {
        *(int *)(state + 0x14) = 0;
        PlayMobySound(0, 0, moby);
    }
    math_step_value_toward_target(moby + 0x10, state + 0x14,
                  *(float *)(state + 0x10) - *(float *)(state + 0x0),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
c3:
    if (flag_is_third_pending_set(moby) == 0) {
        goto end;
    }
    moby_set_state(moby, 4, -1);
    goto out;
c4:
    if (flag_set_first_pending(moby) != 0) {
        PlayMobySound(0, 0, moby);
        *(int *)(state + 0x14) = 0;
    }
    math_step_value_toward_target(moby + 0x10, state + 0x14, *(float *)(state + 0x10),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
end:
out:
    return;
}

/* func_L20_00445890 is defined in L20_00445890-g8.c. */

/* The level's own jump table (the label of the data blob at 0x002B5980). */
extern void *jtbl_002B5980[];

extern int flag_set_first_pending(char *);

extern int flag_is_third_pending_set(char *);

extern float math_step_value_toward_target(char *, char *, float, float, float, float);

extern unsigned char g_moby_group_flags[];

/* The five behaviours the object's state byte selects; the table in the level's data
   holds the address of each. */
/* Updates a platform that rises when a switch is pressed, like the one above but silent. */
void switch_platform_quiet_update(char *moby) {
    static void * volatile tab[] = { &&c0, &&c1, &&c2, &&c3, &&c4 };
    char *state;
    unsigned char sel;

    sel = *(unsigned char *)(moby + 0x20);
    state = *(char **)(moby + 0x68);
    if (sel >= 5) {
        goto end;
    }
    goto *jtbl_002B5980[sel];
c0:
    *(float *)(state + 0x10) = *(float *)(moby + 0x10);
    moby_set_state(moby, 1, -1);
    goto out;
c1:
    if ((g_moby_group_flags[((unsigned char *)moby)[0xB0] + *(int *)0x001A79F0 * 16] & 0x80) == 0) {
        goto end;
    }
    moby_set_state(moby, 2, -1);
    goto out;
c2:
    if (flag_set_first_pending(moby) != 0) {
        *(int *)(state + 0x14) = 0;
    }
    math_step_value_toward_target(moby + 0x10, state + 0x14,
                  *(float *)(state + 0x10) - *(float *)(state + 0x0),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
c3:
    if (flag_is_third_pending_set(moby) == 0) {
        goto end;
    }
    moby_set_state(moby, 4, -1);
    goto out;
c4:
    if (flag_set_first_pending(moby) != 0) {
        *(int *)(state + 0x14) = 0;
    }
    math_step_value_toward_target(moby + 0x10, state + 0x14, *(float *)(state + 0x10),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
end:
out:
    return;
}

extern int hero_is_current_selected_id(char *);
extern float math_fabs(float);
extern int snd_is_voice_playing_for_owner(char *, int);
extern int PlayMobySound(int, int, char *);
extern void snd_stop_voice(int);
extern int moby_is_hit_by_player_or_aim(char *);
extern void mat_combine_and_store(void *, void *, void *, void *);
typedef struct { char pad[0x74]; unsigned char active; char pad2[0x13]; char *owner; } SoundSlot;
extern SoundSlot g_sound_state[];
extern float g_elevator_reference_height;

/* Updates an elevator that slides between two heights with a sound, and carries anything standing on it. */
void elevator_l20_update(char *moby) {
    Vec4 pos, rot, delta;
    char *state = *(char **)(moby + 0x68);
    qcopy(&pos, moby+0x10);
    qcopy(&rot, moby+0xF0);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(int *)(state+0x5C) |= 1;
        {
            float target=*(float *)(state+0x60);
            float start=*(float *)(moby+0x14);
            *(float *)(state+0x6C) = 0.0011666667f;
            *(float *)(state+0x64) = start;
            *(float *)(state+0x70) = (start+target)*0.5f;
        }
        if (*(int *)(state+0x78) == 0) *(int *)(state+0x74)=0;
        else *(int *)(state+0x74)=1;
        moby_set_state(moby,1,-1);
        break;
    case 1:
        if (flag_is_third_pending_set(moby)) {
            if (hero_is_current_selected_id(moby) || (*(float *)(moby+0x14)-*(float *)(state+0x70))*(g_elevator_reference_height-*(float *)(state+0x70)) < 0.0f) {
                if (*(int *)(state+0x74)==0) moby_set_state(moby,2,-1);
                else moby_set_state(moby,3,-1);
                if (!snd_is_voice_playing_for_owner(moby,*(int *)(state+0x7C))) *(int *)(state+0x7C)=PlayMobySound(0,4,moby);
            }
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) *(int *)(state+0x68)=0;
        if (math_fabs(*(float *)(state+0x60)-*(float *)(moby+0x14)) < 0.03f) {
            int slot_index=*(int *)(state+0x7C);
            if (slot_index != -1) {
                SoundSlot *slot=(SoundSlot *)((char *)g_sound_state+slot_index*0x70);
                if (slot->owner==moby && slot->active) snd_stop_voice(slot_index);
            }
            *(int *)(state+0x7C)=-1;
            if (!moby_is_hit_by_player_or_aim(moby)) {
                *(int *)(state+0x74)=1;
                *(float *)(moby+0x14)=*(float *)(state+0x60);
                moby_set_state(moby,1,-1);
            }
        } else math_step_value_toward_target(moby+0x14,state+0x68,*(float *)(state+0x60),*(float *)(state+0x6C),*(float *)(state+0x6C),0.20000002f);
        break;
    case 3:
        if (flag_set_first_pending(moby)) *(int *)(state+0x68)=0;
        if (math_fabs(*(float *)(moby+0x14)-*(float *)(state+0x64)) < 0.03f) {
            int slot_index=*(int *)(state+0x7C);
            if (slot_index != -1) {
                SoundSlot *slot=(SoundSlot *)((char *)g_sound_state+slot_index*0x70);
                if (slot->owner==moby && slot->active) snd_stop_voice(slot_index);
            }
            *(int *)(state+0x7C)=-1;
            if (!moby_is_hit_by_player_or_aim(moby)) {
                *(int *)(state+0x74)=0;
                *(float *)(moby+0x14)=*(float *)(state+0x64);
                moby_set_state(moby,1,-1);
            }
        } else math_step_value_toward_target(moby+0x14,state+0x68,*(float *)(state+0x64),*(float *)(state+0x6C),*(float *)(state+0x6C),0.20000002f);
        break;
    }
    FastVecSub(&delta,moby+0x10,&pos);
    mat_combine_and_store(state+0x20,&delta,&rot,moby+0xF0);
}

extern void moby_set_flag_bit(char *, int);
extern void yeedil_destroy_group_protopets(char *);

/* Updates a platform that rises, waits, drops and waits again in a repeating cycle. */
void cycling_platform_update(char *moby) {
    char *state;
    TI128 pos, rot, delta;
    float accel;

    state = *(char **)(moby + 0x68);
    qcopy(&pos, moby + 0x10);
    qcopy(&rot, moby + 0xF0);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        qcopy(state + 0x60, moby + 0x10);
        *(int *)(state + 0x5C) |= 1;
        moby_set_flag_bit(moby, 1);
        moby_set_state((int)moby, 4, -1);
        break;
    case 1:
        if (flag_set_first_pending(moby) != 0) {
            *(int *)(state + 0x88) = 0;
            *(int *)(state + 0x84) = *(int *)(state + 0x74);
        }
        if (math_fast_float_d(state + 0x84) != 0) {
            moby_set_state((int)moby, 2, -1);
        }
        {
            int duration = *(int *)(state + 0x74);
            float speed = *(float *)(state + 0x70);
            float start = *(float *)(state + 0x68) + speed;
            accel = (speed * 4.0f) / (float)(duration * duration);
            math_step_value_toward_target(moby + 0x18, state + 0x88, start, accel,
                          accel, accel * (float)duration);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby) != 0) {
            *(int *)(state + 0x84) = *(int *)(state + 0x78);
        }
        if (math_fast_float_d(state + 0x84) != 0) {
            moby_set_state((int)moby, 3, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(moby) != 0) {
            *(int *)(state + 0x88) = 0;
            *(int *)(state + 0x84) = *(int *)(state + 0x7C);
        }
        if (math_fast_float_d(state + 0x84) != 0) {
            moby_set_state((int)moby, 4, -1);
        }
        {
            int duration = *(int *)(state + 0x74);
            float speed = *(float *)(state + 0x70);
            float start = *(float *)(state + 0x68);
            accel = (speed * 4.0f) / (float)(duration * duration);
            math_step_value_toward_target(moby + 0x18, state + 0x88, start, accel,
                          accel, accel * (float)duration);
        }
        break;
    case 4:
        if (flag_set_first_pending(moby) != 0) {
            *(int *)(state + 0x84) = *(int *)(state + 0x80);
        }
        if (math_fast_float_d(state + 0x84) != 0) {
            moby_set_state((int)moby, 1, -1);
        }
        break;
    }
    if (flag_is_third_pending_set(moby) == 0) {
        if (0.0f < *(float *)(state + 0x8C)) {
            yeedil_destroy_group_protopets(moby);
            *(float *)(state + 0x8C) = -1000.0f;
        }
    }
    FastVecSub(&delta, moby + 0x10, &pos);
    mat_combine_and_store(state + 0x20, &delta, &rot, moby + 0xF0);
}

/* func_L20_00447640 is defined in L20_00447640-g8.c (it reads D_L20_001B2FB8 through $gp). */

/* func_L20_00447748 is defined in L20_00447748-g8.c. */

extern char g_water_tile_grid[];

extern void render_water_grids();

/* Starts the level effect with a fixed setting. */
void level_start_fixed_effect(void) {
    render_water_grids(g_water_tile_grid, 6);
}

/* func_L20_00447930 is defined in L20_00447930-g8.c (it reaches data through $gp). */

extern float FastAddRotations(float, float);
extern int coll_test_point(char *, int, char *, float);
extern float FastVecDot(char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern float FastVecLength(char *);

extern char g_debris_hit_info[];

/* Moves, spins and bounces a piece of debris off walls, then fades it out and removes it. */
void debris_l20_update(char *moby) {
    char *state = *(char **)(moby + 0x68);
    float velocity_z, speed;
    char bounce[0x10];

    velocity_z = *(float *)(state + 8);
    *(float *)(state + 8) = velocity_z - (velocity_z > 0.0f ? *(float *)(state + 0x20) * 4.0f : *(float *)(state + 0x20));

    FastVecAdd(moby + 0x10, moby + 0x10, state);
    *(float *)(moby + 0xF0) = FastAddRotations(*(float *)(moby + 0xF0), *(float *)(state + 0x10));
    *(float *)(moby + 0xF4) = FastAddRotations(*(float *)(moby + 0xF4), *(float *)(state + 0x14));
    *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(moby + 0xF8), *(float *)(state + 0x18));

    if (coll_test_point(moby + 0x10, 0, moby, 1.5f) != 0) {
        char *hit_info = g_debris_hit_info;

        qcopy(moby + 0x10, hit_info);
        if (FastVecDot(state, hit_info + 0x10) < 0.0f) {
            vec_scale_to_length(hit_info + 0x10, hit_info + 0x10, 1.0f);
            speed = FastVecLength(state);
            FastVecScale(bounce, hit_info + 0x10, -FastVecDot(state, hit_info + 0x10) * 1.25f);
            FastVecAdd(state, state, bounce);
            vec_scale_to_length(state, state, speed * 0.5f);
        }
        *(int *)(state + 0x24) = 0;
        if ((unsigned char)moby[0x23] > 0x60) {
            moby[0x23] = 0x60;
        }
    }

    if (math_fast_float_d(state + 0x24) != 0) {
        if ((unsigned char)moby[0x23] < 5) {
            moby_mark_spawned(moby);
        } else {
            moby[0x23] = moby[0x23] - 4;
        }
    }
}

/* func_L20_00448A18 is defined in L20_00448A18-helpers-g8.c. */
/* func_L20_00448A18 reaches four globals through $gp: its near miss is in
   nonmatching/levels/func_L20_00448A18.c and belongs in the -G8 sibling. */
