#include "names.h"
/* func_PAL_002D1120, the PAL copy of func_002D01D0: the same C, with four slots in place of
   five (the 0xBF slot is gone, so the switch becomes a ladder and each arm folds its
   D_001ABA08 index to a constant) and the menu's slot field skipping the removed one.
   Compiled at -G32 like the original (config/cflags.txt). D_001A7478 is read absolute
   (lui/lw) and written through $gp, so it has a plain name and an sda name; D_001ABA08
   has both forms too: absolute at a constant index, $gp for its base. */
#include "common.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;

typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;

extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern int g_extras_page_cursor __attribute__((sda));
extern short g_sequence_active_flag[];
typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;

extern int g_extras_page_unlocked[4];
extern int D_001ABA08_gp[] SDATA(D_001ABA08);
extern int D_001A7478_sda __attribute__((sda));
extern int g_extras_menu_page;
extern int g_loader_state_word;
extern int g_extras_page_value_block[];
extern char g_loader_movie[];
extern void menu_restore_saved_screen_image(int);
extern int request_begin_slot(int, int, int, int, int);
extern int req_push_queue(char *, int);
extern int req_launch_queued(char *);
extern MenuFields g_extras_page_fields;
extern FlagTarget *g_extras_page_flag_targets[];
typedef struct { char p00[8]; int f08; char p0c[8]; int f14; int f18; char pad[0xE4]; int f100; int f104; char pad2[0x38]; int f140; } GameObj;


int menu_handle_extras_page_input_pal(void)
{
    int sound = -1;
    int movie_a = -1;
    int movie_b = -1;
    int result = 0;
    int flags = ((CallbackMenuState *)&g_pad_state)->flags;
    int old_cursor = g_extras_page_cursor;

    if (flags & 0x10) {
        int value;
        int status;
        g_extras_page_cursor = 0;
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900) {
        g_extras_page_cursor = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            snd_play_from_global_bank(3, 0, 0);
            if (--g_extras_page_cursor < 0)
                g_extras_page_cursor = 3;
        } else if (flags & 0x4000) {
            snd_play_from_global_bank(3, 0, 0);
            if (++g_extras_page_cursor >= 4)
                g_extras_page_cursor = 0;
        }
        if (((CallbackMenuState *)&g_pad_state)->flags & 0x40) {
            switch (g_extras_page_cursor) {
            case 2:
                if (g_extras_page_unlocked[g_extras_page_cursor] != 0) { sound = 4; movie_a = 0xBD; movie_b = 0xBE; } else sound = 5;
                break;
            case 3:
                if (g_extras_page_unlocked[g_extras_page_cursor] != 0) { sound = 4; movie_a = 0xC1; } else sound = 5;
                break;
            case 1:
                if (g_extras_page_unlocked[g_extras_page_cursor] != 0) {
                    menu_restore_saved_screen_image(1);
                    sound = 4;
                    g_extras_menu_page = 2;
                    ((GameObj *)&g_pause_menu_state)->f100 = ((GameObj *)&g_pause_menu_state)->f14;
                    ((GameObj *)&g_pause_menu_state)->f104 = ((GameObj *)&g_pause_menu_state)->f08;
                    request_begin_slot(9, 1, 0, 0, 0);
                } else sound = 5;
                break;
            case 0:
                g_pause_menu_state.value = (int)g_extras_page_value_block;
                sound = 4;
                break;
            default:
                break;
            }
            if (movie_a != -1) {
                char *obj;
                menu_restore_saved_screen_image(0);
                ((GameObj *)&g_pause_menu_state)->f100 = ((GameObj *)&g_pause_menu_state)->f14;
                ((GameObj *)&g_pause_menu_state)->f104 = ((GameObj *)&g_pause_menu_state)->f08;
                ((GameObj *)&g_pause_menu_state)->f140 = g_loader_state_word;
                D_001A7478_sda = 2;
                obj = g_loader_movie;
                req_push_queue(obj, movie_a);
                if (movie_b != -1)
                    req_push_queue(obj, movie_b);
                req_launch_queued(obj);
            }
            if (sound != -1)
                snd_play_from_global_bank(sound, 0, 0);
        }
        if (g_extras_page_cursor >= 2)
            ((MenuFields *)&g_extras_page_fields)->f58 = g_extras_page_cursor + 1;
        else
            ((MenuFields *)&g_extras_page_fields)->f58 = g_extras_page_cursor;
        if (D_001ABA08_gp[g_extras_page_cursor] != 0) {
            if (old_cursor == g_extras_page_cursor) {
                if (g_sequence_active_flag[0] == 0) {
                    MenuFields *menu = &g_extras_page_fields;
                    if (menu->f50 == old_cursor && menu->f44 == 2) {
                        g_extras_page_flag_targets[0]->flags &= -5;
                    } else if (menu->f54 == old_cursor && menu->f44 == 4) {
                        g_extras_page_flag_targets[0]->flags &= -5;
                    }
                }
            }
        } else {
            g_extras_page_flag_targets[0]->flags |= 4;
        }
    }
    return result;
}
