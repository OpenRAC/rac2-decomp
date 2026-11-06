/* func_US2_002DDD30, the USA v2.00 copy of func_002DCFE8, at -G32 like v1.01's unit. The same C, where the
   word D_001B1A3C becomes the accessors func_US2_00299960/68 (one extra saved register), the back test also
   needs D_001A8C8C clear, the field offset is 0x3CEA0 and the delay 0x2C93. */
typedef struct { char p00[0x14]; char *owner; int value; char p1c[0x118]; int fallback; int busy; int delay; char p140[0x24]; int ready; } MenuRoot;
typedef struct { char reserved[0x1B4]; int alt; char p1b8[0xC]; int flags; } PadState;
typedef struct { int status; char p04[0x18]; } SaveSlot;
typedef struct { char p00[8]; int mode; char p0c[4]; int f10; char p14[4]; short slot; char p1a[0x16]; SaveSlot slots[4]; char p0a0[0xA8]; int f148; char p14c[0x10]; int f15c; char p160[4]; int f164; int f168; int f16c; char p170[0xC]; int f17c; } SaveState;
typedef struct { char p00[0x30]; int flags; char p34[0xC]; int cursor; } SaveMenu;

extern MenuRoot D_001F2840;
extern PadState D_00138180;
extern SaveState D_001393E0;
extern char *D_001A8CFC;
extern int D_001A8C8C;
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
extern void func_US2_0033A7D8(char *, int);
extern int func_US2_00299960(void);
extern int func_US2_00299968(void);
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

int func_US2_002DDD30(SaveMenu *menu)
{
    int old = menu->cursor;
    int buttons;

    if (D_001A8CFC != 0)
        func_US2_0033A7D8(D_001A8CFC + 0x3CEA0, old);
    if (D_001F2840.busy != 0) {
        if (D_001393E0.f15c >= 3)
            return 0;
        if (D_001393E0.f164 >= 0)
            return 0;
        if (D_001F2840.ready < 11)
            return 0;
        D_001F2840.busy = 0;
        if (D_001393E0.f16c != 0 || D_001393E0.f10 != 0 || func_US2_00299960() != 0) {
            D_001393E0.f17c = 0;
            D_001A7424 |= 0x100;
            if (func_002B49E0(4, 1, 1, (int)D_001F2840.owner, 0) == 0)
                return 0;
        } else {
            D_001393E0.f17c = 1;
            func_002E4860();
            func_002B7CE0(1);
            func_00132938(D_001A7B98 == 0);
            if (D_001A79F0 <= 0 && D_001A7BE8 == 0)
                func_002F64A8();
            else
                func_002B49E0(6, 2, 5, D_001A79F0, 0);
            D_00152C28[0] = 0;
            return 0;
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
        func_002D5B38(5, D_001A8C88 ? D_00260DB8 : D_0025DB68);
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
        if (save->mode == 2 && save->slots[D_001A7C08].status >= 0) {
            func_002E5E58(4, 0, 0);
            save->f148 = 0;
            save->slot = menu->cursor;
            func_0029ADA0(D_001F2A40);
            func_002C9A78();
            if (save->f164 < 0) {
                save->f168 = 0;
                save->f164 = 13;
            }
            D_001F2840.busy = 1;
            func_US2_00299968();
            D_001F2840.delay = 0x2C93;
            D_001C4FB0[0] = 0;
        } else
            func_002E5E58(5, 0, 0);
    }
    if (menu->cursor != old)
        func_002E5E58(3, 0, 0);
    return 0;
}
