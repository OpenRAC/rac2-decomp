#include "names.h"
/* func_002DCFE8 in its own unit: retail reads its small scalars absolute and through $gp, so
   the file is compiled at -G32 (config/cflags.txt). */
typedef struct { char p00[0x14]; char *owner; int value; char p1c[0x118]; int fallback; int busy; int delay; char p140[0x24]; int ready; } MenuRoot;
typedef struct { char reserved[0x1B4]; int alt; char p1b8[0xC]; int flags; } PadState;
typedef struct { int status; char p04[0x18]; } SaveSlot;
typedef struct { char p00[8]; int mode; char p0c[4]; int f10; char p14[4]; short slot; char p1a[0x16]; SaveSlot slots[4]; char p0a0[0xA8]; int f148; char p14c[0x10]; int f15c; char p160[4]; int f164; int f168; int f16c; char p170[0xC]; int f17c; } SaveState;
typedef struct { char p00[0x30]; int flags; char p34[0xC]; int cursor; } SaveMenu;

extern MenuRoot D_001F2840;
extern PadState D_00138180;
extern SaveState D_001393E0;
extern char *D_001A8CFC;
extern int D_001B1A3C;
extern int D_001A7424;
extern int D_001A7420;
extern int D_001A8C88;
extern int D_001A7B98;
extern int D_001A79F0;
extern unsigned char D_001A7BE8;
extern int D_001A7C08;
extern short D_00152C28[];
extern int D_001C4FB0[];
extern char D_001F2A40[];
extern char D_00260DB8[];
extern char D_0025DB68[];
extern void func_00339790(char *, int);
extern void func_002E4860(void);
extern int func_002B7CE0(int);
extern void func_00132938(int);
extern void func_002F64A8(void);
extern void func_002D5B38(int, char *);
extern void func_0029ADA0(char *);
extern void func_002C9A78(void);
extern int func_002B49E0(int, int, int, int, int);
extern int func_00287E70(void);
extern int func_002857B0(void);
extern int func_002E5E58(int, unsigned int, void *);

/* Handles the load-game slot menu: moves the cursor over the four slots and starts loading the chosen one. */
int func_002DCFE8(SaveMenu *menu)
{
    int oldCursor = menu->cursor;
    int buttons;

    if (D_001A8CFC != 0)
        SetPopupRow(D_001A8CFC + 0x3CAA8, oldCursor);
    if (gPauseMenuState.busy != 0) {
        if (gMemcardState.f15c >= 3)
            return 0;
        if (gMemcardState.f164 >= 0)
            return 0;
        if (gPauseMenuState.ready < 11)
            return 0;
        gPauseMenuState.busy = 0;
        if (gMemcardState.f16c != 0 || gMemcardState.f10 != 0 || D_001B1A3C != 0) {
            gMemcardState.f17c = 0;
            gSaveMenuFlags |= 0x100;
            if (BeginSlotRequest(4, 1, 1, (int)gPauseMenuState.owner, 0) == 0)
                return 0;
        } else {
            gMemcardState.f17c = 1;
            SetDefaultSoundGroupVolumes();
            PumpMusicAndDiscRead(1);
            SendSoundCommand11_00132938(D_001A7B98 == 0);
            if (gCurrentMapIndex <= 0 && D_001A7BE8 == 0)
                LoadDataAndSetupCallback();
            else
                BeginSlotRequest(6, 2, 5, gCurrentMapIndex, 0);
            D_00152C28[0] = 0;
            return 0;
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
        SendMenuRequest(5, D_001A8C88 ? D_00260DB8 : D_0025DB68);
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
        if (save->mode == 2 && save->slots[D_001A7C08].status >= 0) {
            PlaySoundFromGlobalBank(4, 0, 0);
            save->f148 = 0;
            save->slot = menu->cursor;
            BuildSavePacket(D_001F2A40);
            InitMenuBlockFields();
            if (save->f164 < 0) {
                save->f168 = 0;
                save->f164 = 13;
            }
            gPauseMenuState.busy = 1;
            gPauseMenuState.delay = 0x2DFD;
            D_001C4FB0[0] = 0;
            D_001B1A3C = 0;
        } else
            PlaySoundFromGlobalBank(5, 0, 0);
    }
    if (menu->cursor != oldCursor)
        PlaySoundFromGlobalBank(3, 0, 0);
    return 0;
}
