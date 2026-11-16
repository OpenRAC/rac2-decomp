#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef signed int s32;
extern void moby_set_state();
extern u8 g_unlock_flag_c __attribute__((sda));
extern u8 g_message_sequence_flags[];
extern u8 g_message_queue[];
extern char g_hero_position[];
extern int IsPointInCuboid(void *, int);
extern s32 req_push_queue(u8 *, s32);
extern s32 req_launch_queued(u8 *);
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
void message_sequence_update_us2(u8 *moby) {
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

