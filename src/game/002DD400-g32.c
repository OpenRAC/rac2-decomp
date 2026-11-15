#include "names.h"
/* func_002DD400 in its own unit, a sibling of func_002DCB58 (002DCB58-g32.c): the save-slot
   menu's handler. -O2 -G32 -Wa,-G32 like its siblings (config/cflags.txt). The screen for the
   cross button is one store of a conditional value, so its base address is formed once before
   the test. The empty-slot arm tests the 0x2000 flag as the other arm does; jump2's cross-jumping
   merges its two identical outcomes after life analysis, which leaves retail's dead
   `andi 0x2000` there. */
typedef struct { char p00[0x14]; char *owner; int value; char p1c[0xC4]; char *screen; int fe4; char pe8[0x4C]; int fallback; int busy; int delay; char p140[0x24]; int ready; } MenuRoot;
typedef struct { char reserved[0x1B4]; int alt; char p1b8[0xC]; int flags; } PadState;
typedef struct { unsigned char b[8]; } Stamp;
typedef struct { int status; int balance; int level; int ticks; Stamp stamp; int tail; } SaveSlot;
typedef struct { char p00[8]; int mode; char p0c[4]; int f10; char p14[4]; short slot; char p1a[0x16]; SaveSlot slots[4]; char p0a0[0xA8]; int f148; char p14c[0x10]; int f15c; char p160[4]; int f164; int f168; int f16c; char p170[0xC]; int f17c; } SaveState;
typedef struct { char p00[0x30]; int flags; char p34[0xC]; int cursor; int f44; int f48; int stage; } SaveMenu;
typedef struct { char p00[0x12C]; int f12c; } SaveScreen;

extern MenuRoot D_001F2840;
extern PadState D_00138180;
extern SaveState D_001393E0;
extern SaveScreen D_00261108;
extern SaveScreen D_002613B8;
extern int D_0025E9E0[];
extern char *D_001A8CFC;
extern int D_001B1A3C;
extern int D_001A7424;
extern int D_001A7420;
extern int D_001A8C88;
extern int D_001A8C8C;
extern int D_001A79F0;
extern int D_001A79F8;
extern int D_001A7BC0;
extern unsigned char D_001A7A0A;
extern Stamp D_001A7360;
extern int D_001A7C08;
extern char D_00261238[];
extern char D_00260EE8[];
extern char D_0025DA38[];
extern void func_00339790(char *, int);
extern void func_002DE990(int);
extern void func_002DE900(int, int);
extern void func_002F64A8(void);
extern void func_00298E08(void);
extern void func_002D5B38(int, char *);
extern int func_002B49E0(int, int, int, int, int);
extern int func_00287E70(void);
extern int func_002857B0(void);
extern void func_002DF190(int, int);

/* Handles the slot menu with a cancel button and confirmation screens: moves the cursor, starts a save into the chosen slot, and finishes or reports the result. */
int func_002DD400(SaveMenu *menu)
{
    int oldCursor;
    int buttons;

    if (*(SaveMenu **)(gPauseMenuState.owner + 0xE8) != menu)
        return 0;
    oldCursor = menu->cursor;
    if (D_001A8CFC != 0)
        SetPopupRow(D_001A8CFC + 0x3CAA8, oldCursor);
    if (menu->stage == 0 && gPauseMenuState.screen == (char *)&D_00261108 && ((SaveScreen *)gPauseMenuState.screen)->f12c != 0)
        menu->stage = 1;
    if (menu->stage == 0 && gPauseMenuState.screen == (char *)&D_002613B8 && ((SaveScreen *)gPauseMenuState.screen)->f12c != 0)
        menu->stage = 1;
    if (menu->stage == 1) {
        if (menu->flags & 0x2000)
            RestartGameKeepingProgress(menu->cursor);
        else
            ClearSlotAndStartSave(menu->f48, menu->cursor);
        gMemcardState.f17c = 1;
        gPauseMenuState.busy = 1;
        D_001B1A3C = 0;
        gPauseMenuState.ready = 0;
        gPauseMenuState.delay = 0x2DFC;
    }
    menu->stage = 2;
    if (gPauseMenuState.busy != 0) {
        SaveState *save = &gMemcardState;
        if (save->f15c >= 3)
            return 0;
        if (save->f164 >= 0)
            return 0;
        if (gPauseMenuState.ready < 11)
            return 0;
        gPauseMenuState.busy = 0;
        if (save->f16c != 0 || save->f10 != 0 || D_001B1A3C != 0) {
            if (D_001A8C8C != 0) {
                gSaveMenuFlags |= 0x80;
                BeginSlotRequest(4, 1, 5, (int)gPauseMenuState.owner, 0);
                gMemcardState.f17c = 0;
                return 0;
            }
            gMemcardState.f17c = 0;
            gSaveMenuFlags |= 0x80;
            BeginSlotRequest(4, 1, 1, (int)gPauseMenuState.owner, 0);
            return 0;
        }
        save->f17c = 1;
        gMemcardState.slots[gMemcardState.slot].balance = gPlayerBolts;
        gMemcardState.slots[gMemcardState.slot].status = gCurrentMapIndex;
        gMemcardState.slots[gMemcardState.slot].ticks = D_001A7BC0;
        {
            Stamp *stamp = &gMemcardState.slots[gMemcardState.slot].stamp;
            *stamp = D_001A7360;
        }
        gMemcardState.slots[gMemcardState.slot].level = D_001A7A0A;
        LoadDataAndSetupCallback();
        save->f17c = 1;
        D_001A8C88 = 0;
        return 0;
    }
    if ((gPadState.flags & 0x900) && gPauseMenuState.fallback == 0 && D_001A8C8C == 0)
        return 1;
    if ((gPadState.flags & 0x10) && D_001A8C8C == 0) {
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
    {
        char *screen;
        if (D_001A8C8C != 0)
            screen = D_00261238;
        else if (D_001A8C88 != 0)
            screen = D_00260EE8;
        else
            screen = D_0025DA38;
        SendMenuRequest(4, screen);
    }
    else if (gSaveMenuScreen != 16 && gSaveMenuScreen != 1) {
        if (GetMenuCounter() == 0 && GetMenuMode() == 1)
            BeginSlotRequest(4, 1, 1, (int)gPauseMenuState.owner, 0);
        else if (D_001A8C8C == 0) {
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
    if ((buttons & 0x20) && gMemcardState.mode == 2) {
        if (menu->flags & 0x2000) {
            gMemcardState.f17c = 0;
            RestartGameKeepingProgress(-1);
            LoadDataAndSetupCallback();
            return 0;
        }
        LoadGameDataAndResetSaveMenu();
        {
            int mode = gSaveMenuFlags & ~2;
            mode &= ~4;
            gSaveMenuFlags = mode | 0x20;
        }
        LoadDataAndSetupCallback();
        return 0;
    }
    if (buttons & 0x40) {
        if (gMemcardState.slots[menu->cursor].status != -1) {
            gPauseMenuState.value = (menu->flags & 0x2000) ? (int)&D_002613B8 : (int)&D_00261108;
            gPauseMenuState.fe4 = (menu->flags & 0x2000) ? 2 : 1;
            D_0025E9E0[0] = menu->cursor;
        } else {
            if (menu->flags & 0x2000) {
                menu->stage = 1;
                return 0;
            }
            menu->stage = 1;
            return 0;
        }
    }
    if (menu->cursor != oldCursor)
        PlayMenuSoundIfEnabled(1, 0x11);
    return 0;
}
