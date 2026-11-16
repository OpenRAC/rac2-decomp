#include "include_asm.h"
#include "names.h"

extern int load_start_disc_read(int value, char *target);
extern short snd_pump_music_and_disc_read(int value);
extern int g_tutorial_probe_context[];
extern int g_copy_setup_data[];

/* Same body as func_L00_003046D0: compares two words of a 332-byte-stride table and calls the
 * two helpers when the entry ahead is greater; returns 1. */
int cutscene_start_next_chunk_pal(int index)
{
    int j = index + 1;
    int *d = g_tutorial_probe_context;
    int *b = g_copy_setup_data;
    int *t = (int *)((char *)b + 16040);
    int n = d[12] * 332;
    int hold = d[28];
    int j4 = j * 4;
    int cur = *(int *)((char *)t + (n + index * 4));
    int next = *(int *)((char *)t + (j4 + n));

    n = next - cur;
    if (n > 0) {
        load_start_disc_read(hold, (char *)(cur + b[3977]));
        snd_pump_music_and_disc_read(0);
    }
    return 1;
}

