#include "common.h"

extern int D_001A8CFC;
extern int ref_002D08C8_01 __attribute__((sda));
extern int D_001F2848[];
extern int D_001ABA0C[4] __attribute__((sda));
extern int ref_002D08C8_02 __attribute__((sda));
extern volatile unsigned char D_001A7A0A;

/* Unlocks the entries of the five-entry Extras page that the player has earned. */
int menu_unlock_extras_page_entries(void)
{
    if (D_001A8CFC != 0) {
        D_001F2848[0] = 1;
        if (ref_002D08C8_01 != 0)
            D_001ABA0C[1] = 1;
        if (ref_002D08C8_02 != 0)
            D_001ABA0C[2] = 1;
        if (D_001A7A0A != 0) {
            D_001ABA0C[0] = 1;
            D_001ABA0C[3] = 1;
        }
    }
    return 0;
}
