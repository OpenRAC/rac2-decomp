#include "names.h"
/* func_002DB1B0 in its own unit: its fade value and toggle flag are written through $gp, so the
   file is compiled at -G32 (config/cflags.txt). D_001B1F10 is read absolute and written through
   $gp, so it has a plain name and an sda name (as D_001A7478 in 002D01D0-g32.c). */
typedef struct { int f0; unsigned char *toggle; int pad8[2]; int flags; } ListEntry;
typedef struct { char pad0[0x34]; ListEntry *list; int cursor; int timer; } ListMenu;

extern char D_001F2840[];
extern int D_00138180[];
extern float D_001B15A0 __attribute__((sda));
extern unsigned char D_001B1F10_sda __attribute__((sda));
extern unsigned char D_001B1F10;
extern void func_002DF190(int, int);
extern void func_002B49E0(int, int, int, int, int);
extern void func_0027D330(int);

/* Handles input for a list menu: moves the cursor, toggles the chosen entry, or starts a short fade for special entries. */
int func_002DB1B0(ListMenu *object)
{
    char *root = gPauseMenuState;
    int active = *(ListMenu **)(*(char **)(root + 0x14) + 0xE8) == object;
    int flags;
    int old;

    if (object->timer != 0) {
        int t = --object->timer;
        gScreenFade = (float)(t < 5 ? t : 4) * 0.25f;
        return 0;
    }
    if (!active)
        return 0;
    {
        int *state = gPadState;
        if (!(state[0x1C4 / 4] & 0x900))
            goto proceed;
        if (*(int *)(root + 0x134) == 0)
            return 1;
    }
proceed:
    {
        int *state = gPadState;
        flags = state[0x1C4 / 4];
    }
    if (flags & 0x10) {
        char *root = gPauseMenuState;
        int value = *(int *)(*(char **)(root + 0x14) + 0xE0);
        int status;
        if (value != 0) {
            *(int *)(root + 0x18) = value;
        } else {
            switch (*(int *)(root + 0x134)) {
            case 0:
                status = -1;
                goto finish;
            default:
                break;
            }
        }
        status = 0;
finish:
        return status;
    }
    old = object->cursor;
    if (flags & 0x1000) {
        if (old != 0)
            object->cursor = old - 1;
    }
    if (gPadState[0x1C4 / 4] & 0x4000) {
        int cur = object->cursor;
        if (object->list[cur + 1].f0 != 0)
            object->cursor = cur + 1;
    }
    if (gPadState[0x1C4 / 4] & 0x40) {
        PlayMenuSoundIfEnabled(0, 0x11);

        if (object->list[object->cursor].flags & 1) {
            if (D_001B1F10_sda) {
                char *root = gPauseMenuState;
                BeginSlotRequest(4, 1, 3, *(int *)(root + 0x14), 0);
            } else {
                FadeToBlack(4);
                object->timer = 0x10;
                D_001B1F10_sda = !D_001B1F10;
            }
        } else if (object->list[object->cursor].toggle) {
            *object->list[object->cursor].toggle = !*object->list[object->cursor].toggle;
        }
    }
    if (object->cursor != old)
        PlayMenuSoundIfEnabled(1, 0x11);
    return 0;
}
