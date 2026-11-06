#include "common.h"
#include "include_asm.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;

extern CallbackMenuState D_00138180;
extern SelectionCallback D_001F2840;
extern int D_001ABA28 __attribute__((sda));
extern unsigned char D_001ABA30[8] __attribute__((sda));
extern int D_001A7904 __attribute__((sda));
extern short D_001A63AC[];
extern FlagTarget *D_0025C540[];
extern MenuFields D_0025C580;
extern int D_0026CD20[];
extern int D_PAL_001A7A78 MACRO_ADDR;
extern int D_PAL_001A7988 MACRO_ADDR;

extern int func_002E5E58(int, unsigned int, void *);
extern void func_00288CB0(int, int);

/* func_PAL_002D1EB0, the PAL copy of func_002D0FA0: the same C, where the last case also
 * sets D_001A7904 and keeps D_PAL_001A7A78 in D_PAL_001A7988 unless it is already 21. */
int func_PAL_002D1EB0(void)
{
    static void *cases[8] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7};
    int flags = ((CallbackMenuState *)&D_00138180)->flags;
    int old = D_001ABA28;
    int result = 0;

    if (flags & 0x10) {
        int value;
        int status;
        D_001ABA28 = 0;
        value = *(int *)(D_001F2840.source + 0xE0);
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
    if (flags & 0x900) {
        D_001ABA28 = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            func_002E5E58(3, 0, 0);
            if (--D_001ABA28 < 0)
                D_001ABA28 = 7;
        } else if (flags & 0x4000) {
            func_002E5E58(3, 0, 0);
            if (++D_001ABA28 >= 8)
                D_001ABA28 = 0;
        }
        if (((CallbackMenuState *)&D_00138180)->flags & 0x40) {
            if (D_001ABA30[D_001ABA28] != 0) {
                func_002E5E58(4, 0, 0);
                if ((unsigned)D_001ABA28 < 8)
                    goto *D_0026CD20[D_001ABA28];
                goto cont;
c0:            D_001A7904 = 2; func_00288CB0(2, 1); goto cont;
c1:            D_001A7904 = 3; func_00288CB0(4, 1); goto cont;
c2:            D_001A7904 = 3; func_00288CB0(11, 1); goto cont;
c3:            D_001A7904 = 2; func_00288CB0(11, 1); goto cont;
c4:            D_001A7904 = 1; func_00288CB0(26, 1); goto cont;
c5:            D_001A7904 = 1; func_00288CB0(22, 1); goto cont;
c6:            D_001A7904 = 1; func_00288CB0(23, 1); goto cont;
c7:            D_001A7904 = 1;
               {
                   int level = D_PAL_001A7A78;
                   if (level != 21)
                       D_PAL_001A7988 = level;
               }
               func_00288CB0(21, 1);
               goto cont;
            } else {
                func_002E5E58(5, 0, 0);
            }
        }
cont:
        {
            MenuFields *menu = &D_0025C580;
            menu->f58 = D_001ABA28;
            if (D_001ABA30[D_001ABA28] != 0) {
                if (old == D_001ABA28) {
                    if (D_001A63AC[0] == 0) {
                        if (menu->f50 == old && menu->f44 == 2) {
                            D_0025C540[0]->flags &= -5;
                        } else if (menu->f54 == old && menu->f44 == 4) {
                            D_0025C540[0]->flags &= -5;
                        }
                    }
                }
            } else {
                D_0025C540[0]->flags |= 4;
            }
        }
    }
    return result;
}
