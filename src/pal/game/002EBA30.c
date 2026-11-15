#include "include_asm.h"
#include "names.h"


typedef struct { char pad[0x30]; int selected; char gap[0x3C]; int destination; } State2EB158;
extern State2EB158 g_scene_playback_state;
extern char g_copy_setup_data[];
extern int load_start_disc_read(int, int, int);
extern short snd_pump_music_and_disc_read(int);

int func_PAL_002EC070(int index)
{
    char *table = g_copy_setup_data;
    int row = g_scene_playback_state.selected * 0x14C;
    int destination = g_scene_playback_state.destination;
    int base = (int)(table + 0x3EA8);
    int first = *(int *)((index << 2) + row + base);
    int count = *(int *)(((index + 1) << 2) + row + base) - first;
    if (count > 0) {
        load_start_disc_read(destination, first + *(int *)(table + 0x3E24), count);
        snd_pump_music_and_disc_read(0);
    }
    return 1;
}

