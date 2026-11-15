#include "common.h"

/* A -G8 unit (the profile from the file's name): a plain extern of at most eight bytes is then
   one assembler operand, and with its .extern only at the end of the file the assembler
   expands it to the retail's absolute lui + load through the destination register. -G0
   splits the address into a high-part register of its own. */

extern s32 D_001A7B9C;
extern s32 D_001A7BA0;
extern u8 D_00188660[];

/* Sets the starting volume of each of the six sound groups. */
void func_002E4860(void)
{
    struct Layout { char reserved[0x48]; int group0Volume,group1Volume,group2Volume,group3Volume,group4Volume,group5Volume; };
    struct Layout *soundState = (struct Layout *)gSoundState;
    int maxVolume = D_001A7BA0;
    soundState->group0Volume = maxVolume * 7 / 10;
    soundState->group1Volume = D_001A7B9C;
    soundState->group2Volume = maxVolume;
    soundState->group3Volume = maxVolume * 6 / 10;
    soundState->group4Volume = 614;
    soundState->group5Volume = maxVolume * 25 / 32;
}
