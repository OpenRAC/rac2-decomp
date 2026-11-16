#include "include_asm.h"
#include "names.h"
extern int g_level_l18_mode_word;
extern int g_game_l18_mode_state;
extern void protopet_init(void *);
extern void protopet_check_hit_target(void *);
extern void protopet_run_state_machine(void *);
extern void enemy_update_move_by_type(void *);
extern void protopet_update_step(void *);

/* Per-frame update for the Protopet: sets it up on the first frame, then runs its checks and behavior. */
void protopet_update_pal(char *object)
{
    char *moby = object;
    unsigned char state_id;

    if (g_level_l18_mode_word == 0x13) {
        if (g_game_l18_mode_state == 2) {
            *(int *)(moby + 0x98) = 0;
            *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
        } else {
            char *moby_class = *(char **)(moby + 0x24);

            *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
            *(int *)(moby + 0x98) = *(int *)(moby_class + 0x10);
        }
    }
    state_id = *(unsigned char *)(moby + 0x20);
    if (state_id == 0) {
        protopet_init(moby);
    } else if (state_id != 1 && state_id != 0x13) {
        protopet_check_hit_target(moby);
        protopet_run_state_machine(moby);
        enemy_update_move_by_type(moby);
        protopet_update_step(moby);
    }
}
