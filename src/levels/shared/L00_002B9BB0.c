#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef struct {
    u8 pad0[0x242C];
    int slot[9];
    int want[9];
} Owner_2B9BB0;
extern Owner_2B9BB0 g_hero_state;
extern char g_sound_state[];
extern int PlayMobySound(int index, int mode, void *object);

/* Keeps a sound slot playing the wanted object, starting a new sound if it changed or stopped. */
void snd_update_slot_object(int index, int wanted, int handle)
{
    char *record = g_sound_state + g_hero_state.slot[index] * 0x70;

    if (*(int *)(record + 0x88) != wanted || *(unsigned char *)(record + 0x74) == 0)
        g_hero_state.slot[index] = PlayMobySound(handle, 4, (void *)wanted);
    g_hero_state.want[index] = wanted;
}
