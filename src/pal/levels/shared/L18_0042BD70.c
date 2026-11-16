#include "include_asm.h"

#include "common.h"
typedef struct { u8 reserved00[0x34]; u16 flags; } ObjectFlagsPrefix;
typedef struct { u8 reserved00[0x68]; u8 *state; } LinkEntityPrefix;
extern u8 *g_moby_l18_table MACRO_ADDR;
extern void moby_start_or_forward_anim_pal(u8 *, s32, s32, float);
extern s32 moby_set_anim(u8 *, s32, s32);
extern s32 vec_fast_helper_a(void *);
extern s32 moby_fuse_linked_objects(u8 *, void *, void *, s32, s32);
extern void moby_set_state(u8 *, s32, s32);

/* Wakes a linked enemy: moves it to its partner object and starts its first state, attached or free (PAL). */
void moby_wake_linked_enemy_pal(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *source;
    u8 *target;
    if (*(s32 *)(state + 0x3B4) == -1) return;
    source = g_moby_l18_table + (*(s32 *)(state + 0x3B4) << 8);
    qcopy((object + 0x10), (source + 0x10));
    qcopy((object + 0xF0), (source += 0xF0));
    state[0x2E] = 1;
    state[0x6A] = 0;
    *(s16 *)(state + 0x88) = 0;
    *(float *)(state + 0x20) = (float)*(s16 *)(state + 0x24);
    *(s32 *)(state + 0x94) = 0;
    object[0xA8] = 255;
    moby_start_or_forward_anim_pal(object, 7, 0, 1.0f);
    *(float *)(object + 0x48) = 0.1f;
    *(s32 *)(state + 0x13C) = *(s32 *)(state + 0x380);
    moby_set_anim(object, *(s32 *)(state + 0x36C), -1);
    *(s32 *)(object + 0x98) = 0;
    object[0x7F] = 0;
    ((ObjectFlagsPrefix *)object)->flags &= ~0x1000;
    if (!(state[0x3B1] & 0x80)) vec_fast_helper_a(state + 0x3B1);
    *(float *)(state + 0x100) = 0.7f;
    if (*(s32 *)(state + 0x3B4) != -1 && (target = (u8 *)((*(s32 *)(state + 0x3B4) << 8) + (u32)g_moby_l18_table), *(s16 *)(target + 0xAA)) == 0x114D && target[0x20] != 0xFE && target[0x20] != 0xFD) {
        u8 *entities;
        s32 link_index;
        object[0x31] = 0;
        ((ObjectFlagsPrefix *)object)->flags |= 1;
        entities = g_moby_l18_table;
        link_index = *(s32 *)(state + 0x3B4);
        *(u8 **)((LinkEntityPrefix *)((link_index << 8) + (u32)entities))->state = object;
        *(float *)(object + 0x48) = 1.0f;
        moby_set_state(object, 0, 11);
    } else {
        moby_fuse_linked_objects(object, object + 0x10, object + 0xF0, 0, 0);
        moby_set_state(object, 0, 14);
    }
}
