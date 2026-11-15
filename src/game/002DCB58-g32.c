#include "names.h"
/* func_002DCB58 in its own unit, a sibling of func_002DCFE8: retail reads its small scalars
   absolute and through $gp, so the file is compiled at -G32 (config/cflags.txt). The word at
   D_0025E9E0 gets its own %hi, not one derived from D_0025E870's, so it is its own global. */
typedef struct { char p00[0x14]; char *owner; int value; char p1c[0xC4]; char *screen; int fe4; char pe8[0x4C]; int fallback; int busy; int delay; char p140[0x24]; int ready; } MenuRoot;
typedef struct { char reserved[0x1B4]; int alt; char p1b8[0xC]; int flags; } PadState;
typedef struct { unsigned char b[8]; } Stamp;
typedef struct { int status; int balance; int level; int ticks; Stamp stamp; int tail; } SaveSlot;
typedef struct { char p00[8]; int mode; char p0c[4]; int f10; char p14[4]; short slot; char p1a[0x16]; SaveSlot slots[4]; char p0a0[0xA8]; int f148; char p14c[0x10]; int f15c; char p160[4]; int f164; int f168; int f16c; char p170[0xC]; int f17c; } SaveState;
typedef struct { char p00[0x30]; int flags; char p34[0xC]; int cursor; int f44; int f48; int stage; } SaveMenu;
typedef struct { char p00[0x12C]; int f12c; char p130[0x40]; int f170; } SaveScreen;

extern MenuRoot D_001F2840;
extern PadState D_00138180;
extern SaveState D_001393E0;
extern SaveScreen D_0025E870;
extern int D_0025E9E0[];
extern char *D_001A8CFC;
extern int D_001B1A3C;
extern int D_001A7424;
extern int D_001A7420;
extern int D_001A8C88;
extern int D_001A79F0;
extern int D_001A79F8;
extern int D_001A7BC0;
extern unsigned char D_001A7A0A;
extern Stamp D_001A7360;
extern int D_001A7C08;
extern char D_00260EE8[];
extern char D_0025DA38[];
extern void func_00339790(char *, int);
extern void func_002DE858(int, int);
extern void func_00287E98(void);
extern void func_002D5B38(int, char *);
extern int func_002B49E0(int, int, int, int, int);
extern int func_00287E70(void);
extern int func_002857B0(void);
extern int func_002E5E58(int, unsigned int, void *);

/* Handles the save-game slot menu: moves the cursor over the four slots, asks before overwriting a used slot, and updates the slot summary after a save finishes. */
int func_002DCB58(SaveMenu *menu)
{
    int oldCursor;
    int buttons;

    if (*(SaveMenu **)(gPauseMenuState.owner + 0xE8) != menu)
        return 0;
    if (D_001A8CFC != 0)
        SetPopupRow(D_001A8CFC + 0x3CAA8, menu->cursor);
    if (menu->stage == 0 && gPauseMenuState.screen == (char *)&D_0025E870 && D_0025E870.f12c != 0)
        menu->stage = 1;
    if (menu->stage == 1) {
        StartSaveGameToSlot(menu->f48, menu->cursor);
        gPauseMenuState.busy = 1;
        gPauseMenuState.delay = 0x2DFC;
        D_001B1A3C = 0;
    }
    menu->stage = 2;
    oldCursor = menu->cursor;
    if (gPauseMenuState.busy != 0) {
        if (gMemcardState.f15c >= 3)
            return 0;
        if (gMemcardState.f164 >= 0)
            return 0;
        if (gPauseMenuState.ready < 11)
            return 0;
        gPauseMenuState.busy = 0;
        if (gMemcardState.f16c != 0 || gMemcardState.f10 != 0 || D_001B1A3C != 0) {
            gSaveMenuFlags |= 0x80;
            if (gMemcardState.f17c != 0) {
                gMemcardState.f17c = 0;
                SetConfirmPending();
            }
            if (BeginSlotRequest(4, 1, 1, (int)gPauseMenuState.owner, 0) == 0)
                return 0;
        } else {
            gMemcardState.f17c = 1;
            gMemcardState.slots[gMemcardState.slot].balance = gPlayerBolts;
            gMemcardState.slots[gMemcardState.slot].status = gCurrentMapIndex;
            gMemcardState.slots[gMemcardState.slot].ticks = D_001A7BC0;
            {
                Stamp *stamp = &gMemcardState.slots[gMemcardState.slot].stamp;
                *stamp = D_001A7360;
            }
            gMemcardState.slots[gMemcardState.slot].level = D_001A7A0A;
        }
    }
    if ((gPadState.flags & 0x900) && gPauseMenuState.fallback == 0)
        return 1;
    if (gPadState.flags & 0x10) {
        int parentScreen = *(int *)(gPauseMenuState.owner + 0xE0);
        int result;
        if (parentScreen != 0)
            gPauseMenuState.value = parentScreen;
        else if (gPauseMenuState.fallback == 0) {
            result = -1;
            goto finish;
        }
        result = 0;
finish:
        return result;
    }
    if (gSaveMenuScreen == 9)
        SendMenuRequest(4, D_001A8C88 ? D_00260EE8 : D_0025DA38);
    else if (gSaveMenuScreen != 16 && gSaveMenuScreen != 1) {
        if (GetMenuCounter() == 0 && GetMenuMode() == 1)
            BeginSlotRequest(4, 1, 1, (int)gPauseMenuState.owner, 0);
        else {
            int parentScreen = *(int *)(gPauseMenuState.owner + 0xE0);
            int result;
            if (parentScreen != 0)
                gPauseMenuState.value = parentScreen;
            else if (gPauseMenuState.fallback == 0) {
                result = -1;
                goto done;
            }
            result = 0;
done:
            return result;
        }
    }
    if (gMemcardState.f15c >= 3)
        return 0;
    if (gMemcardState.f164 >= 0)
        return 0;
    if (gPauseMenuState.ready < 11)
        return 0;
    if (gMemcardState.mode != 2)
        return 0;
    if (menu->flags & 1)
        buttons = gPadState.alt;
    else
        buttons = gPadState.flags;
    menu->cursor = D_001A7C08;
    if ((buttons & 0x1000) && D_001A7C08 != 0)
        menu->cursor = D_001A7C08 - 1;
    if ((buttons & 0x4000) && menu->cursor < 3)
        menu->cursor = menu->cursor + 1;
    D_001A7C08 = menu->cursor;
    if (buttons & 0x40) {
        SaveState *save = &gMemcardState;
        if (save->mode == 2) {
            PlaySoundFromGlobalBank(4, 0, 0);
            if (save->slots[menu->cursor].status != -1) {
                gPauseMenuState.fe4 = 0;
                gPauseMenuState.value = (int)&D_0025E870;
                D_0025E9E0[0] = menu->cursor;
            } else
                menu->stage = 1;
        }
    }
    if (menu->cursor != oldCursor)
        PlaySoundFromGlobalBank(3, 0, 0);
    return 0;
}
