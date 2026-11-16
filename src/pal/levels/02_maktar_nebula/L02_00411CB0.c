#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
extern void moby_set_state();
extern void set_moby_color(void *, void *, void *, void *);
extern void anim_start_blended(void *, int, int, int);
extern float math_random_float_range(float, float);
extern void anim_start_blended(void *, int, int, int);
extern u8 g_unlock_flag_c __attribute__((sda));
extern u8 g_message_sequence_flags[];
extern u8 g_message_queue[];

/* resets the actor's aim: three records and the two shared limits */
void blade_ball_wake_pal(u8 *moby, int wait_threshold) {
    u8 *vars = *(u8 **)(moby + 0x68);

    *(u16 *)(vars + 0x1B8) = 0;
    *(float *)(vars + 0x20) = (float)*(s16 *)(vars + 0x24);
    moby_set_state(moby, 3, 1);
    if (*(u8 *)(moby + 0x43) != 0)
        anim_start_blended(moby, 0, 0, 8);
    *(u32 *)(moby + 0x98) = *(u32 *)(*(u32 *)(moby + 0x24) + 0x10);
    *(u8 *)(vars + 0x2E) = 1;
    *(u8 *)(moby + 0x7F) = 0;
    *(u8 *)(moby + 0x31) = 1;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x1000) & 0xFFB8;
    *(float *)(vars + 0x18C) = math_random_float_range(0.0f, 90.0f) * 0.01745329424738884f;
    *(u16 *)(vars + 0x1BA) = wait_threshold;
    *(u16 *)(vars + 0x3C) = 0;
    *(u32 *)(vars + 0x38) = 0;
    if (*(s16 *)(vars + 0x50) != 0) {
        *(u16 *)(vars + 0x50) = 0;
        set_moby_color(moby, *(u32 *)(vars + 0x1A0), *(u32 *)(vars + 0x1A4),
                      *(u32 *)(vars + 0x1A8));
        *(u16 *)(vars + 0x52) = 1;
    }
}

typedef signed int s32;
extern char g_sound_l02_record_table[];
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float,
                          int, int, int, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void func_002A05A8(void *);
extern void snd_stop_voice(int);
extern void IncrementMaktarTypeCounter(void *, int);
extern s32 req_push_queue(u8 *, s32);
extern s32 req_launch_queued(u8 *);

/* Lets go of the slot the actor holds (+0x19C) when that slot's record still names it and is live,
   ends the state at +0x1B8 when it is 1 (func_L02_003FC1B0), starts the effect pair when the actor
   is shown (+0x31), then clears the state and the shared fields as func_L02_0040B980 does. */
void blade_ball_explode_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    s32 slot = *(s32 *)(vars + 0x19C);

    if (slot != -1) {
        u8 *sound_record = (u8 *)g_sound_l02_record_table + slot * 0x70;

        if (*(u8 **)(sound_record + 0x88) == moby && sound_record[0x74] != 0)
            snd_stop_voice(slot);
    }
    *(s32 *)(vars + 0x19C) = -1;
    if (*(s16 *)(vars + 0x1B8) == 1) {
        *(u16 *)(vars + 0x1B8) = 0;
        IncrementMaktarTypeCounter(*(void **)(moby + 0xB8), *(s16 *)(moby + 0xAA));
    }
    if (moby[0x31] != 0) {
        SpawnExplosion(moby + 0x10, 0, 0xA, 0x1E, 0, 0xA, 0x2D, 1, 0.3f, 0.0f, 0, 0, 0, 0);
        snd_play_from_class_bank(0, 0, moby, 0xC3E);
    }
    *(u16 *)(vars + 0x1B8) = 0;
    *(s32 *)(vars + 0x184) = 0;
    anim_start_blended(moby, 0, 0, 3);
    func_002A05A8(moby);
    moby_set_state(moby, 1, 0);
    moby[0x31] = 0;
    *(u32 *)(moby + 0x98) = 0;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xEFFF) | 0x47;
}

extern char g_hero_position[];
extern int IsPointInCuboid(void *, int);
extern int game_is_either_mode_two(void);
extern void moby_mark_flag_and_append_to_list(int);
extern void snd_play_indexed(int);
extern void moby_mark_spawned(u8 *);

/* Steps the actor by its kind byte (+0x20). Kind 0 hands it to func_0029F338 when it holds no
   record at +0x68 and calls func_002A7750 with 1 otherwise. Kind 1 waits for D_001A7BCB and the
   byte D_L02_001395B8[4] to be clear and func_002ACBC8 to accept the index at +0xC of the
   record, then queues the messages 0x2D, 3 and 0x2E on D_L02_001C0700, sets the byte and calls
   func_002A7750 with 2. Kind 2 runs func_002AD7B8 and func_002AF0A8 with 3 and calls
   func_002A7750 with 3, unless func_002F5D10 answers yes. */
void message_sequence_update_pal(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        if (state == 0)
            moby_mark_spawned(moby);
        else
            moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (g_unlock_flag_c == 0 && g_message_sequence_flags[4] == 0 &&
            IsPointInCuboid(g_hero_position, *(s32 *)(state + 0xC)) != 0 &&
            req_push_queue(g_message_queue, 0x2D) != 0) {
            req_push_queue(g_message_queue, 3);
            req_push_queue(g_message_queue, 0x2E);
            req_launch_queued(g_message_queue);
            g_message_sequence_flags[4] = 1;
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (game_is_either_mode_two() == 0) {
            moby_mark_flag_and_append_to_list(3);
            snd_play_indexed(3);
            moby_set_state(moby, 3, -1);
        }
        break;
    }
}

