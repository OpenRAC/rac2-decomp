#include "names.h"
/* func_PAL_L08_00428EA8, the PAL copy of func_L08_00423970: the same C, where the func_002A7820 timers take
   the 50 Hz scale except the first, the frame limits become 200, 100 and 300, and the rise and fall rates
   become 0.010000001f, 0.006f, 0.6f and 0.00392f. */
#include "common.h"

#define FIELD(base, type, offset) (*(type *)((base) + (offset)))

extern float math_fabs(float);
extern float moby_get_anim_value(void *);
extern int flag_set_first_pending(void *);
extern int PlayMobySound(int, int, void *);
extern float math_step_value_toward_target(void *, float, void *, float, float, float);
extern void part_spawn_dust_burst(void *, void *, int, float, float, float, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern int coll_test_point(void *, float, int, void *);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float IntToFloat(int);
extern float math_wrap_angle_to_pi(float);
extern void sandfly_pick_flight_target(void *);
extern int sandfly_move_toward_target(void *, float, float, float, float, float, float, float, float);
extern void sandfly_pick_random_target(void *);
extern float vec_distance_xy(void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern int coll_sweep_from_object(void *, void *, float, float, float, int, int, int, int);
extern void snd_stop_queued(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void part_spawn_ground_sparkles(void *);
extern void part_l08_spawn_spark_shower(void *, void *);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void SetDeathBits(void *, int, int);
extern char *g_hero_moby_target NOT_SDA;
extern int g_frame_l08_counter MACRO_ADDR;
extern struct { char pad[0x2294]; int state; int pad2298; int secondaryState; } g_hero_state;
extern char g_str_effect_name[] __attribute__((sda));
extern struct { char pad[0x464]; u8 flags[0]; } g_moby_spawn_state_flags_a;
extern unsigned char g_moby_state_flags[] __attribute__((sda));
extern unsigned char g_moby_group_flags[];
extern s32 g_moby_array __attribute__((sda));
typedef struct {
    int state;
    char pad04[8];
    int mode;
    char pad10[0x18];
    float height;
    char pad2C[0xC];
    float secondHeight;
} HeightGate;
extern HeightGate g_init_context;
extern struct { char pad[0x464]; u8 flags[0]; } g_moby_spawn_state_flags_b;
extern unsigned char g_moby_nibble_table[];

extern int g_current_map_index MACRO_ADDR;
extern void sandfly_check_hit(char *);
extern void sandfly_init(char *);
extern void sandfly_tick_timers(char *);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern int SelectNearestListedMoby(char *, char *, float, float, int, int, int, int);
extern int moby_l08_is_linked_running_2(int);
extern int moby_l08_is_linked_gone_4(int);
extern int moby_l08_is_linked_gone_3(int);
extern int moby_l08_is_linked_running_or_gone_2(int);
extern void STUB_printf(char *, int, int);
extern char g_str_sandfly_debug[];
extern int FastDecTimer(short *);
extern void anim_start_blended(char *, int, int, int);
extern void moby_set_state(char *, int, int);
extern void moby_mark_spawned(char *);

/* Apply the height gates, dispatch the actor state, and update timers and bounds. */
/* Sandfly update: applies the height gates, dispatches on its state and updates timers and bounds (PAL version). */
/* Sandfly update: applies the height gates, dispatches on its state and updates timers and bounds (PAL version). */
void sandfly_update_pal(char *actor) {
    char *vars;
    int ready;
    int condition;
    float local[4];
    float z;
    int mode = g_init_context.mode;
    if (mode != 0) {
        float height = *(float *)(actor + 0x18);
        if (height < g_init_context.height && g_init_context.state == 1) return;
        if (g_init_context.height < height && g_init_context.state == 0) return;
        if (mode == 2) {
            if (g_init_context.secondHeight < height && g_init_context.state == 1) return;
            if (height < g_init_context.secondHeight && g_init_context.state == mode) return;
        }
    }
    vars = *(char **)(actor + 0x68);
    sandfly_check_hit(actor);
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0: {
        int id = *(int *)(vars + 0x184);
        if (id != -1) {
            char *other = (char *)g_moby_array + (id << 8);
            if (*(unsigned char *)(other + 0xB0) != 255) {
                unsigned short tag = *(unsigned short *)(other + 0xB2);
                if (g_moby_spawn_state_flags_b.flags[(short)tag] ||
                    ((g_moby_nibble_table[((short)tag >> 1) + (g_current_map_index << 10)] >> ((tag & 1) ? 4 : 0)) & 7)) {
                    unsigned short ownTag = *(unsigned short *)(actor + 0xB2);
                    if ((g_moby_nibble_table[((short)ownTag >> 1) + (g_current_map_index << 10)] >> ((ownTag & 1) ? 4 : 0)) & 7) goto destroy;
                }
            }
        }
        sandfly_init(actor);
        break;
    }
    case 1:
        ready = 0;
        switch (*(unsigned char *)(vars + 0x18B)) {
        case 0:
            if (!math_random_int_below(7)) {
                /* Result 2 is false; normalize this with the other nonzero triggers. */
                condition = SelectNearestListedMoby(actor, vars + 0x100,
                    (float)*(unsigned char *)(vars + 0x18D), 0.0f,
                    *(int *)(vars + 0x190), *(int *)(vars + 0x198),
                    *(int *)(vars + 0x194), -1) ^ 2;
                goto normalize;
            }
            break;
        case 1:
            if (*(int *)(vars + 0x180) != -1) ready = moby_l08_is_linked_running_2(*(int *)(vars + 0x180)) != 0;
            else {
                STUB_printf(g_str_sandfly_debug, *(short *)(actor + 0xAA), *(short *)(actor + 0xB2));
                *(unsigned char *)(vars + 0x18B) = 0;
            }
            break;
        case 2: condition = *(u8 *)(actor + 0xBC); goto normalize;
        case 3: ready = moby_l08_is_linked_gone_4(*(int *)(vars + 0x1AC)) != 0; break;
        case 4: ready = moby_l08_is_linked_gone_3(*(int *)(vars + 0x180)) != 0; break;
        case 5:
            condition = moby_l08_is_linked_running_or_gone_2(*(int *)(vars + 0x184));
normalize:
            ready = condition != 0;
            break;
        }
        if (*(unsigned char *)(actor + 0xBC) & 2) ready = 1;
        if (ready) {
            *(unsigned char *)(actor + 0x30) = *(unsigned char *)(vars + 0x188);
            qzero(vars + 0x170);
            *(short *)(vars + 0x1B8) = math_random_int_range(0, 180);
            moby_set_state(actor, 3, -1);
        }
        break;
    case 3:
        if (FastDecTimer((short *)(vars + 0x1B8))) {
            if (*(unsigned char *)(actor + 0x43)) anim_start_blended(actor, 0, 0, 10);
            *(unsigned char *)(actor + 0x31) = 1;
            *(unsigned short *)(actor + 0x34) &= 0xFFFE;
            moby_set_state(actor, 2, 0);
        }
        break;
    case 2:
        z = FIELD(actor, float, 0x18);
        switch (FIELD(actor, u8, 0x95)) {
        case 0: z = FIELD(vars, float, 0x1B4); break;
        case 1: z = FIELD(vars, float, 0x1B0) - 1.7f; break;
        }
        if (flag_set_first_pending(actor)) PlayMobySound(4, 0, actor);
        math_step_value_toward_target(actor + 0x18, z, vars + 0x178,
                       0.010000001f, 0.006f, 0.6f);
        if (moby_get_anim_value(actor) < 12.0f) {
            qcopy(local, actor + 0x10);
            local[2] = FIELD(vars, float, 0x1B0);
            part_spawn_dust_burst(actor, local, 3, 1.0f, 1.5f, 0.5f, 0.0f, 0.1f, 0.8f);
        }
        if (math_fabs(FIELD(actor, float, 0x18) - z) < 0.2f) {
            switch (FIELD(actor, u8, 0x95)) {
            case 0:
                FIELD(actor, u16, 0x34) |= 0x1000;
                if (FIELD(actor, u8, 0x43) != 3) anim_start_blended(actor, 3, 0, 3);
                FIELD(vars, s16, 0x1B8) = ((s32)(math_random_int_range(180, 360)) * 5 + 2) / 6;
                moby_set_state(actor, 5, -1);
                break;
            case 1:
                FIELD(actor, u16, 0x34) &= 0xEFFF;
                if (FIELD(actor, u8, 0x43) != 1) anim_start_blended(actor, 1, 0, 3);
                FIELD(vars, s16, 0x1B8) = 0;
                FIELD(actor, u8, 0x31) = 0;
                FIELD(actor, u16, 0x34) |= 1;
                moby_set_state(actor, 1, -1);
                break;
            }
        }
        break;
    case 4:
        FastVecAdd(actor + 0x10, actor + 0x10, vars + 0x170);
        FIELD(vars, float, 0x178) -= 0.00392f;
        FIELD(actor, float, 0x18) += 0.75f;
        if (coll_test_point(actor + 0x10, 0.75f, 0, actor)) {
            if (g_hero_moby_target == 0 || FIELD(g_hero_moby_target, s16, 0xAA) != 0x945) {
                if (FIELD(actor, u8, 0x43) != 3) anim_start_blended(actor, 3, 0, 3);
                FIELD(vars, s16, 0x1B8) = ((s32)(math_random_int_range(180, 360)) * 5 + 2) / 6;
                moby_set_state(actor, 5, -1);
            }
        }
        if (FIELD(vars, float, 0x178) < 0 || FIELD(actor, u16, 0x96) > 200) {
            if (FIELD(actor, u8, 0x43) != 3) anim_start_blended(actor, 3, 0, 3);
            FIELD(vars, s16, 0x1B8) = ((s32)(math_random_int_range(180, 360)) * 5 + 2) / 6;
            moby_set_state(actor, 5, -1);
        }
        FIELD(actor, float, 0x18) -= 0.75f;
        FIELD(vars, float, 0x178) -= 0.00392f;
        if (FIELD(actor, float, 0x18) < FIELD(vars, float, 0x1B0))
            FIELD(actor, float, 0x18) = FIELD(vars, float, 0x1B0);
        break;
    case 5: {
        float angle = FIELD(vars, float, 0x16C);
        float phase;
        if (FIELD(actor, u16, 0x96) == 0 || g_frame_l08_counter % 50 == FIELD(actor, s16, 0xB2) % 50) {
            if (angle > 0.0f) angle = math_random_float_range(0.2f, 0.5f) * -1.5707963705062866f;
            else angle = math_random_float_range(0.2f, 0.5f) * 1.5707963705062866f;
        }
        FIELD(vars, float, 0x160) = math_fast_sin_or_cos_a(FastAddRotations(FIELD(actor, float, 0xF8), angle)) * 2.0f;
        FIELD(vars, float, 0x164) = math_fast_sin_or_cos_b(FastAddRotations(FIELD(actor, float, 0xF8), angle)) * 2.0f;
        FIELD(vars, s32, 0x168) = 0;
        FastVecAdd(vars + 0x160, vars + 0x160, actor + 0x10);
        phase = math_wrap_angle_to_pi(IntToFloat(g_frame_l08_counter) * 0.025f);
        sandfly_pick_flight_target(actor);
        if (sandfly_move_toward_target(actor, 360.0f, 180.0f, 560.0f, 20.0f, 0.0f, 16.0f,
                              FIELD(vars, float, 0x15C) + 1.7f + 1.0f + math_fast_sin_or_cos_b(phase), -2.0f))
            angle *= 1.025f;
        FIELD(vars, float, 0x16C) = angle;
        if (FIELD(vars, s16, 0x1B8) == 0) {
            if (FIELD(actor, u8, 0x43) != 1) anim_start_blended(actor, 1, 0, 3);
            moby_set_state(actor, 6, 0);
        }
        break;
    }
    case 6:
        switch (FIELD(actor, u8, 0x95)) {
        case 0:
            if (FIELD(vars, s16, 0x1B8) == 0) {
                FIELD(vars, s16, 0x1B8) = ((s32)(math_random_int_range(30, 90)) * 5 + 2) / 6;
                if (FIELD(vars, s16, 0x1B8) >= 7 && FIELD(actor, u8, 0x43) != 3)
                    anim_start_blended(actor, 3, 0, 3);
                moby_set_state(actor, 6, 1);
            }
            break;
        case 1:
            sandfly_move_toward_target(actor, 120.0f, 360.0f, 120.0f, 30.0f, 0.0f, 8.0f,
                              FIELD(vars, float, 0x15C) + 1.7f, 1.0f);
            if (FIELD(vars, s16, 0x1B8) == 0) {
                sandfly_pick_random_target(actor);
                FIELD(vars, s16, 0x1B8) = ((s32)(math_random_int_range(0, 0)) * 5 + 2) / 6;
                if (FIELD(vars, s16, 0x1B8) >= 7 && FIELD(actor, u8, 0x43) != 1)
                    anim_start_blended(actor, 1, 0, 3);
                moby_set_state(actor, 6, 0);
            }
            break;
        case 2:
            qcopy(vars + 0x160, vars + 0x150);
            if (sandfly_move_toward_target(actor, 120.0f, 360.0f, 120.0f, 30.0f, 0.0f, 8.0f,
                                  FIELD(vars, float, 0x15C) + 1.7f, 1.0f) & 8) {
                if (FIELD(actor, u8, 0x43) != 2) anim_start_blended(actor, 2, 0, 10);
                moby_set_state(actor, 2, 1);
            }
            break;
        }
        if (SelectNearestListedMoby(actor, vars + 0x100, (float)FIELD(actor, s16, 0x32), 0.0f,
                             FIELD(vars, int, 0x19C), FIELD(vars, int, 0x1A4), FIELD(vars, int, 0x1A0), -1) != 2) {
            if (!math_random_int_below(9)) {
                FIELD(vars, s16, 0x1BA) = ((s32)(math_random_int_range(300, 360)) * 5 + 2) / 6;
                moby_set_state(actor, 7, 0);
            }
        } else if (FIELD(actor, u8, 0x20) == 6 && FIELD(vars, u8, 0x18A) == 0) {
            moby_set_state(actor, 6, 2);
        }
        break;
    case 7:
        switch (FIELD(actor, u8, 0x95)) {
        case 0:
            if (FIELD(vars, s16, 0x1B8) == 0) {
                FIELD(vars, s16, 0x1B8) = ((s32)(math_random_int_range(30, 90)) * 5 + 2) / 6;
                if (FIELD(vars, s16, 0x1B8) >= 7 && FIELD(actor, u8, 0x43) != 3)
                    anim_start_blended(actor, 3, 0, 3);
                moby_set_state(actor, 7, 1);
            }
            break;
        case 1:
            if (sandfly_move_toward_target(actor, 250.0f, 180.0f, 250.0f, 32.0f, 0.1f, 13.0f,
                                  FIELD(vars, float, 0x15C) + 1.7f, 1.0f) & 8)
                FIELD(vars, s16, 0x1B8) = 0;
            if (FIELD(vars, s16, 0x1B8) == 0) {
                sandfly_pick_random_target(actor);
                FIELD(vars, s16, 0x1B8) = ((s32)(math_random_int_range(0, 0)) * 5 + 2) / 6;
                if (FIELD(vars, s16, 0x1B8) >= 7 && FIELD(actor, u8, 0x43) != 1)
                    anim_start_blended(actor, 1, 0, 3);
                moby_set_state(actor, 7, 0);
            }
            break;
        }
        if (SelectNearestListedMoby(actor, vars + 0x100, (float)FIELD(actor, s16, 0x32), (float)FIELD(vars, u8, 0x18D),
                             FIELD(vars, int, 0x19C), FIELD(vars, int, 0x1A4), FIELD(vars, int, 0x1A0), -1) == 2 ||
            g_hero_state.state == 0x31 || g_hero_state.secondaryState == 0x11 ||
            g_hero_state.secondaryState == 0x12) {
            FIELD(vars, int, 0x144) = 2;
            if (FIELD(vars, s16, 0x1BA) == 0) moby_set_state(actor, 6, 0);
        } else if (**(int **)(vars + 0x1CC) < 3 && FIELD(vars, s16, 0x1BC) == 0 &&
                    vec_distance_xy(actor + 0x10, vars + 0x120) < 12.0f) {
            FIELD(vars, u8, 0x18C) = 1;
            qcopy(vars + 0x160, vars + 0x120);
            moby_set_state(actor, 8, 0);
            ++**(int **)(vars + 0x1CC);
        }
        break;
    case 8: {
        qcopy(vars + 0x160, vars + 0x120);
        switch (FIELD(actor, u8, 0x95)) {
        case 0:
            sandfly_move_toward_target(actor, 260.0f, 180.0f, 270.0f, 32.0f, 0.15f, 8.0f, 0.4f, 0.5f);
            if (vec_distance_xy(actor + 0x10, vars + 0x120) < 1.5f &&
                math_fabs(FIELD(actor, float, 0x18) - FIELD(vars, float, 0x128)) < 1.1f) {
                if (FIELD(actor, u8, 0x43) != 4) anim_start_blended(actor, 4, 0, 3);
                moby_set_state(actor, 8, 1);
            }
            break;
        case 1:
            sandfly_move_toward_target(actor, 260.0f, 180.0f, 270.0f, 32.0f, 0.15f, 8.0f, 0.3f, 0.5f);
            moby_set_state(actor, 8, 2);
            break;
        case 2:
            if (FIELD(actor, u8, 0x42) == 4) {
                if (moby_get_anim_value(actor) > 19.5f && moby_get_anim_value(actor) < 29.0f) {
                    moby_transform_joint_to_world(actor, 1, local);
                    coll_sweep_from_object(actor, local, 0.5f, (float)FIELD(vars, u8, 0x34), 1.0f, 1, 0, 1, 0);
                }
                if (FIELD(actor, u8, 0x60) & 2) {
                    FIELD(vars, s16, 0x1B8) = 100;
                    FIELD(vars, s16, 0x1BC) = ((s32)(math_random_int_range(180, 260)) * 5 + 2) / 6;
                    if (FIELD(actor, u8, 0x43) != 1) anim_start_blended(actor, 1, 0, 3);
                    moby_set_state(actor, 8, 3);
                }
            }
            break;
        case 3:
            sandfly_move_toward_target(actor, 260.0f, 180.0f, 270.0f, 32.0f, 0.15f, 8.0f, 0.3f, 0.5f);
            if (FastDecTimer((s16 *)(vars + 0x1B8))) {
                if (vec_distance_xy(actor + 0x10, vars + 0x120) < 1.5f &&
                    math_fabs(FIELD(actor, float, 0x18) - FIELD(vars, float, 0x128)) < 1.1f) {
                    if (FIELD(actor, u8, 0x43) != 4) anim_start_blended(actor, 4, 0, 3);
                    moby_set_state(actor, 8, 1);
                } else {
                    qcopy(vars + 0x160, vars + 0x120);
                    moby_set_state(actor, 8, 0);
                }
            }
            break;
        }
        if (SelectNearestListedMoby(actor, vars + 0x100, (float)FIELD(actor, s16, 0x32), (float)FIELD(vars, u8, 0x18D),
                             FIELD(vars, int, 0x19C), FIELD(vars, int, 0x1A4), FIELD(vars, int, 0x1A0), -1) == 2 ||
            g_hero_state.state == 0x31 || g_hero_state.secondaryState == 0x11 ||
            g_hero_state.secondaryState == 0x12) {
            snd_stop_queued(actor);
            if (FIELD(vars, s16, 0x1BA) != 0) {
                FIELD(vars, s16, 0x1B8) = 0;
                if (FIELD(actor, u8, 0x43) != 3) anim_start_blended(actor, 3, 0, 3);
                moby_set_state(actor, 6, 0);
            } else {
                FastVecSub(vars + 0x160, actor + 0x10, vars + 0x160);
                FastVecAdd(vars + 0x160, vars + 0x160, actor + 0x10);
                vec_scale_to_length(vars + 0x160, vars + 0x160, 5.0f);
                sandfly_pick_flight_target(actor);
                sandfly_move_toward_target(actor, 260.0f, 180.0f, 270.0f, 32.0f, 0.15f, 8.0f, 0.3f, 0.5f);
                FIELD(vars, s16, 0x1B8) = 0;
                if (FIELD(actor, u8, 0x43) != 3) anim_start_blended(actor, 3, 0, 3);
                FIELD(vars, s16, 0x1BC) = ((s32)(math_random_int_range(180, 260)) * 5 + 2) / 6;
                moby_set_state(actor, 7, 0);
            }
        }
        break;
    }
    case 9: {
        int result;
        ++FIELD(vars, u16, 0x1BE);
        if (flag_set_first_pending(actor)) PlayMobySound(0, 0, actor);
        result = moby_dispatch_action_by_kind(actor, vars + 0x50);
        if (result & 1) {
            moby_set_state(actor, 10, -1);
        } else if ((result & 2) || FIELD(vars, s16, 0x1BE) > 300) {
            FIELD(vars, u8, 0x6A) = 2;
            if (FIELD(actor, u8, 0x43) != 1) anim_start_blended(actor, 1, 0, 3);
            FIELD(vars, s16, 0x1BE) = 0;
            qzero(vars + 0x170);
            if (FIELD(vars, float, 0x20) <= 0.0f) moby_set_state(actor, 10, -1);
            else moby_set_state(actor, 7, 0);
        }
        break;
    }
    case 10: {
        u16 tag;
        int kind;
        u32 bits;
        if (flag_set_first_pending(actor)) PlayMobySound(1, 0, actor);
        part_spawn_ground_sparkles(actor);
        part_l08_spawn_spark_shower(actor, g_str_effect_name);
        SpawnExplosionEffects(actor, vars + 0x170, 0, 0.0f, 0.0f, 4, 0, 0,
                      2.0f, 1.0f, 9.0f, 1.0f, -1, 0.0f, 0, 0, -1, 1, 0x810001);
        snd_stop_queued(actor);
        SetDeathBits(actor, 0, 3);
        g_moby_spawn_state_flags_a.flags[FIELD(actor, s16, 0xB2)] = FIELD(actor, u8, 0xB0) + 2;
        kind = FIELD(actor, u8, 0xB0);
        if (kind == 255 || (!(g_moby_state_flags[(u8)kind] & 0x80) &&
                            (g_moby_group_flags[(u8)kind + (g_current_map_index << 4)] & 0x80))) {
            g_moby_spawn_state_flags_b.flags[FIELD(actor, s16, 0xB2)] = kind + 2;
        }
        tag = FIELD(actor, u16, 0xB2);
        if (tag & 1) {
            bits = g_moby_nibble_table[((s16)tag >> 1) + (g_current_map_index << 10)];
            if (((bits >> 4) & 7) != 7)
                g_moby_nibble_table[((s16)tag >> 1) + (g_current_map_index << 10)] = bits + 0x10;
        } else {
            bits = g_moby_nibble_table[((s16)tag >> 1) + (g_current_map_index << 10)];
            if ((bits & 7) != 7)
                g_moby_nibble_table[((s16)tag >> 1) + (g_current_map_index << 10)] = bits + 1;
        }
destroy:
        moby_mark_spawned(actor);
        return;
    }
    }
    sandfly_tick_timers(actor);
    if (*(float *)(actor + 0x10) < 20.0f || 1003.0f < *(float *)(actor + 0x10) ||
        *(float *)(actor + 0x14) < 20.0f || 1003.0f < *(float *)(actor + 0x14) ||
        *(float *)(actor + 0x18) < 20.0f || 1003.0f < *(float *)(actor + 0x18)) moby_mark_spawned(actor);
}
