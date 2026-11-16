#include "include_asm.h"
#include "names.h"

/* Level 23 globals the retail code reaches through $gp. */
extern char *g_mothership_boss_moby __attribute__((sda));

extern int g_boss_part_was_active __attribute__((sda));

extern int g_mothership_scan_slots __attribute__((sda));

extern int g_beam_frame_count __attribute__((sda));

extern int g_mothership_fade_scale __attribute__((sda));

extern int g_mothership_clear_red __attribute__((sda));

extern int g_mothership_clear_green __attribute__((sda));

extern int g_mothership_clear_blue __attribute__((sda));

extern int g_energy_barrier_timer;

extern int g_mothership_slot_count;

extern int PlayMobySound(int index, int a1, char *a2);

extern void gfx_set_clear_color_packet(int, int, int, int);

extern int g_charged_l23_blast_timer __attribute__((sda));

extern int g_charged_blast_timer_max __attribute__((sda));

extern float g_boss_timer_value __attribute__((sda));

extern void func_31A108(int);

extern void mothership_release_effect_handles(char *);

extern void snd_stop_both_looping(void);

/* Reports whether a word of the object reached through the pointer global is set. */
/* Says whether the boss has its "held" flag set. */
int mothership_is_held(void) {
    return *(int *)(*(char **)(g_mothership_boss_moby + 0x68) + 0x604) != 0;
}

extern void AttachManipulator(char *, int, char *);

extern void build_axis_rotation_quaternion(void *, int, float);

extern float fast_subtract_rotations(float, float);

extern float g_joint_turn_speed_a __attribute__((sda));

extern float g_joint_turn_speed_b __attribute__((sda));

/* Relatches the two measured pairs at +0x580 and +0x584 from the two float arguments. */
/* Turns two boss joints a little each frame, starting their effects first if needed. */
void mothership_turn_joints(char *moby, float deltaA, float deltaB) {
    char *vars = *(char **)(g_mothership_boss_moby + 0x68);

    if (*(unsigned char *)(vars + 0x4F1) == 0)
        AttachManipulator(moby, 0x28, vars + 0x4F0);
    build_axis_rotation_quaternion(vars + 0x500, 0, *(float *)(vars + 0x580));
    *(float *)(vars + 0x580) = fast_subtract_rotations(*(float *)(vars + 0x580), deltaA * g_joint_turn_speed_a * 0.00029088825f);
    if (*(unsigned char *)(vars + 0x531) == 0)
        AttachManipulator(moby, 0x29, vars + 0x530);
    build_axis_rotation_quaternion(vars + 0x540, 0, *(float *)(vars + 0x584));
    *(float *)(vars + 0x584) = fast_subtract_rotations(*(float *)(vars + 0x584), deltaB * g_joint_turn_speed_b * 0.00029088825f);
}

typedef int TI128 __attribute__((mode(TI)));

extern void matrix_mul_vec3(char *, char *, char *);

extern void FastVecAdd(char *, char *, char *);

extern char *SpawnExplosion(char *, int, int, int, int, int, int, int, float, float, int, int, int, int);

extern char g_hero_state[];

/* Builds the measured vector when the state's first word names the argument, and lays out the call. */
/* Spawns hit sparks on the thing that was hit (more if it is the hero) and plays a sound unless it is a shield. */
void part_l23_spawn_hit_sparks(char *hitMoby) {
    union {
        TI128 q;
        float f[4];
    } hitOffset;
    char *heroBase = g_hero_state;

    if (*(char **)(heroBase + 0x2290) == hitMoby) {
        hitOffset.q = 0;
        hitOffset.f[0] = 1.3f;
        hitOffset.f[2] = 4.5f;
        hitOffset.f[3] = 1.0f;
        matrix_mul_vec3((char *)&hitOffset, (char *)&hitOffset, hitMoby + 0xC0);
        FastVecAdd((char *)&hitOffset, (char *)&hitOffset, heroBase + 0x80);
        SpawnExplosion((char *)&hitOffset, 0, 10, 10, 10, 25, 30, 0, 3.0f, 20.0f, 0, 1, 0, 0);
    } else {
        SpawnExplosion(hitMoby + 0x10, 0, 25, 20, 20, 15, 25, 1, 1.5f, 20.0f, 0, 0, 0, 0);
    }
    if (*(short *)(hitMoby + 0xAA) != 0x118F /* moby class 4495 */)
        PlayMobySound(3, 0, g_mothership_boss_moby);
}

/* Zero unless the counter is positive and below the limit. */
/* Says whether the blast timer is running (above zero and below its limit). */
int mothership_is_blast_timer_running(void) {
    if (g_charged_l23_blast_timer > 0 && g_charged_l23_blast_timer < g_charged_blast_timer_max)
        return 1;
    return 0;
}

/* One for the two measured state bytes, zero otherwise. */
/* Says whether the boss is in one of its two attack states. */
int mothership_is_attack_state(void) {
    unsigned char mobyState = *(unsigned char *)(g_mothership_boss_moby + 0x20);

    if (mobyState == 0x10 || mobyState == 0xC)
        return 1;
    return 0;
}



/* Stores one in the state at +0x68, after the measured shared call. */
/* Marks the boss as held and plays its sound the first time. */
void mothership_mark_held(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    if (g_boss_part_was_active == 0 && g_mothership_boss_moby != 0)
        PlayMobySound(0x10, 0, g_mothership_boss_moby);
    *(int *)(vars + 0x604) = 1;
}

/* Clears the measured slot of the four state pointers and of the argument state. */
/* Turns off the extra object flags on all the boss parts so they stop reacting. */
void mothership_disable_part_flags(char *moby) {
    char *state = *(char **)(g_mothership_boss_moby + 0x68);
    int *slot;
    int i;

    slot = *(int **)(state + 0x610);
    if (slot != 0)
        *(int *)((char *)slot + 0x98) = 0;
    slot = *(int **)(state + 0x614);
    if (slot != 0)
        *(int *)((char *)slot + 0x98) = 0;
    slot = (int *)(state + 0x358);
    for (i = 4; i >= 0; i--) {
        if (*slot != 0)
            *(int *)(*slot + 0x98) = 0;
        slot++;
    }
    *(int *)(moby + 0x98) = 0;
}

extern int g_mothership_beam_light __attribute__((sda));

extern float g_mothership_beam_param_a __attribute__((sda));

extern float g_mothership_beam_param_b __attribute__((sda));

extern float g_mothership_beam_param_c __attribute__((sda));

extern float g_mothership_beam_effect_size __attribute__((sda));

extern void gfx_free_point_light(int);

extern char g_hero_position[];

extern void FastVecAdd(char *, char *, char *);

extern void FastVecScale(char *, char *, float);

extern float math_random_float_range(float, float);

extern int part_l00_alloc_effect_slot_2(char *, float, float, float, float, float);

extern void mothership_project_point_onto_surface(char *, float);

extern void mothership_apply_fade_ratio(void);

extern void gfx_register_final_draw_callback(void (*)(void), int);

/* Releases the held handle, makes a new one from jittered values when the difference has low bits set, then registers the callback. */
/* Replaces the running beam effect with a new one with slightly random settings and hooks up its per-frame callback. */
void mothership_restart_beam_effect(char *moby) {
    char offset[16];
    int frameDiff;
    float jitter;
    float valueA;
    float valueB;
    float valueC;

    frameDiff = g_beam_frame_count - g_energy_barrier_timer;
    if (g_mothership_beam_light != -1)
        gfx_free_point_light(g_mothership_beam_light);
    if ((frameDiff & 3) != 0) {
        FastVecAdd(offset, moby + 0x10, g_hero_position);
        FastVecScale(offset, offset, 0.5f);
        mothership_project_point_onto_surface(offset, 5.0f);
        jitter = math_random_float_range(0.0f, g_mothership_beam_param_a * 0.33333334f);
        valueA = g_mothership_beam_param_a + jitter;
        jitter = math_random_float_range(0.0f, g_mothership_beam_param_b * 0.33333334f);
        valueB = g_mothership_beam_param_b + jitter;
        jitter = math_random_float_range(0.0f, g_mothership_beam_param_c * 0.33333334f);
        valueC = g_mothership_beam_param_c + jitter;
        g_mothership_beam_light = part_l00_alloc_effect_slot_2(offset, 35.0f, g_mothership_beam_effect_size, valueA, valueB, valueC);
    }
    gfx_register_final_draw_callback(mothership_apply_fade_ratio, (int)moby);
}

/* Calls the measured shared helper with the measured ratio expression. */
/* Passes the current fade amount to the screen effect. */
void mothership_apply_fade_ratio(void) {
    gfx_set_clear_color_packet(g_mothership_clear_red, g_mothership_clear_green, g_mothership_clear_blue,
                  (g_beam_frame_count - g_energy_barrier_timer) * g_mothership_fade_scale / g_beam_frame_count);
}

/* Stores the incoming float in the level global reached through $gp. */
/* Sets the boss timer value used by the attack logic. */
void mothership_set_timer_value(float value) { g_boss_timer_value = value; }

/* Copies the measured word of every live slot into the object the argument names. */
/* Gives all the boss parts their normal object flags back. */
void mothership_restore_part_flags(char *moby) {
    char *state = *(char **)(g_mothership_boss_moby + 0x68);
    char *slot;
    char **p;
    int i;

    slot = *(char **)(state + 0x610);
    if (slot != 0)
        *(int *)(slot + 0x98) = *(int *)(*(char **)(slot + 0x24) + 0x10);
    slot = *(char **)(state + 0x614);
    if (slot != 0)
        *(int *)(slot + 0x98) = *(int *)(*(char **)(slot + 0x24) + 0x10);
    p = (char **)(state + 0x358);
    for (i = 4; i >= 0; i--) {
        if (*p != 0)
            *(int *)(*p + 0x98) = *(int *)(*(char **)(*p + 0x24) + 0x10);
        p++;
    }
    *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
}

/* Releases the three measured handles of the level state. */
/* Frees the boss effect handles when the boss fight ends. */
void mothership_free_effect_handles(void) {
    char *state;

    mothership_release_effect_handles(g_mothership_boss_moby);
    state = *(char **)(g_mothership_boss_moby + 0x68);
    if (*(char **)(state + 0x620) != 0) {
        func_31A108((int)*(char **)(state + 0x620));
        *(char **)(state + 0x620) = 0;
    }
    if (*(char **)(state + 0x624) != 0) {
        snd_stop_both_looping();
        func_31A108((int)*(char **)(state + 0x624));
        *(char **)(state + 0x624) = 0;
    }
    if (*(char **)(state + 0x614) != 0) {
        func_31A108((int)*(char **)(state + 0x614));
        *(char **)(state + 0x614) = 0;
    }
}

/* Zero while the counter is negative. */
/* Says whether the blast timer is negative (cooling down). */
int mothership_is_blast_cooling_down(void) {
    if (g_charged_l23_blast_timer < 0)
        return 1;
    return 0;
}

/* Zero when the value is among the first D_L23_001B38C0 words of the table, else one. */
/* Says whether a value is not yet in the list of used slots. */
int mothership_is_value_not_in_slots(int value) {
    int *table = &g_mothership_scan_slots;
    int i;

    for (i = 0; i < g_mothership_slot_count; i++) {
        if (table[i] == value)
            return 0;
    }
    return 1;
}

extern int g_boss_part_age_counter __attribute__((sda));

extern unsigned char g_game_flag_table[];


extern void level_store_value_pair(int, int);

extern void level_set_dependent_value(void);

/* Releases the five slot objects and the level object, then raises three flags. The flags are
 * written through a pointer set after the calls, as retail's `lui`/`addiu` base with the 0x88 and
 * 0xA1 displacements; written as D_001395B8[0xA1] and [0x88], the high half is hoisted into a
 * saved register (160 bytes). */
/* Removes the boss parts and boss object, then marks the fight as finished. */
void mothership_destroy_parts(void) {
    char **p = (char **)(*(char **)(g_mothership_boss_moby + 0x68) + 0x358);
    unsigned char *flags;
    int i;

    for (i = 4; i >= 0; i--) {
        if (*p != 0) {
            moby_mark_spawned(*p);
            *p = 0;
        }
        p++;
    }
    if (g_mothership_boss_moby != 0) {
        level_store_value_pair(0, 0);
        level_set_dependent_value();
        moby_mark_spawned(g_mothership_boss_moby);
        g_mothership_boss_moby = 0;
    }
    flags = g_game_flag_table;
    g_boss_part_age_counter = 1;
    flags[0xA1] = 1;
    flags[0x88] = 1;
}

/* The state at +0x68 as func_L23_0041BE70 reads it. Indexing the slot array through the
 * struct keeps the base first in the address sum (`addu $v0,$a0,$v0`); pointer arithmetic
 * puts the scaled index first. */
typedef struct Vars_0041BE70 {
    char pad0[0x358];
    char *slot[5];            /* 0x358 */
    char pad1[0x60C - 0x36C];
    int index;                /* 0x60C */
    char *held;               /* 0x610 */
} Vars_0041BE70;

/* A scalar: declared as an array, its address is scheduled differently in the two calls. */
extern int g_boss_effect_position;

extern void part_start_effect_default_table(void *, int, int, void *, float);

/* Attaches the level object, the indexed slot or the held object, with the argument's two
 * words. The two early returns give retail's arm layout: [no held object][slot][held]. */
/* Attaches a hit effect to the boss, one of its parts, or the held object. */
void mothership_attach_hit_effect(char *source) {
    char *state = g_mothership_boss_moby;
    Vars_0041BE70 *vars = *(Vars_0041BE70 **)(state + 0x68);
    int index = vars->index;
    char *p;

    if (index == -1) {
        p = vars->held;
        if (p == 0) {
            part_start_effect_default_table(state, *(int *)(source + 0x20), 0x10000, state + 0x10,
                          *(float *)(source + 0x2C));
            return;
        }
    } else {
        part_start_effect_default_table(vars->slot[index], *(int *)(source + 0x20), 0x10000, &g_boss_effect_position,
                      *(float *)(source + 0x2C));
        return;
    }
    if ((*(unsigned short *)(p + 0x34) | 0x4000) != 0)
        part_start_effect_default_table(p, *(int *)(source + 0x20), 0x10000, &g_boss_effect_position,
                      *(float *)(source + 0x2C));
}

extern float g_ease_angle_start_degrees __attribute__((sda));

extern float g_ease_angle_end_degrees __attribute__((sda));

extern float g_ease_time_scale __attribute__((sda));

/* Returns the new value in $f0. Declared void, the call leaves $f0 free and the measure
 * reloaded right after it takes $f0 where retail has $f1. */
extern float math_step_value_toward_target(float *, float *, float, float, float, float);

extern float math_fabs(float);

/* Springs the first measure toward its target at the three scaled global rates, and latches
 * it once it is within a tenth of the target. */
/* Eases a boss value toward its target, and stops once it is close enough. */
void mothership_ease_value_to_target(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    if (*(int *)(vars + 0x5DC) != 0)
        return;
    math_step_value_toward_target((float *)(vars + 0x5C8), (float *)(vars + 0x5CC), *(float *)(vars + 0x5D0),
                  g_ease_angle_start_degrees * 0.00027777778f, g_ease_angle_end_degrees * 0.00027777778f,
                  g_ease_time_scale * 0.016666668f);
    if (math_fabs(*(float *)(vars + 0x5C8) - *(float *)(vars + 0x5D0)) < 0.1f) {
        *(int *)(vars + 0x5DC) = 1;
        *(int *)(vars + 0x5CC) = 0;
    }
}

extern void moby_mark_spawned(void *);

extern void snd_stop_voice(int);

extern void gfx_free_point_light(int);

extern int g_mothership_barrier_voice __attribute__((sda));

extern short g_mothership_barrier_light __attribute__((sda));

/* the two 8 x 3 handle tables */
extern void *g_mothership_beam_handles[8][3];

extern void *g_mothership_beam_end_handles[8][3];

/* four handles; declared at 8 bytes so this -G8 unit loads its address as the bare
   lui/addiu pair into one register, as retail does (an incomplete or 16-byte array splits it) */
extern void *g_mothership_effect_handles[2];

/* Releases the measured handles, then every object handle of the three tables, and clears them. */
/* Removes all the boss's effect objects and handles, and clears them. */
void mothership_release_effect_handles(char *boss) {
    char *vars = *(char **)(boss + 0x68);
    int i;
    int j;

    if (g_mothership_barrier_voice != -1) {
        snd_stop_voice(g_mothership_barrier_voice);
        g_mothership_barrier_voice = -1;
    }
    if (g_mothership_barrier_light != -1) {
        gfx_free_point_light(g_mothership_barrier_light);
        g_mothership_barrier_light = -1;
    }
    if (*(int *)(vars + 0x5B0) != 0) {
        *(int *)(vars + 0x5C4) = 0;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 3; j++) {
                if (g_mothership_beam_handles[i][j] != 0) {
                    moby_mark_spawned(g_mothership_beam_handles[i][j]);
                    g_mothership_beam_handles[i][j] = 0;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (g_mothership_effect_handles[i] != 0) {
                moby_mark_spawned(g_mothership_effect_handles[i]);
                g_mothership_effect_handles[i] = 0;
            }
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 3; j++) {
                if (g_mothership_beam_end_handles[i][j] != 0) {
                    moby_mark_spawned(g_mothership_beam_end_handles[i][j]);
                    g_mothership_beam_end_handles[i][j] = 0;
                }
            }
        }
        *(int *)(vars + 0x5B0) = 0;
    }
}

/* boot data: a pointer whose byte at +0x43 selects the draw range; nosda keeps its lui/lw pair */
extern unsigned char *g_hero_moby __attribute__((nosda));

extern int g_effect_pools[3][60];

extern int math_random_int_below(int);

extern int part_spawn_effect_in_free_slot(char *, void *, int, int);

/* Draws a row (0, 1 or 2, the last one only when the byte at +0x43 is not 6) and hands the
 * position to func_L23_0041C8C0 with that row. The search for a free slot is retail's: its
 * result is never used. The three cases make cc1 build the decision tree rooted on 1 (with two,
 * it emits a comparison chain from 0). */
/* Picks a random effect row and spawns the effect at the given position. */
void part_spawn_random_row_effect(void *pos, int extra) {
    int row = 0;
    int i;

    switch (math_random_int_below(g_hero_moby[0x43] == 6 ? 2 : 3)) {
    case 0:
        row = 1;
        break;
    case 1:
        row = 2;
        break;
    case 2:
        row = 0;
        break;
    }
    for (i = 0; i < 50; i++) {
        if (g_effect_pools[row][i] == 0)
            break;
        if (i == 49) {
            i = -1;
            break;
        }
    }
    part_spawn_effect_in_free_slot(g_mothership_boss_moby, pos, row, extra);
}
/* The fields of the level state, the object and the hero this function reads. */
typedef struct {
    char pad0[0x408];
    int handle;
    char pad40C[0x588 - 0x40C];
    float limit;
    char pad58C[0x5B8 - 0x58C];
    float dist;
    float range;
    float level;
} C0E8State;

typedef struct {
    char pad0[0x10];
    TI128 pos;
    unsigned char state;
} C0E8Moby;

typedef struct {
    char pad0[0x80];
    float pos[4];
    char pad90[0x1DC - 0x90];
    short busy;
    char pad1DE[0x33C - 0x1DE];
    int armed;
    int charge;
    char pad344[0x34E - 0x344];
    short heat;
} C0E8Hero;

extern int g_charged_blast_saved_value __attribute__((sda));

extern float g_boss_blast_range __attribute__((sda));

extern float g_boss_blast_level_tolerance __attribute__((sda));

extern int g_charged_blast_timer_start __attribute__((sda));

extern int g_charged_blast_fired_flag __attribute__((sda));

extern int g_charged_blast_armed_flag __attribute__((sda));

extern int g_charged_blast_cooldown_frames __attribute__((sda));

extern float g_blast_impulse_length __attribute__((sda));

extern float g_boss_hit_point[4] __attribute__((sda));

extern int g_charged_l23_blast_timer_2;

extern int math_fast_float_d(int *);

extern void FastVecSub(float *, float *, float *);

extern void vec_scale_to_length(float *, float *, float);

extern void cam_play_effect_on_target(void *, int, int, TI128 *, float *, int);

extern void *slot_effect_create(void *, void *, int, int, int, int, int, int, float, int, int, int, int, int);

/* Runs the boss's charged blast: waits for the hero to charge, fires the blast, and pushes the hero back if close. */
void mothership_update_charged_blast(C0E8Moby *boss) {
    C0E8State *state = *(C0E8State **)(g_mothership_boss_moby + 0x68);
    float impulse[4] __attribute__((aligned(16)));
    TI128 spawnPos;

    math_fast_float_d(&g_charged_l23_blast_timer_2);
    if (boss->state == 0x10 && state->dist < g_boss_blast_range && state->level > state->limit &&
        math_fabs(state->level - state->limit) < g_boss_blast_level_tolerance) {
        C0E8Hero *hero = (C0E8Hero *)g_hero_state;

        if (hero->charge >= 11 && g_charged_l23_blast_timer == 0) {
            g_charged_blast_fired_flag = 1;
            g_charged_l23_blast_timer = g_charged_blast_timer_start;
            if (g_charged_blast_armed_flag != 0) {
                g_charged_blast_armed_flag = 0;
                g_charged_l23_blast_timer = g_charged_blast_timer_max;
            }
        }
    }
    if (g_charged_l23_blast_timer > 0) {
        if (g_charged_l23_blast_timer == g_charged_blast_timer_max) {
            if (g_charged_blast_fired_flag != 0)
                g_charged_l23_blast_timer_2 = 0;
            else
                g_charged_l23_blast_timer += 2;
        } else {
            C0E8Hero *hero = (C0E8Hero *)g_hero_state;

            if (hero->heat >= 11)
                g_charged_blast_armed_flag = 1;
        }
    }
    if (g_charged_blast_armed_flag != 0 && g_charged_l23_blast_timer > g_charged_blast_timer_max) {
        C0E8Hero *hero = (C0E8Hero *)g_hero_state;

        if (hero->charge >= 11)
            g_charged_l23_blast_timer = g_charged_blast_timer_max;
    }
    {
        C0E8Hero *hero = (C0E8Hero *)g_hero_state;

        if (hero->charge != 0 && hero->armed == 0)
            g_charged_blast_armed_flag = 0;
    }
    {
        C0E8Hero *hero = (C0E8Hero *)g_hero_state;

        if (hero->charge >= 11 && g_charged_blast_fired_flag == 0 && g_charged_l23_blast_timer > 0 && g_charged_l23_blast_timer <= g_charged_blast_timer_max)
            g_charged_l23_blast_timer = g_charged_blast_timer_max + 5;
    }
    if (g_charged_l23_blast_timer == g_charged_blast_timer_max) {
        PlayMobySound(10, 0, (char *)boss);
        PlayMobySound(0x11, 0, (char *)boss);
    }
    if (g_charged_l23_blast_timer < 0) {
        g_charged_l23_blast_timer++;
        if (g_charged_l23_blast_timer_2 == 0) {
            C0E8Hero *hero = (C0E8Hero *)g_hero_state;

            if (hero->charge != 0 && state->range < 10.0f && state->level > state->limit) {
                FastVecSub(impulse, hero->pos, (float *)&boss->pos);
                vec_scale_to_length(impulse, impulse, 3.0f);
                spawnPos = boss->pos;
                impulse[3] = 5627.9248046875f;
                cam_play_effect_on_target((void *)state->handle, 0x10007, 0x46, &spawnPos, impulse, 0);
                g_charged_l23_blast_timer_2 = g_charged_blast_saved_value;
                SpawnExplosion((char *)g_boss_hit_point, 1, 5, 0x46, 3, 15, 20, 1, 3.0f, 20.0f, 0, 1, 0, 0);
            }
        }
    } else if (g_charged_l23_blast_timer > 0) {
        math_fast_float_d(&g_charged_l23_blast_timer);
        if (g_charged_l23_blast_timer == 0) {
            state->handle = slot_effect_create(&boss->pos, boss, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1.0f, 1, 1, 0, 0, 0x40);
            g_charged_l23_blast_timer = -g_charged_blast_cooldown_frames;
            PlayMobySound(7, 0, (char *)boss);
            PlayMobySound(12, 0, (char *)boss);
            if (state->range < 15.0f && state->level > state->limit) {
                C0E8Hero *hero = (C0E8Hero *)g_hero_state;

                if (hero->busy == 0) {
                    FastVecSub(impulse, hero->pos, (float *)&boss->pos);
                    vec_scale_to_length(impulse, impulse, g_blast_impulse_length);
                    spawnPos = boss->pos;
                    impulse[3] = 5627.9248046875f;
                    cam_play_effect_on_target(boss, 0x10007, 0x46, &spawnPos, impulse, 0);
                    SpawnExplosion((char *)g_boss_hit_point, 1, 5, 0x46, 3, 15, 20, 1, 3.0f, 20.0f, 0, 1, 0, 0);
                }
            }
        }
    }
}
