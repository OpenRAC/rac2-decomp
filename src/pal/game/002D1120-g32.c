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
extern int D_001ABA04 __attribute__((sda));
extern short D_001A63AC[];
typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;

extern int D_001ABA08[4];
extern int D_001ABA08_gp[] SDATA(D_001ABA08);
extern int D_001A7478_sda __attribute__((sda));
extern int D_001B1580;
extern int D_001A7478;
extern int D_0025C2B8[];
extern char D_001BAD40[];
extern void menu_restore_saved_screen_image(int);
extern int request_begin_slot(int, int, int, int, int);
extern int req_push_queue(char *, int);
extern int req_launch_queued(char *);
extern MenuFields D_0025C250;
extern FlagTarget *D_0025C210[];
typedef struct { char p00[8]; int f08; char p0c[8]; int f14; int f18; char pad[0xE4]; int f100; int f104; char pad2[0x38]; int f140; } GameObj;


int func_PAL_002D1120(void)
{
    int a = -1;
    int b = -1;
    int c = -1;
    int result = 0;
    int flags = ((CallbackMenuState *)&g_pad_state)->flags;
    int old = D_001ABA04;

    if (flags & 0x10) {
        int value;
        int status;
        D_001ABA04 = 0;
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
        D_001ABA04 = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            snd_play_from_global_bank(3, 0, 0);
            if (--D_001ABA04 < 0)
                D_001ABA04 = 3;
        } else if (flags & 0x4000) {
            snd_play_from_global_bank(3, 0, 0);
            if (++D_001ABA04 >= 4)
                D_001ABA04 = 0;
        }
        if (((CallbackMenuState *)&g_pad_state)->flags & 0x40) {
            switch (D_001ABA04) {
            case 2:
                if (D_001ABA08[D_001ABA04] != 0) { a = 4; b = 0xBD; c = 0xBE; } else a = 5;
                break;
            case 3:
                if (D_001ABA08[D_001ABA04] != 0) { a = 4; b = 0xC1; } else a = 5;
                break;
            case 1:
                if (D_001ABA08[D_001ABA04] != 0) {
                    menu_restore_saved_screen_image(1);
                    a = 4;
                    D_001B1580 = 2;
                    ((GameObj *)&g_pause_menu_state)->f100 = ((GameObj *)&g_pause_menu_state)->f14;
                    ((GameObj *)&g_pause_menu_state)->f104 = ((GameObj *)&g_pause_menu_state)->f08;
                    request_begin_slot(9, 1, 0, 0, 0);
                } else a = 5;
                break;
            case 0:
                g_pause_menu_state.value = (int)D_0025C2B8;
                a = 4;
                break;
            default:
                break;
            }
            if (b != -1) {
                char *obj;
                menu_restore_saved_screen_image(0);
                ((GameObj *)&g_pause_menu_state)->f100 = ((GameObj *)&g_pause_menu_state)->f14;
                ((GameObj *)&g_pause_menu_state)->f104 = ((GameObj *)&g_pause_menu_state)->f08;
                ((GameObj *)&g_pause_menu_state)->f140 = D_001A7478;
                D_001A7478_sda = 2;
                obj = D_001BAD40;
                req_push_queue(obj, b);
                if (c != -1)
                    req_push_queue(obj, c);
                req_launch_queued(obj);
            }
            if (a != -1)
                snd_play_from_global_bank(a, 0, 0);
        }
        if (D_001ABA04 >= 2)
            ((MenuFields *)&D_0025C250)->f58 = D_001ABA04 + 1;
        else
            ((MenuFields *)&D_0025C250)->f58 = D_001ABA04;
        if (D_001ABA08_gp[D_001ABA04] != 0) {
            if (old == D_001ABA04) {
                if (D_001A63AC[0] == 0) {
                    MenuFields *menu = &D_0025C250;
                    if (menu->f50 == old && menu->f44 == 2) {
                        D_0025C210[0]->flags &= -5;
                    } else if (menu->f54 == old && menu->f44 == 4) {
                        D_0025C210[0]->flags &= -5;
                    }
                }
            }
        } else {
            D_0025C210[0]->flags |= 4;
        }
    }
    return result;
}
