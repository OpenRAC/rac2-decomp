#include "common.h"

/* This unit is built with -G8: func_L20_00409480 needs the -G8 profile. Its register
   allocation differs from the -G0 one this cc1 makes (in a -G0 unit the address of
   D_L20_001FBB20[arg0] lands in $a1 instead of $v1, and the loads of D_L20_001B2FB8
   come out split instead of absolute). */

extern char *g_group_l20_id_lists[];

extern int g_group_count;

extern char *g_group_l20_member_table;

extern void shared_counter_release(char *);

extern void moby_destroy_linked(char *);

extern void moby_mark_spawned(void *);

/* Destroys every Megacorp Trooper Legs object in the given group. */
void trooper_legs_destroy_group(s32 group) {
    char *id_list = g_group_l20_id_lists[group];
    s32 group_byte = group & 0xFF;
    char *member;

    if (group_byte == 0xFF) {
        goto end;
    }
    if (g_group_count < group) {
        goto end;
    }
    if (id_list == 0) {
        goto end;
    }
    for (;;) {
        member = g_group_l20_member_table + ((*(u16 *)id_list & 0x7FFF) << 8);

        if (member == 0) {
            goto end;
        }
        if (*(s16 *)(member + 0xAA) == MOBY_CLASS_MEGACORP_TROOPER_LEGS) {
            if (*(u8 *)(member + 0x20) != 0xFE) {
                if (*(u8 *)(member + 0x20) != 0xFD) {
                    *(int *)(*(char **)(member + 0x68) + 0x20) = 0;
                    shared_counter_release(member);
                    moby_destroy_linked(member);
                    moby_mark_spawned(member);
                }
            }
        }
        id_list += 2;
        if ((group & 0xFF) == 0xFF) {
            goto end;
        }
        if (g_group_count < group) {
            goto end;
        }
        if (id_list == 0) {
            return;
        }
        if (*(s16 *)(id_list - 2) >= 0) {
            continue;
        }
        if (id_list == g_group_l20_id_lists[group]) {
            continue;
        }
        break;
    }
end:
    return;
}
