#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern int weapon_select_aim_target(char *, int, float, float, int, int);
extern char *FindLastGroupMemberInRange(char *, char *);

/* Chooses what the trooper aims at: the nearest valid target, or its owner if there is none. */
void trooper_choose_target(char *mobyIn) {
    char *moby = mobyIn;
    char *vars = *(char **)(moby + 0x68);
    char *found;
    int targetPtr;

    if (*(int *)(vars + 0x27C) != 0) {
        *(int *)(vars + 0x280) = 0;
        weapon_select_aim_target(mobyIn, *(int *)(vars + 0x230), 0.0f, 0.0f, 0, 0);
    } else {
        found = FindLastGroupMemberInRange(*(char **)(moby + 0xB8), moby);
        *(int *)(vars + 0x280) = (int)found;
        if (found == 0) {
            *(int *)(vars + 0x280) = *(int *)(moby + 0xB8);
        }
        targetPtr = *(int *)(vars + 0x280);
        *(int *)(vars + 0x200) = targetPtr;
        *(TI128 *)(vars + 0x1F0) = *(TI128 *)((char *)targetPtr + 0x10);
    }
}
