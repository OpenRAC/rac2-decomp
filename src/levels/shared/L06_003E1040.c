#include "include_asm.h"
#include "names.h"

typedef int s32;

extern s32 g_pickup_notice_ids[];
extern int ForceClaimNotice(int, int, int);

/* Shows the pickup message for the item kind stored in the moby. */
void hud_show_pickup_notice(char *moby)
{
    s32 itemKind = **(s32 **)(moby + 0x68);

    if (itemKind == 0x18) {
        ForceClaimNotice(8, 0x1243, 1);
    } else {
        ForceClaimNotice(8, g_pickup_notice_ids[itemKind - 1], 1);
    }
}
