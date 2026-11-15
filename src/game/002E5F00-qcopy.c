#include "names.h"
typedef int TI128 __attribute__((mode(TI)));
extern char g_sound_state[];

/* Gives a sound voice a position offset from its owner and marks the voice to use it. */
int snd_set_voice_offset(int voiceIndex, char *offsetVector) {
    int off = voiceIndex * 0x70;
    char *voice = g_sound_state + off;
    char *offsetBase = g_sound_state + 0xA0;

    voice[0x75] |= 0x40;
    *(TI128 *)(offsetBase + off) = *(TI128 *)offsetVector;
    return 1;
}
