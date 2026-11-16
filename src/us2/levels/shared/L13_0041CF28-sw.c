#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern int TryClaimNotice(int, int, int);

/* The func_L02_004114A0 message pick for the five level-13 states. Each case calls on
   its own: with one shared body the five labels would collapse into three ranges and
   the switch would become a compare tree. */
void l13_claim_notice_by_kind_us2(u8 *moby) {
    int kind = *(int *)(*(void **)(moby + 0x68) + 0x10);

    switch (kind) {
    case 0:
        TryClaimNotice(0xB, 0x1BC6, 1);
        break;
    case 1:
        TryClaimNotice(0xB, 0x130B, 1);
        break;
    case 2:
        TryClaimNotice(0xB, 0x12E5, 1);
        break;
    case 3:
        TryClaimNotice(0xB, 0x12E5, 1);
        break;
    case 4:
        TryClaimNotice(0xB, 0x12E5, 1);
        break;
    default:
        TryClaimNotice(0xB, 0x12E5, 1);
        break;
    }
}
