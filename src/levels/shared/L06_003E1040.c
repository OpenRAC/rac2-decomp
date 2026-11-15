#include "include_asm.h"
#include "names.h"

typedef int s32;

extern s32 D_0029CAE0[];
extern void func_002B0CE0(int, int, int);

/* Shows the pickup message for the item kind stored in the moby. */
void func_L06_003E1040(char *moby)
{
    s32 itemKind = **(s32 **)(moby + 0x68);

    if (itemKind == 0x18) {
        ForceClaimNotice(8, 0x1243, 1);
    } else {
        ForceClaimNotice(8, D_0029CAE0[itemKind - 1], 1);
    }
}
