#include "names.h"
/* A unit of its own for -frac2-gcse-unsplit-edges (config/cflags.txt): PRE then hoists the high
   half of each re-read address into the block above the first test, as func_0029DDC0 does with
   its bytes. Read both values at every test: the retail rebuilds the low half at each one. */

typedef struct {
    unsigned char pad[0x1D];
    unsigned char value;
} Flag_29DD30;

typedef struct {
    unsigned char pad[0x5C];
    int value;
} Word_29DD30;

extern char g_game_flag_table[];
extern char g_request_flag_table[];
extern unsigned short ref_L00_0030EDB0_00;

#define FLAG (((Flag_29DD30 *)D_001395B8)->value)
#define WORD (((Word_29DD30 *)D_00139768)->value)

/* Checks two status values, sets a sound or text id to match, and returns 0, 1 or 2 for the combination. */
int menu_select_status_id_from_values(void)
{
    if (FLAG == 0 && WORD >= 0) {
        ref_L00_0030EDB0_00 = 0x1F;
        return 0;
    }
    if (FLAG != 0 && WORD >= 0) {
        ref_L00_0030EDB0_00 = 0x20;
        return 1;
    }
    if (FLAG == 0 && WORD < 0) {
        ref_L00_0030EDB0_00 = 0x1F;
        return 2;
    }
    return 0;
}
