#include "names.h"
/* func_L08_0036F030 (116 bytes; levels 08, 19): clears the low two flag bits of the
   current object and, when there is one, of every object in the null-terminated list,
   and copies each one's class word into it. */
#include "common.h"

extern u8 *g_object_list_head;
extern u8 *g_disabled_object_list[];

/* Turns off the two low flag bits for the current object and every object in its list, and restores their class word. */
void moby_restore_object_list_flags(void)
{
    s32 i;

    if (g_object_list_head != 0) {
        *(u16 *)(g_object_list_head + 0x34) &= 0xFFFC;
        *(s32 *)(g_object_list_head + 0x98) = *(s32 *)(*(s32 *)(g_object_list_head + 0x24) + 0x10);
        for (i = 0; g_disabled_object_list[i] != 0; i++) {
            *(u16 *)(g_disabled_object_list[i] + 0x34) &= 0xFFFC;
            *(s32 *)(g_disabled_object_list[i] + 0x98) = *(s32 *)(*(s32 *)(g_disabled_object_list[i] + 0x24) + 0x10);
        }
    }
}
