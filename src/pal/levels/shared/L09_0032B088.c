#include "include_asm.h"
#include "names.h"

extern unsigned int D_L09_001FE6C0[];
extern int path_follow_nodes(char *object, unsigned int entry);

int func_PAL_L09_0032B088(char *object, int index)
{
    unsigned int entry;

    if (index == -1)
        return 0;
    entry = D_L09_001FE6C0[index];
    if (entry == 0)
        return 0;
    return path_follow_nodes(object, entry);
}

