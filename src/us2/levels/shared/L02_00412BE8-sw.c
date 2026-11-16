#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern int TryClaimNotice(int, int, int);

/* Shows the help message that matches the moby's state value (USA v2.00). */
void hud_show_message_for_state_us2(u8 *moby) {
    int message_state = *(int *)(*(void **)(moby + 0x68) + 0x10);
    int msg;

    switch (message_state) {
    case 1:
        msg = 0x130B;
        break;
    case 3:
        msg = 0x133B;
        break;
    case 4:
        msg = 0x1348;
        break;
    case 5:
        msg = 0x133D;
        break;
    case 6:
        msg = 0x1344;
        break;
    case 7:
        msg = 0x1345;
        break;
    case 8:
        msg = 0x1346;
        break;
    case 9:
        msg = 0x1347;
        break;
    case 0:
    case 2:
    default:
        msg = 0x12E5;
        break;
    }
    TryClaimNotice(0xB, msg, 1);
}
