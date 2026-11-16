#include "common.h"

/* func_L20_0039D680 lives in a -G8 unit of its own: it reads D_L20_001B2FB8 through $gp,
   while func_L20_0039E890 in L20_0039C448-g8.c reads the same word absolutely. */

extern float vec_distance_xy(void *, void *);
extern char g_hero_position[];
extern char *g_group_l20_id_lists[];
extern char *g_group_l20_member_table;
/* 0x1AEFF0 + 0x3FC8: read through $gp. */
extern int g_group_count __attribute__((sda));

/* Counts the other objects of this object's group (the 0x7FFF-masked id list at
   D_L20_001FBB20[object[0x21]]) that are closer to D_00189EA0 than the object itself,
   skipping state 6; sets state+0x27C when fewer than two are.  The loop condition is
   the group-iteration form of func_00325DA0: its size keeps jump from duplicating the
   exit test, so the test stays at the bottom, entered by a branch, as in retail. */
/* Checks how many trooper friends are closer to the player than this one and records whether it is among the closest two. */
void trooper_count_closer_mates(unsigned char *object) {
    char *state = *(char **)(object + 0x68);
    float limit = vec_distance_xy(object + 0x10, g_hero_position);
    unsigned short *p;
    unsigned char *e;
    int count = 0;

    for (p = (unsigned short *)g_group_l20_id_lists[object[0x21]];
         object[0x21] != 0xFF && object[0x21] <= g_group_count && p != 0 &&
         ((p != 0 && (short)p[-1] >= 0) || p == (unsigned short *)g_group_l20_id_lists[object[0x21]]);
         p++) {
        e = (unsigned char *)g_group_l20_member_table + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e != object && e[0x20] != 6 && vec_distance_xy(e + 0x10, g_hero_position) < limit)
            count++;
    }
    *(int *)(state + 0x27C) = count < 2;
}
