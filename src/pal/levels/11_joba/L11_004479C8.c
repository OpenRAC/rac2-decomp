#include "include_asm.h"
#include "names.h"

typedef float f32;
typedef unsigned char u8;
typedef int s32;
typedef short s16;
typedef unsigned short u16;
extern s32 point_in_path_xy(f32 *point, f32 *vertices, s32 count);
extern u8 D_L11_004465F8[];
extern u8 *g_group_id_lists[];
extern u8 *g_moby_l11_table __attribute__((section(".sdata")));
extern s32 func_417238(s32);
extern s32 func_417270(s32);
extern u8 *g_group_id_lists[];
extern u8 *g_moby_l11_table;
extern void smasher_robot_deactivate(u8 *);
extern void flamethrower_robot_deactivate(u8 *);
extern void drone_reset_to_idle(u8 *);
extern void fighter_reset_to_idle(u8 *);
extern void enemy_reset_to_idle(u8 *);
extern void drone_kill_with_effects(u8 *);
extern u8 *D_L11_001B368C __attribute__((sda));
extern s32 D_L11_001B35B8[] __attribute__((sda));
#define GROUP(off) (*(s32 *)(state + (off)))
#define FOR_EACH_ID(p, off) \
    for (p = (u16 *)D_L11_001FC420[GROUP(off)]; \
         (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L11_001B35B8[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L11_001FC420[GROUP(off)]); \
         p++)
extern s16 moby_get_vars_counter(u8 *);
extern s32 moby_get_busy_flag(u8 *);
extern s32 arena_is_target_outside(u8 *, u8 *, s32);
extern void moby_set_anim_type_three(u8 *, s32, s32);
extern void security_robot_kill(u8 *, s32, s32);
extern s32 drone_is_state_at_least_four(u8 *);
extern void part_queue_moby_for_glow(u8 *, s32, void (*)(u8 *));
extern void hero_record_play_counters(void);
extern u8 g_hero_state[];
extern u8 g_music_state[];

/* Hands every entity of the object's group (state word 0xC0) that the shared test func_L11_00441FB8
   accepts, and whose state byte is not 0xFE, 0xFD or below 3, to the handler of its class (the
   halfword at +0xAA); then runs the test once more on the entity D_00189E20 holds at +0x2290. */
void func_PAL_L11_004479C8(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 *p;
    u8 *e;
    u8 *player;

    FOR_EACH_ID(p, 0xC0) {
        e = g_moby_l11_table + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] == 0xFE)
            continue;
        if (e[0x20] == 0xFD)
            continue;
        if (e[0x20] < 3)
            continue;
        if (arena_is_target_outside(object, e, 0) == 0)
            continue;
        switch (*(s16 *)(e + 0xAA)) {
        case 0xD98:
            security_robot_kill(e, 0, 0);
            break;
        case 0xDCF:
            moby_set_anim_type_three(e, 0, -1);
            smasher_robot_deactivate(e);
            break;
        case 0xDF4:
            moby_set_anim_type_three(e, 0, -1);
            flamethrower_robot_deactivate(e);
            break;
        case 0xDF7:
            moby_set_anim_type_three(e, 0, -1);
            drone_reset_to_idle(e);
            break;
        case 0xDF9:
            moby_set_anim_type_three(e, 0, -1);
            part_queue_moby_for_glow(e, 0, fighter_reset_to_idle);
            break;
        case 0xD37:
            moby_set_anim_type_three(e, 0, -1);
            enemy_reset_to_idle(e);
            break;
        case 0xD4B:
            if (drone_is_state_at_least_four(e))
                drone_kill_with_effects(e);
            break;
        }
    }
    player = g_hero_state;
    if (arena_is_target_outside(object, *(u8 **)(player + 0x2290), 1))
        hero_record_play_counters();
}


extern s32 D_L11_001CAE40;
extern u8 D_001395B8[];
extern s32 D_L11_001AA170 __attribute__((sda));
extern u8 g_hero_position[];
extern s32 arena_queue_voice_line(u8 *, s32);
extern void func_PAL_L11_00446A20(u8 *);
extern void moby_set_state(u8 *, s32, s32);
extern void cam_end_override(s32);
extern void func_PAL_L00_00305110(s32, void *);
extern void vec_clear_128(void *);
extern s32 arena_get_challenge_flag_index(s32);
extern void func_PAL_L00_002B9CD8(s32, s32, s32, s32);
extern void level_capture_checkpoint_state(void *, void *);
extern void script_queue_keyed_request(void *, void *);

/* Restarts the actor's state machine, releases the level's helper objects and hands
   the state's slots to the two level handlers. */
void func_PAL_L11_00447E20(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    f32 buf[4];

    arena_queue_voice_line(obj, 0x20);
    moby_set_state(obj, 1, -1);
    if (*(s32 *)(state + 0x170) != 0) {
        cam_end_override(*(s32 *)(state + 0x170));
        *(s32 *)(state + 0x170) = 0;
    }
    if (D_L11_001CAE40 != 0) {
        func_PAL_L00_00305110(0, *(void **)(state + 0x2F4));
    }
    vec_clear_128(buf);
    if (D_001395B8[arena_get_challenge_flag_index(1)] != 0) {
        buf[2] = 2.16f;
        func_PAL_L00_002B9CD8((s32)(D_L11_001B368C + (*(s32 *)(state + 0x15C) << 7)) + 0x30, (s32)buf, 0, 1);
    } else {
        buf[2] = -2.52f;
        func_PAL_L00_002B9CD8((s32)(D_L11_001B368C + (*(s32 *)(state + 0x158) << 7)) + 0x30, (s32)buf, 0, 1);
    }
    level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
    func_PAL_L11_00446A20(obj);
    script_queue_keyed_request(*(void **)(state + 0x2F4), *(void **)(state + 0x2FC));
    D_L11_001AA170 = -1;

}

