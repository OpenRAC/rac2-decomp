#include "include_asm.h"
#include "names.h"



extern int load_start_disc_read(int value, char *target);
extern short snd_pump_music_and_disc_read(int value);
extern int D_L00_001BCAC0[];
extern int g_copy_setup_data[];

/* Reads a record count from a per-level data root, indexes a fixed 332-byte-stride table with it, and when the int after position index is greater than the one at position index calls two helpers with the entry value added to a per-level base; returns 1. */
int func_PAL_L00_003062B0(int index)
{
    int j = index + 1;
    int *d = D_L00_001BCAC0;
    int *b = g_copy_setup_data;
    int *t = (int *)((char *)b + 25416);
    int n = d[12] * 332;
    int hold = d[28];
    int j4 = j * 4;
    int cur = *(int *)((char *)t + (n + index * 4));
    int next = *(int *)((char *)t + (j4 + n));

    n = next - cur;
    if (n > 0) {
        load_start_disc_read(hold, (char *)(cur + b[6341]));
        snd_pump_music_and_disc_read(0);
    }
    return 1;
}

typedef int s32;
struct Table2 { char pad[52]; s32 slots[4]; };
extern struct Table2 Fee2b87d1_D_00152CD0;

void func_PAL_L00_003066C8(void)
{
    extern void mem_clear(unsigned int *, unsigned int, int);
    struct Table2 *table = &Fee2b87d1_D_00152CD0;
    int i;
    mem_clear((unsigned int *)table, 0, 0x35840);
    *(short *)((char *)table + 0x14) = -1;
    for (i = 2; i >= 0; --i)
        table->slots[i] = -1;
}

