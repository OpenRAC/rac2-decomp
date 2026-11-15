#include "include_asm.h"
#include "names.h"

extern char *g_moby_l02_pool __attribute__((sda));
extern char *g_entity_group_lists[];
extern int D_L02_001B35B8 __attribute__((sda));
typedef int L02Word;
extern L02Word D_L02_001B35B8 __attribute__((sda));
extern int D_L02_001B35B8 __attribute__((sda));

/* Sets every entity of the object's group to state 1 with a 0xB4 timer. */
void func_PAL_L02_003D1828(unsigned char *arg0) {
    unsigned short *q;
    char *e;

    if (arg0[0x21] == 0xFF)
        return;
    q = (unsigned short *)g_entity_group_lists[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L02_001B35B8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)g_entity_group_lists[arg0[0x21]])) {
        char *o;

        e = g_moby_l02_pool + ((*q & 0x7FFF) << 8);
        if (e == 0)
            break;
        o = *(char **)(e + 0x68);
        *(unsigned short *)(o + 0x382) = 1;
        *(unsigned short *)(o + 0x386) = 0x96;
        q++;
    }
}

#include "common.h"
extern void moby_aim_at_target_offset(char *, char *);
extern int moby_l01_turn_toward_target(char *, char *);
extern int moby_turn_toward_target_and_step(char *, float *, float);
extern int D_L02_001A8FF0 __attribute__((sda));

/* Runs the kind's entry hook: the first when the level flag is set, the second when the third
   argument is clear, the third with the object's own angle otherwise. */
void func_PAL_L02_003D2898(char *a0, char *a1, int a2) {
    char *p = *(char **)(a0 + 0x68);

    if (D_L02_001A8FF0)
        moby_aim_at_target_offset(a0, a1);
    else if (a2 == 0)
        moby_l01_turn_toward_target(a0, a1);
    else
        moby_turn_toward_target_and_step(a0, (float *)a1, *(float *)(p + 0x31C));
}

