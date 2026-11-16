#include "include_asm.h"
#include "names.h"
extern int g_frame_l00_counter[] __attribute__((sda));
extern char *g_moby_l00_list_head[] __attribute__((sda));
extern float g_same_kind_min_distance __attribute__((sda));
extern float func_002EE2B0(char *a, char *b);
extern void func_00381F80(char *a, char *b);

/* walks the object list once the shared flag is set, stopping at either special state and
   otherwise acting on the entries whose handle reports type 0x13 */
void moby_find_nearby_same_kind_pal(char *arg)
{
    char *o;

    if ((g_frame_l00_counter[0] & 1) == 0)
        return;

    for (o = g_moby_l00_list_head[0]; o != 0; o = *(char **)(o + 40)) {
        unsigned char state = *(unsigned char *)(o + 32);

        if (state == 0xFE)
            return;
        if (state == 0xFD)
            return;
        if (o == 0 || *(int *)(o + 36) == 0 || *(short *)(*(int *)(o + 36) + 70) != 0x13)
            continue;
        if (func_002EE2B0(o + 16, arg + 16) < g_same_kind_min_distance)
            func_00381F80(o, arg);
    }
}
