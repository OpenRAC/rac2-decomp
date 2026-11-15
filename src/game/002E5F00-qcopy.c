#include "names.h"
typedef int TI128 __attribute__((mode(TI)));
extern char D_00188660[];

/* Gives a sound voice a position offset from its owner and marks the voice to use it. */
int func_002E5F00(int voiceIndex, char *offsetVector) {
    int off = voiceIndex * 0x70;
    char *voice = gSoundState + off;
    char *offsetBase = gSoundState + 0xA0;

    voice[0x75] |= 0x40;
    *(TI128 *)(offsetBase + off) = *(TI128 *)offsetVector;
    return 1;
}
