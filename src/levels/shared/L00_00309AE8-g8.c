#include "include_asm.h"
#include "names.h"

extern unsigned int g_save_menu_flags;
extern int D_001A7420_1;
extern unsigned int D_001A7424_1;
extern int D_001A7420_2;
extern unsigned int D_001A7424_2;
extern int D_001A7420_3;
extern unsigned int D_001A7424_3;
extern int D_001A7420_4;

/* Write state value 3 when bit 0x40 is clear in the absolute flag word; preserve the existing value otherwise. */
void level_l00_set_state_three_if_clear(void)
{
    if ((g_save_menu_flags & 0x40u) == 0)
        D_001A7420_1 = 3;
}

/* Write state value 3 when bit 0x40 is clear in the absolute flag word; preserve the existing value otherwise. */
void level_l00_set_state_three_if_clear_2(void)
{
    if ((D_001A7424_1 & 0x40u) == 0)
        D_001A7420_2 = 3;
}

/* Write state value 3 when bit 0x40 is clear in the absolute flag word; preserve the existing value otherwise. */
void level_l00_set_state_three_if_clear_3(void)
{
    if ((D_001A7424_2 & 0x40u) == 0)
        D_001A7420_3 = 3;
}

/* Write state value 3 when bit 0x40 is clear in the absolute flag word; preserve the existing value otherwise. */
void level_l00_set_state_three_if_clear_4(void)
{
    if ((D_001A7424_3 & 0x40u) == 0)
        D_001A7420_4 = 3;
}
