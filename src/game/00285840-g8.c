#include "include_asm.h"
#include "names.h"

/* -G8 sibling for src/game/00285840.c: func_002858C0 stores through $gp into the
   small-data word D_001A8A5C, which only comes out gp-relative in a file built
   with -G8. */

typedef int s32;
typedef short s16;

typedef struct {
    char reserved00[0x40];
    s32 mode;
    char reserved44[0x10];
    s32 modeArg;
    s32 field58;
    s32 field5C[4];
    s32 field6C[4];
    s16 field7C;
    s16 field7E;
    s32 field80;
    char reserved84[4];
    s32 field88;
} Limits_2858C0;

extern Limits_2858C0 g_modal_state;
extern s32 g_modal_state_word[];
extern s32 g_current_game_mode;
extern s32 g_menu_mode __attribute__((sda));

extern s32 mode_get_stack_top(void);
extern void snd_send_cmd22(s32);
extern s32 menu_is_state_seven(void);
extern void music_Pause(s32);
extern int snd_play_from_global_bank(int, unsigned int, void *);

/* Switches the menu to a new mode. It clears the menu counters, plays the menu sound and may start a pause. */
void menu_set_mode(s32 newMode, s32 modeArg)
{
    s32 i;

    g_menu_mode = newMode;
    if (newMode == 5) {
        g_modal_state.field80 = g_modal_state_word[0];
    } else {
        g_modal_state.field80 = 0;
    }
    g_modal_state.modeArg = modeArg;
    g_modal_state.mode = newMode;
    g_modal_state.field7C = 0;
    g_modal_state.field7E = 0;
    g_modal_state.field58 = 0;
    g_modal_state.field88 = (mode_get_stack_top() != 3);
    if (g_current_game_mode != 3) {
        snd_send_cmd22(0x5D);
        if (menu_is_state_seven() == 0) {
            music_Pause(0);
        }
    }
    for (i = 0; i < 4; i++) {
        g_modal_state.field5C[i] = 0;
        g_modal_state.field6C[i] = 0;
    }
    if (newMode == 10) {
        snd_play_from_global_bank(0x12, 0, 0);
    }
}
