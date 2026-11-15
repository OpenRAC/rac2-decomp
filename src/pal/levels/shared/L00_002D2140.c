#include "include_asm.h"

#include "common.h"
typedef struct {
 unsigned char pad0[0x1310]; char *p1310, *p1314;
 unsigned char pad1[0x1334-0x1318]; int mode;
 unsigned char pad2[0x229C-0x1338]; int action, state;
} HeroState;
extern HeroState g_hero_state;
extern int hero_pick_linked_anim_pair(int, int *, int *);
extern int FindSlotTableKey(int, int *);
extern int hero_slot_item_id(int);
extern void func_PAL_002A7E68(void *, int, int, int);

void func_PAL_L00_002D2140(int a0, int a1, float f12)
{
    char *p1;
    char *p2;
    int out0;
    int out1;
    int flag;
    int s0;
    float f20 = f12;

    if (g_hero_state.mode != 2)
        return;
    p1 = g_hero_state.p1310;
    p2 = g_hero_state.p1314;
    if (p1 == 0)
        return;
    if (p2 == 0)
        return;

    if (hero_pick_linked_anim_pair(a0, &out0, &out1) != 0 && a0 != 0) {
        if ((unsigned char)p1[0x43] != out0) {
            s0 = (int)f20;
            func_PAL_002A7E68(p1, out0, a1, s0);
            func_PAL_002A7E68(p2, out1, a1, s0);
        }
        return;
    }

    flag = 1;
    {

        if (g_hero_state.action == 0) {
            if (FindSlotTableKey((unsigned char)p1[0x43], &a0) != 0 && a0 == 0)
                flag = 0;
        }
        if (flag == 0)
            return;

        s0 = 6;
        if (g_hero_state.state == 8) {
            if (hero_slot_item_id(3) == 2)
                s0 = 0x10;
        }
    }
    if ((unsigned char)p1[0x43] != 1)
        func_PAL_002A7E68(p1, 1, 0, s0);
    if ((unsigned char)p2[0x43] != 1)
        func_PAL_002A7E68(p2, 1, 0, s0);
}

