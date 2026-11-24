#include "include_asm.h"
#include "names.h"
#include "moby_classes.h"
#include "names.h"

extern float g_actor_cycle_timer_rate __attribute__((sda));

extern int g_actor_shared_state;

extern char g_cutscene_camera_position[8] __attribute__((sda));

extern char g_cutscene_l02_camera_rotation[8] __attribute__((sda));

extern char g_cutscene_camera_pose_start[8] __attribute__((sda));

extern char g_cutscene_camera_pose_end[8] __attribute__((sda));

extern int g_cutscene_camera_mode_arg __attribute__((sda));

extern void vec_clear_128(void *);

extern void SetCamera5Pose(char *, char *, int, int, int);

/* Advances a repeating 0 to 1 timer in the actor data each frame. */
void actor_advance_cycle_timer(void) {
    int actorBase = g_actor_shared_state;
    float *timerPtr = (float *)((char *)actorBase + 0x74);
    float newValue;

    newValue = timerPtr[0] + g_actor_cycle_timer_rate * 1.6666667535901069641113281250e-02f;
    timerPtr[0] = newValue;
    if (newValue > 1.0f)
        timerPtr[0] = newValue - 1.0f;
}

extern int g_hero_height_zone_active;

/* Four bytes: cc1 then emits the address as a single `la`, which gas expands to an adjacent
   lui/addiu pair (an array of unknown size is split by cc1 itself). */
extern char g_arena_anchor_pos[4];

extern void sky_shift_records_by_period(int, float);

extern float fast_vec_dist(void *, void *);

extern void script_queue_keyed_request(int, int);

typedef struct {
    char pad0[0x80];
    char pos[8];
    float f88;
    char pad1[0x2236];
    unsigned char b22C2;
    char pad2[0x22D];
    unsigned char b24F0;
} L02_003F5710_Hero;

extern L02_003F5710_Hero g_hero_state;

/* Watches the hero block's height (+0x88) against 420.0 and the copy of it the actor kept at
   +0x98. Crossing it downwards clears the byte at +0x24F0 and the global flag; crossing it upwards
   sets both when the flag is clear and the hero is within 150.0 of D_L02_001B3210, and clears
   both when the flag is set and the hero is farther away. While the flag is set the hero's byte
   at +0x22C2 is raised, and the first time the actor's word at +0xDC is set and handed its two
   words at +0x1C and +0x20. The height is then kept at +0x98.

   The flag is a plain extern int: the assembler decides each access at its use, a gp-relative one
   inside a delay slot and the absolute lui/lw pair elsewhere, as retail has them. */
/* Checks whether the hero is above or below a set height and turns the actor area flags on or off. */
void hero_update_height_zone_flags(char *moby) {
    char *state = *(char **)(moby + 0x68);
    float distance;

    if (g_hero_state.f88 < 420.0f && *(float *)(state + 0x98) >= 420.0f) {
        sky_shift_records_by_period(0, 420.0f);
        g_hero_state.b24F0 = 0;
        g_hero_height_zone_active = 0;
    } else if (g_hero_state.f88 > 420.0f && *(float *)(state + 0x98) <= 420.0f) {
        sky_shift_records_by_period(1, 420.0f);
        distance = fast_vec_dist(g_hero_state.pos, g_arena_anchor_pos);
        if (g_hero_height_zone_active == 0 && distance < 150.0f) {
            int on = 1;

            g_hero_state.b24F0 = on;
            g_hero_height_zone_active = on;
        } else if (g_hero_height_zone_active != 0 && distance > 150.0f) {
            g_hero_state.b24F0 = 0;
            g_hero_height_zone_active = 0;
        }
    }
    if (g_hero_height_zone_active != 0) {
        g_hero_state.b22C2 = 1;
        if (*(int *)(state + 0xDC) == 0) {
            *(int *)(state + 0xDC) = 1;
            script_queue_keyed_request(*(int *)(state + 0x1C), *(int *)(state + 0x20));
        }
    }
    *(float *)(state + 0x98) = g_hero_state.f88;
}

/* Sets up the camera for a short scene. */
void cutscene_setup_camera(char *moby) {
    char buf[16];
    vec_clear_128(buf);
    SetCamera5Pose(g_cutscene_camera_pose_start, g_cutscene_camera_pose_end, 1, 0, 0);
    SetCamera5Mode(2, g_cutscene_camera_mode_arg);
    object_copy_vector_to_selected(g_cutscene_camera_position);
    cam_set_state_rotation(g_cutscene_l02_camera_rotation);
}

extern char g_camera_l02_position[];
extern int g_hero_at_console_flag;
extern void moby_set_state(char *, int, int);

extern char *g_arena_challenge_table_2[] __attribute__((sda));

/* Whether the pair of table entries the object names still agree with its own four words. */
/* func_L02_003FCBF0 is defined in L02_003FCBF0-g8.c. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef float f32;

extern char *g_arena_challenge_table_2[2] __attribute__((sda));
extern unsigned char *g_moby_l02_pool[3] __attribute__((sda));
extern s32 g_group_max_index[] __attribute__((sda));
extern u32 g_entity_group_lists[];
extern f32 g_cutscene_camera_time __attribute__((sda));
extern f32 g_cutscene_camera_angle __attribute__((sda));
extern s32 moby_is_state_six(char *);
extern s32 moby_is_state_one_cleared_vars(char *);
extern s32 math_random_int_below(s32);
extern void teleporter_bind_captured_object(char *, char *, f32, f32);

#define GROUP(off) (*(s32 *)(state + (off)))
/* Leaves the function when the group is 0xFF or empty; the braces it opens close in END_IDS. */
#define FOR_EACH_ID(p, off) \
    if (GROUP(off) == 0xFF) \
        return; \
    { u16 *q = (u16 *)D_L02_001FC060[GROUP(off)]; \
    if (q == 0) \
        return; \
    for (p = q; (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L02_001B35B8[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L02_001FC060[GROUP(off)]); \
         p++)
#define END_IDS }
/* One half: collect the entities of group OFF for which func_00312B58 holds (counting the
   others in m), then, up to 1000 passes over group 0xCC while m is below the record's limit,
   hand one collected entity at a time to func_L02_00416720 with an entity of 0xCC. */
#define HALF(limit, off) \
    { \
        s32 n, m, i, k; \
        if (*(s16 *)(rec + (limit)) != 0) { \
            m = 0; \
            n = 0; \
            for (k = 15; k >= 0; k--) \
                buf[k] = 0; \
            FOR_EACH_ID(p, off) { \
                e = (char *)D_L02_001B359C[0] + ((*p & 0x7FFF) << 8); \
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
                    FOR_EACH_ID(p, 0xCC) { \
                        e = (char *)D_L02_001B359C[0] + ((*p & 0x7FFF) << 8); \
                        if (e == 0) \
                            break; \
                        if (n <= 0) \
                            break; \
                        if (func_L02_00416800(e) != 0 && func_002A77E0(6) == 0) { \
                            n--; \
                            func_L02_00416720(e, buf[n], D_L02_001B1258 * 0.016666668f, \
                                              D_L02_001B125C * 2.908882452175021e-4f); \
                            m++; \
                            break; \
                        } \
                    } END_IDS \
                } \
            } \
        } \
    }

/* Tells nearby enemies from two groups to attack, a few at a time. */
void arena_command_group_attacks(char *moby) {
    char *state = *(char **)(moby + 0x68);
    char *rec = *(char **)(g_arena_challenge_table_2[*(s16 *)(state + 0x120)] + 4)
                + *(s16 *)(state + 0x122) * 0x14;
    char *buf[16];
    u16 *p;
    char *e;

    HALF(0xC, 0xC8)
    HALF(0xE, 0xC4)
}

extern s32 moby_has_free_child_slot_state2(char *);

extern s32 arena_is_entity_far_from_hero(char *);

extern f32 vec_distance_xy(char *, char *);

extern char g_hero_position[];

/* Fills the slot of the list at +0xA8 that the counter at +0xD8 names. It goes on when that slot is
   empty, or when func_L02_003D77B8 returns 0 for the entity in it and the counter is below the
   table record's limit (byte +0x12 less one: the counter is then stepped). The entity group the
   object names (+0x44) is walked: the first entity for which func_L02_003FD000 and
   func_L02_003D77B8 both return non-zero goes into the slot; if the slot is still empty, the
   first one with func_L02_003D77B8 non-zero that is more than 30.0 away from D_00189EA0. */
/* Picks a nearby entity for this actor to watch and stores it in a free slot. */
void actor_pick_watched_entity(char *moby) {
    char *state = *(char **)(moby + 0x68);
    char *rec = *(char **)(g_arena_challenge_table_2[*(s16 *)(state + 0x120)] + 4) + *(s16 *)(state + 0x122) * 0x14;
    char *at = state + GROUP(0xD8) * 4;
    char *slot = *(char **)(at + 0xA8);
    s32 go = 0;
    u16 *idPtr;
    u16 *idList;
    char *entity;

    if (slot != 0) {
        if (moby_has_free_child_slot_state2(slot) == 0) {
            if (GROUP(0xD8) < *(u8 *)(rec + 0x12) - 1) {
                go = 1;
                GROUP(0xD8) += 1;
            }
        }
    } else {
        go = 1;
    }
    if (go == 0)
        return;
    if (GROUP(0x44) == 0xFF)
        return;
    idList = (u16 *)g_entity_group_lists[GROUP(0x44)];
    if (idList == 0)
        return;
    for (idPtr = idList; (GROUP(0x44) & 0xFF) != 0xFF && GROUP(0x44) <= g_group_max_index[0] && idPtr != 0 &&
                ((idPtr != 0 && (s16)idPtr[-1] >= 0) || idPtr == (u16 *)g_entity_group_lists[GROUP(0x44)]);
         idPtr++) {
        entity = (char *)g_moby_l02_pool[0] + ((*idPtr & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (arena_is_entity_far_from_hero(entity) != 0 && moby_has_free_child_slot_state2(entity) != 0) {
            char **list = (char **)(state + 0xA8);
            char **cur = list + GROUP(0xD8);

            *cur = entity;
            break;
        }
    }
    {
        char **list = (char **)(state + 0xA8);
        char **cur = list + GROUP(0xD8);

        if (*cur != 0)
            return;
    }
    for (idPtr = (u16 *)g_entity_group_lists[GROUP(0x44)];
         (GROUP(0x44) & 0xFF) != 0xFF && GROUP(0x44) <= g_group_max_index[0] && idPtr != 0 &&
         ((idPtr != 0 && (s16)idPtr[-1] >= 0) || idPtr == (u16 *)g_entity_group_lists[GROUP(0x44)]);
         idPtr++) {
        entity = (char *)g_moby_l02_pool[0] + ((*idPtr & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (moby_has_free_child_slot_state2(entity) != 0 && vec_distance_xy(entity + 0x10, g_hero_position) > 30.0f) {
            char **list = (char **)(state + 0xA8);
            char **cur = list + GROUP(0xD8);

            *cur = entity;
            break;
        }
    }
}

extern unsigned char g_game_flag_table[0x100];

/* D_001A7A0C, written as the second word of an 8-byte object: cc1 then counts the store as two
   instructions and keeps it out of func_L02_003FCDF8's delay slot, and the assembler gives the
   absolute `lui $at ; sw`. */
extern int g_challenge_score_words[2];

extern int g_player_bolts;

extern int arena_get_challenge_save_index(int);

extern int arena_start_announcer_message(char *, int);

extern void help_unlock_entry(int);

extern int moby_handle_request_slot_state(int);

extern int moby_compute_scaled_entry_value_shifted(int);

extern int moby_compute_scaled_entry_value(int);

extern void module_l00_call_handler_with_arg_4(int);

extern int MemcardSave(int, int);

/* With a1 == 0 and no count yet for func_L02_003F9B70(0), plays the hero's scene 7 with its
   word at +0x22C8 kept; otherwise picks the scene from a1 (6, 0xB or a random one), adds the
   two scores and starts func_L00_0030C7F8(0x168). Then counts the entry. The unit is built with
   -frac2-gcse-unsplit-edges and -frac2-keep-block-order (config/cflags.txt): the high half of
   D_001395B8 is computed in the entry block, and the switch keeps its `b default` with the
   default body last, as in retail. `+= 1` keeps the counter's address out of the call. */
/* Starts a scene, adds up the score, and counts how often it was shown. */
void scene_start_count_views(char *moby, int sceneKind) {
    char *state = *(char **)(moby + 0x68);
    int savedWord;
    char *hero;
    int score;

    if (sceneKind == 0 && g_game_flag_table[arena_get_challenge_save_index(0)] == 0) {
        hero = (char *)&g_hero_state;
        savedWord = *(int *)(hero + 0x22C8);
        arena_start_announcer_message(moby, 7);
        help_unlock_entry(0x26);
        moby_handle_request_slot_state(0x26);
        *(int *)(hero + 0x22C8) = savedWord;
    } else {
        switch (sceneKind) {
        case 6:
            arena_start_announcer_message(moby, 8);
            break;
        case 0xB:
            arena_start_announcer_message(moby, 9);
            break;
        default:
            arena_start_announcer_message(moby, math_random_int_below(5) + 2);
            break;
        }
        g_challenge_score_words[1] = g_challenge_score_words[1] + moby_compute_scaled_entry_value_shifted(sceneKind);
        score = moby_compute_scaled_entry_value(sceneKind);
        *(int *)(state + 0x110) = score;
        g_player_bolts = g_player_bolts + score;
        module_l00_call_handler_with_arg_4(0x168);
    }
    g_game_flag_table[arena_get_challenge_save_index(sceneKind)] += 1;
    MemcardSave(0, -1);
}

typedef int TI128 __attribute__((mode(TI)));

extern char g_spark_burst_vectors[8] __attribute__((sda));
extern float g_spark_burst_speed_min __attribute__((sda));
extern float g_spark_burst_speed_max;
extern u32 g_spark_burst_a_word0 __attribute__((sda));
extern u32 g_spark_burst_a_word1;
extern u32 g_spark_burst_b_word0;
extern u32 g_spark_burst_b_word1;
extern u32 g_spark_burst_c_word0;
extern u32 g_spark_burst_c_word1;
extern u32 g_spark_burst_a_color __attribute__((sda));
extern u32 g_spark_burst_b_color;
extern u32 g_spark_burst_c_color;
extern s32 g_frame_l02_counter;

extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_range(s32, s32);
extern char *part_spawn_scaling(void *, void *, u32, s32, s32, s32, s32, s32);

/* Two passes, over the two 16-byte vectors at D_L02_001B1730 in turn.  Each combines the vector
   with the object's vectors at +0xC0 and +0x10 (func_00283098, func_00282CC0) into v0, builds v1
   as a vector whose z is -func_002A7878(D_L02_001B1750, D_L02_001B1754) / 60, combines it with
   A1, and hands v0 and v1 twice to func_002BAE50 with colour words and a pick of func_002A7820:
   first with one of two sets chosen by bit 0 of D_L02_001B30C8, then with a third set. */
/* Draws two bursts of sparks around the object. */
void part_spawn_spark_bursts(char *moby, char *offsetVec) {
    float worldPos[4];
    float sparkVelocity[4];
    float tempVec[4];
    float *velocityPtr = sparkVelocity;
    char *vecPtr = g_spark_burst_vectors;
    s32 i;
    float speed;

    for (i = 1; i >= 0; i--) {
        matrix_mul_vec3(worldPos, vecPtr, moby + 0xC0);
        vecPtr += 0x10;
        FastVecAdd(worldPos, worldPos, moby + 0x10);
        *(TI128 *)tempVec = 0;
        speed = math_random_float_range(g_spark_burst_speed_min, g_spark_burst_speed_max);
        tempVec[2] = -(speed * 0.016666668f);
        *(TI128 *)sparkVelocity = *(TI128 *)tempVec;
        FastVecAdd(sparkVelocity, sparkVelocity, offsetVec);
        if (g_frame_l02_counter & 1) {
            part_spawn_scaling(worldPos, velocityPtr, g_spark_burst_a_word0, g_spark_burst_a_word1, math_random_int_range(0x12, 0x16), g_spark_burst_a_color, -10, 1);
        } else {
            part_spawn_scaling(worldPos, velocityPtr, g_spark_burst_b_word0, g_spark_burst_b_word1, math_random_int_range(0x14, 0x18), g_spark_burst_b_color, -10, 1);
        }
        part_spawn_scaling(worldPos, velocityPtr, g_spark_burst_c_word0, g_spark_burst_c_word1, math_random_int_range(0xA, 0xF), g_spark_burst_c_color, -10, 1);
    }
}

extern s32 g_request_enabled_flag __attribute__((nosda));
extern float g_actor_health_fraction_scale __attribute__((sda));
extern s32 arena_start_announcer_message(char *, s32);

/* Picks the message to ask for after the entity the object is attending to (state word 0xD0),
   for its kinds 0x9F8 and 0xA44: while D_0018C2EC is not positive, one of two at random (0x10 or
   0x11, 0x16 or 0x17), dropped when the state's flag for it is set; then 0x12 (0x18) when the
   entity's float at +0x20 is below its half-word at +0x24 scaled by D_L02_001B1534, unless the
   state's half-word at 0x1F4 (0x200) is set, and 0x13 (0x19) when that float is not above zero,
   unless the half-word at 0x1F6 (0x202) is set.  A positive pick is handed to func_L02_00400650. */
/* Chooses which message the actor says about the entity it is watching (Chainblade or Brawler Legs). */
void actor_pick_watched_message(char *moby) {
    char *state = *(char **)(moby + 0x68);
    char *target = *(char **)(state + 0xD0);
    char *chainbladeVars;
    char *brawlerVars;
    char *flagAddr;
    s32 msg;

    if (target == 0)
        return;
    msg = -1;
    switch (*(s16 *)(target + 0xAA)) {
    case 0x9F8: /* Chainblade */
        chainbladeVars = *(char **)(target + 0x68);
        if ((float)g_request_enabled_flag <= 0.0f) {
            msg = math_random_int_below(2) + 0x10;
            flagAddr = state + msg * 2;
            if (*(s16 *)(flagAddr + 0x1D0) != 0)
                msg = -1;
        }
        if (*(s16 *)(state + 0x1F4) == 0) {
            if (*(float *)(chainbladeVars + 0x20) < (float)*(s16 *)(chainbladeVars + 0x24) * g_actor_health_fraction_scale)
                msg = 0x12;
        }
        if (*(s16 *)(state + 0x1F6) == 0) {
            if (*(float *)(chainbladeVars + 0x20) <= 0.0f)
                msg = 0x13;
        }
        break;
    case 0xA44: /* B2 Brawler Legs */
        brawlerVars = *(char **)(target + 0x68);
        if ((float)g_request_enabled_flag <= 0.0f) {
            msg = math_random_int_below(2) + 0x16;
            flagAddr = state + msg * 2;
            if (*(s16 *)(flagAddr + 0x1D0) != 0)
                msg = -1;
        }
        if (*(s16 *)(state + 0x200) == 0) {
            if (*(float *)(brawlerVars + 0x20) < (float)*(s16 *)(brawlerVars + 0x24) * g_actor_health_fraction_scale)
                msg = 0x18;
        }
        if (*(s16 *)(state + 0x202) == 0) {
            if (*(float *)(brawlerVars + 0x20) <= 0.0f)
                msg = 0x19;
        }
        break;
    }
    if (msg > 0)
        arena_start_announcer_message(moby, msg);
}

extern s32 g_game_mode __attribute__((nosda));
extern u8 g_game_flag_table[];
extern u8 g_item_slot_to_record[];

typedef struct {
    char pad0[4];
    u8 f4;
    char pad1[0xDB];
} L02_003FF9A0_Rec;

extern L02_003FF9A0_Rec g_material_l02_table[];

extern s32 hero_l00_set_move_state(s32, s32);
extern s32 PadPressedWithin(s32, s32, s32 *);
extern s32 arena_get_challenge_save_index(s32);
extern s32 flag_is_byte_set(void);
extern void arena_cancel_challenge_menu(char *);
extern void arena_draw_info_panel(char *);
extern void gfx_add_draw_callback_first(void *, void *);

/* Calls func_L00_002C42E0(0x6F, 1) unless D_0018C0B4 already is 0x6F.  When the input test
   func_L00_0032EF10(0x40, 0x3C, 0) holds, the object changes state to 7 and its selection (state
   half-word 0x118) moves to the next entry of the table at D_L02_001B1190 that is usable: the flag
   of D_001395B8 at the index func_L02_003F9B70 gives for the entry's word at +8 is set, entries from
   12 on also pass func_00288D58, and entries 7 and 8 need the byte at +4 of the record of
   D_L02_00264A70 that D_00139568[0x1E] (0x2A) names.  The pick is kept in the state and in
   D_001395B8[0x3C].  Otherwise, when func_L00_0032EF10(0x10, 0x3C, 0) holds, func_L02_003FCA80
   runs; if neither test holds the callback func_L02_003FF6E8 is registered for the object. */
/* Handles the menu input that picks the next usable entry, or hands off to other actions. */
void menu_select_next_usable(char *moby) {
    char *state = *(char **)(moby + 0x68);
    s32 i;
    L02_003FF9A0_Rec *record;

    if (g_game_mode != 0x6F)
        hero_l00_set_move_state(0x6F, 1);
    if (PadPressedWithin(0x40, 0x3C, 0) != 0) {
        moby_set_state(moby, 7, -1);
        for (i = *(s16 *)(state + 0x118) + 1; i < 0xE; i++) {
            if (g_game_flag_table[arena_get_challenge_save_index(*(s32 *)(g_arena_challenge_table_2[i] + 8))] == 0)
                continue;
            if (i >= 0xC && flag_is_byte_set() == 0)
                continue;
            if (i == 7) {
                record = &g_material_l02_table[g_item_slot_to_record[0x1E]];
                if (record->f4 == 0)
                    continue;
            }
            if (i == 8) {
                record = &g_material_l02_table[g_item_slot_to_record[0x2A]];
                if (record->f4 == 0)
                    continue;
            }
            *(s16 *)(state + 0x118) = i;
            g_game_flag_table[0x3C] = *(u8 *)(state + 0x118);
            return;
        }
    } else if (PadPressedWithin(0x10, 0x3C, 0) != 0) {
        arena_cancel_challenge_menu(moby);
    } else {
        gfx_add_draw_callback_first(arena_draw_info_panel, moby);
    }
}

extern const float g_actor_idle_message_time_limit __attribute__((sda));
extern const s32 g_actor_idle_message_count_limit __attribute__((sda));
extern float g_actor_message_threshold __attribute__((sda));
extern float g_actor_message_hero_scale __attribute__((sda));
extern s32 g_actor_message_delay_base __attribute__((sda));
extern s32 g_player_stats;
extern char g_music_state[];
extern s32 math_fast_float_d(void *);

/* Picks an idle message for the object. Nothing happens while the message system at D_001A63A8
   is busy (+0x68 set, +0x24 not -1) or while the countdown at +0xE4 of the state runs. A float
   (+0xE8, plus a2) and a count (+0xEC, plus a1) accumulate; when the float passes D_L02_001B1520
   or the count D_L02_001B1524, the messages 0x1D..0x22 not played yet (the half-words at
   +0x1D0 + id * 2; 0x1D only while +0xD0 is zero) become candidates and both restart. When
   func_00282948 reports the timer at +0x100 idle, both restart and the timer is set to 300. The
   messages 0x1A..0x1C join when a3 is above D_L02_001B1528, 0x23 when the hero block's int at
   +0x24CC is under D_001A7A00 * D_L02_001B152C and 0x24 when it is not positive. One candidate,
   picked at random, is started through func_L02_00400650 and the countdown is set to
   D_L02_001B1530 plus a random share of it.

   Each loop points lp at the list before it fills it. Set in two places, lp has no base the
   alias analysis knows (alias.c's record_set), so the stores of the second loop may reach the
   globals and the loads of D_001A7A00 and D_L02_001B152C stay below that loop, as in retail;
   with one lp, or with list[n++] in the loops, gcse's PRE hoists them above it. The thresholds
   are const (retail reads them ahead of the stores to the state); the hero block's address and
   the ids 0x23/0x24 each have a variable of their own, as retail rebuilds the address from its
   high half and loads each id next to its store. */
/* Picks a random idle message for the actor to say, from the ones not yet played. */
void actor_pick_idle_message(char *moby, s32 countStep, float floatStep, float threshold) {
    char *state = *(char **)(moby + 0x68);
    char *msgSystem = g_music_state;
    char *hero;
    char *hero2;
    s32 id23;
    s32 id24;
    s32 list[12];
    s32 *listPtr;
    s32 candidateCount;
    s32 j;
    s32 k;
    s32 count;
    float acc;

    if (*(s32 *)(msgSystem + 0x68) != 0)
        return;
    if (*(s32 *)(msgSystem + 0x24) != -1)
        return;
    if (*(s32 *)(state + 0xE4) != 0)
        return;
    candidateCount = 0;
    acc = *(float *)(state + 0xE8) + floatStep;
    count = *(s32 *)(state + 0xEC) + countStep;
    *(s32 *)(state + 0xEC) = count;
    *(float *)(state + 0xE8) = acc;
    if (g_actor_idle_message_time_limit < acc || g_actor_idle_message_count_limit < count) {
        listPtr = list;
        for (j = 0; j < 6; j++) {
            s32 id;

            if (j == 0 && *(s32 *)(state + 0xD0) != 0)
                continue;
            id = j + 0x1D;
            if (*(s16 *)(state + 0x1D0 + id * 2) == 0)
                listPtr[candidateCount++] = id;
        }
        *(s32 *)(state + 0xEC) = 0;
        *(s32 *)(state + 0xE8) = 0;
    }
    if (math_fast_float_d(state + 0x100) != 0) {
        *(s32 *)(state + 0xEC) = 0;
        *(s32 *)(state + 0x100) = 300;
        *(s32 *)(state + 0xE8) = 0;
    }
    if (g_actor_message_threshold < threshold) {
        listPtr = list;
        for (k = 0; k < 3; k++) {
            s32 id = k + 0x1A;

            if (*(s16 *)(state + 0x1D0 + id * 2) == 0)
                listPtr[candidateCount++] = id;
        }
    }
    hero = (char *)&g_hero_state;
    if ((float)*(s32 *)(hero + 0x24CC) < (float)g_player_stats * g_actor_message_hero_scale) {
        id23 = 0x23;
        if (*(s16 *)(state + 0x216) == 0)
            list[candidateCount++] = id23;
    }
    hero2 = (char *)&g_hero_state;
    if (*(s32 *)(hero2 + 0x24CC) <= 0) {
        id24 = 0x24;
        if (*(s16 *)(state + 0x218) == 0)
            list[candidateCount++] = id24;
    }
    if (candidateCount != 0) {
        arena_start_announcer_message(moby, list[math_random_int_below(candidateCount)]);
        *(s32 *)(state + 0xE4) = g_actor_message_delay_base + math_random_int_below(g_actor_message_delay_base);
    }
}

extern void *cam_alloc_override_slot(s32);
extern void cam_end_override(void *);
extern f32 g_helper_offset_a_x __attribute__((sda));
extern f32 g_helper_offset_a_y __attribute__((sda));
extern f32 g_helper_offset_a_z __attribute__((sda));
extern f32 g_helper_offset_b_x __attribute__((sda));
extern f32 g_helper_offset_b_y __attribute__((sda));
extern f32 g_helper_offset_b_z __attribute__((sda));
extern f32 g_helper_offset_c_x __attribute__((sda));
extern f32 g_helper_offset_c_y __attribute__((sda));
extern f32 g_helper_offset_c_z __attribute__((sda));

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} L02_003FC9C0_Vec3;

/* In state 8 the actor's 0xC0 object is created through func_L00_002D70A0(5) when missing,
   otherwise it gets one of three float triples: by the class (+0xAA, 0x9F8 or 0xA44) of the
   0xD0 object, or the default one when there is none. In any other state the object is
   released through func_L00_002D7140 and the slot cleared.
   Each branch writes its own triple; the y and z stores (re-reading 0xC0) come out as one tail
   through cross-jumping after reload, which is why z keeps its own register ($f2). The stores
   are struct fields so the sda loads are not ordered behind them. */
/* Creates or updates the helper object, with settings based on the watched entity, and removes it in other states. */
void actor_update_helper_offsets(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u8 *)(moby + 0x20) == 8) {
        L02_003FC9C0_Vec3 *obj = *(L02_003FC9C0_Vec3 **)(vars + 0xC0);

        if (obj == 0) {
            *(L02_003FC9C0_Vec3 **)(vars + 0xC0) = cam_alloc_override_slot(5);
        } else {
            u8 *attended = *(u8 **)(vars + 0xD0);

            if (attended != 0) {
                if (*(s16 *)(attended + 0xAA) == MOBY_CLASS_CHAINBLADE) {
                    obj->x = g_helper_offset_b_x;
                    (*(L02_003FC9C0_Vec3 **)(vars + 0xC0))->y = g_helper_offset_b_y;
                    (*(L02_003FC9C0_Vec3 **)(vars + 0xC0))->z = g_helper_offset_b_z;
                } else if (*(s16 *)(attended + 0xAA) == MOBY_CLASS_B2_BRAWLER_LEGS) {
                    obj->x = g_helper_offset_c_x;
                    (*(L02_003FC9C0_Vec3 **)(vars + 0xC0))->y = g_helper_offset_c_y;
                    (*(L02_003FC9C0_Vec3 **)(vars + 0xC0))->z = g_helper_offset_c_z;
                }
            } else {
                obj->x = g_helper_offset_a_x;
                (*(L02_003FC9C0_Vec3 **)(vars + 0xC0))->y = g_helper_offset_a_y;
                (*(L02_003FC9C0_Vec3 **)(vars + 0xC0))->z = g_helper_offset_a_z;
            }
        }
    } else {
        cam_end_override(*(L02_003FC9C0_Vec3 **)(vars + 0xC0));
        *(L02_003FC9C0_Vec3 **)(vars + 0xC0) = 0;
    }
}
