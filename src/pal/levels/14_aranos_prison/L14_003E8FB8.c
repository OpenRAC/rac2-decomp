#include "include_asm.h"
#include "names.h"

/* func_PAL_L14_003E8FB8, the PAL copy of func_L14_003E4BA0: the same C, where the reloaded key
   counter is the key word, read whole and scaled to 50 Hz. The walks also pair up differently:
   retail keeps the first in $a2 and the other two in $a1, so the first has its own pointer and
   the other two share one. */

extern unsigned short *g_group_entity_lists[];
extern unsigned char *g_moby_l14_pool __attribute__((sda));
extern int g_group_link_limit __attribute__((sda));
extern int flag_set_first_pending(char *self);
extern int FastDecTimer(char *p);
extern void moby_update_keyframe_span_blend_pal(char *self);
extern void moby_store_pos_lookup_links(char *self);
extern void ring_state_advance_pal(char *self);
extern void moby_clear_linked_flag(char *self);
extern void moby_send_colors_to_linked(char *self);
extern void moby_set_child_fade_colors_pal(char *self);

/* The key state of an object that steers a group (+0x14 the current key, +0x16 the key index,
   +0x34 the key word). The last walk stores through this struct, as in the template: loop.c can
   then hoist the two level globals and the constants out of that loop. */
typedef struct {
    unsigned char pad[0x14];
    unsigned short cur;
    unsigned short index;
} L14Key;

/* Updates a moby that steers a group (PAL): copies its key colours to the group's class-0xB19 members, runs the state handlers, counts down the key timer and passes the current key on to the members. */
void keyed_group_update_pal(unsigned char *moby)
{
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    unsigned short *walk;
    unsigned short *key_walk;
    unsigned char *member;

    switch (moby[0x20]) {
    case 0:
        for (walk = g_group_entity_lists[moby[0x21]];
             moby[0x21] != 0xFF && moby[0x21] <= g_group_link_limit && walk != 0 &&
             ((walk != 0 && (short)walk[-1] >= 0) || walk == g_group_entity_lists[moby[0x21]]);
             walk++) {
            member = g_moby_l14_pool + ((*walk & 0x7FFF) << 8);
            if (member == 0)
                break;
            if (*(short *)(member + 0xAA) == 0xB19) {
                unsigned char *member_vars = *(unsigned char **)(member + 0x68);

                *(unsigned short *)(member_vars + 0x40) = *(unsigned short *)(vars + 0x40);
                *(unsigned short *)(member_vars + 0x42) = *(unsigned short *)(vars + 0x42);
                *(unsigned short *)(member_vars + 0x44) = *(unsigned short *)(vars + 0x44);
                *(unsigned short *)(member_vars + 0x46) = *(unsigned short *)(vars + 0x46);
                *(unsigned short *)(member_vars + 0x48) = *(unsigned short *)(vars + 0x48);
                *(unsigned short *)(member_vars + 0x4A) = *(unsigned short *)(vars + 0x4A);
            }
        }
        moby_store_pos_lookup_links((char *)moby);
        break;
    case 2:
        if (flag_set_first_pending((char *)moby) != 0) {
            moby_set_child_fade_colors_pal((char *)moby);
            moby_clear_linked_flag((char *)moby);
        }
        break;
    case 1:
        if (flag_set_first_pending((char *)moby) != 0)
            moby_send_colors_to_linked((char *)moby);
        moby_update_keyframe_span_blend_pal((char *)moby);
        break;
    }
    if (*(int *)(vars + 0x34) != 0) {
        if (FastDecTimer((char *)(vars + 0x14)) != 0) {
            *(unsigned short *)(vars + 0x14) = (*(int *)(vars + 0x34) * 5 + 2) / 6;
            for (key_walk = g_group_entity_lists[moby[0x21]];
                 moby[0x21] != 0xFF && moby[0x21] <= g_group_link_limit && key_walk != 0 &&
                 ((key_walk != 0 && (short)key_walk[-1] >= 0) || key_walk == g_group_entity_lists[moby[0x21]]);
                 key_walk++) {
                member = g_moby_l14_pool + ((*key_walk & 0x7FFF) << 8);
                if (member == 0)
                    break;
                if (*(short *)(member + 0xAA) == 0xB19)
                    *(unsigned short *)(*(unsigned char **)(member + 0x68) + 0x16) = 0;
            }
        }
        for (key_walk = g_group_entity_lists[moby[0x21]];
             moby[0x21] != 0xFF && moby[0x21] <= g_group_link_limit && key_walk != 0 &&
             ((key_walk != 0 && (short)key_walk[-1] >= 0) || key_walk == g_group_entity_lists[moby[0x21]]);
             key_walk++) {
            member = g_moby_l14_pool + ((*key_walk & 0x7FFF) << 8);
            if (member == 0)
                break;
            if (*(short *)(member + 0xAA) == 0xB19)
                ((L14Key *)*(unsigned char **)(member + 0x68))->cur = ((L14Key *)vars)->cur;
        }
    }
    ring_state_advance_pal((char *)moby);
}
