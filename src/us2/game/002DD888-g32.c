/* func_US2_002DD888, the USA v2.00 copy of func_002DCB58, at -G32 like v1.01's unit. The same C, where the
   word D_001B1A3C becomes the accessors func_US2_00299960/68 (one extra saved register), the back test also
   needs D_001A8C8C clear, the field offset is 0x3CEA0 and the delay 0x2C92. */
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
extern int D_001A8C8C;
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
extern void func_US2_0033A7D8(char *, int);
extern int func_US2_00299960(void);
extern int func_US2_00299968(void);
extern void func_002DE858(int, int);
extern void func_00287E98(void);
extern void func_002D5B38(int, char *);
extern int func_002B49E0(int, int, int, int, int);
extern int func_00287E70(void);
extern int func_002857B0(void);
extern int func_002E5E58(int, unsigned int, void *);

int func_US2_002DD888(SaveMenu *menu)
{
    int old;
    int buttons;

    if (*(SaveMenu **)(D_001F2840.owner + 0xE8) != menu)
        return 0;
    if (D_001A8CFC != 0)
        func_US2_0033A7D8(D_001A8CFC + 0x3CEA0, menu->cursor);
    if (menu->stage == 0 && D_001F2840.screen == (char *)&D_0025E870 && D_0025E870.f12c != 0)
        menu->stage = 1;
    if (menu->stage == 1) {
        func_002DE858(menu->f48, menu->cursor);
        D_001F2840.busy = 1;
        func_US2_00299968();
        D_001F2840.delay = 0x2C92;
    }
    menu->stage = 2;
    old = menu->cursor;
    if (D_001F2840.busy != 0) {
        if (D_001393E0.f15c >= 3)
            return 0;
        if (D_001393E0.f164 >= 0)
            return 0;
        if (D_001F2840.ready < 11)
            return 0;
        D_001F2840.busy = 0;
        if (D_001393E0.f16c != 0 || D_001393E0.f10 != 0 || func_US2_00299960() != 0) {
            D_001A7424 |= 0x80;
            if (D_001393E0.f17c != 0) {
                D_001393E0.f17c = 0;
                func_00287E98();
            }
            if (func_002B49E0(4, 1, 1, (int)D_001F2840.owner, 0) == 0)
                return 0;
        } else {
            D_001393E0.f17c = 1;
            D_001393E0.slots[D_001393E0.slot].balance = D_001A79F8;
            D_001393E0.slots[D_001393E0.slot].status = D_001A79F0;
            D_001393E0.slots[D_001393E0.slot].ticks = D_001A7BC0;
            {
                Stamp *stamp = &D_001393E0.slots[D_001393E0.slot].stamp;
                *stamp = D_001A7360;
            }
            D_001393E0.slots[D_001393E0.slot].level = D_001A7A0A;
        }
    }
    if ((D_00138180.flags & 0x900) && D_001F2840.fallback == 0 && D_001A8C8C == 0)
        return 1;
    if (D_00138180.flags & 0x10) {
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
        func_002D5B38(4, D_001A8C88 ? D_00260EE8 : D_0025DA38);
    else if (D_001A7420 != 16 && D_001A7420 != 1) {
        if (func_00287E70() == 0 && func_002857B0() == 1)
            func_002B49E0(4, 1, 1, (int)D_001F2840.owner, 0);
        else {
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
    if (buttons & 0x40) {
        SaveState *save = &D_001393E0;
        if (save->mode == 2) {
            func_002E5E58(4, 0, 0);
            if (save->slots[menu->cursor].status != -1) {
                D_001F2840.fe4 = 0;
                D_001F2840.value = (int)&D_0025E870;
                D_0025E9E0[0] = menu->cursor;
            } else
                menu->stage = 1;
        }
    }
    if (menu->cursor != old)
        func_002E5E58(3, 0, 0);
    return 0;
}
