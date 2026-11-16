#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

typedef int s32;

typedef unsigned int u32;

typedef unsigned char u8;

typedef unsigned short u16;

typedef short s16;

typedef float f32;

/* Small-data controls: the four measured globals the level's script hooks share. */
extern s32 g_arena_intro_script_handle_a __attribute__((sda));

extern s32 g_arena_intro_script_handle_b __attribute__((sda));

extern s32 g_arena_intro_script_handle_c __attribute__((sda));

extern s32 g_arena_intro_script_handle_d __attribute__((sda));

extern void func_3004A8(void *);

extern void func_4882F0(void *, void *, s32, s32, s32);

extern void func_488268(s32, s32);

extern void func_4881A8(void *);

extern void func_488200(void *);

extern u32 g_arena_script_flags[1];

extern u8 g_hero_l11_position[];

extern u8 *g_moby_l11_table[3] __attribute__((sda));

extern u8 *g_group_id_lists[];

extern float func_282E48(void *, void *);

extern void func_32C9E0();

extern void func_440C90(u8 *);

/* One class record of the measured class table: six halfwords, then the two flag
   bytes at 0x14 and 0x15.  The record is 26 bytes long. */
typedef struct {
    s16 half[6];
    u8 pad0[8];
    u8 flag14;
    u8 flag15;
    u8 pad1[4];
} JobaClassRecordView;

typedef struct {
    s32 count;
    JobaClassRecordView *records;
} JobaClassTableView;

/* The class table itself: an array of pointers to the per-class entries. */
extern u32 g_arena_challenge_table __attribute__((sda));

/* Checks the state's six counters against the class record and reports whether the
   class may still be used. */
/* Tells whether the current wave is finished: all fighters of the wave were used and none are left alive. */
s32 arena_l11_is_wave_complete(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 index = *(s16 *)(state + 0x1F0);
    s32 cls = *(s16 *)(state + 0x1F2);
    JobaClassTableView *entry = ((JobaClassTableView **)&g_arena_challenge_table)[index];
    JobaClassRecordView *rec = &entry->records[cls];
    u32 *counters = (u32 *)(state + 0x100);
    s32 same = 1;
    s32 i;
    s32 result;
    for (i = 0; i < 6; i++) {
        same &= (counters[i] == (u32)rec->half[i]);
    }
    if (rec->flag14 != 0) {
        same &= *(u32 *)(state + 0x118);
    }
    if (rec->flag15 != 0) {
        same &= *(u32 *)(state + 0x11C);
    }
    result = 0;
    if (*(u32 *)(state + 0x140) == 0) {
        if (same != 0) {
            result = 1;
        }
    }
    return result;
}

/* The group count and the entity table's base, as the walks below reach them: the count through
   $gp, the base as a bare symbol (a three-word `sda` array keeps the `lui`/`lw` pair). */
extern s32 g_tribe_group_limit __attribute__((sda));

extern u8 *D_L11_001B359C_abs[3] __attribute__((sda));

extern char g_hero_position[];

extern s32 arena_is_entity_far_in_direction(u8 *);

extern s32 moby_has_free_child_slot_state2(u8 *);

extern float vec_distance_xy(void *, void *);

#define GROUP(off) (*(s32 *)(state + (off)))

/* Claims the slot at the state's count (+0x18C) in its 0x120 table: an empty slot is taken as it
   is, a filled one only when func_L02_003D77B8 refuses its entity and the count is still below
   the class record's limit (byte 0x16), which then advances. The slot gets the first entity of the
   group's id list (state word 0xC4) that func_L11_00442B60 and func_L02_003D77B8 both accept;
   when the slot is still empty after that walk, the first entity that func_L02_003D77B8 accepts
   and that lies more than 30.0 from D_00189EA0 takes it. The table address is formed at each use
   (retail does), which lets GCSE hoist it ahead of the first walk. */
/* Picks the next fighter that will lead the current squad. */
void arena_choose_next_squad_member(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    JobaClassTableView *entry = ((JobaClassTableView **)&g_arena_challenge_table)[*(s16 *)(state + 0x1F0)];
    JobaClassRecordView *rec = &entry->records[*(s16 *)(state + 0x1F2)];
    u8 *slot = *(u8 **)(state + (*(s32 *)(state + 0x18C) << 2) + 0x120);
    s32 ok = 0;
    u16 *listStart;
    u8 **slots;
    u16 *cursor;
    u8 *member;

    if (slot != 0) {
        if (moby_has_free_child_slot_state2(slot) == 0 && *(s32 *)(state + 0x18C) < *((u8 *)rec + 0x16) - 1) {
            ok = 1;
            *(s32 *)(state + 0x18C) = *(s32 *)(state + 0x18C) + 1;
        }
    } else {
        ok = 1;
    }
    if (ok) {
        if (GROUP(0xC4) == 0xFF)
            return;
        listStart = (u16 *)g_group_id_lists[GROUP(0xC4)];
        if (listStart == 0)
            return;
        for (cursor = listStart; (GROUP(0xC4) & 0xFF) != 0xFF && GROUP(0xC4) <= g_tribe_group_limit && cursor != 0 &&
                    ((cursor != 0 && (s16)cursor[-1] >= 0) || cursor == (u16 *)g_group_id_lists[GROUP(0xC4)]);
             cursor++) {
            member = D_L11_001B359C_abs[0] + ((*cursor & 0x7FFF) << 8);
            if (member == 0)
                break;
            if (arena_is_entity_far_in_direction(member)) {
                if (moby_has_free_child_slot_state2(member)) {
                    slots = (u8 **)(state + 0x120);
                    *(u8 **)((u8 *)slots + (GROUP(0x18C) << 2)) = member;
                    break;
                }
            }
        }
        slots = (u8 **)(state + 0x120);
        if (*(u8 **)((u8 *)slots + (GROUP(0x18C) << 2)) == 0) {
            for (cursor = (u16 *)g_group_id_lists[GROUP(0xC4)];
                 (GROUP(0xC4) & 0xFF) != 0xFF && GROUP(0xC4) <= g_tribe_group_limit && cursor != 0 &&
                 ((cursor != 0 && (s16)cursor[-1] >= 0) || cursor == (u16 *)g_group_id_lists[GROUP(0xC4)]);
                 cursor++) {
                member = D_L11_001B359C_abs[0] + ((*cursor & 0x7FFF) << 8);
                if (member == 0)
                    break;
                if (moby_has_free_child_slot_state2(member)) {
                    if (vec_distance_xy(member + 0x10, g_hero_position) > 30.0f) {
                        slots = (u8 **)(state + 0x120);
                        *(u8 **)((u8 *)slots + (GROUP(0x18C) << 2)) = member;
                        return;
                    }
                }
            }
        }
    }
}

/* The four angle and length constants the script reads through $gp. */
extern f32 g_arena_fighter_param_min __attribute__((sda));

extern f32 g_arena_fighter_param_max __attribute__((sda));

extern f32 g_arena_fighter_turn_step __attribute__((sda));

extern f32 g_arena_fighter_velocity_scale __attribute__((sda));

extern float FastAddRotations(float, float);

extern float math_fast_sin_or_cos_a(float);

extern float math_fast_sin_or_cos_b(float);

extern float math_random_float_range(float, float);

extern void FastVecAdd(u8 *, u8 *, u8 *);

extern void euler_rotation_basis(u8 *, u8 *);

extern u8 *arena_get_center_point(u8 *);

extern void enemy_init_state(char *, int, int);

extern void security_robot_init(char *, int, int);

extern void smasher_robot_init(char *, int, int);

extern void flamethrower_robot_init(char *, int, int);

extern void drone_init_state(char *, int, int);

/* arms the script bridge over the measured buffers and starts it on the shared slot */
/* Starts the short intro script that moves the camera. */
void arena_start_intro_script(void) {
    s32 buffer[4];
    func_3004A8(buffer);
    func_4882F0(&g_arena_intro_script_handle_c, &g_arena_intro_script_handle_d, 1, 0, 0);
    func_488268(2, 0x168);
    func_4881A8(&g_arena_intro_script_handle_a);
    func_488200(&g_arena_intro_script_handle_b);
}

/* Turns the script's angle around the actor and hands the result to the level's
   helpers when the angle is small enough. */
/* Keeps the intro script going and changes the arena state once the camera has turned far enough. */
void arena_update_intro_script(u8 *obj) {
    s32 objState;

    g_arena_script_flags[0] = 1;
    if (func_282E48(g_hero_l11_position, &g_arena_intro_script_handle_a) < 0.01f) {
        objState = obj[0x20];
        if (objState == 4) {
            func_32C9E0(obj, 7, -1);
        } else if (objState == 5) {
            func_32C9E0(obj, 6, -1);
        }
        func_488268(1, 0);
        func_4881A8(&g_arena_intro_script_handle_a);
        func_488200(&g_arena_intro_script_handle_b);
    }
}

/* Turns the script's angle around the actor, hands the result to the level's helpers
   and counts the class the script's identifier names. */
/* Places a fighter in the arena, turns it toward the middle and starts it. It also counts the fighter as used. */
s32 arena_place_and_start_fighter(u8 *object, u8 *fighter) {
    u8 *state = *(u8 **)(object + 0x68);
    f32 turnStep = g_arena_fighter_turn_step;
    f32 value;

    value = FastAddRotations(*(f32 *)(state + 0x19C), turnStep);
    *(f32 *)(state + 0x19C) = value;
    value = math_fast_sin_or_cos_a(value);
    *(f32 *)(fighter + 0x10) = g_arena_fighter_velocity_scale * value;
    value = math_fast_sin_or_cos_b(*(f32 *)(state + 0x19C));
    *(f32 *)(fighter + 0x14) = g_arena_fighter_velocity_scale * value;
    FastVecAdd(fighter + 0x10, fighter + 0x10, arena_get_center_point(object));
    *(f32 *)(fighter + 0x18) = math_random_float_range(g_arena_fighter_param_min, g_arena_fighter_param_max);
    *(f32 *)(fighter + 0xF4) = -1.570796489715576171875f;
    *(s32 *)(fighter + 0xF0) = 0;
    *(f32 *)(fighter + 0xF8) = *(f32 *)(state + 0x19C);
    euler_rotation_basis(fighter + 0xC0, fighter + 0xF0);
    switch (*(s16 *)(fighter + 0xAA)) {
    case 0xD98 /* Joba security robot */:
        security_robot_init(fighter, 0, 1);
        *(s32 *)(state + 0x100) += 1;
        break;
    case 0xDCF /* Joba smasher robot */:
        smasher_robot_init(fighter, 0, 1);
        *(s32 *)(state + 0x104) += 1;
        break;
    case 0xDF4 /* moby class 3572 */:
        flamethrower_robot_init(fighter, 0, 1);
        *(s32 *)(state + 0x108) += 1;
        break;
    case 0xDF7 /* moby class 3575 */:
        drone_init_state(fighter, 0, 1);
        *(s32 *)(state + 0x10C) += 1;
        break;
    case 0xD37 /* moby class 3383 */:
        enemy_init_state(fighter, 0, 1);
        *(s32 *)(state + 0x114) += 1;
        break;
    }
    return 1;
}

/* The group count once more, read bare (`lui`/`lw`) in these walks, under a second name: the
   scalar above is read through $gp. */
extern s32 D_L11_001B35B8_1[] __attribute__((sda));
extern f32 g_arena_spawn_time_scale __attribute__((sda));
extern f32 g_arena_spawn_angle_scale __attribute__((sda));
extern s32 moby_is_state_six(u8 *);
extern s32 moby_is_state_one_cleared_vars(u8 *);
extern s32 math_random_int_below(s32);
extern void teleporter_bind_captured_object(u8 *, u8 *, f32, f32);

/* Leaves the function when the group is 0xFF or empty; the braces it opens close in END_IDS. */
#define FOR_EACH_ID(p, off) \
    if (GROUP(off) == 0xFF) \
        return; \
    { u16 *q = (u16 *)D_L11_001FC420[GROUP(off)]; \
    if (q == 0) \
        return; \
    for (p = q; (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L11_001B35B8_1[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L11_001FC420[GROUP(off)]); \
         p++)
#define END_IDS }
/* One half: collect the entities of group OFF for which func_00312B58 holds (counting the
   others in m), then, up to 1000 passes over the group at state word 0x17C while m is below
   the record's limit, hand one collected entity at a time to func_L02_00416720 with an entity
   of that group. */
#define HALF(limit, off) \
    { \
        s32 n, m, i, k; \
        if (*(s16 *)(rec + (limit)) != 0) { \
            m = 0; \
            n = 0; \
            for (k = 15; k >= 0; k--) \
                buf[k] = 0; \
            FOR_EACH_ID(p, off) { \
                e = D_L11_001B359C[0] + ((*p & 0x7FFF) << 8); \
                if (e == 0) \
                    break; \
                if (func_00312B58(e) == 0) { \
                    m++; \
                } else { \
                    buf[n] = e; \
                    n++; \
                } \
            } END_IDS \
            if (n != 0) { \
                for (i = 0; i < 1000 && m < *(s16 *)(rec + (limit)); i++) { \
                    FOR_EACH_ID(p, 0x17C) { \
                        e = D_L11_001B359C[0] + ((*p & 0x7FFF) << 8); \
                        if (e == 0) \
                            break; \
                        if (n <= 0) \
                            break; \
                        if (func_L02_00416800(e) != 0 && func_002A77E0(6) == 0) { \
                            n--; \
                            func_L02_00416720(e, buf[n], D_L11_001B1614 * 0.016666668f, \
                                              D_L11_001B1618 * 2.908882452175021e-4f); \
                            m++; \
                            break; \
                        } \
                    } END_IDS \
                } \
            } \
        } \
    }

/* For each of the object's two groups (state words 0x178 and 0x174), gathers the entities
   func_00312B58 accepts and counts the ones it refuses; then, while that count is below the
   limit of the class record the state names (the halfword at 0x10, at 0x12 for the second
   group), hands the gathered entities, last first, to func_L02_00416720 together with entities
   of the group at state word 0x17C. */
/* Hands waiting fighters to their spawn points until enough of each group are in the arena. */
void arena_assign_fighters_to_spawns(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    JobaClassTableView *entry =
        ((JobaClassTableView **)&g_arena_challenge_table)[*(s16 *)(state + 0x1F0)];
    u8 *rec = (u8 *)&entry->records[*(s16 *)(state + 0x1F2)];
    u8 *buf[16];
    u16 *p;
    u8 *e;

    HALF(0x10, 0x178)
    HALF(0x12, 0x174)
}

extern const f32 g_arena_camera_guide_a_x __attribute__((sda));
extern const f32 g_arena_camera_guide_a_y __attribute__((sda));
extern const f32 g_arena_camera_guide_a_z __attribute__((sda));
extern const f32 g_arena_camera_guide_b_x __attribute__((sda));
extern const f32 g_arena_camera_guide_b_y __attribute__((sda));
extern const f32 g_arena_camera_guide_b_z __attribute__((sda));
extern const f32 g_arena_camera_guide_c_x __attribute__((sda));
extern const f32 g_arena_camera_guide_c_y __attribute__((sda));
extern const f32 g_arena_camera_guide_c_z __attribute__((sda));
extern const f32 g_arena_camera_guide_d_x __attribute__((sda));
extern const f32 g_arena_camera_guide_d_y __attribute__((sda));
extern const f32 g_arena_camera_guide_d_z __attribute__((sda));
extern const f32 g_arena_camera_guide_e_x __attribute__((sda));
extern const f32 g_arena_camera_guide_e_y __attribute__((sda));
extern const f32 g_arena_camera_guide_e_z __attribute__((sda));
extern u8 g_hero_state[];
extern void *cam_alloc_override_slot(s32);
extern void cam_end_override(void *);
extern void cam_set_strength_and_steer_target(void *, f32, f32);

/* The object state's guide vector (state +0x170), allocated while the mode byte is 8 or 9:
   it is set from one of five read-only small-data vectors chosen by the target's class. */
#define GUIDE (*(f32 **)(s + 0x170))
#define SET_GUIDE(x, y, z) (GUIDE[0] = (x), GUIDE[1] = (y), GUIDE[2] = (z))

/* Sets the point the camera guide follows, depending on which kind of boss is fighting. */
void arena_update_camera_guide(u8 *obj) {
    u8 *s = *(u8 **)(obj + 0x68);

    if (obj[0x20] == 8 || obj[0x20] == 9) {
        if (GUIDE == 0) {
            GUIDE = cam_alloc_override_slot(5);
        } else if (*(void **)(s + 0x180) != 0) {
            if (*(u8 **)(s + 0x184) == 0) {
                SET_GUIDE(g_arena_camera_guide_a_x, g_arena_camera_guide_a_y, g_arena_camera_guide_a_z);
                return;
            }
            if (*(s16 *)(*(u8 **)(s + 0x184) + 0xAA) == 0xD4A /* moby class 3402 */)
                SET_GUIDE(g_arena_camera_guide_c_x, g_arena_camera_guide_c_y, g_arena_camera_guide_c_z);
            if (*(s16 *)(*(u8 **)(s + 0x184) + 0xAA) == 0xD4B /* moby class 3403 */)
                SET_GUIDE(g_arena_camera_guide_e_x, g_arena_camera_guide_e_y, g_arena_camera_guide_e_z);
            else if (*(s16 *)(*(u8 **)(s + 0x184) + 0xAA) == MOBY_CLASS_ARACHNOID)
                SET_GUIDE(g_arena_camera_guide_d_x, g_arena_camera_guide_d_y, g_arena_camera_guide_d_z);
        } else if (obj[0x20] == 9) {
            u8 *player = g_hero_state;
            SET_GUIDE(g_arena_camera_guide_b_x, g_arena_camera_guide_b_y, g_arena_camera_guide_b_z);
            if (*(f32 *)(player + 0x88) > ((f32 *)arena_get_center_point(obj))[2] + 16.0f) {
                if (*(u16 *)(obj + 0x96) < 500)
                    cam_set_strength_and_steer_target(arena_get_center_point(obj), 0.17453295f, 0.0f);
                else
                    cam_set_strength_and_steer_target(arena_get_center_point(obj), 0.008726647f, 0.0f);
            }
        } else {
            SET_GUIDE(g_arena_camera_guide_a_x, g_arena_camera_guide_a_y, g_arena_camera_guide_a_z);
        }
    } else {
        cam_end_override(GUIDE);
        GUIDE = 0;
    }
}

#undef SET_GUIDE
#undef GUIDE
