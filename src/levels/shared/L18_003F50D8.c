#include "include_asm.h"
#include "names.h"

extern int D_L18_001A79F0;
extern int D_L18_001A8F00;
extern void protopet_init(void *);
extern void protopet_check_hit_target(void *);
extern void protopet_run_state_machine(void *);
extern void enemy_update_move_by_type(void *);
extern void protopet_update_step(void *);

/* Per-frame update for the Protopet: sets it up on the first frame, then runs its checks and behavior. */
void protopet_update(char *moby)
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
        protopet_init(mobyAlias);
    } else if (stateId != 1 && stateId != 0x13) {
        protopet_check_hit_target(mobyAlias);
        protopet_run_state_machine(mobyAlias);
        enemy_update_move_by_type(mobyAlias);
        protopet_update_step(mobyAlias);
    }
}
