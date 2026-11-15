#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_002B3BA8(char *, int, float, float, int, int);
extern char *func_L20_004448A8(char *, char *);

/* Chooses what the trooper aims at: the nearest valid target, or its owner if there is none. */
void func_L20_0039E158(char *mobyIn) {
    char *moby = mobyIn;
    char *vars = *(char **)(moby + 0x68);
    char *found;
    int targetPtr;

    if (*(int *)(vars + 0x27C) != 0) {
        *(int *)(vars + 0x280) = 0;
        SelectAimTarget_002B3BA8(mobyIn, *(int *)(vars + 0x230), 0.0f, 0.0f, 0, 0);
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
