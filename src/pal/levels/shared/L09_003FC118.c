#include "include_asm.h"
#include "names.h"

extern unsigned int g_path_l09_table[];
extern float vec_distance_xy(char *a, int b);

/* reports whether the index still names a reachable entry, or whether the frame moved close enough */
int path_is_entry_reachable_pal(char *object, int index) {
    char *frame = *(char **)(object + 0x68);
    int entry = path_check_entry_for_moby(object, index);

    if (entry == 0 && index != -1) {
        int off = (*(short *)(frame + 0x1CA) << 4) + 0x10;

        if (vec_distance_xy(object + 0x10, g_path_l09_table[index] + off) <
            *(float *)(frame + 0x134))
            entry = 1;
    }
    return entry;
}

