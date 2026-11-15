#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
extern s32 func_002F3220(char *, float);
extern s32 func_003D77F8(char *);
extern s32 moby_is_state_two_no_children(char *);
extern char *g_moby_l02_pool __attribute__((sda));
extern u32 g_entity_group_lists[];
extern void actor_tear_down(char *);
extern void flamethrower_robot_knock_out(char *);
extern void blade_ball_explode(char *);
extern s32 arena_start_announcer_message(char *, s32);
extern char g_hero_position[];
extern char *g_moby_l02_pool __attribute__((sda));
extern u32 g_entity_group_lists[];
extern char *g_moby_l02_pool __attribute__((sda));
extern u32 g_entity_group_lists[];
extern void actor_tear_down(char *);
extern void flamethrower_robot_knock_out(char *);
extern void blade_ball_explode(char *);
extern char *g_moby_l02_pool __attribute__((section(".sdata")));
extern s32 D_L02_001B35B8[] __attribute__((sda));
extern s16 moby_get_vars_counter(char *);
#define GROUP(off) (*(s32 *)(state + (off)))
#define FOR_EACH_ID(p, off) \
    for (p = (u16 *)D_L02_001FC060[GROUP(off)]; \
         (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L02_001B35B8[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L02_001FC060[GROUP(off)]); \
         p++)
extern s32 moby_get_busy_flag(char *);
extern void armed_enemy_drop_held_and_reset(char *, int, int);
extern void moby_set_anim_type_three(char *, int, int);
extern int coll_point_inside_record_volume(void *, int);
extern void hero_record_play_counters(void);
extern u8 D_001395B8[];

/* Walks the entities of the group the object names (the group word is re-read for every
   test: the handlers may change it).  Each live, unflagged one that passes the screen
   against the two bounds is handed to the handler of its type.  Afterwards the follow-up is
   called unless the resident record passes the screen. */
void func_PAL_L02_00400F20(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    u16 *p;
    char *e;
    u8 c;

    FOR_EACH_ID(p, 0x40) {
        e = g_moby_l02_pool + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        c = *(u8 *)(e + 0x20);
        if (c == 0xFE)
            continue;
        if (c == 0xFD)
            continue;
        if (c < 3)
            continue;
        if (*(u16 *)(e + 0x34) & 2)
            continue;
        if (coll_point_inside_record_volume(e + 0x10, *(s32 *)(state + 0x80)) == 0 &&
            coll_point_inside_record_volume(e + 0x10, *(s32 *)(state + 0x7C)) != 0)
            continue;
        switch (*(s16 *)(e + 0xAA)) {
        case 0x9CA:
            armed_enemy_drop_held_and_reset(e, 0, 0);
            break;
        case 0xB22:
            moby_set_anim_type_three(e, 0, -1);
            actor_tear_down(e);
            break;
        case 0xC3B:
            moby_set_anim_type_three(e, 0, -1);
            flamethrower_robot_knock_out(e);
            break;
        case 0xC3E:
            moby_set_anim_type_three(e, 0, -1);
            blade_ball_explode(e);
            break;
        }
    }
    if (coll_point_inside_record_volume(g_hero_position, *(s32 *)(state + 0x7C)) == 0)
        hero_record_play_counters();
}


extern void moby_set_state(char *, s32, s32);
extern char *D_L02_001B368C __attribute__((sda));
extern int math_random_int_below(int);
extern void cam_end_override(char *);
extern void load_scene_chunk(int, int);
extern void vec_clear_128(void *);
extern int arena_get_challenge_save_index(int);
extern void hero_reset_position_and_direction(char *, float *, int, int);
extern void level_capture_checkpoint_state(void *, void *);
extern void script_queue_keyed_request(int, int);
extern int D_L02_001CAA80;
extern char *D_L02_001B369C __attribute__((sda));
extern int D_L02_001AA1B0 __attribute__((sda));

/* Starts the actor: calls func_L02_00400650 with 0x25 plus a random pick below 2, sets state 1,
   releases the object held at +0xC0 and, by a per-slot flag, hands a vector whose third float
   is -1.59 or 2.16, with the matching 128-byte record, to func_L00_002B9D60; ends by setting
   D_L02_001AA1B0 to -1. */
void func_PAL_L02_004011D8(char *a0) {
    char *s1 = *(char **)(a0 + 0x68);
    float v[4];

    arena_start_announcer_message(a0, math_random_int_below(2) + 0x25);
    moby_set_state(a0, 1, -1);
    if (*(char **)(s1 + 0xC0) != 0) {
        cam_end_override(*(char **)(s1 + 0xC0));
        *(s32 *)(s1 + 0xC0) = 0;
    }
    if (D_L02_001CAA80 != 0)
        load_scene_chunk(0, *(s32 *)(s1 + 0x224));
    vec_clear_128(v);
    if (D_001395B8[arena_get_challenge_save_index(0)] != 0) {
        v[2] = -1.59f;
        hero_reset_position_and_direction(D_L02_001B369C + *(s32 *)(s1 + 0x74) * 128 + 0x30, v, 0, 1);
    } else {
        v[2] = 2.16f;
        hero_reset_position_and_direction(D_L02_001B368C + *(s32 *)(s1 + 0x78) * 128 + 0x30, v, 0, 1);
    }
    level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
    arena_reset_group_enemies(a0);
    arena_match_active_count_a(a0, 0);
    arena_match_active_count_b(a0, 0);
    script_queue_keyed_request(*(s32 *)(s1 + 0x224), *(s32 *)(s1 + 0x22C));
    D_L02_001AA1B0 = -1;
}

