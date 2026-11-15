#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;

extern void func_002B0C28(int, int, int);

/* The func_L02_004114A0 message pick for the five level-13 states. Each case calls on
   its own: with one shared body the five labels would collapse into three ranges and
   the switch would become a compare tree. */
/* Shows the help message that matches the warp ring's current state. */
void func_L13_0041BA60(u8 *moby) {
    int v = *(int *)(*(void **)(moby + 0x68) + 0x10);

    switch (v) {
    case 0:
        TryClaimNotice(0xB, 0x2800, 1);
        break;
    case 1:
        TryClaimNotice(0xB, 0x27B9, 1);
        break;
    case 2:
        TryClaimNotice(0xB, 0x2793, 1);
        break;
    case 3:
        TryClaimNotice(0xB, 0x2793, 1);
        break;
    case 4:
        TryClaimNotice(0xB, 0x2793, 1);
        break;
    default:
        TryClaimNotice(0xB, 0x2793, 1);
        break;
    }
}
