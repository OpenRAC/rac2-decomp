#include "include_asm.h"
#include "names.h"

extern int F46b43b72_FUN_002B7B18(int value, char *target);
extern short F46b43b72_FUN_002B7CE0(int value);
extern int F46b43b72_D_001B8840[];
extern int F46b43b72_D_0014B540[];

int load_chunk_part_from_disc_pal(int index)
{
    int j = index + 1;
    int *d = F46b43b72_D_001B8840;
    int *b = F46b43b72_D_0014B540;
    int *t = (int *)((char *)b + 25416);
    int n = d[12] * 332;
    int hold = d[28];
    int j4 = j * 4;
    int cur = *(int *)((char *)t + (n + index * 4));
    int next = *(int *)((char *)t + (j4 + n));

    n = next - cur;
    if (n > 0) {
        F46b43b72_FUN_002B7B18(hold, (char *)(cur + b[6341]));
        F46b43b72_FUN_002B7CE0(0);
    }
    return 1;
}

