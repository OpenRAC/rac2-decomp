/* func_002CFBE8 in its own unit, a sibling of func_002D0930: the cursor goes through $gp, so the
   file is compiled at -G32 (config/cflags.txt). The unlock table's address is built by one
   lui/addiu pair in one register, the assembler's la macro, so it is declared MACRO_ADDR. */
#include "common.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;
typedef struct { short f0; short text; short f4; } TextEntry;

extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern int D_001AB9FC __attribute__((sda));
extern short D_001A63AC[];
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern MenuFields D_0025C0B8;
extern FlagTarget *D_0025C024[];
extern int D_0025C094[];
extern TextEntry D_0026CF18[];

/* Handles input on the skill points list: moves the cursor through the 30 entries and shows the earned entry text. */
int menu_handle_skill_points_list_input(void)
{
    int result = 0;
    int flags = g_pad_state.flags;
    int oldCursor = D_001AB9FC;

    if (flags & 0x10) {
        int value;
        int returnCode;
        D_001AB9FC = 0;
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            returnCode = -1;
            goto finish;
        }
        returnCode = 0;
finish:
        return returnCode;
    }
    if (flags & 0x900) {
        D_001AB9FC = 0;
        result = 1;
    } else if (flags & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        if (--D_001AB9FC < 0)
            D_001AB9FC = 29;
    } else if (flags & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        if (++D_001AB9FC >= 30)
            D_001AB9FC = 0;
    }
    {
        MenuFields *menu = &D_0025C0B8;
        menu->f58 = D_001AB9FC;
        if (D_001A7A60[D_001AB9FC] != 0) {
            if (oldCursor == D_001AB9FC) {
                if (D_001A63AC[0] == 0) {
                    if (menu->f50 == oldCursor && menu->f44 == 2) {
                        D_0025C024[0]->flags &= -5;
                    } else if (menu->f54 == oldCursor && menu->f44 == 4) {
                        D_0025C024[0]->flags &= -5;
                    }
                }
            }
            D_0025C094[0] = D_0026CF18[D_001AB9FC].text;
        } else {
            D_0025C024[0]->flags |= 4;
            D_0025C094[0] = 0;
        }
    }
    return result;
}
