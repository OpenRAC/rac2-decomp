#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef struct {
    u8 pad0[0x242C];
    int slot[9];
    int want[9];
} Owner_2B9BB0;
extern Owner_2B9BB0 D_00189E20;
extern char D_00188660[];
extern int func_002E5CF8(int index, int mode, void *object);

/* Keeps a sound slot playing the wanted object, starting a new sound if it changed or stopped. */
void func_L00_002B9BB0(int index, int wanted, int handle)
{
    char *record = gSoundState + gHeroState.slot[index] * 0x70;

    if (*(int *)(record + 0x88) != wanted || *(unsigned char *)(record + 0x74) == 0)
        gHeroState.slot[index] = PlayMobySound(handle, 4, (void *)wanted);
    gHeroState.want[index] = wanted;
}
