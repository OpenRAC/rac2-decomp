#include "names.h"
/* A unit of its own for -frac2-gcse-unsplit-edges (config/cflags.txt): PRE then hoists the re-read
   bytes into the block above the first test, and the re-reads after its labels keep their masks.
   Both bytes stay one assembler operand, the retail's absolute lui + load through the destination
   register. Read the bytes at every test: caching them in locals lets combine drop the masks. */

extern unsigned char g_menu_status_flag_2 __attribute__((sda));
extern unsigned char g_status_flag_b __attribute__((sda));
extern unsigned short ref_L00_0030EE40_00;

/* Checks two status bytes, sets an id to match, and returns 0, 1 or 2 for the combination. */
int menu_select_status_id_from_bytes(void)
{
    if (g_menu_status_flag_2 == 0 && g_status_flag_b == 0) {
        ref_L00_0030EE40_00 = 0x28;
        return 0;
    }
    if (g_menu_status_flag_2 != 0 && g_status_flag_b == 0) {
        ref_L00_0030EE40_00 = 0x29;
        return 1;
    }
    if (g_menu_status_flag_2 == 0 && g_status_flag_b != 0) {
        ref_L00_0030EE40_00 = 0x29;
        return 2;
    }
    return 0;
}
