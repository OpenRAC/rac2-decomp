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

extern void anim_start_blended(void *, int, int, int);

/* Sets the animations of the two linked hero objects to match the hero's new animation. */
void hero_sync_linked_object_anims(int seq, int frame, float f12)
{
    char *upperObj;
    char *lowerObj;
    int animA;
    int animB;
    int flag;
    int rate;
    float speed = f12;

    if (g_hero_state.mode != 2)
        return;
    upperObj = g_hero_state.p1310;
    lowerObj = g_hero_state.p1314;
    if (upperObj == 0)
        return;
    if (lowerObj == 0)
        return;

    if (hero_pick_linked_anim_pair(seq, &animA, &animB) != 0 && seq != 0) {
        if ((unsigned char)upperObj[0x43] != animA) {
            rate = (int)speed;
            anim_start_blended(upperObj, animA, frame, rate);
            anim_start_blended(lowerObj, animB, frame, rate);
        }
        return;
    }

    flag = 1;
    {

        if (g_hero_state.action == 0) {
            if (FindSlotTableKey((unsigned char)upperObj[0x43], &seq) != 0 && seq == 0)
                flag = 0;
        }
        if (flag == 0)
            return;

        rate = 7;
        if (g_hero_state.state == 8) {
            if (hero_slot_item_id(3) == 2)
                rate = 0x13;
        }
    }
    if ((unsigned char)upperObj[0x43] != 1)
        anim_start_blended(upperObj, 1, 0, rate);
    if ((unsigned char)lowerObj[0x43] != 1)
        anim_start_blended(lowerObj, 1, 0, rate);
}
