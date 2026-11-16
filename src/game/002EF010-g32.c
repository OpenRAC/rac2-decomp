#include "names.h"
extern unsigned char g_cutscene_gap_sizes[27] __attribute__((sda));
extern unsigned char g_cutscene_gap_ends[] __attribute__((sda));

/* Turns a cutscene number into a compact index by skipping the unused numbers in between. Numbers outside the normal range are shifted down. */
int cutscene_map_id_to_index(int cutscene_id)
{
    int i;
    int first_gap_end;
    unsigned char gap_size;
    int out_of_range = (unsigned int)(cutscene_id - 0x20) >= 0x91;

    if (!out_of_range) {
        first_gap_end = g_cutscene_gap_ends[0];
        if (cutscene_id >= first_gap_end) {
            cutscene_id -= first_gap_end;
        } else {
            i = 0x1B;
        next:
            i--;
            if (i >= 0) {
                gap_size = g_cutscene_gap_sizes[i];
                if (cutscene_id < gap_size)
                    goto next;
                cutscene_id -= gap_size;
            }
        }
    } else if (cutscene_id >= 0xB1) {
        cutscene_id -= 0x91;
    }
    return cutscene_id;
}
