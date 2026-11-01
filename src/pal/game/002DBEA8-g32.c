#include "include_asm.h"

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

int func_PAL_002DBEA8(ListMenu *object)
{
    char *root = D_001F2840;
    int active = *(ListMenu **)(*(char **)(root + 0x14) + 0xE8) == object;
    int flags;
    int old;

    if (object->timer != 0) {
        int t = --object->timer;
        D_001B15A0 = (float)(t < 5 ? t : 4) * 0.25f;
        return 0;
    }
    if (!active)
        return 0;
    {
        int *state = D_00138180;
        if (!(state[0x1C4 / 4] & 0x900))
            goto proceed;
        if (*(int *)(root + 0x134) == 0)
            return 1;
    }
proceed:
    {
        int *state = D_00138180;
        flags = state[0x1C4 / 4];
    }
    if (flags & 0x10) {
        char *root = D_001F2840;
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
    if (D_00138180[0x1C4 / 4] & 0x4000) {
        int cur = object->cursor;
        if (object->list[cur + 1].f0 != 0)
            object->cursor = cur + 1;
    }
    if (D_00138180[0x1C4 / 4] & 0x40) {
        func_002DF190(0, 0x11);

        if (object->list[object->cursor].flags & 1) {
            if (D_001B1F10_sda) {
                char *root = D_001F2840;
                func_002B49E0(4, 1, 3, *(int *)(root + 0x14), 0);
            } else {
                func_0027D330(4);
                object->timer = 0xD;
                D_001B1F10_sda = !D_001B1F10;
            }
        } else if (object->list[object->cursor].toggle) {
            *object->list[object->cursor].toggle = !*object->list[object->cursor].toggle;
        }
    }
    if (object->cursor != old)
        func_002DF190(1, 0x11);
    return 0;
}
