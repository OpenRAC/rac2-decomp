#include "common.h"

extern char *D_L20_001FBB20[];
extern int D_L20_001B2FB8;
extern char *D_L20_001B2F9C;
extern float func_00282E80(void *, void *);

/* Walks the id lists that arg0's state names for arg1's class (0xD0F: two lists,
   0x119E/0x12EF: one) and returns the last moby, not flagged at +0x34 bit 0, for which
   func_00282E80(moby + 0x10, arg0 + 0x10) < 1025.0f; 0 if none.  Built with -G8 and
   split addresses: the list limit and the moby bank are single absolute loads, the
   list table is reached through a %hi/%lo pair. */
char *func_L20_004448A8(char *arg0, char *arg1) {
    char *state = *(char **)(arg0 + 0x68);
    /* Retail's frame has 0x20 bytes of locals for this list; only two slots are used. */
    int loc[8];
    int n = 0;
    char *best;
    float range;
    int i;

    switch (*(s16 *)(arg1 + 0xAA)) {
    case 0xD0F:
        n = 2;
        loc[0] = *(int *)(state + 0x21C);
        loc[1] = *(int *)(state + 0x240);
        break;
    case 0x119E:
    case 0x12EF:
        n = 1;
        loc[0] = *(int *)(state + 0x23C);
        break;
    }
    range = 1025.0f;
    best = 0;
    for (i = 0; i < n; i++) {
        u16 *rec;

        for (rec = (u16 *)D_L20_001FBB20[loc[i]];
             (loc[i] & 0xFF) != 0xFF && D_L20_001B2FB8 >= loc[i] && rec != 0 &&
             (*(s16 *)(rec - 1) >= 0 || rec == (u16 *)D_L20_001FBB20[loc[i]]);
             rec++) {
            char *e = D_L20_001B2F9C + ((*rec & 0x7FFF) << 8);

            if (e == 0) {
                break;
            }
            if (!(*(u16 *)(e + 0x34) & 1)) {
                if (func_00282E80(e + 0x10, arg0 + 0x10) < range) {
                    best = e;
                }
            }
        }
    }
    return best;
}
