#include "include_asm.h"
#include "names.h"

extern int F46b43b72_FUN_002B7B18(int value, char *target);
extern short F46b43b72_FUN_002B7CE0(int value);
extern int F46b43b72_D_001B8840[];
extern int F46b43b72_D_0014B540[];

/* Reads the part of the current chunk between this entry and the next one from the disc, when it is not empty. Always returns 1. */
int load_chunk_part_from_disc_pal(int index)
{
    int next_index = index + 1;
    int *disc_state = F46b43b72_D_001B8840;
    int *disc_data = F46b43b72_D_0014B540;
    int *toc = (int *)((char *)disc_data + 25416);
    int len = disc_state[12] * 332;
    int hold = disc_state[28];
    int next_offset = next_index * 4;
    int cur = *(int *)((char *)toc + (len + index * 4));
    int next = *(int *)((char *)toc + (next_offset + len));

    len = next - cur;
    if (len > 0) {
        F46b43b72_FUN_002B7B18(hold, (char *)(cur + disc_data[6341]));
        F46b43b72_FUN_002B7CE0(0);
    }
    return 1;
}

