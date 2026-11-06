#include "common.h"

/* func_PAL_0029C8A0, the PAL copy of func_0029BF08: the same C, where the callback tables move
   up by 0x738 and the camera scale moves. */
extern int ref_L00_0030CFE0_00[] __attribute__((sda));
extern int D_001A8BB0[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern unsigned int func_00285840(void);
extern unsigned int func_002857B0(void);
extern void func_00290680(void);
extern void func_0029BEB8(void);
extern void func_0029BE88(void);
extern void func_0027AB40(void);

typedef unsigned int (*Cb)(void);

typedef struct { void *cb; int pad; } SlotBf;
typedef struct {
    char pad0[0x7A84];
    void *cb1;
    char pad1[0x7AA4 - 0x7A88];
    void *cb2;
    char pad2[0x7AAC - 0x7AA8];
    SlotBf slot[4];
    SlotBf slot2[2];
} SubBf;

/* The same table seen from its other end: the callback pointer is the second word. */
typedef struct { int pad; void *fn; } FnBf;

typedef struct { char pad[0xB0]; float scale; } CamBf;

/* The camera object: its projection scale is at +0xB0. */
extern CamBf ref_L00_0030CFE0_01;

void func_PAL_0029C8A0(void)
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

    if (D_001A8BB0[0] == 4) {
        if (func_002857B0() == 8)
            return;
    }

    func_00290680();
    result = 0;
    func_0029BEB8();

    fn = (Cb)((SubBf *)(D_001A8CFC[0] + 0x38000))->cb2;
    if (fn != 0)
        result = fn() != 0;

    for (i = 0; i < 4; i++) {
        sub = (SubBf *)(D_001A8CFC[0] + 0x38000);
        if (sub->slot[i].cb != 0)
            result |= ((Cb)((FnBf *)(D_001A8CFC[0] + 0x3FAA8))[i].fn)();
    }

    for (i = 0; i < 2; i++) {
        sub = (SubBf *)(D_001A8CFC[0] + 0x38000);
        if (sub->slot2[i].cb != 0)
            result |= ((Cb)((FnBf *)(D_001A8CFC[0] + 0x3FAC8))[i].fn)();
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
