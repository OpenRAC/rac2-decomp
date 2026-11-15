#include "names.h"
/* func_002D0930 in its own unit, a sibling of func_002D01D0: the cursor and the D_001A7478 write
   go through $gp, so the file is compiled at -G32 (config/cflags.txt). */

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;

typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;

extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern int D_001ABA20 __attribute__((sda));
extern short D_001A63AC[];
typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;

extern int D_001A7478_sda __attribute__((sda));
extern int D_001A7478;
extern char D_001BAD40[];
extern void menu_restore_saved_screen_image(int);
extern int req_push_queue(char *, int);
extern int req_launch_queued(char *);
extern MenuFields D_0025C3E8;
extern FlagTarget *D_0025C3A8[];
typedef struct { short f0; short text; short enabled; } MenuEntry;
extern MenuEntry D_00261858[];
typedef struct { char p00[8]; int f08; char p0c[8]; int f14; int f18; char pad[0xE4]; int f100; int f104; char pad2[0x38]; int f140; } GameObj;


/* Handles input on the list of 33 movies: moves the cursor and starts the chosen movie if it is unlocked. */
int movie_list_handle_input(void)
{
    int result = 0;
    int flags = ((CallbackMenuState *)&g_pad_state)->flags;
    int oldCursor = D_001ABA20;

    if (flags & 0x10) {
        int value;
        int returnCode;
        D_001ABA20 = 0;
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
        D_001ABA20 = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            snd_play_from_global_bank(3, 0, 0);
            if (--D_001ABA20 < 0)
                D_001ABA20 = 0x20;
        } else if (flags & 0x4000) {
            snd_play_from_global_bank(3, 0, 0);
            if (++D_001ABA20 >= 0x21)
                D_001ABA20 = 0;
        }
        if (((CallbackMenuState *)&g_pad_state)->flags & 0x40) {
            if (D_00261858[D_001ABA20].enabled != 0) {
                char *obj;
                snd_play_from_global_bank(4, 0, 0);
                menu_restore_saved_screen_image(0);
                ((GameObj *)&g_pause_menu_state)->f100 = ((GameObj *)&g_pause_menu_state)->f14;
                ((GameObj *)&g_pause_menu_state)->f104 = ((GameObj *)&g_pause_menu_state)->f08;
                ((GameObj *)&g_pause_menu_state)->f140 = D_001A7478;
                D_001A7478_sda = 2;
                obj = D_001BAD40;
                req_push_queue(obj, D_00261858[D_001ABA20].text);
                req_launch_queued(obj);
            } else
                snd_play_from_global_bank(5, 0, 0);
        }
        {
            MenuFields *menu = &D_0025C3E8;
            menu->f58 = D_001ABA20;
            if (D_00261858[D_001ABA20].enabled != 0) {
                if (oldCursor == D_001ABA20) {
                    if (D_001A63AC[0] == 0) {
                        if (menu->f50 == oldCursor && menu->f44 == 2) {
                            D_0025C3A8[0]->flags &= -5;
                        } else if (menu->f54 == oldCursor && menu->f44 == 4) {
                            D_0025C3A8[0]->flags &= -5;
                        }
                    }
                }
            } else {
                D_0025C3A8[0]->flags |= 4;
            }
        }
    }
    return result;
}
