#include "include_asm.h"

#include "common.h"
typedef struct {
    short pending;
    short id;
    short timer;
    short arg;
} DelayedSlot_9CA8;
extern struct {
    u8 pad0[0x149D];
    u8 b149D;
    u8 pad149e[0x23EC - 0x149E];
    DelayedSlot_9CA8 slots[8];
} D_00189E20_9CA8;
extern void func_PAL_L00_002A6058(int, int, int, int);

/* Ticks the timer of each of the eight entries; one whose timer reports 2 is cleared and
   fires: id 0x16 calls func_PAL_L00_002A6058 with the resident byte at +0x149D, any other id
   goes to func_L00_002B9B88 with the entry's argument. */
void func_PAL_L00_002B9C20(void)
{
    int i;
    short id;

    for (i = 0; i < 8; i++) {
        if (FastDecTimer(&D_00189E20_9CA8.slots[i].timer) == 2) {
            id = D_00189E20_9CA8.slots[i].id;
            D_00189E20_9CA8.slots[i].pending = 0;
            if (id == 0x16)
                func_PAL_L00_002A6058(D_00189E20_9CA8.b149D, 1, 1, 0x32);
            else
                func_L00_002B9B88(id, D_00189E20_9CA8.slots[i].arg);
        }
    }
}


extern char D_00189EA0[];
extern int D_L00_001B9080;
extern void func_00283410(void *a, void *b);
extern void func_002833F0(void *a, void *b);
extern void func_L00_002B2BD0(void);
extern void func_L00_00322EC8(void *p);
extern void func_PAL_L00_002AF6C0(void);
extern void func_L00_002A53B8(void);
extern void func_PAL_L00_002C4480(int a0, int a1);
extern void func_L00_002D23C0(int a0, int a1);
extern void func_L00_002B4900(void);
extern float func_00282E48(void *a, void *b);
extern void func_PAL_L00_003E38E8(int a0, int a1);
extern void func_PAL_L00_004071F0(void *a, int b);
extern void func_L00_002D9D98(void);
extern void func_L00_00311DC0(void *p);
typedef struct {
    u8 pad000[0x34E];
    short h34E;
    u8 pad350[0x3A0 - 0x350];
    int i3A0;
    int flags3A4;
    u8 pad3a8[0x2290 - 0x3A8];
    char *object;
    u8 pad2294[0x229C - 0x2294];
    int i229C;
    u8 pad22a0[0x24EF - 0x22A0];
    u8 b24EF;
} ResidentState_9D60;

/* Reset the hero position and direction, the resident movement state and the related level objects. */
void func_PAL_L00_002B9CD8(void *position, void *direction, int sound, int refresh)
{
    ResidentState_9D60 *res;
    char *hero = D_00189EA0;

    qcopy(hero, position);
    res = (ResidentState_9D60 *)(hero - 0x80);
    qcopy(res->object + 0x10, position);
    qcopy(hero + 0x10, direction);

    func_00283410(res, hero + 0x10);
    func_002833F0(res->object + 0xC0, hero + 0x10);
    func_L00_002B2BD0();
    func_L00_00322EC8(hero + 0x1860);
    func_L00_00322EC8(hero + 0x19B0);

    res->flags3A4 &= ~1;
    res->flags3A4 &= ~2;
    res->h34E = 1;
    res->i3A0 = 0;
    res->b24EF = 0;

    func_PAL_L00_002AF6C0();
    func_L00_002A53B8();

    if (sound != -1)
        func_PAL_L00_002C4480(sound, 2);

    func_L00_002D23C0(*(u8 *)(res->object + 0x43), *(u8 *)(res->object + 0x41));

    if (res->i229C == 0x11)
        D_L00_001B9080 = 1;
    else
        D_L00_001B9080 = 0;

    func_L00_002B4900();

    if (func_00282E48(D_00189EA0, D_00189EA0 + 0x250) < 1.0f)
        qcopy(D_00189EA0, D_00189EA0 + 0x250);

    func_PAL_L00_003E38E8(0, 0);
    func_PAL_L00_004071F0(0, 0);

    if (refresh != 0)
        func_L00_002D9D98();

    func_L00_00311DC0(*(void **)(D_00189EA0 + 0x2210));
}

