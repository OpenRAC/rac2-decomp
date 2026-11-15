#include "common.h"
extern u8 *CreateMoby(s32);
extern void moby_init_child_from_parent(void *, void *);
extern void anim_start_blended(void *, s32, s32, s32);

/* Creates the attached record on demand, or updates both full aligned vectors
 * and propagates the owner's enable bit with the inverse state byte. */
/* Creates the attached child object on demand and keeps it on the owner's position. */
void snivelak_sync_child(u8 *owner)
{
    u8 *state = *(u8 **)(owner + 0x68);
    u8 *child = *(u8 **)(state + 0x274);
    if (child == 0) {
        u8 *created = CreateMoby(0xECB);
        *(u8 **)(state + 0x274) = created;
        if (created == 0)
            return;
        moby_init_child_from_parent(created, owner);
        *(u16 *)(*(u8 **)(state + 0x274) + 0x32) = *(u16 *)(owner + 0x32);
        anim_start_blended(*(u8 **)(state + 0x274), 1, 0, 0);
        return;
    }
    qcopy(child + 0x10, owner + 0x10);
    qcopy(child + 0xF0, owner + 0xF0);
    if (*(u16 *)(owner + 0x34) & 1) {
        *(u16 *)(child + 0x34) |= 1;
        (*(u8 **)(state + 0x274))[0x31] = 0;
    } else {
        *(u16 *)(child + 0x34) &= ~1;
        (*(u8 **)(state + 0x274))[0x31] = 1;
    }
}
