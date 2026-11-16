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
extern void anim_start_blended_pal(void *, int, int, int);

/* Switches the hero's two linked objects to the animations picked for anim_id, or back to idle
   (sequence 1) when none is picked. */
void hero_sync_linked_object_anims_pal(int anim_id, int blend_arg, float speed)
{
    char *first_object;
    char *second_object;
    int first_anim;
    int second_anim;
    int allow_idle;
    int blend_frames;
    float speed_copy = speed;

    if (g_hero_state.mode != 2)
        return;
    first_object = g_hero_state.p1310;
    second_object = g_hero_state.p1314;
    if (first_object == 0)
        return;
    if (second_object == 0)
        return;

    if (hero_pick_linked_anim_pair(anim_id, &first_anim, &second_anim) != 0 && anim_id != 0) {
        if ((unsigned char)first_object[0x43] != first_anim) {
            blend_frames = (int)speed_copy;
            anim_start_blended_pal(first_object, first_anim, blend_arg, blend_frames);
            anim_start_blended_pal(second_object, second_anim, blend_arg, blend_frames);
        }
        return;
    }

    allow_idle = 1;
    {

        if (g_hero_state.action == 0) {
            if (FindSlotTableKey((unsigned char)first_object[0x43], &anim_id) != 0 && anim_id == 0)
                allow_idle = 0;
        }
        if (allow_idle == 0)
            return;

        blend_frames = 6;
        if (g_hero_state.state == 8) {
            if (hero_slot_item_id(3) == 2)
                blend_frames = 0x10;
        }
    }
    if ((unsigned char)first_object[0x43] != 1)
        anim_start_blended_pal(first_object, 1, 0, blend_frames);
    if ((unsigned char)second_object[0x43] != 1)
        anim_start_blended_pal(second_object, 1, 0, blend_frames);
}

