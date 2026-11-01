#include "common.h"
/* func_0029BCD8 is in 0029BCC8-g8.c (it reaches small data through $gp). */

extern int ref_L00_0030CDB0_00[] __attribute__((sda));
extern int D_001A8BB0[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern void func_0029BB30(void);
extern unsigned int func_00285840(void);
extern void func_0029B858(void);

typedef int (*Fn)(void);

/* The level object D_001A8CFC points at: the callback tables live at +0x38000. */
typedef struct { void *cb; int pad; } Slot;
typedef struct {
    char pad0[0x7350];
    void *cb1;
    char pad1[0x7368 - 0x7354];
    void *cb2;
    char pad2[0x7370 - 0x736C];
    Slot slot[4];
    Slot slot2[2];
} Sub;

void func_0029BCD8(void)
{
    int i;
    int result;
    Sub *sub;
    Fn fn;
    char *g;

    if (ref_L00_0030CDB0_00[0] != 0)
        return;

    if (D_001A8CFC[0] == 0)
        goto states;
    func_0029BB30();
    fn = (Fn)((Sub *)(D_001A8CFC[0] + 0x38000))->cb2;
    if (fn != 0) {
        if (fn() != 0)
            return;
    }
    result = 0;
    for (i = 0; i < 4; i++) {
        sub = (Sub *)(D_001A8CFC[0] + 0x38000);
        if (sub->slot[i].cb != 0)
            result |= ((Fn *)(D_001A8CFC[0] + 0x3F370))[i * 2]();
    }
    if (result != 0)
        return;
    for (i = 0; i < 2; i++) {
        sub = (Sub *)(D_001A8CFC[0] + 0x38000);
        if (sub->slot2[i].cb != 0)
            result |= ((Fn *)(D_001A8CFC[0] + 0x3F390))[i * 2]();
    }
    if (result != 0)
        return;
states:
    if (D_001A8BB0[0] != 0 && D_001A8BB0[0] != 5) {
        if (D_001A8BB0[0] == 4) {
            if (func_00285840() != 7)
                return;
        }
    }
    g = D_001A8CFC[0];
    if (g != 0) {
        char *b = g + 0x38000;
        g = (char *)((Sub *)b)->cb1;
        ((Fn)g)();
        func_0029B858();
    }
}

/* func_0029BF08: the same level-object callback tables as func_0029BCD8, but at
   different offsets, plus a camera projection scale written around a call. */
extern int ref_L00_0030CFE0_00[] __attribute__((sda));
extern void func_00290680(void);
extern void func_0029BEB8(void);
extern void func_0029BE88(void);
extern void func_0027AB40(void);

typedef unsigned int (*Cb)(void);

typedef struct { void *cb; int pad; } SlotBf;
typedef struct {
    char pad0[0x734C];
    void *cb1;
    char pad1[0x736C - 0x7350];
    void *cb2;
    char pad2[0x7374 - 0x7370];
    SlotBf slot[4];
    SlotBf slot2[2];
} SubBf;

/* The same table seen from its other end: the callback pointer is the second word. */
typedef struct { int pad; void *fn; } FnBf;

typedef struct { char pad[0xB0]; float scale; } CamBf;

/* The camera object: its projection scale is at +0xB0. */
extern CamBf ref_L00_0030CFE0_01;

void func_0029BF08(void)
{
    int result;
    int i;
    Cb fn;
    SubBf *sub;
    char *g;
    float saved;

    if (ref_L00_0030CFE0_00[0] != 0)
        return;

    if (D_001A8CFC[0] == 0)
        goto states;

    func_00290680();
    result = 0;
    func_0029BEB8();

    fn = (Cb)((SubBf *)(D_001A8CFC[0] + 0x38000))->cb2;
    if (fn != 0)
        result = fn() != 0;

    for (i = 0; i < 4; i++) {
        sub = (SubBf *)(D_001A8CFC[0] + 0x38000);
        if (sub->slot[i].cb != 0)
            result |= ((Cb)((FnBf *)(D_001A8CFC[0] + 0x3F370))[i].fn)();
    }

    for (i = 0; i < 2; i++) {
        sub = (SubBf *)(D_001A8CFC[0] + 0x38000);
        if (sub->slot2[i].cb != 0)
            result |= ((Cb)((FnBf *)(D_001A8CFC[0] + 0x3F390))[i].fn)();
    }

    if (result != 0)
        return;

states:
    if (D_001A8BB0[0] != 0 && D_001A8BB0[0] != 5) {
        if (D_001A8BB0[0] == 4) {
            if (func_00285840() != 7)
                return;
        }
    }

    g = D_001A8CFC[0];
    if (g != 0) {
        char *b = g + 0x38000;
        g = (char *)((SubBf *)b)->cb1;
        ((Cb)g)();
        saved = ref_L00_0030CFE0_01.scale;
        ref_L00_0030CFE0_01.scale = 0.62f;
        func_0027AB40();
        func_0029BE88();
        ref_L00_0030CFE0_01.scale = saved;
        func_0027AB40();
    }
}


typedef struct Entry29D830 {
    short id;
    short a;
    int ka;
    short b;
    short pad0A;
    int kb;
    unsigned short flags;
    char pad12[10];
    int (*fn)(int);
    int arg;
    short state;
    short result;
} Entry29D830;
typedef struct { char pad[0x230]; int index; } Base29D830;
extern Base29D830 D_001C4FA0;
extern Entry29D830 *D_00258BA0[];
typedef struct { int unused; int count; Entry29D830 *list; } State29D830;
extern State29D830 D_001B1A50[] __attribute__((sda));
extern unsigned char D_001A7BE8[] MACRO_ADDR;
extern int func_0029D9D0(int, int);

int func_0029D830(void)
{
    Entry29D830 *e;

    D_001B1A50[0].list = D_00258BA0[D_001C4FA0.index];
    if (D_001B1A50[0].list == 0)
        return 0;
    e = D_001B1A50[0].list;
    for (; e->id != 0; e++) {
        if ((e->flags & 4) && D_001A7BE8[D_001C4FA0.index] == 0) {
            e->state = 0;
            continue;
        }
        if (func_0029D9D0(e->a, e->ka) == 0)
            e->state = 0;
        else if (func_0029D9D0(e->b, e->kb) == 0)
            e->state = 1;
        else
            e->state = 2;
    }
    for (e = D_001B1A50[0].list; e->id != 0; e++) {
        if (e->fn != 0)
            e->result = e->fn(e->arg);
    }
    D_001B1A50[0].count = 0;
    for (e = D_001B1A50[0].list; e->id != 0; e++) {
        if (e->state == 1 && (e->flags & 2) == 0)
            D_001B1A50[0].count++;
    }
    return D_001B1A50[0].count == 0;
}
