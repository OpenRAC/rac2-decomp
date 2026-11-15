#include "common.h"

typedef struct {
 unsigned char pad0[0x1310]; char *p1310, *p1314;
 unsigned char pad1[0x1334-0x1318]; int mode;
 unsigned char pad2[0x229C-0x1338]; int action, state;
} HeroState;
extern HeroState D_00189E20;

extern int func_L00_002D1DA0(int, int *, int *);

extern int func_L00_002D1B70(int, int *);

extern int func_L00_002ADEA0(int);

extern void func_002A7470(void *, int, int, int);

/* Sets the animations of the two linked hero objects to match the hero's new animation. */
void func_L00_002D1C40(int seq, int frame, float f12)
{
    char *upperObj;
    char *lowerObj;
    int animA;
    int animB;
    int flag;
    int rate;
    float speed = f12;

    if (gHeroState.mode != 2)
        return;
    upperObj = gHeroState.p1310;
    lowerObj = gHeroState.p1314;
    if (upperObj == 0)
        return;
    if (lowerObj == 0)
        return;

    if (PickLinkedAnimationPair(seq, &animA, &animB) != 0 && seq != 0) {
        if ((unsigned char)upperObj[0x43] != animA) {
            rate = (int)speed;
            StartAnimationBlended(upperObj, animA, frame, rate);
            StartAnimationBlended(lowerObj, animB, frame, rate);
        }
        return;
    }

    flag = 1;
    {

        if (gHeroState.action == 0) {
            if (FindSlotTableKey((unsigned char)upperObj[0x43], &seq) != 0 && seq == 0)
                flag = 0;
        }
        if (flag == 0)
            return;

        rate = 7;
        if (gHeroState.state == 8) {
            if (hero_slot_item_id(3) == 2)
                rate = 0x13;
        }
    }
    if ((unsigned char)upperObj[0x43] != 1)
        StartAnimationBlended(upperObj, 1, 0, rate);
    if ((unsigned char)lowerObj[0x43] != 1)
        StartAnimationBlended(lowerObj, 1, 0, rate);
}
