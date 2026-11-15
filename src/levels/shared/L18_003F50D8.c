#include "include_asm.h"
#include "names.h"

extern int D_L18_001A79F0;
extern int D_L18_001A8F00;
extern void func_L18_003F5198(void *);
extern void func_L18_003F53D8(void *);
extern void func_L18_003F5650(void *);
extern void func_L18_003F6CA8(void *);
extern void func_L18_003F7198(void *);

/* Per-frame update for the Protopet: sets it up on the first frame, then runs its checks and behavior. */
void func_L18_003F50D8(char *moby)
{
    char *mobyAlias = moby;
    unsigned char stateId;

    if (D_L18_001A79F0 == 0x13) {
        if (D_L18_001A8F00 == 2) {
            *(int *)(mobyAlias + 0x98) = 0;
            *(unsigned short *)(mobyAlias + 0x34) = (*(unsigned short *)(mobyAlias + 0x34) | 0x41) & 0xEFFF;
        } else {
            char *classInfo = *(char **)(mobyAlias + 0x24);

            *(unsigned short *)(mobyAlias + 0x34) = (*(unsigned short *)(mobyAlias + 0x34) & 0xFFBE) | 0x1000;
            *(int *)(mobyAlias + 0x98) = *(int *)(classInfo + 0x10);
        }
    }
    stateId = *(unsigned char *)(mobyAlias + 0x20);
    if (stateId == 0) {
        InitProtopet(mobyAlias);
    } else if (stateId != 1 && stateId != 0x13) {
        CheckProtopetHitAndTarget(mobyAlias);
        RunProtopetStateMachine(mobyAlias);
        UpdateEnemyMoveByType(mobyAlias);
        UpdateProtopetStep(mobyAlias);
    }
}
