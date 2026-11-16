#include "common.h"

extern char g_hero_position[];
extern u8 g_game_flag_table[];

/* Two level globals that retail reaches both ways: absolutely, as the assembler
   expands an access to an object of unknown size (the incomplete sda arrays), and
   through $gp (the SDATA views of the same storage). */
extern s32 g_message_switch_state[] __attribute__((sda));
extern s32 D_L17_001B27CC_gp SDATA(D_L17_001B27CC);
extern f32 g_message_switch_float_param[] __attribute__((sda));
extern f32 D_L17_001B2868_gp SDATA(D_L17_001B2868);

extern s32 IsPointInCuboid(void *, s32);
extern int flag_set_first_pending(u8 *);
extern void script_queue_keyed_request(s32, s32);
extern void moby_set_state(u8 *, s32, s32);

/* Switches between two settings depending on a player message flag and sets two level
   values while it is on. */
void message_flag_switch_update(u8 *self) {
    s32 *state = *(s32 **)(self + 0x68);
    u8 mode;

    self[0x30] = 0xFF;
    if (IsPointInCuboid(g_hero_position, state[0]) != 0) {
        g_message_switch_state[0] = 2;
        D_L17_001B2868_gp = 55.0f;
    } else if (g_message_switch_state[0] == 2) {
        D_L17_001B27CC_gp = 0;
    }

    mode = self[0x20];
    switch (mode) {
    case 0:
        if (IsPointInCuboid(g_hero_position, state[1]) != 0) {
            moby_set_state(self, 1, -1);
        } else {
            moby_set_state(self, 2, -1);
        }
        break;
    case 1:
        if (flag_set_first_pending(self) != 0) {
            script_queue_keyed_request(state[4], state[5]);
            g_game_flag_table[0x85] = 1;
            g_message_switch_float_param[0] = 75.0f;
        }
        if (IsPointInCuboid(g_hero_position, state[1]) == 0) {
            moby_set_state(self, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(self) != 0) {
            script_queue_keyed_request(state[6], state[5]);
        }
        if (IsPointInCuboid(g_hero_position, state[1]) != 0) {
            moby_set_state(self, 1, -1);
        }
        break;
    }
}
