#include "names.h"
/* func_PAL_L11_00425B68, the PAL copy of func_L11_00420C88: the same C, where the
 * per-frame float rates, the blend lengths (10 -> 8, 5 -> 4, 20 -> 17, 40 -> 33) and
 * one func_002A7750 argument (0x10 -> 0x13) change, and each func_002A7820 random length is scaled
 * to 50 Hz. The Joba NPC state machine (two switches over the object's
 * mode bytes 0x95 and 0x20). Its own unit for the -frac2-qcopy profile
 * (config/cflags.txt). Control-flow notes: each arm that ends in a
 * func_002A7750 call has its own call and break, so jump2 cross-jumps only the
 * shared call; float compares are strict (x < c); case-local pointers keep
 * object, state and path in $s2, $s3 and $s1. func_002B60B0 returns nothing
 * (src/game/002B60B0.c; no retail call reads $v0), so the index load after it
 * may take $v0 (cases 14, 15 and 22).
 */
#include "common.h"

typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
#define BYTE(p, o) (*(unsigned char *)((char *)(p) + (o)))
#define SIGNED_BYTE(p, o) (*(signed char *)((char *)(p) + (o)))
#define HALF(p, o) (*(short *)((char *)(p) + (o)))
#define UHALF(p, o) (*(unsigned short *)((char *)(p) + (o)))
#define WORD(p, o) (*(int *)((char *)(p) + (o)))
#define REAL(p, o) (*(float *)((char *)(p) + (o)))
#define POINTER(p, o) (*(char **)((char *)(p) + (o)))
#define QUAD(p, o) (*(QuadWord *)((char *)(p) + (o)))

extern int g_active_rider_count;
extern int g_enemy_spawn_enabled __attribute__((sda));
extern int g_arena_progress_level __attribute__((sda));
extern int g_moby_l11_table;
extern int g_tribe_group_limit;
extern unsigned short *g_group_id_lists[];
extern Vector g_hero_l11_position;
extern char g_str_rider_debug_index[], g_str_debug_rider[];
extern float coll_probe_ground_height_below(void *, int, float);
extern void STUB_printf(const char *, ...);
extern int math_random_int_below(int);
extern void moby_set_flag_bit(unsigned char *, int);
extern void moby_set_controller_speed_limits(unsigned char *, float, float, float, float);
extern void moby_set_state(unsigned char *, unsigned char, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern char *CreateMoby(int);
extern void func_002A0F48(void *);
extern void moby_copy_joint_transform_to_object(void *, void *, int, int);
extern void moby_mark_spawned(void *);
extern void part_spawn_explosion_with_sparks_pal(void *, void *, int, float, float);
extern void moby_transform_joint_to_world(char *, int, char *);
extern int moby_count_group_not_in_state(int, int);
extern void SetDeathBits_pal(void *, int, int);

struct family_27f9_object;
extern int g_enemy_freeze_flag __attribute__((nosda));
/* One hero-state object: retail retains its common base across cases. */
typedef struct {
    unsigned char unknown0000[0x80];
    Vector position;
    unsigned char unknown0090[0x40];
    Vector aim;
    unsigned char unknown00E0[0x1168];
    int state;
    unsigned char unknown124C[0x1044];
    char *moby;
    int mode;
} Hero20C88;
extern Hero20C88 g_hero_state;
extern char *g_path_l11_table[];
extern char g_str_tribesman_debug[];
extern int func_PAL_L11_00429B30(unsigned char *);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern float FastAddRotations(float, float);
extern float FastDiffRots(float, float);
extern int flag_is_third_pending_set(unsigned char *);
extern int flag_set_second_pending(unsigned char *);
extern int math_random_int_range(int, int);
extern int path_set_follower_nodes(void *, void *, int, int);
extern int moby_step_controller_pal(void *, void *, float);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void part_queue_moby_for_glow(void *, int, void (*)(void *));
extern int joba_enemy_apply_source_damage(unsigned char *);
extern void euler_rotation_basis(void *, void *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern float moby_get_anim_value(char *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int moby_move_over_ground(void *, void *, void *, float, float, float, float, int);
extern u8 *moby_find_linked_object(unsigned char *);
extern int moby_l01_turn_toward_target_pal(char *, char *);
extern float moby_turn_toward_position(struct family_27f9_object *, float *, float *, float, float, float);
extern float MobySpringTurn(struct family_27f9_object *, float *, float, float, float, float);
extern int moby_turn_toward_target_and_step_pal(char *, float *, float);
extern int func_PAL_L11_0042A858(char *, char *, float, float, float, float);
extern float math_fabs(float);
extern int func_PAL_002AF6C0(char *, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern char *robot_spawn_debris_pal(void *, void *, void *, int, float);
extern int coll_sweep_from_object(void *, void *, int, float, float, float, int, int, int);
extern void func_PAL_L11_0042AB20(char *);

/* A group's ID list entry names an object; bit 15 only marks the list's last entry. */
static inline int group_entry_id(unsigned short *entry)
{
    return *entry & 0x7fff;
}

static inline char *moby_at(int id)
{
    return (char *)(g_moby_l11_table + id * 0x100);
}

static inline signed char moby_state(char *moby)
{
    return SIGNED_BYTE(moby, 0x20);
}

static inline short moby_class(char *moby)
{
    return HALF(moby, 0xaa);
}

static inline char *moby_vars(char *moby)
{
    return POINTER(moby, 0x68);
}

static inline int rider_kind(char *moby)
{
    return WORD(moby_vars(moby), 0x540);
}

/* The guarded animation transition is repeated throughout both state machines. */
#define PLAY(p, animation, start, blend) \
    (BYTE((p), 0x43) != (animation) ? func_PAL_002A7E68((p), (animation), (start), (blend)) : (void)0)

void func_PAL_L11_00425B68(unsigned char *object)
{
    Vector offset, side, point;
    char *state, *path;
    int index, kind;
    float old_z, distance, angle, other_angle, pitch, limit;
    int flags;

    if (g_enemy_freeze_flag != 0) return;
    if (g_hero_state.mode == 0x6f && BYTE(object, 0x95) != 4) return;
    old_z = REAL(object, 0x18);
    state = POINTER(object, 0x68);
    if (func_PAL_L11_00429B30(object) != 0) {
        moby_mark_spawned(object);
        return;
    }
    switch (BYTE(object, 0x95)) {
    case 10:
        if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) < 6.0f) {
            limit = 1.5707965f;
            angle = mat_fast_helper_a(REAL(g_hero_state.moby, 0x10) - REAL(object, 0x10), REAL(g_hero_state.moby, 0x14) - REAL(object, 0x14));
            angle = fast_subtract_rotations(angle, REAL(object, 0xf8));
            if (flag_is_third_pending_set(object) != 0) angle = -angle;
            if (angle > limit) angle = limit;
            else if (angle < -limit) angle = -limit;
            REAL(state, 0x308) = angle;
        }
        if (g_hero_state.state != 0x41) BYTE(object, 0x95) = 0;
        break;
    case 0: {
        char *linked;

        if (flag_set_second_pending(object) != 0)
            moby_set_controller_speed_limits(object, 0.0022f, 0.055000003f, 0.0016755164f, 0.12566373f);
        if (HALF(state, 0x264) == 2) {
            if (WORD(state, 0x284) != -1) {
                PLAY(object, 15, 0, 8);
                moby_set_state(object, 0x1e, 2);
            }
            if (WORD(state, 0x548) != -1) {
                linked = (char *)(g_moby_l11_table + WORD(state, 0x548) * 0x100);
                if ((unsigned int)(BYTE(linked, 0x20) - 5) > 1) {
                    PLAY(object, 15, 0, 8);
                    moby_set_state(object, 0x1d, 2);
                    BYTE(linked, 0x20) = 6;
                    BYTE(object, 0xbc) = 1;
                    break;
                }
                if (WORD(state, 0x294) == 1) {
                    if (BYTE(object, 0x43) != 0x22)
                        func_PAL_002A7E68(object, 0x22, 0, ((s32)math_random_int_range(7, 20) * 5 + 2) / 6);
                    moby_set_state(object, 0x18, 2);
                } else {
                    if (WORD(state, 0x570) != 0) {
                        PLAY(object, 0x21, 0, 8);
                        moby_set_state(object, 0x18, 3);
                    } else {
                        WORD(state, 0x290) = 1;
                        PLAY(object, 14, 0, 4);
                        moby_set_state(object, 0x18, 3);
                    }
                }
            } else {
                if (WORD(state, 0x580) != -1) {
                    PLAY(object, 15, 0, 8);
                    moby_set_state(object, 0x20, 2);
                } else {
                    if (WORD(state, 0x294) == 1) {
                        if (BYTE(object, 0x43) != 0x22)
                            func_PAL_002A7E68(object, 0x22, 0, ((s32)math_random_int_range(7, 20) * 5 + 2) / 6);
                        moby_set_state(object, 0x18, 2);
                    } else {
                        if (WORD(state, 0x570) != 0) {
                            PLAY(object, 0x21, 0, 8);
                            moby_set_state(object, 0x18, 3);
                        } else {
                            WORD(state, 0x290) = 1;
                            PLAY(object, 14, 0, 4);
                            moby_set_state(object, 0x18, 3);
                        }
                    }
                    if (WORD(state, 0x270) == -1) break;
                    WORD(state, 0x274) = g_moby_l11_table + WORD(state, 0x270) * 0x100;
                    moby_set_controller_speed_limits(object, 0.0056000003f, 0.14000002f, 0.004886923f, 0.31415933f);
                    PLAY(object, 15, 0, 8);
                    moby_set_state(object, 0x1f, 2);
                }
            }
            break;
        } else {
            if (HALF(state, 0x266) == 0) break;
            if (WORD(state, 0x558) != -1 && WORD(state, 0x560) == 1) {
                if (BYTE(object, 0x43) != 0x18)
                    func_PAL_002A7E68(object, 0x18, 0, ((s32)math_random_int_range(5, 15) * 5 + 2) / 6);
                moby_set_state(object, 6, -1);
            } else if (WORD(state, 0x558) != -1 && WORD(state, 0x560) > 1) {
                if (BYTE(object, 0x43) != 15)
                    func_PAL_002A7E68(object, 15, 0, ((s32)math_random_int_range(5, 15) * 5 + 2) / 6);
                moby_set_state(object, 7, -1);
                moby_set_controller_speed_limits(object, 0.0056000003f, 0.14000002f, 0.004886923f, 0.31415933f);
            } else {
                BYTE(object, 0x95) = 1;
                PLAY(object, 0x18, 0, 17);
            }
            if ((unsigned int)(UHALF(state, 0x264) - 1) < 2) {
                if (WORD(state, 0x284) != -1) {
                    PLAY(object, 15, 0, 8);
                    moby_set_state(object, 0x1e, 2);
                } else if (WORD(state, 0x580) != -1) {
                    PLAY(object, 15, 0, 8);
                    moby_set_state(object, 0x20, 2);
                } else if (WORD(state, 0x294) == 1) {
                    if (BYTE(object, 0x43) != 0x22)
                        func_PAL_002A7E68(object, 0x22, 0, ((s32)math_random_int_range(7, 20) * 5 + 2) / 6);
                    moby_set_state(object, 0x18, 2);
                } else if (WORD(state, 0x570) != 0) {
                    PLAY(object, 0x21, 0, 4);
                    moby_set_state(object, 0x18, 3);
                } else {
                    WORD(state, 0x290) = 1;
                    PLAY(object, 14, 0, 8);
                    moby_set_state(object, 0x18, 3);
                }
            }
            HALF(state, 0x266) = 0;
            if (WORD(state, 0x548) != -1) {
                linked = (char *)(g_moby_l11_table + WORD(state, 0x548) * 0x100);
                if ((unsigned int)(BYTE(linked, 0x20) - 5) > 1) {
                    PLAY(object, 15, 0, 8);
                    moby_set_state(object, 0x1d, 2);
                    BYTE(linked, 0x20) = 6;
                    BYTE(object, 0xbc) = 1;
                }
                HALF(state, 0x266) = 1;
            }
            break;
        }
    }
    case 1: {
        char *linked;

        if (flag_set_second_pending(object) != 0) REAL(state, 0x12c) = 6.0f;
        if (WORD(state, 0x548) != -1) {
            linked = (char *)(g_moby_l11_table + WORD(state, 0x548) * 0x100);
            if ((unsigned int)(BYTE(linked, 0x20) - 5) > 1) {
                WORD(state, 0x178) &= ~0x10;
                PLAY(object, 15, 0, 8);
                moby_set_state(object, 0x1d, 2);
                BYTE(linked, 0x20) = 6;
                BYTE(object, 0xbc) = 1;
            }
        }
        if ((unsigned int)(UHALF(state, 0x264) - 1) > 1) break;
        WORD(state, 0x178) &= ~0x10;
        if (WORD(state, 0x284) != -1) {
            float nearest_distance;
            int node, nearest;

            PLAY(object, 15, 0, 8);
            nearest_distance = 100.0f;
            moby_set_state(object, 0x1e, 2);
            node = 0;
            nearest = 0;
            for (; node < WORD(g_path_l11_table[WORD(state, 0x284)], 0); ++node) {
                float d = vec_distance_xy(((char *)object + 0x10), g_path_l11_table[WORD(state, 0x284)] + 0x10 + node * 0x10);
                if (d < nearest_distance) {
                    nearest_distance = d;
                    nearest = node;
                }
            }
            path_set_follower_nodes(object, g_path_l11_table[WORD(state, 0x284)], -1, nearest);
        }
        if (WORD(state, 0x548) != -1) {
            linked = (char *)(g_moby_l11_table + WORD(state, 0x548) * 0x100);
            if ((unsigned int)(BYTE(linked, 0x20) - 5) > 1) {
                WORD(state, 0x178) &= ~0x10;
                PLAY(object, 15, 0, 8);
                moby_set_state(object, 0x1d, 2);
                BYTE(linked, 0x20) = 6;
                BYTE(object, 0xbc) = 1;
                break;
            }
            if (WORD(state, 0x294) == 1) {
                if (BYTE(object, 0x43) != 0x19) {
                    index = math_random_int_below(4);
                    func_PAL_002A7E68(object, 0x19, index, ((s32)math_random_int_range(7, 20) * 5 + 2) / 6);
                }
                moby_set_state(object, 0x18, 2);
            } else {
                WORD(state, 0x290) = 1;
                PLAY(object, 14, 0, 33);
                moby_set_state(object, 0x18, 3);
            }
        } else {
            if (WORD(state, 0x294) == 1) {
                if (BYTE(object, 0x43) != 0x22) {
                    index = math_random_int_below(4);
                    func_PAL_002A7E68(object, 0x22, index, ((s32)math_random_int_range(7, 20) * 5 + 2) / 6);
                }
                moby_set_state(object, 0x18, 2);
            } else {
                WORD(state, 0x290) = 1;
                PLAY(object, 14, 0, 33);
                moby_set_state(object, 0x18, 3);
            }
        }
        break;
    }
    case 2: {
        char *linked;

        if (flag_set_second_pending(object) != 0)
            moby_set_controller_speed_limits(object, 0.0056000003f, 0.14000002f, 0.005445428f, 0.35604724f);
        if ((unsigned int)(UHALF(state, 0x264) - 1) > 1 && BYTE(object, 0x20) != 0x1d &&
            BYTE(object, 0x20) != 0x22 && BYTE(object, 0x20) != 0x20 && math_random_int_below(4) == 1) {
            REAL(object, 0x48) = 1.0f;
            kind = math_random_int_below(4);
            if (kind == 0) PLAY(object, 14, 0, 8);
            else if (kind == 2) PLAY(object, 0x1e, 0, 17);
            else PLAY(object, 0x18, 0, 17);
            moby_set_state(object, 0x13, 1);
            WORD(state, 0x560) = 0;
            HALF(state, 0x260) = ((s32)math_random_int_range(580, 600) * 5 + 2) / 6;
        }
        if (WORD(state, 0x548) != -1) {
            linked = (char *)(g_moby_l11_table + WORD(state, 0x548) * 0x100);
            if ((unsigned int)(BYTE(linked, 0x20) - 5) > 1) {
                PLAY(object, 15, 0, 8);
                moby_set_state(object, 0x1d, 2);
                BYTE(linked, 0x20) = 6;
                BYTE(object, 0xbc) = 1;
            }
        }
        goto check_route;
    }
    case 8: {
        char *linked;

        if (g_hero_state.mode != 0x31) {
            if (WORD(state, 0x548) != -1) {
                linked = (char *)(g_moby_l11_table + WORD(state, 0x548) * 0x100);
                PLAY(object, 15, 0, 8);
                moby_set_state(object, 0x1d, 2);
                BYTE(linked, 0x20) = 6;
                BYTE(object, 0xbc) = 1;
            } else if (WORD(state, 0x294) != 0) {
                PLAY(object, 15, 0, 8);
                moby_set_state(object, 0x1c, 2);
            } else {
                PLAY(object, 0x19, 0, 8);
                moby_set_state(object, 0x18, 2);
            }
        }
        break;
    }
    case 4:
        if (REAL(state, 0x20) > 0.0f) {
            moby_step_controller_pal(object, ((char *)object + 0x10),
                          mat_fast_helper_a(g_hero_state.position.v[0] - REAL(object, 0x10), g_hero_state.position.v[1] - REAL(object, 0x14)));
        }
        flags = moby_dispatch_action_by_kind(object, state + 0x60);
        if ((flags & 1) != 0) {
            --g_active_rider_count;
            SetDeathBits_pal(object, 0, 3);
            part_queue_moby_for_glow(object, 0, 0);
            return;
        }
        if ((flags & 2) == 0) break;
        HALF(state, 0x26) = 0;
        if ((unsigned int)(UHALF(state, 0x264) - 1) < 2) {
            PLAY(object, 15, 0, 8);
            moby_set_state(object, 0x1c, 2);
            if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) < 2.5f) {
                angle = mat_fast_helper_a(g_hero_state.position.v[0] - REAL(object, 0x10), g_hero_state.position.v[1] - REAL(object, 0x14));
                if (FastDiffRots(REAL(object, 0xf8), angle) < 0.6108653f) {
                    PLAY(object, 0x11, 9, 3);
                    moby_set_controller_speed_limits(object, 0.0056000003f, 0.14000002f, 0.0016755164f, 0.12566373f);
                    moby_set_state(object, 0x22, 2);
                }
            }
            if (BYTE(state, 0x37) == 10) {
                PLAY(object, 0x11, 9, 3);
                moby_set_controller_speed_limits(object, 0.0056000003f, 0.14000002f, 0.0016755164f, 0.12566373f);
                moby_set_state(object, 0x22, 2);
            }
            if (g_hero_state.mode == 0x31 && WORD(state, 0x574) != -1) {
                if (BYTE(object, 0x43) != 15) func_PAL_002A7E68(object, 15, 0, ((s32)math_random_int_range(5, 15) * 5 + 2) / 6);
                moby_set_state(object, 8, 8);
            }
        } else if (WORD(state, 0x558) != -1) {
            WORD(state, 0x178) &= ~0x10;
            if (BYTE(object, 0x43) != 15) func_PAL_002A7E68(object, 15, 0, ((s32)math_random_int_range(5, 15) * 5 + 2) / 6);
            moby_set_state(object, 7, 1);
            moby_set_controller_speed_limits(object, 0.0056000003f, 0.14000002f, 0.004886923f, 0.31415933f);
        } else {
            PLAY(object, 0x18, 0, 8);
            moby_set_state(object, 0x13, 1);
            HALF(state, 0x260) = ((s32)math_random_int_range(580, 600) * 5 + 2) / 6;
        }
        break;
    case 3:
        if (flag_set_second_pending(object) != 0)
            moby_set_controller_speed_limits(object, 0.0056000003f, 0.14000002f, 0.0016755164f, 0.12566373f);
        if (WORD(state, 0x294) == 1) {
            PLAY(object, 15, 0, 8);
            moby_set_state(object, 0x1c, 2);
        }
        if ((unsigned int)(UHALF(state, 0x264) - 1) > 1) {
            PLAY(object, 0x1a, 0, 25);
            moby_set_state(object, 0x13, 1);
            HALF(state, 0x260) = ((s32)math_random_int_range(580, 600) * 5 + 2) / 6;
            WORD(state, 0x560) = 0;
        }
    check_route:
        if (g_hero_state.mode == 0x31 && WORD(state, 0x574) != -1) {
            if (BYTE(object, 0x43) != 15) func_PAL_002A7E68(object, 15, 0, ((s32)math_random_int_range(5, 15) * 5 + 2) / 6);
            moby_set_state(object, 9, 8);
            moby_set_controller_speed_limits(object, 0.0056000003f, 0.14000002f, 0.004886923f, 0.31415933f);
        }
        break;
    case 5: {
        char *linked;

        if (POINTER(state, 0x278) != 0) moby_copy_joint_transform_to_object(object, POINTER(state, 0x278), 1, 0);
        linked = POINTER(state, 0x274);
        QUAD(object, 0x10) = QUAD(linked, 0x10);
        QUAD(object, 0xf0) = QUAD(linked, 0xf0);
        {
            char *carrier = POINTER(state, 0x280);
            QUAD(carrier, 0x10) = QUAD(object, 0x10);
            QUAD(carrier, 0xf0) = QUAD(object, 0xf0);
            QUAD(carrier, 0x10) = QUAD(object, 0x10);
            REAL(carrier, 0x18) += 0.65f;
        }
        if (WORD(state, 0x26c) == 0 || POINTER(state, 0x274) == 0 ||
            BYTE(POINTER(state, 0x274), 0x20) == 0xfe || BYTE(POINTER(state, 0x274), 0x20) == 0xfd) {
            part_spawn_explosion_with_sparks_pal(object, POINTER(state, 0x278) + 0x10, -1, 0.5f, 3.0f);
            moby_mark_spawned(POINTER(state, 0x278));
            POINTER(state, 0x278) = 0;
            moby_mark_spawned(POINTER(state, 0x280));
            WORD(POINTER(POINTER(state, 0x274), 0x68), 0x27c) = 0;
            moby_set_state(object, 2, 6);
        } else {
            if (joba_enemy_apply_source_damage(object) == 0) break;
            part_spawn_explosion_with_sparks_pal(object, POINTER(state, 0x278) + 0x10, -1, 0.5f, 3.0f);
            moby_mark_spawned(POINTER(state, 0x278));
            POINTER(state, 0x278) = 0;
            moby_mark_spawned(POINTER(state, 0x280));
            WORD(POINTER(POINTER(state, 0x274), 0x68), 0x27c) = 0;
            PLAY(object, 9, 0, 0);
            moby_set_state(object, 3, 6);
        }
        break;
    }
    case 6:
        if (flag_set_second_pending(object) != 0 && POINTER(state, 0x29c) == 0) {
            POINTER(state, 0x29c) = CreateMoby(0x9ac);
            if (POINTER(state, 0x29c) != 0) {
                BYTE(POINTER(state, 0x29c), 0x30) = BYTE(object, 0x30);
                UHALF(POINTER(state, 0x29c), 0x32) = UHALF(object, 0x32);
                BYTE(POINTER(state, 0x29c), 0x31) = 1;
                *(long *)(POINTER(state, 0x29c) + 0x38) = *(long *)(object + 0x38);
                func_002A0F48(POINTER(state, 0x29c));
                WORD(POINTER(state, 0x29c), 0x98) = 0;
                moby_copy_joint_transform_to_object(object, POINTER(state, 0x29c), 3, 0);
                WORD(state, 0x290) = 1;
                REAL(object, 0xf0) = 0.0f;
                REAL(object, 0xf4) = 0.0f;
                euler_rotation_basis(object + 0xc0, object + 0xf0);
            } else {
                moby_mark_spawned(object);
                return;
            }
        }
        break;
    case 7: {
        char *other_state;
        char *linked;

        linked = (char *)(g_moby_l11_table + WORD(state, 0x548) * 0x100);
        WORD(state, 0x290) = 0;
        other_state = POINTER(linked, 0x68);
        if (BYTE(linked, 0x43) == 1) {
            REAL(linked, 0x48) = 0.65f;
            REAL(object, 0x48) = 0.65f;
            if (WORD(state, 0x58c) != 0) {
                REAL(linked, 0x48) = 0.35f;
                REAL(object, 0x48) = 0.35f;
            }
        } else { REAL(linked, 0x48) = 1.0f; REAL(object, 0x48) = 1.0f; }
        if (BYTE(object, 0x20) != 0x28) {
            moby_step_controller_pal(object, ((char *)object + 0x10), mat_fast_helper_a(g_hero_state.position.v[0] - REAL(object, 0x10), g_hero_state.position.v[1] - REAL(object, 0x14)));
            distance = vec_distance_xy(((char *)object + 0x10), &g_hero_state.aim);
            pitch = mat_fast_helper_a(distance, g_hero_state.aim.v[2] - REAL(object, 0x18));
            if (pitch < -0.52359885f) pitch = -0.52359885f;
            else if (pitch > 0.52359885f) pitch = 0.52359885f;
            REAL(other_state, 0xb4) = -pitch;
            moby_update_eased_node(linked, other_state + 0x70, 2, 0.0432f, 0.43200004f);
        }
        REAL(object, 0x10) = REAL(linked, 0x10);
        REAL(object, 0x14) = REAL(linked, 0x14);
        REAL(object, 0x18) = REAL(linked, 0x18) + 1.5f;
        euler_rotation_basis(linked + 0xc0, object + 0xf0);
        if ((unsigned int)(UHALF(state, 0x264) - 1) > 1 && BYTE(object, 0x20) != 0x26 && BYTE(object, 0x20) != 0x28) {
            PLAY(object, 0x1f, 0, 8);
            func_PAL_002A7E68(linked, 0, 0, 8);
            moby_set_state(object, 0x28, -1);
        }
        if (BYTE(object, 0x20) == 0x28 && HALF(state, 0x264) == 2) {
            moby_set_controller_speed_limits(object, 0.0056000003f, 0.14000002f, 0.0016755164f, 0.12566373f);
            PLAY(object, 0x20, 0, 8);
            moby_set_state(object, 0x27, -1);
            func_PAL_002A7E68(linked, 1, 0, 8);
        }
        break;
    }
    case 9:
        distance = coll_probe_ground_height_below(((char *)object + 0x10), 0, 0.5f);
        math_spring_float_to_goal((float *)(object + 0x18), (float *)(state + 0x550), distance,
                     0.00080000004f, 0.00040000002f, 0.37600002f);
        break;
    default:
        break;
    }
    switch (BYTE(object, 0x20)) {
    case 2:
    case 3: {
        float range;

        if ((BYTE(object, 0x60) & 2) != 0) {
            UHALF(object, 0x34) |= 0x5000;
            WORD(object, 0x98) = WORD(POINTER(object, 0x24), 0x10);
            moby_set_state(object, 0x13, 1);
            if (HALF(state, 0x260) < 250) HALF(state, 0x260) = ((s32)math_random_int_range(480, 600) * 5 + 2) / 6;
            PLAY(object, 13, 0, 8);
            if (REAL(state, 0x20) <= 0.0f) REAL(state, 0x20) = 0.1f;
        }
        range = moby_get_anim_value((char *)object);
        if (range >= 10.0f) REAL(object, 0x18) = coll_probe_ground_height_below(((char *)object + 0x10), 0, 0.5f);
        if (range >= 1.5f && range <= 17.0f) {
            offset.v[0] = math_fast_sin_or_cos_a(REAL(object, 0xf8) + 3.141593f) * 0.15f;
            offset.v[1] = math_fast_sin_or_cos_b(REAL(object, 0xf8) + 3.141593f) * 0.15f;
            offset.v[2] = 0.0f;
            side.v[0] = math_fast_sin_or_cos_a(REAL(object, 0xf8) + 1.5707965f) * 0.05f;
            side.v[1] = math_fast_sin_or_cos_b(REAL(object, 0xf8) + 1.5707965f) * 0.05f;
            side.v[2] = 0.0f;
            point.word = QUAD(object, 0x10);
            FastVecAdd(&point, ((char *)object + 0x10), &side);
            FastVecAdd(&point, ((char *)object + 0x10), &offset);
            moby_move_over_ground(object, ((char *)object + 0x10), &point, 0.5f, 0.55f, 0.5f, 0.52359885f, 0);
        }
        break;
    }
    case 5: {
        char *target = POINTER(state, 0x55c);

        if (target == 0) break;
        if (WORD(state, 0x540) == 3 && BYTE(object, 0x95) != 10) {
            limit = 1.5707965f;
            angle = mat_fast_helper_a(REAL(target, 0x10) - REAL(object, 0x10), REAL(target, 0x14) - REAL(object, 0x14));
            angle = fast_subtract_rotations(angle, REAL(object, 0xf8));
            if (flag_is_third_pending_set(object) != 0) angle = -angle;
            if (angle > limit) angle = limit;
            else if (angle < -limit) angle = -limit;
            REAL(state, 0x308) = angle;
        }
    }
        if (WORD(state, 0x540) == 1 && BYTE(object, 0x42) == 0x1c && math_random_int_below(200) == 1) {
            PLAY(object, 0x1b, 0, 25);
            if (math_random_int_below(3) == 1) PLAY(object, 0x1a, 0, 25);
        }
        if ((unsigned int)(BYTE(object, 0x42) - 0x1a) < 2 && (BYTE(object, 0x60) & 2) != 0) {
            PLAY(object, 0x1d, 0, 25);
            if (HALF(POINTER(state, 0x55c), 0xaa) == 0xcf5) {
                WORD(POINTER(POINTER(state, 0x55c), 0x68), 0x540) = 1;
                WORD(state, 0x540) = 2;
            }
        }
        if (BYTE(object, 0x42) == 0x1d && (BYTE(object, 0x60) & 2) != 0) {
            PLAY(object, 0x1e, 0, 25);
            if (WORD(state, 0x540) == 1) PLAY(object, 0x1c, 0, 25);
            if (WORD(state, 0x540) == 3) {
                unsigned short *ids;
                char *linked;

                ids = g_group_id_lists[BYTE(object, 0x21)];
                for (;;) {
                    linked = moby_at(group_entry_id(ids));
                    if (moby_state(linked) >= 0 && moby_class(linked) == 0xcf5 &&
                        rider_kind(linked) == 1)
                        break;
                    if (*(short *)ids++ < 0) goto partner_done;
                }
                POINTER(state, 0x55c) = linked;
            partner_done:;
            }
        }
        if (WORD(state, 0x540) == 1 && BYTE(object, 0x42) == 0x1e) PLAY(object, 0x1d, 0, 17);
        if (WORD(state, 0x540) == 3 && BYTE(POINTER(state, 0x55c), 0x42) == 0x1d) PLAY(object, 0x1d, 0, 29);
        break;
    case 6:
        WORD(state, 0x290) = 1;
        if ((BYTE(object, 0x60) & 2) != 0) {
            moby_set_state(object, 7, -1);
            PLAY(object, 0x10, 0, 25);
            WORD(state, 0x290) = 0;
        }
        break;
    case 7:
        if (path_follow_nodes_pal((char *)object, g_path_l11_table[WORD(state, 0x558)]) == 0) break;
        moby_set_state(object, 11, -1);
        PLAY(object, 0x18, 0, 17);
        if (BYTE(object, 0x95) == 1 && WORD(state, 0x56c) != -1) moby_set_state(object, 0x17, -1);
        break;
    case 8:
        if (path_follow_nodes_pal((char *)object, g_path_l11_table[WORD(state, 0x574)]) != 0) {
            moby_set_state(object, 11, -1);
            PLAY(object, 0x18, 0, 17);
        }
        break;
    case 9:
        moby_l01_turn_toward_target_pal((char *)object, g_path_l11_table[WORD(state, 0x574)] + 0x10);
        if (vec_distance_xy(((char *)object + 0x10), g_path_l11_table[WORD(state, 0x574)] + 0x10) < 0.5f) {
            PLAY(object, 0x25, 0, 8);
            moby_set_state(object, 10, -1);
        }
        if (WORD(state, 0x588) != 0) {
            if (BYTE(object, 0x43) != 15) func_PAL_002A7E68(object, 15, 0, ((s32)math_random_int_range(5, 15) * 5 + 2) / 6);
            moby_set_state(object, 8, 8);
        }
        break;
    case 10:
        if ((BYTE(object, 0x60) & 2) != 0) {
            if (BYTE(object, 0x43) != 15) func_PAL_002A7E68(object, 15, 0, ((s32)math_random_int_range(5, 15) * 5 + 2) / 6);
            moby_set_state(object, 8, 8);
            WORD(state, 0x588) = 1;
        }
        break;
    case 11:
        if ((BYTE(object, 0x60) & 2) != 0) {
            moby_set_controller_speed_limits(object, 0.0022f, 0.055000003f, 0.0016755164f, 0.12566373f);
            if (moby_count_group_not_in_state(BYTE(object, 0x21), -1) > 1) {
                POINTER(state, 0x55c) = (char *)moby_find_linked_object(object);
                moby_set_state(object, 13, -1);
                PLAY(object, 0x1c, 0, 25);
                WORD(state, 0x540) = 1;
                if (BYTE(POINTER(state, 0x55c), 0x42) == 0x1c) {
                    PLAY(object, 0x1e, 0, 25);
                    WORD(state, 0x540) = 2;
                }
            }
        }
        break;
    case 13:
        moby_step_controller_pal(object, ((char *)object + 0x10),
                      mat_fast_helper_a(REAL(POINTER(state, 0x55c), 0x10) - REAL(object, 0x10), REAL(POINTER(state, 0x55c), 0x14) - REAL(object, 0x14)));
        angle = mat_fast_helper_a(REAL(POINTER(state, 0x55c), 0x10) - REAL(object, 0x10), REAL(POINTER(state, 0x55c), 0x14) - REAL(object, 0x14));
        if (FastDiffRots(REAL(object, 0xf8), angle) < 0.087266475f) moby_set_state(object, 5, -1);
        break;
    case 14:
        moby_set_controller_speed_limits(object, 0.0022f, 0.055000003f, 0.005445428f, 0.35604724f);
        if (path_follow_nodes_pal((char *)object, g_path_l11_table[WORD(state, 0x54c)]) != 0) {
            moby_set_state(object, 0x11, -1);
            PLAY(object, 13, 0, 17);
        }
        break;
    case 15: {
        float turn_scale = 1.0f;
        float turned;

        moby_set_controller_speed_limits(object, 0.0022f, 0.055000003f, 0.010890856f, 0.7120945f);
        if (path_follow_nodes_pal((char *)object, g_path_l11_table[WORD(state, 0x54c)]) != 0) {
            path = g_path_l11_table[WORD(state, 0x54c)];
            distance = vec_distance_xy(((char *)object + 0x10), path + 0x10);
            other_angle = vec_distance_xy(((char *)object + 0x10), path + WORD(path, 0) * 0x10);
            if (other_angle < distance) path_set_follower_nodes(object, g_path_l11_table[WORD(state, 0x54c)], 0, WORD(path, 0) - 1);
            else path_set_follower_nodes(object, g_path_l11_table[WORD(state, 0x54c)], WORD(path, 0) - 1, 0);
            if (math_random_int_below(5) == 1) {
                PLAY(object, 0x19, 0, 12);
                moby_set_state(object, 0x10, -1);
            }
        }
        limit = 1.5707965f;
        angle = mat_fast_helper_a(g_hero_state.position.v[0] - REAL(object, 0x10), g_hero_state.position.v[1] - REAL(object, 0x14));
        angle = fast_subtract_rotations(angle, REAL(object, 0xf8));
        if (flag_is_third_pending_set(object) != 0) angle = FastAddRotations(angle, 3.141593f);
        if (angle > limit) angle = limit;
        else if (angle < -limit) angle = -limit;
        turned = FastAddRotations(angle * turn_scale, REAL(state, 0x308));
        REAL(state, 0x308) = turned;
        if (turned > limit) REAL(state, 0x308) = limit;
        else if (turned < -limit) REAL(state, 0x308) = -limit;
        break;
    }
    case 16:
        moby_step_controller_pal(object, ((char *)object + 0x10), mat_fast_helper_a(g_hero_state.position.v[0] - REAL(object, 0x10), g_hero_state.position.v[1] - REAL(object, 0x14)));
        if ((BYTE(object, 0x60) & 2) != 0) {
            moby_set_state(object, 15, -1);
            PLAY(object, 0x10, 0, 17);
        }
        break;
    case 17:
        if ((BYTE(object, 0x60) & 2) != 0) {
            path = g_path_l11_table[WORD(state, 0x54c)];
            distance = vec_distance_xy(((char *)object + 0x10), path + 0x10);
            other_angle = vec_distance_xy(((char *)object + 0x10), path + WORD(path, 0) * 0x10);
            if (other_angle < distance) path_set_follower_nodes(object, g_path_l11_table[WORD(state, 0x54c)], 0, WORD(path, 0) - 1);
            else path_set_follower_nodes(object, g_path_l11_table[WORD(state, 0x54c)], WORD(path, 0) - 1, 0);
            moby_set_state(object, 14, -1);
            PLAY(object, 0x10, 0, 17);
        }
        break;
    case 19:
        moby_turn_toward_position((struct family_27f9_object *)object, (float *)g_hero_state.moby, (float *)(state + 0x27c),
                     0.001f, 0.01f, 0.1f);
        if ((BYTE(object, 0x60) & 2) != 0) {
            PLAY(object, 0x17, 0, 17);
            moby_set_state(object, 0x14, -1);
            WORD(state, 0x178) |= 0x10;
            if (WORD(state, 0x56c) != -1) QUAD(state, 0x110) = QUAD(g_path_l11_table[WORD(state, 0x56c)], 0x10);
        }
        break;
    case 20:
        WORD(state, 0x290) = 1;
        moby_turn_toward_position((struct family_27f9_object *)object, (float *)g_hero_state.moby, (float *)(state + 0x27c),
                     0.001f, 0.01f, 0.1f);
        moby_set_controller_speed_limits(object, 0.00080000004f, 0.020000001f, 0.0016755164f, 0.12566373f);
        moby_l01_turn_toward_target_pal((char *)object, state + 0x110);
        if (vec_distance_xy(((char *)object + 0x10), state + 0x110) < 2.0f) {
            WORD(state, 0x178) &= ~0x10;
            moby_set_state(object, 0x15, -1);
            PLAY(object, 0x18, 0, 17);
            if (WORD(state, 0x56c) != -1) moby_set_state(object, 0x17, -1);
        }
        break;
    case 22:
        moby_set_controller_speed_limits(object, 0.0022f, 0.055000003f, 0.005445428f, 0.35604724f);
        if (path_follow_nodes_pal((char *)object, g_path_l11_table[WORD(state, 0x56c)]) != 0) {
            moby_set_state(object, 0x17, -1);
            PLAY(object, 0x18, 0, 17);
        }
        break;
    case 23:
        if ((BYTE(object, 0x60) & 2) != 0) {
            path = g_path_l11_table[WORD(state, 0x56c)];
            distance = vec_distance_xy(((char *)object + 0x10), path + 0x10);
            other_angle = vec_distance_xy(((char *)object + 0x10), path + WORD(path, 0) * 0x10);
            if (other_angle < distance) path_set_follower_nodes(object, g_path_l11_table[WORD(state, 0x56c)], 0, WORD(path, 0) - 1);
            else path_set_follower_nodes(object, g_path_l11_table[WORD(state, 0x56c)], WORD(path, 0) - 1, 0);
            moby_set_state(object, 22, -1);
            PLAY(object, 0x10, 0, 17);
        }
        break;
    case 28: {
        char *other_state;

        if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) < 3.5f && REAL(state, 0x20) > 1.0f) {
            WORD(state, 0x290) = 1;
            moby_set_controller_speed_limits(object, 0.00080000004f, 0.020000001f, 0.0016755164f, 0.12566373f);
            moby_set_state(object, 0x1b, -1);
            PLAY(object, 0x17, 0, 8);
            break;
        }
        if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) < 2.5f) {
            angle = mat_fast_helper_a(g_hero_state.position.v[0] - REAL(object, 0x10), g_hero_state.position.v[1] - REAL(object, 0x14));
            if (FastDiffRots(REAL(object, 0xf8), angle) < 0.3490659f) {
                PLAY(object, 0x11, 0, 8);
                moby_set_controller_speed_limits(object, 0.0056000003f, 0.14000002f, 0.0016755164f, 0.12566373f);
                moby_set_state(object, 0x22, 2);
                break;
            }
        }
        if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) < 2.5f) {
            moby_step_controller_pal(object, ((char *)object + 0x10), mat_fast_helper_a(g_hero_state.position.v[0] - REAL(object, 0x10), g_hero_state.position.v[1] - REAL(object, 0x14)));
            break;
        }
        if (WORD(state, 0x528) == 0) {
            moby_turn_toward_target_and_step_pal((char *)object, g_hero_state.position.v, REAL(state, 0x298));
        } else if (func_PAL_L11_0042A858((char *)object, (char *)&g_hero_state.position, REAL(object, 0xf8), 7.0f, 0.25f, REAL(state, 0x298)) != 0 &&
                   BYTE(object, 0x21) <= g_tribe_group_limit && moby_count_group_not_in_state(BYTE(object, 0x21), -1) > 1) {
            unsigned short *ids;
            unsigned int id;

            ids = g_group_id_lists[BYTE(object, 0x21)];
            do {
                char *partner;

                id = *ids;
                partner = (char *)(g_moby_l11_table + (id & 0x7fff) * 0x100);
                other_state = POINTER(partner, 0x68);
                if (WORD(other_state, 0x294) == 0) {
                    distance = vec_distance_xy(partner + 0x10, &g_hero_state.position);
                    other_angle = vec_distance_xy(((char *)object + 0x10), &g_hero_state.position);
                    if (distance < other_angle && REAL(other_state, 0x20) > 0.0f) {
                        WORD(other_state, 0x294) = 1;
                        WORD(state, 0x294) = 0;
                        PLAY(object, 14, 0, 8);
                        moby_set_state(object, 0x18, 3);
                    }
                    break;
                }
                ++ids;
            } while ((short)id >= 0);
        }
        break;
    }
    case 29: {
        char *other_state;
        char *linked;

        linked = (char *)(g_moby_l11_table + WORD(state, 0x548) * 0x100);
        other_state = POINTER(linked, 0x68);
        if (BYTE(linked, 0x20) != 5) {
            vec_spring_to_target(linked + 0xf0, object + 0xf0, state + 0x550, 0.0016755164f, 0.0033510327f, 0.12566373f);
            euler_rotation_basis(linked + 0xc0, linked + 0xf0);
            REAL(linked, 0x18) += ((REAL(other_state, 0x5c) - 1.2f) - REAL(linked, 0x18)) * 0.11f;
        }
        moby_l01_turn_toward_target_pal((char *)object, linked + 0x10);
        if (vec_distance_xy(((char *)object + 0x10), linked + 0x10) < 1.5f && BYTE(linked, 0x20) != 5) {
            BYTE(linked, 0x20) = 6;
            REAL(object, 0x10) = REAL(linked, 0x10);
            REAL(object, 0x14) = REAL(linked, 0x14);
            REAL(object, 0x18) = REAL(linked, 0x18) + 1.5f;
            REAL(state, 0x554) = REAL(linked, 0x18) + 0.75f;
            PLAY(object, 0x1f, 0, 21);
            moby_set_state(object, 0x26, 7);
            WORD(state, 0x584) = 0;
            BYTE(object, 0xbc) = 1;
        }
        break;
    }
    case 32: {
        char *linked;

        linked = (char *)(g_moby_l11_table + WORD(state, 0x580) * 0x100);
        moby_l01_turn_toward_target_pal((char *)object, linked + 0x10);
        if (vec_distance_xy(((char *)object + 0x10), linked + 0x10) < 0.25f) {
            if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) < 8.0f) {
                WORD(state, 0x290) = 1;
                PLAY(object, 0x15, 0, 8);
                moby_set_state(object, 0x19, -1);
            } else {
                WORD(state, 0x290) = 1;
                PLAY(object, 15, 0, 8);
                moby_set_state(object, 0x1a, 3);
            }
            if (WORD(state, 0x294) != 0) {
                PLAY(object, 15, 0, 8);
                moby_set_state(object, 0x1c, 2);
            }
            moby_set_flag_bit((unsigned char *)linked, 5);
        }
        break;
    }
    case 38: {
        char *linked;

        linked = (char *)(g_moby_l11_table + WORD(state, 0x548) * 0x100);
        math_spring_float_to_goal((float *)(linked + 0x18), (float *)(state + 0x550), REAL(state, 0x554),
                     0.00040000002f, 0.0024f, 0.040000003f);
        REAL(object, 0x18) = REAL(linked, 0x18) + 1.5f;
        if (math_fabs(REAL(linked, 0x18) - REAL(state, 0x554)) < 0.1f) {
            PLAY(object, 0x20, 0, 4);
            moby_set_state(object, 0x27, -1);
            PLAY(linked, 1, 0, 4);
        }
        angle = mat_fast_helper_a(g_hero_state.position.v[0] - REAL(object, 0x10), g_hero_state.position.v[1] - REAL(object, 0x14));
        if (FastDiffRots(REAL(object, 0xf8), angle) < 0.26179942f && BYTE(linked, 0x43) != 1) {
            func_PAL_002A7E68(linked, 1, 0, 4);
            PLAY(object, 0x20, 0, 4);
            break;
        }
        if (BYTE(linked, 0x42) != 1) break;
        if (func_PAL_002AF6C0(linked, 6.0f) != 0 || func_PAL_002AF6C0(linked, 12.0f) != 0 || func_PAL_002AF6C0(linked, 0.0f) != 0) {
            moby_transform_joint_to_world(linked, 1, (char *)&offset);
            FastVecSub(&side, &g_hero_state.aim, &offset);
            vec_scale_to_length(&side, &side, 0.6f);
            robot_spawn_debris_pal(linked, &side, &offset, 0, (float)BYTE(state, 0x36));
            break;
        } else if (func_PAL_002AF6C0(linked, 3.0f) != 0 || func_PAL_002AF6C0(linked, 9.0f) != 0 || func_PAL_002AF6C0(linked, 15.0f) != 0) {
            moby_transform_joint_to_world(linked, 0, (char *)&offset);
            FastVecSub(&side, &g_hero_state.aim, &offset);
            vec_scale_to_length(&side, &side, 0.6f);
            robot_spawn_debris_pal(linked, &side, &offset, 0, (float)BYTE(state, 0x36));
            break;
        }
        break;
    }
    case 39: {
        char *linked;

        linked = (char *)(g_moby_l11_table + WORD(state, 0x548) * 0x100);
        if (func_PAL_002AF6C0(linked, 6.0f) != 0 || func_PAL_002AF6C0(linked, 12.0f) != 0 || func_PAL_002AF6C0(linked, 0.0f) != 0) {
            moby_transform_joint_to_world(linked, 1, (char *)&offset);
            FastVecSub(&side, &g_hero_state.aim, &offset);
            vec_scale_to_length(&side, &side, 0.6f);
            robot_spawn_debris_pal(linked, &side, &offset, 0, (float)BYTE(state, 0x36));
            break;
        } else if (func_PAL_002AF6C0(linked, 3.0f) != 0 || func_PAL_002AF6C0(linked, 9.0f) != 0 || func_PAL_002AF6C0(linked, 15.0f) != 0) {
            moby_transform_joint_to_world(linked, 0, (char *)&offset);
            FastVecSub(&side, &g_hero_state.aim, &offset);
            vec_scale_to_length(&side, &side, 0.6f);
            robot_spawn_debris_pal(linked, &side, &offset, 0, (float)BYTE(state, 0x36));
            break;
        }
        break;
    }
    case 40: {
        char *mount, *node, *next;

        if (WORD(state, 0x564) == -1) break;
        moby_set_controller_speed_limits(object, 0.0056000003f, 0.14000002f, 0.0027925272f, 0.0069813184f);
        node = g_path_l11_table[WORD(state, 0x564)] + WORD(state, 0x568) * 0x10;
        mount = (char *)(g_moby_l11_table + WORD(state, 0x548) * 0x100);
        moby_step_controller_pal(object, ((char *)object + 0x10), mat_fast_helper_a(REAL(node, 0x10) - REAL(object, 0x10), REAL(node, 0x14) - REAL(object, 0x14)));
        REAL(object, 0x10) = REAL(mount, 0x10);
        REAL(object, 0x14) = REAL(mount, 0x14);
        REAL(object, 0x18) = REAL(mount, 0x18) + 1.5f;
        euler_rotation_basis(mount + 0xc0, object + 0xf0);
        next = g_path_l11_table[WORD(state, 0x564)] + WORD(state, 0x568) * 0x10;
        angle = mat_fast_helper_a(REAL(next, 0x10) - REAL(object, 0x10), REAL(next, 0x14) - REAL(object, 0x14));
        if (FastDiffRots(REAL(object, 0xf8), angle) <= 0.087266475f) {
            ++WORD(state, 0x568);
            if (WORD(state, 0x568) > 1) WORD(state, 0x568) = 0;
            if (BYTE(object, 0x42) == 0x20 && UHALF(object, 0x96) > 120) {
                PLAY(object, 0x1f, 0, 8);
                func_PAL_002A7E68(mount, 0, 0, 8);
            }
        }
        if (WORD(state, 0x584) != 0) {
            STUB_printf(g_str_tribesman_debug);
            PLAY(object, 0x20, 0, 4);
            func_PAL_002A7E68(mount, 1, 0, 4);
            WORD(state, 0x584) = 0;
            UHALF(object, 0x96) = 0;
        }
        if (BYTE(object, 0x42) != 0x20) break;
        if (func_PAL_002AF6C0(mount, 6.0f) != 0 || func_PAL_002AF6C0(mount, 12.0f) != 0 || func_PAL_002AF6C0(mount, 0.0f) != 0) {
            moby_transform_joint_to_world(mount, 1, (char *)&offset);
            vec_build_spherical_offset(side.v, 0.6f, REAL(object, 0xf8),
                          mat_fast_helper_a(vec_distance_xy(&offset, &g_hero_state.aim), g_hero_state.aim.v[2] - offset.v[2]));
            robot_spawn_debris_pal(mount, &side, &offset, 0, (float)BYTE(state, 0x36));
        } else if (func_PAL_002AF6C0(mount, 3.0f) != 0 || func_PAL_002AF6C0(mount, 9.0f) != 0 || func_PAL_002AF6C0(mount, 15.0f) != 0) {
            moby_transform_joint_to_world(mount, 0, (char *)&offset);
            vec_build_spherical_offset(side.v, 0.6f, REAL(object, 0xf8),
                          mat_fast_helper_a(vec_distance_xy(&offset, &g_hero_state.aim), g_hero_state.aim.v[2] - offset.v[2]));
            robot_spawn_debris_pal(mount, &side, &offset, 0, (float)BYTE(state, 0x36));
        }
        break;
    }
    case 24:
        WORD(state, 0x290) = 0;
        moby_step_controller_pal(object, ((char *)object + 0x10), mat_fast_helper_a(g_hero_state.position.v[0] - REAL(object, 0x10), g_hero_state.position.v[1] - REAL(object, 0x14)));
        if ((BYTE(object, 0x60) & 2) == 0 && WORD(state, 0x578) == 0 && BYTE(object, 0x42) != 15) break;
        if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) < 8.0f) {
            WORD(state, 0x290) = 1;
            PLAY(object, 0x15, 0, 8);
            moby_set_state(object, 0x19, -1);
        } else {
            WORD(state, 0x290) = 1;
            PLAY(object, 15, 0, 8);
            moby_set_state(object, 0x1a, 3);
        }
        if (WORD(state, 0x294) != 0) {
            PLAY(object, 15, 0, 8);
            moby_set_state(object, 0x1c, 2);
        }
        break;
    case 31:
        moby_l01_turn_toward_target_pal((char *)object, POINTER(state, 0x274) + 0x10);
        if (vec_distance_xy(((char *)object + 0x10), POINTER(state, 0x274) + 0x10) < 2.1f) {
            PLAY(object, 0, 0, 17);
            moby_set_state(object, 0x21, -1);
        }
        break;
    case 33:
        MobySpringTurn((struct family_27f9_object *)object, (float *)(state + 0x27c), REAL(POINTER(state, 0x274), 0xf8),
                     0.003f, 0.03f, 0.12566373f);
        FastVecSub(&offset, POINTER(state, 0x274) + 0x10, ((char *)object + 0x10));
        vec_scale_to_length(&offset, &offset, 0.120000005f);
        FastVecAdd(((char *)object + 0x10), ((char *)object + 0x10), &offset);
        if (vec_distance_xy(((char *)object + 0x10), POINTER(state, 0x274) + 0x10) < 0.05f) {
            moby_set_state(object, 1, 5);
            {
                char *dock = POINTER(state, 0x274);

                QUAD(object, 0x10) = QUAD(dock, 0x10);
                QUAD(object, 0xf0) = QUAD(dock, 0xf0);
            }
            WORD(object, 0x98) = 0;
            UHALF(object, 0x34) &= 0xafff;
            {
                char *dock_state = POINTER(POINTER(state, 0x274), 0x68);

                POINTER(dock_state, 0x27c) = (char *)object;
                WORD(dock_state, 0x2c8) = 0;
            }
            POINTER(state, 0x280) = CreateMoby(0x911);
            if (POINTER(state, 0x280) != 0) {
                BYTE(POINTER(state, 0x280), 0x30) = BYTE(object, 0x30);
                BYTE(POINTER(state, 0x280), 0x31) = 0;
                func_002A0F48(POINTER(state, 0x280));
                {
                    char *carrier = POINTER(state, 0x280);

                    QUAD(carrier, 0x10) = QUAD(object, 0x10);
                    REAL(carrier, 0x18) += 0.75f;
                }
            }
            WORD(state, 0x26c) = 1;
        }
        break;
    case 25:
        moby_turn_toward_position((struct family_27f9_object *)object, (float *)g_hero_state.moby, (float *)(state + 0x27c), 0.001f, 0.01f, 0.1f);
        if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) > 12.0f) {
            PLAY(object, 15, 0, 8);
            moby_set_state(object, 0x1a, -1);
        }
        if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) < 2.5f) {
            PLAY(object, 0x11, 0, 8);
            moby_set_state(object, 0x22, -1);
        }
        if (math_random_int_below(3) == 1 && (BYTE(object, 0x60) & 2) != 0) {
            PLAY(object, 0x19, 0, 8);
            if (math_random_int_below(3) == 1) PLAY(object, 0x18, 0, 8);
            moby_set_state(object, 0x18, 3);
        }
        break;
    case 26:
        if (WORD(state, 0x528) != 0) {
            if (func_PAL_L11_0042A858((char *)object, (char *)&g_hero_state.position, REAL(object, 0xf8), 7.0f, 0.25f, REAL(state, 0x298)) != 0) {
                PLAY(object, 0x15, 0, 8);
                moby_set_state(object, 0x19, -1);
            }
        } else {
            moby_turn_toward_target_and_step_pal((char *)object, g_hero_state.position.v, REAL(state, 0x298));
        }
        if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) < 8.0f) {
            PLAY(object, 0x15, 0, 8);
            moby_set_state(object, 0x19, -1);
        }
        break;
    case 27:
        if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) < 2.5f) {
            angle = mat_fast_helper_a(g_hero_state.position.v[0] - REAL(object, 0x10), g_hero_state.position.v[1] - REAL(object, 0x14));
            if (FastDiffRots(REAL(object, 0xf8), angle) < 0.3490659f) {
                PLAY(object, 0x11, 0, 5);
                moby_set_controller_speed_limits(object, 0.0056000003f, 0.14000002f, 0.0016755164f, 0.12566373f);
                moby_set_state(object, 0x22, 2);
                break;
            }
        }
        if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) < 2.5f) {
            moby_step_controller_pal(object, ((char *)object + 0x10), mat_fast_helper_a(g_hero_state.position.v[0] - REAL(object, 0x10), g_hero_state.position.v[1] - REAL(object, 0x14)));
            break;
        }
        if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) > 5.0f) {
            moby_set_controller_speed_limits(object, 0.0056000003f, 0.14000002f, 0.0016755164f, 0.12566373f);
            PLAY(object, 15, 0, 8);
            moby_set_state(object, 0x1c, -1);
        } else {
            moby_set_controller_speed_limits(object, 0.00080000004f, 0.020000001f, 0.0016755164f, 0.12566373f);
            moby_turn_toward_target_and_step_pal((char *)object, g_hero_state.position.v, REAL(state, 0x298));
        }
        break;
    case 30:
        if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) < 2.5f) {
            PLAY(object, 0x11, 0, 2);
            moby_set_state(object, 0x22, -1);
            WORD(state, 0x284) = -1;
            REAL(state, 0x164) = 0.0012f;
        } else {
            REAL(state, 0x164) = 0.006f;
            if (path_follow_nodes_pal((char *)object, g_path_l11_table[WORD(state, 0x284)]) != 0) {
                if (WORD(state, 0x294) == 1) {
                    PLAY(object, 15, 0, 8);
                    moby_set_state(object, 0x1c, 2);
                } else {
                    WORD(state, 0x290) = 1;
                    if (math_random_int_below(3) == 1) {
                        PLAY(object, 14, 0, 8);
                        moby_set_state(object, 0x18, 3);
                    } else {
                        PLAY(object, 15, 0, 8);
                        moby_set_state(object, 0x1a, 3);
                    }
                }
                WORD(state, 0x284) = -1;
            }
        }
        break;
    case 34: {
        float range;

        WORD(state, 0x290) = 0;
        range = moby_get_anim_value((char *)object);
        if (BYTE(object, 0x42) == 0x11 && range >= 10.0f && range <= 15.0f) {
            moby_transform_joint_to_world((char *)object, 2, (char *)&offset);
            side.v[0] = math_fast_sin_or_cos_a(REAL(object, 0xf8)) * 0.5f;
            side.v[1] = math_fast_sin_or_cos_b(REAL(object, 0xf8)) * 0.5f;
            side.v[2] = 0.0f;
            FastVecAdd(&offset, &offset, &side);
            coll_sweep_from_object(object, &offset, 1, 0.4f, REAL(state, 0x28c), 1.0f, 0, 1, 0);
            side.v[0] = math_fast_sin_or_cos_a(REAL(object, 0xf8));
            side.v[1] = math_fast_sin_or_cos_b(REAL(object, 0xf8));
            side.v[2] = 0.0f;
            FastVecAdd(&offset, &offset, &side);
            coll_sweep_from_object(object, &offset, 1, 0.4f, REAL(state, 0x28c), 1.0f, 0, 1, 0);
        } else REAL(object, 0x48) = 1.0f;
        if ((BYTE(object, 0x60) & 2) == 0) break;
        if (REAL(state, 0x20) > 1.0f) {
            PLAY(object, 0x22, 0, 8);
            if (math_random_int_below(2) == 1) PLAY(object, 14, 0, 8);
            moby_set_state(object, 0x23, -1);
        } else {
            PLAY(object, 0x22, 0, 8);
            if (math_random_int_below(2) == 1) PLAY(object, 14, 0, 8);
            moby_set_state(object, 0x23, -1);
        }
        if (BYTE(object, 0x95) != 2) {
            moby_set_state(object, 0x19, -1);
            PLAY(object, 0x15, 0, 8);
        }
        break;
    }
    case 35:
        if ((BYTE(object, 0x60) & 2) != 0) {
            if (vec_distance_xy(((char *)object + 0x10), &g_hero_state.position) < 2.5f) {
                PLAY(object, 15, 0, 8);
                moby_set_state(object, 0x1c, -1);
            } else {
                PLAY(object, 15, 0, 8);
                moby_set_state(object, 0x1c, -1);
            }
        }
        break;
    case 1:
    default:
        break;
    }
    func_PAL_L11_0042AB20((char *)object);
    if (math_fabs(REAL(object, 0x18) - old_z) < 0.005f) REAL(object, 0x18) = old_z;
}
