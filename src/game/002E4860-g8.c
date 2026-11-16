#include "common.h"

/* A -G8 unit (the profile from the file's name): a plain extern of at most eight bytes is then
   one assembler operand, and with its .extern only at the end of the file the assembler
   expands it to the retail's absolute lui + load through the destination register. -G0
   splits the address into a high-part register of its own. */

extern s32 g_music_volume;
extern s32 g_effects_volume;
extern u8 g_sound_state[];

/* Sets the starting volume of each of the six sound groups. */
void snd_set_default_group_volumes(void)
{
    struct Layout { char reserved[0x48]; int group0Volume,group1Volume,group2Volume,group3Volume,group4Volume,group5Volume; };
    struct Layout *sound_state = (struct Layout *)g_sound_state;
    int max_volume = g_effects_volume;
    sound_state->group0Volume = max_volume * 7 / 10;
    sound_state->group1Volume = g_music_volume;
    sound_state->group2Volume = max_volume;
    sound_state->group3Volume = max_volume * 6 / 10;
    sound_state->group4Volume = 614;
    sound_state->group5Volume = max_volume * 25 / 32;
}
