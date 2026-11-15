#include "names.h"
typedef float f32;
typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;

extern s32 D_L11_001CAE40;

extern u8 *D_L11_001B368C __attribute__((sda));

extern u8 D_001395B8[];

extern s32 D_L11_001AA170 __attribute__((sda));

extern u8 g_hero_position[];

extern void arena_queue_voice_line(u8 *, s32);

extern void arena_run_member_handlers(u8 *);

extern void moby_set_state(u8 *, s32, s32);

extern void cam_end_override(s32);

extern void load_scene_chunk(s32, void *);

extern void vec_clear_128(void *);

extern s32 arena_get_challenge_flag_index(s32);

extern void hero_reset_position_and_direction(s32, s32, s32, s32);

extern void level_capture_checkpoint_state(void *, void *);

extern void script_queue_keyed_request(void *, void *);

/* Restarts the actor's state machine, releases the level's helper objects and hands
   the state's slots to the two level handlers. */
/* Puts the arena back to its starting state after a challenge ends. */
void arena_reset_encounter(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    f32 position[4];

    arena_queue_voice_line(obj, 0x20);
    moby_set_state(obj, 1, -1);
    if (*(s32 *)(state + 0x170) != 0) {
        cam_end_override(*(s32 *)(state + 0x170));
        *(s32 *)(state + 0x170) = 0;
    }
    if (D_L11_001CAE40 != 0) {
        load_scene_chunk(0, *(void **)(state + 0x2F4));
    }
    vec_clear_128(position);
    if (D_001395B8[arena_get_challenge_flag_index(1)] != 0) {
        position[2] = 2.16f;
        hero_reset_position_and_direction((s32)(D_L11_001B368C + (*(s32 *)(state + 0x15C) << 7)) + 0x30, (s32)position, 0, 1);
    } else {
        position[2] = -2.52f;
        hero_reset_position_and_direction((s32)(D_L11_001B368C + (*(s32 *)(state + 0x158) << 7)) + 0x30, (s32)position, 0, 1);
    }
    level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
    arena_run_member_handlers(obj);
    script_queue_keyed_request(*(void **)(state + 0x2F4), *(void **)(state + 0x2FC));
    D_L11_001AA170 = -1;

}
