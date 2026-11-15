#include "names.h"
/* func_PAL_L08_00428EA8, the PAL copy of func_L08_00423970: the same C, where the func_002A7820 timers take
   the 50 Hz scale except the first, the frame limits become 200, 100 and 300, and the rise and fall rates
   become 0.010000001f, 0.006f, 0.6f and 0.00392f. */
#include "common.h"

#define FIELD(base, type, offset) (*(type *)((base) + (offset)))

extern float math_fabs(float);
extern float moby_get_anim_value(void *);
extern int flag_set_first_pending(void *);
extern void PlayMobySound(int, int, void *);
extern void math_step_value_toward_target(void *, float, void *, float, float, float);
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
extern void coll_sweep_from_object(void *, void *, float, float, float, int, int, int, int);
extern void snd_stop_queued(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void part_spawn_ground_sparkles(void *);
extern void part_l08_spawn_spark_shower(void *, void *);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void SetDeathBits(void *, int, int);
extern char *D_L08_001BFF58 NOT_SDA;
extern int D_L08_001B2508 MACRO_ADDR;
extern struct { char pad[0x2294]; int state; int pad2298; int secondaryState; } g_hero_state;
extern char D_L08_001A8F20[] __attribute__((sda));
extern struct { char pad[0x464]; u8 flags[0]; } D_L08_0021DE80;
extern unsigned char D_L08_001B2840[] __attribute__((sda));
extern unsigned char D_0019B2E8[];
extern s32 D_L08_001B29DC __attribute__((sda));
typedef struct {
    int state;
    char pad04[8];
    int mode;
    char pad10[0x18];
    float height;
    char pad2C[0xC];
    float secondHeight;
} HeightGate;
extern HeightGate D_L08_001CA080;
extern struct { char pad[0x464]; u8 flags[0]; } D_L08_0021EAF0;
extern unsigned char D_0019B4A8[];

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
extern char D_L08_002B5600[];
extern int FastDecTimer(short *);
extern void anim_start_blended(char *, int, int, int);
extern void moby_set_state(char *, int, int);
extern void moby_mark_spawned(char *);

/* Apply the height gates, dispatch the actor state, and update timers and bounds. */
void func_PAL_L08_00428EA8(char *actor) {
    char *p;
    int ready;
    int condition;
    float local[4];
    float z;
    int mode = D_L08_001CA080.mode;
    if (mode != 0) {
        float height = *(float *)(actor + 0x18);
        if (height < D_L08_001CA080.height && D_L08_001CA080.state == 1) return;
        if (D_L08_001CA080.height < height && D_L08_001CA080.state == 0) return;
        if (mode == 2) {
            if (D_L08_001CA080.secondHeight < height && D_L08_001CA080.state == 1) return;
            if (height < D_L08_001CA080.secondHeight && D_L08_001CA080.state == mode) return;
        }
    }
    p = *(char **)(actor + 0x68);
    sandfly_check_hit(actor);
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0: {
        int id = *(int *)(p + 0x184);
        if (id != -1) {
            char *other = (char *)D_L08_001B29DC + (id << 8);
            if (*(unsigned char *)(other + 0xB0) != 255) {
                unsigned short tag = *(unsigned short *)(other + 0xB2);
                if (D_L08_0021EAF0.flags[(short)tag] ||
                    ((D_0019B4A8[((short)tag >> 1) + (g_current_map_index << 10)] >> ((tag & 1) ? 4 : 0)) & 7)) {
                    unsigned short ownTag = *(unsigned short *)(actor + 0xB2);
                    if ((D_0019B4A8[((short)ownTag >> 1) + (g_current_map_index << 10)] >> ((ownTag & 1) ? 4 : 0)) & 7) goto destroy;
                }
            }
        }
        sandfly_init(actor);
        break;
    }
    case 1:
        ready = 0;
        switch (*(unsigned char *)(p + 0x18B)) {
        case 0:
            if (!math_random_int_below(7)) {
                /* Result 2 is false; normalize this with the other nonzero triggers. */
                condition = SelectNearestListedMoby(actor, p + 0x100,
                    (float)*(unsigned char *)(p + 0x18D), 0.0f,
                    *(int *)(p + 0x190), *(int *)(p + 0x198),
                    *(int *)(p + 0x194), -1) ^ 2;
                goto normalize;
            }
            break;
        case 1:
            if (*(int *)(p + 0x180) != -1) ready = moby_l08_is_linked_running_2(*(int *)(p + 0x180)) != 0;
            else {
                STUB_printf(D_L08_002B5600, *(short *)(actor + 0xAA), *(short *)(actor + 0xB2));
                *(unsigned char *)(p + 0x18B) = 0;
            }
            break;
        case 2: condition = *(u8 *)(actor + 0xBC); goto normalize;
        case 3: ready = moby_l08_is_linked_gone_4(*(int *)(p + 0x1AC)) != 0; break;
        case 4: ready = moby_l08_is_linked_gone_3(*(int *)(p + 0x180)) != 0; break;
        case 5:
            condition = moby_l08_is_linked_running_or_gone_2(*(int *)(p + 0x184));
normalize:
            ready = condition != 0;
            break;
        }
        if (*(unsigned char *)(actor + 0xBC) & 2) ready = 1;
        if (ready) {
            *(unsigned char *)(actor + 0x30) = *(unsigned char *)(p + 0x188);
            qzero(p + 0x170);
            *(short *)(p + 0x1B8) = math_random_int_range(0, 180);
            moby_set_state(actor, 3, -1);
        }
        break;
    case 3:
        if (FastDecTimer((short *)(p + 0x1B8))) {
            if (*(unsigned char *)(actor + 0x43)) anim_start_blended(actor, 0, 0, 10);
            *(unsigned char *)(actor + 0x31) = 1;
            *(unsigned short *)(actor + 0x34) &= 0xFFFE;
            moby_set_state(actor, 2, 0);
        }
        break;
    case 2:
        z = FIELD(actor, float, 0x18);
        switch (FIELD(actor, u8, 0x95)) {
        case 0: z = FIELD(p, float, 0x1B4); break;
        case 1: z = FIELD(p, float, 0x1B0) - 1.7f; break;
        }
        if (flag_set_first_pending(actor)) PlayMobySound(4, 0, actor);
        math_step_value_toward_target(actor + 0x18, z, p + 0x178,
                       0.010000001f, 0.006f, 0.6f);
        if (moby_get_anim_value(actor) < 12.0f) {
            qcopy(local, actor + 0x10);
            local[2] = FIELD(p, float, 0x1B0);
            part_spawn_dust_burst(actor, local, 3, 1.0f, 1.5f, 0.5f, 0.0f, 0.1f, 0.8f);
        }
        if (math_fabs(FIELD(actor, float, 0x18) - z) < 0.2f) {
            switch (FIELD(actor, u8, 0x95)) {
            case 0:
                FIELD(actor, u16, 0x34) |= 0x1000;
                if (FIELD(actor, u8, 0x43) != 3) anim_start_blended(actor, 3, 0, 3);
                FIELD(p, s16, 0x1B8) = ((s32)(math_random_int_range(180, 360)) * 5 + 2) / 6;
                moby_set_state(actor, 5, -1);
                break;
            case 1:
                FIELD(actor, u16, 0x34) &= 0xEFFF;
                if (FIELD(actor, u8, 0x43) != 1) anim_start_blended(actor, 1, 0, 3);
                FIELD(p, s16, 0x1B8) = 0;
                FIELD(actor, u8, 0x31) = 0;
                FIELD(actor, u16, 0x34) |= 1;
                moby_set_state(actor, 1, -1);
                break;
            }
        }
        break;
    case 4:
        FastVecAdd(actor + 0x10, actor + 0x10, p + 0x170);
        FIELD(p, float, 0x178) -= 0.00392f;
        FIELD(actor, float, 0x18) += 0.75f;
        if (coll_test_point(actor + 0x10, 0.75f, 0, actor)) {
            if (D_L08_001BFF58 == 0 || FIELD(D_L08_001BFF58, s16, 0xAA) != 0x945) {
                if (FIELD(actor, u8, 0x43) != 3) anim_start_blended(actor, 3, 0, 3);
                FIELD(p, s16, 0x1B8) = ((s32)(math_random_int_range(180, 360)) * 5 + 2) / 6;
                moby_set_state(actor, 5, -1);
            }
        }
        if (FIELD(p, float, 0x178) < 0 || FIELD(actor, u16, 0x96) > 200) {
            if (FIELD(actor, u8, 0x43) != 3) anim_start_blended(actor, 3, 0, 3);
            FIELD(p, s16, 0x1B8) = ((s32)(math_random_int_range(180, 360)) * 5 + 2) / 6;
            moby_set_state(actor, 5, -1);
        }
        FIELD(actor, float, 0x18) -= 0.75f;
        FIELD(p, float, 0x178) -= 0.00392f;
        if (FIELD(actor, float, 0x18) < FIELD(p, float, 0x1B0))
            FIELD(actor, float, 0x18) = FIELD(p, float, 0x1B0);
        break;
    case 5: {
        float angle = FIELD(p, float, 0x16C);
        float phase;
        if (FIELD(actor, u16, 0x96) == 0 || D_L08_001B2508 % 50 == FIELD(actor, s16, 0xB2) % 50) {
            if (angle > 0.0f) angle = math_random_float_range(0.2f, 0.5f) * -1.5707963705062866f;
            else angle = math_random_float_range(0.2f, 0.5f) * 1.5707963705062866f;
        }
        FIELD(p, float, 0x160) = math_fast_sin_or_cos_a(FastAddRotations(FIELD(actor, float, 0xF8), angle)) * 2.0f;
        FIELD(p, float, 0x164) = math_fast_sin_or_cos_b(FastAddRotations(FIELD(actor, float, 0xF8), angle)) * 2.0f;
        FIELD(p, s32, 0x168) = 0;
        FastVecAdd(p + 0x160, p + 0x160, actor + 0x10);
        phase = math_wrap_angle_to_pi(IntToFloat(D_L08_001B2508) * 0.025f);
        sandfly_pick_flight_target(actor);
        if (sandfly_move_toward_target(actor, 360.0f, 180.0f, 560.0f, 20.0f, 0.0f, 16.0f,
                              FIELD(p, float, 0x15C) + 1.7f + 1.0f + math_fast_sin_or_cos_b(phase), -2.0f))
            angle *= 1.025f;
        FIELD(p, float, 0x16C) = angle;
        if (FIELD(p, s16, 0x1B8) == 0) {
            if (FIELD(actor, u8, 0x43) != 1) anim_start_blended(actor, 1, 0, 3);
            moby_set_state(actor, 6, 0);
        }
        break;
    }
    case 6:
        switch (FIELD(actor, u8, 0x95)) {
        case 0:
            if (FIELD(p, s16, 0x1B8) == 0) {
                FIELD(p, s16, 0x1B8) = ((s32)(math_random_int_range(30, 90)) * 5 + 2) / 6;
                if (FIELD(p, s16, 0x1B8) >= 7 && FIELD(actor, u8, 0x43) != 3)
                    anim_start_blended(actor, 3, 0, 3);
                moby_set_state(actor, 6, 1);
            }
            break;
        case 1:
            sandfly_move_toward_target(actor, 120.0f, 360.0f, 120.0f, 30.0f, 0.0f, 8.0f,
                              FIELD(p, float, 0x15C) + 1.7f, 1.0f);
            if (FIELD(p, s16, 0x1B8) == 0) {
                sandfly_pick_random_target(actor);
                FIELD(p, s16, 0x1B8) = ((s32)(math_random_int_range(0, 0)) * 5 + 2) / 6;
                if (FIELD(p, s16, 0x1B8) >= 7 && FIELD(actor, u8, 0x43) != 1)
                    anim_start_blended(actor, 1, 0, 3);
                moby_set_state(actor, 6, 0);
            }
            break;
        case 2:
            qcopy(p + 0x160, p + 0x150);
            if (sandfly_move_toward_target(actor, 120.0f, 360.0f, 120.0f, 30.0f, 0.0f, 8.0f,
                                  FIELD(p, float, 0x15C) + 1.7f, 1.0f) & 8) {
                if (FIELD(actor, u8, 0x43) != 2) anim_start_blended(actor, 2, 0, 10);
                moby_set_state(actor, 2, 1);
            }
            break;
        }
        if (SelectNearestListedMoby(actor, p + 0x100, (float)FIELD(actor, s16, 0x32), 0.0f,
                             FIELD(p, int, 0x19C), FIELD(p, int, 0x1A4), FIELD(p, int, 0x1A0), -1) != 2) {
            if (!math_random_int_below(9)) {
                FIELD(p, s16, 0x1BA) = ((s32)(math_random_int_range(300, 360)) * 5 + 2) / 6;
                moby_set_state(actor, 7, 0);
            }
        } else if (FIELD(actor, u8, 0x20) == 6 && FIELD(p, u8, 0x18A) == 0) {
            moby_set_state(actor, 6, 2);
        }
        break;
    case 7:
        switch (FIELD(actor, u8, 0x95)) {
        case 0:
            if (FIELD(p, s16, 0x1B8) == 0) {
                FIELD(p, s16, 0x1B8) = ((s32)(math_random_int_range(30, 90)) * 5 + 2) / 6;
                if (FIELD(p, s16, 0x1B8) >= 7 && FIELD(actor, u8, 0x43) != 3)
                    anim_start_blended(actor, 3, 0, 3);
                moby_set_state(actor, 7, 1);
            }
            break;
        case 1:
            if (sandfly_move_toward_target(actor, 250.0f, 180.0f, 250.0f, 32.0f, 0.1f, 13.0f,
                                  FIELD(p, float, 0x15C) + 1.7f, 1.0f) & 8)
                FIELD(p, s16, 0x1B8) = 0;
            if (FIELD(p, s16, 0x1B8) == 0) {
                sandfly_pick_random_target(actor);
                FIELD(p, s16, 0x1B8) = ((s32)(math_random_int_range(0, 0)) * 5 + 2) / 6;
                if (FIELD(p, s16, 0x1B8) >= 7 && FIELD(actor, u8, 0x43) != 1)
                    anim_start_blended(actor, 1, 0, 3);
                moby_set_state(actor, 7, 0);
            }
            break;
        }
        if (SelectNearestListedMoby(actor, p + 0x100, (float)FIELD(actor, s16, 0x32), (float)FIELD(p, u8, 0x18D),
                             FIELD(p, int, 0x19C), FIELD(p, int, 0x1A4), FIELD(p, int, 0x1A0), -1) == 2 ||
            g_hero_state.state == 0x31 || g_hero_state.secondaryState == 0x11 ||
            g_hero_state.secondaryState == 0x12) {
            FIELD(p, int, 0x144) = 2;
            if (FIELD(p, s16, 0x1BA) == 0) moby_set_state(actor, 6, 0);
        } else if (**(int **)(p + 0x1CC) < 3 && FIELD(p, s16, 0x1BC) == 0 &&
                    vec_distance_xy(actor + 0x10, p + 0x120) < 12.0f) {
            FIELD(p, u8, 0x18C) = 1;
            qcopy(p + 0x160, p + 0x120);
            moby_set_state(actor, 8, 0);
            ++**(int **)(p + 0x1CC);
        }
        break;
    case 8: {
        qcopy(p + 0x160, p + 0x120);
        switch (FIELD(actor, u8, 0x95)) {
        case 0:
            sandfly_move_toward_target(actor, 260.0f, 180.0f, 270.0f, 32.0f, 0.15f, 8.0f, 0.4f, 0.5f);
            if (vec_distance_xy(actor + 0x10, p + 0x120) < 1.5f &&
                math_fabs(FIELD(actor, float, 0x18) - FIELD(p, float, 0x128)) < 1.1f) {
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
                    coll_sweep_from_object(actor, local, 0.5f, (float)FIELD(p, u8, 0x34), 1.0f, 1, 0, 1, 0);
                }
                if (FIELD(actor, u8, 0x60) & 2) {
                    FIELD(p, s16, 0x1B8) = 100;
                    FIELD(p, s16, 0x1BC) = ((s32)(math_random_int_range(180, 260)) * 5 + 2) / 6;
                    if (FIELD(actor, u8, 0x43) != 1) anim_start_blended(actor, 1, 0, 3);
                    moby_set_state(actor, 8, 3);
                }
            }
            break;
        case 3:
            sandfly_move_toward_target(actor, 260.0f, 180.0f, 270.0f, 32.0f, 0.15f, 8.0f, 0.3f, 0.5f);
            if (FastDecTimer((s16 *)(p + 0x1B8))) {
                if (vec_distance_xy(actor + 0x10, p + 0x120) < 1.5f &&
                    math_fabs(FIELD(actor, float, 0x18) - FIELD(p, float, 0x128)) < 1.1f) {
                    if (FIELD(actor, u8, 0x43) != 4) anim_start_blended(actor, 4, 0, 3);
                    moby_set_state(actor, 8, 1);
                } else {
                    qcopy(p + 0x160, p + 0x120);
                    moby_set_state(actor, 8, 0);
                }
            }
            break;
        }
        if (SelectNearestListedMoby(actor, p + 0x100, (float)FIELD(actor, s16, 0x32), (float)FIELD(p, u8, 0x18D),
                             FIELD(p, int, 0x19C), FIELD(p, int, 0x1A4), FIELD(p, int, 0x1A0), -1) == 2 ||
            g_hero_state.state == 0x31 || g_hero_state.secondaryState == 0x11 ||
            g_hero_state.secondaryState == 0x12) {
            snd_stop_queued(actor);
            if (FIELD(p, s16, 0x1BA) != 0) {
                FIELD(p, s16, 0x1B8) = 0;
                if (FIELD(actor, u8, 0x43) != 3) anim_start_blended(actor, 3, 0, 3);
                moby_set_state(actor, 6, 0);
            } else {
                FastVecSub(p + 0x160, actor + 0x10, p + 0x160);
                FastVecAdd(p + 0x160, p + 0x160, actor + 0x10);
                vec_scale_to_length(p + 0x160, p + 0x160, 5.0f);
                sandfly_pick_flight_target(actor);
                sandfly_move_toward_target(actor, 260.0f, 180.0f, 270.0f, 32.0f, 0.15f, 8.0f, 0.3f, 0.5f);
                FIELD(p, s16, 0x1B8) = 0;
                if (FIELD(actor, u8, 0x43) != 3) anim_start_blended(actor, 3, 0, 3);
                FIELD(p, s16, 0x1BC) = ((s32)(math_random_int_range(180, 260)) * 5 + 2) / 6;
                moby_set_state(actor, 7, 0);
            }
        }
        break;
    }
    case 9: {
        int result;
        ++FIELD(p, u16, 0x1BE);
        if (flag_set_first_pending(actor)) PlayMobySound(0, 0, actor);
        result = moby_dispatch_action_by_kind(actor, p + 0x50);
        if (result & 1) {
            moby_set_state(actor, 10, -1);
        } else if ((result & 2) || FIELD(p, s16, 0x1BE) > 300) {
            FIELD(p, u8, 0x6A) = 2;
            if (FIELD(actor, u8, 0x43) != 1) anim_start_blended(actor, 1, 0, 3);
            FIELD(p, s16, 0x1BE) = 0;
            qzero(p + 0x170);
            if (FIELD(p, float, 0x20) <= 0.0f) moby_set_state(actor, 10, -1);
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
        part_l08_spawn_spark_shower(actor, D_L08_001A8F20);
        SpawnExplosionEffects(actor, p + 0x170, 0, 0.0f, 0.0f, 4, 0, 0,
                      2.0f, 1.0f, 9.0f, 1.0f, -1, 0.0f, 0, 0, -1, 1, 0x810001);
        snd_stop_queued(actor);
        SetDeathBits(actor, 0, 3);
        D_L08_0021DE80.flags[FIELD(actor, s16, 0xB2)] = FIELD(actor, u8, 0xB0) + 2;
        kind = FIELD(actor, u8, 0xB0);
        if (kind == 255 || (!(D_L08_001B2840[(u8)kind] & 0x80) &&
                            (D_0019B2E8[(u8)kind + (g_current_map_index << 4)] & 0x80))) {
            D_L08_0021EAF0.flags[FIELD(actor, s16, 0xB2)] = kind + 2;
        }
        tag = FIELD(actor, u16, 0xB2);
        if (tag & 1) {
            bits = D_0019B4A8[((s16)tag >> 1) + (g_current_map_index << 10)];
            if (((bits >> 4) & 7) != 7)
                D_0019B4A8[((s16)tag >> 1) + (g_current_map_index << 10)] = bits + 0x10;
        } else {
            bits = D_0019B4A8[((s16)tag >> 1) + (g_current_map_index << 10)];
            if ((bits & 7) != 7)
                D_0019B4A8[((s16)tag >> 1) + (g_current_map_index << 10)] = bits + 1;
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
