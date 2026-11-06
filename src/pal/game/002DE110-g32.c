/* func_PAL_002DE110, the PAL copy of func_002DD400 (src/game/002DD400-g32.c, where its notes are):
   the same C, where the flag D_001B1A3C goes through func_PAL_00299518 and func_PAL_00299520, the
   field at D_001A8CFC moves to 0x3CF50 and the delay is 0xC0D. Compiled at -G32 like v1.01's unit
   (config/cflags.txt). */
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
extern void func_PAL_0033B6B8(char *, int);
extern void func_PAL_002DF760(int);
extern void func_PAL_002DF6D0(int, int);
extern void func_002F64A8(void);
extern void func_00298E08(void);
extern void func_PAL_002D6710(int, char *);
extern int func_002B49E0(int, int, int, int, int);
extern int func_00287E70(void);
extern int func_002857B0(void);
extern void func_PAL_002DFF60(int, int);
extern int func_PAL_00299518(void);
extern int func_PAL_00299520(void);

int func_PAL_002DE110(SaveMenu *menu)
{
    int old;
    int buttons;

    if (*(SaveMenu **)(D_001F2840.owner + 0xE8) != menu)
        return 0;
    old = menu->cursor;
    if (D_001A8CFC != 0)
        func_PAL_0033B6B8(D_001A8CFC + 0x3CF50, old);
    if (menu->stage == 0 && D_001F2840.screen == (char *)&D_00261108 && ((SaveScreen *)D_001F2840.screen)->f12c != 0)
        menu->stage = 1;
    if (menu->stage == 0 && D_001F2840.screen == (char *)&D_002613B8 && ((SaveScreen *)D_001F2840.screen)->f12c != 0)
        menu->stage = 1;
    if (menu->stage == 1) {
        if (menu->flags & 0x2000)
            func_PAL_002DF760(menu->cursor);
        else
            func_PAL_002DF6D0(menu->f48, menu->cursor);
        D_001393E0.f17c = 1;
        D_001F2840.busy = 1;
        func_PAL_00299520();
        D_001F2840.ready = 0;
        D_001F2840.delay = 0xC0D;
    }
    menu->stage = 2;
    if (D_001F2840.busy != 0) {
        SaveState *save = &D_001393E0;
        if (save->f15c >= 3)
            return 0;
        if (save->f164 >= 0)
            return 0;
        if (D_001F2840.ready < 11)
            return 0;
        D_001F2840.busy = 0;
        if (save->f16c != 0 || save->f10 != 0 || func_PAL_00299518() != 0) {
            if (D_001A8C8C != 0) {
                D_001A7424 |= 0x80;
                func_002B49E0(4, 1, 5, (int)D_001F2840.owner, 0);
                D_001393E0.f17c = 0;
                return 0;
            }
            D_001393E0.f17c = 0;
            D_001A7424 |= 0x80;
            func_002B49E0(4, 1, 1, (int)D_001F2840.owner, 0);
            return 0;
        }
        save->f17c = 1;
        D_001393E0.slots[D_001393E0.slot].balance = D_001A79F8;
        D_001393E0.slots[D_001393E0.slot].status = D_001A79F0;
        D_001393E0.slots[D_001393E0.slot].ticks = D_001A7BC0;
        {
            Stamp *stamp = &D_001393E0.slots[D_001393E0.slot].stamp;
            *stamp = D_001A7360;
        }
        D_001393E0.slots[D_001393E0.slot].level = D_001A7A0A;
        func_002F64A8();
        save->f17c = 1;
        D_001A8C88 = 0;
        return 0;
    }
    if ((D_00138180.flags & 0x900) && D_001F2840.fallback == 0 && D_001A8C8C == 0)
        return 1;
    if ((D_00138180.flags & 0x10) && D_001A8C8C == 0) {
        int value = *(int *)(D_001F2840.owner + 0xE0);
        int status;
        if (value != 0)
            D_001F2840.value = value;
        else if (D_001F2840.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
finish:
        return status;
    }
    if (D_001A7420 == 9)
    {
        char *screen;
        if (D_001A8C8C != 0)
            screen = D_00261238;
        else if (D_001A8C88 != 0)
            screen = D_00260EE8;
        else
            screen = D_0025DA38;
        func_PAL_002D6710(4, screen);
    }
    else if (D_001A7420 != 16 && D_001A7420 != 1) {
        if (func_00287E70() == 0 && func_002857B0() == 1)
            func_002B49E0(4, 1, 1, (int)D_001F2840.owner, 0);
        else if (D_001A8C8C == 0) {
            int value = *(int *)(D_001F2840.owner + 0xE0);
            int status;
            if (value != 0)
                D_001F2840.value = value;
            else if (D_001F2840.fallback == 0) {
                status = -1;
                goto done;
            }
            status = 0;
done:
            return status;
        }
    }
    if (D_001393E0.f15c >= 3)
        return 0;
    if (D_001393E0.f164 >= 0)
        return 0;
    if (D_001F2840.ready < 11)
        return 0;
    if (D_001393E0.mode != 2)
        return 0;
    if (menu->flags & 1)
        buttons = D_00138180.alt;
    else
        buttons = D_00138180.flags;
    menu->cursor = D_001A7C08;
    if ((buttons & 0x1000) && D_001A7C08 != 0)
        menu->cursor = D_001A7C08 - 1;
    if ((buttons & 0x4000) && menu->cursor < 3)
        menu->cursor = menu->cursor + 1;
    D_001A7C08 = menu->cursor;
    if ((buttons & 0x20) && D_001393E0.mode == 2) {
        if (menu->flags & 0x2000) {
            D_001393E0.f17c = 0;
            func_PAL_002DF760(-1);
            func_002F64A8();
            return 0;
        }
        func_00298E08();
        {
            int mode = D_001A7424 & ~2;
            mode &= ~4;
            D_001A7424 = mode | 0x20;
        }
        func_002F64A8();
        return 0;
    }
    if (buttons & 0x40) {
        if (D_001393E0.slots[menu->cursor].status != -1) {
            D_001F2840.value = (menu->flags & 0x2000) ? (int)&D_002613B8 : (int)&D_00261108;
            D_001F2840.fe4 = (menu->flags & 0x2000) ? 2 : 1;
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
    if (menu->cursor != old)
        func_PAL_002DFF60(1, 0x11);
    return 0;
}
