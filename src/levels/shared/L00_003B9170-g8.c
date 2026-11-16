#include "include_asm.h"
#include "names.h"

extern char *g_moby_array_base;
extern char *g_moby_array_last;
extern int g_special_moby_count __attribute__((sda));
extern char *g_saved_special_mobys[];
extern int g_saved_moby_values[];
extern char g_str_special_moby_overflow[];
extern int g_current_map_index;
extern void STUB_printf(const char *,...);

/* Collects up to 64 mobys of a fixed set of classes into a table, saving each one's value at +0x98.
   Reports an error if the table fills up. */
void moby_collect_special_into_table(void)
{
    char *moby;
    g_special_moby_count=0;
    for (moby=g_moby_array_base; moby<g_moby_array_last; moby+=0x100) {
        short classId=*(short *)(moby+0xaa);
        if (classId==0x1146 || classId==0x1185 || classId==0x119b || classId==0x11a4 || classId==0x1204 || classId==0x11fc || classId==0x120c || classId==0x1135 || classId==0x1148 || classId==0x11fc) {
            g_saved_special_mobys[g_special_moby_count]=moby;
            g_saved_moby_values[g_special_moby_count]=*(int *)(moby+0x98);
            g_special_moby_count++;
            if (g_special_moby_count>=64) {
                STUB_printf(g_str_special_moby_overflow,64,g_current_map_index);
                return;
            }
        }
    }
}
