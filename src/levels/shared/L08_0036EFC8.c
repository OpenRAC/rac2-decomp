#include "names.h"
/* func_L08_0036EFC8 (100 bytes; levels 08, 19): sets the low two flag bits of the current
   object and, when there is one, of every object in the null-terminated list, and clears
   each one's class word. The counterpart of func_L08_0036F030. */
#include "common.h"

extern u8 *g_object_list_head;
extern u8 *g_disabled_object_list[];

/* Turns on the two low flag bits for the current object and every object in its list, and clears their class word. */
void moby_disable_object_list_flags(void)
{
    s32 i;

    if (g_object_list_head != 0) {
        *(u16 *)(g_object_list_head + 0x34) |= 3;
        *(s32 *)(g_object_list_head + 0x98) = 0;
        for (i = 0; g_disabled_object_list[i] != 0; i++) {
            *(u16 *)(g_disabled_object_list[i] + 0x34) |= 3;
            *(s32 *)(g_disabled_object_list[i] + 0x98) = 0;
        }
    }
}
