#include "names.h"
/* func_L08_0036F030 (116 bytes; levels 08, 19): clears the low two flag bits of the
   current object and, when there is one, of every object in the null-terminated list,
   and copies each one's class word into it. */
#include "common.h"

extern u8 *D_L08_00152C00;
extern u8 *D_L08_00221AE0[];

/* Turns off the two low flag bits for the current object and every object in its list, and restores their class word. */
void moby_restore_object_list_flags(void)
{
    s32 i;

    if (D_L08_00152C00 != 0) {
        *(u16 *)(D_L08_00152C00 + 0x34) &= 0xFFFC;
        *(s32 *)(D_L08_00152C00 + 0x98) = *(s32 *)(*(s32 *)(D_L08_00152C00 + 0x24) + 0x10);
        for (i = 0; D_L08_00221AE0[i] != 0; i++) {
            *(u16 *)(D_L08_00221AE0[i] + 0x34) &= 0xFFFC;
            *(s32 *)(D_L08_00221AE0[i] + 0x98) = *(s32 *)(*(s32 *)(D_L08_00221AE0[i] + 0x24) + 0x10);
        }
    }
}
