#include "include_asm.h"
#include "names.h"

extern char *moby_get_motion_data(char *object, int flag);
extern void func_00282C88_2(char *target);
extern void moby_clear_links(char *object);
extern void follower_set_state(char *object, int value);
extern void moby_l05_set_state_value(char *object, int value);
extern void follower_start_random_push(char *object);
extern void moby_reset_action_state(char *object);
extern int g_feltzin_challenge_state[];

/* Initialises a spawned sub-object from the owner'vars fields and increments a shared counter, then runs three follow-up calls and conditionally two more. */
void moby_init_spawned_sub_object_pal(char *object, int flag)
{
    char *vars;
    int **slot;

    vars = moby_get_motion_data(object, flag);
    if (vars == 0)
        return;

    *(short *)(object + 50) = 511;
    *(unsigned char *)(object + 48) = 255;
    *(short *)(object + 52) = *(unsigned short *)(object + 52) & 0xfffc;
    *(int *)(object + 152) = *(int *)(*(int *)(object + 36) + 16);
    *(int *)(vars + 272) = 1;
    *(int *)(vars + 248) = 0;
    func_00282C88_2(vars + 112);
    *(int *)(vars + 268) = 0;
    *(int *)(vars + 280) = 0;
    *(int *)(vars + 252) = 0;
    *(int *)(vars + 308) = 0;
    *(int *)(vars + 332) = 1;
    *(int *)(vars + 348) = 0;
    slot = *(int ***)(object + 104);
    *(float *)*slot = (float)*(int *)(vars + 328);
    g_feltzin_challenge_state[4] = g_feltzin_challenge_state[4] + 1;
    moby_clear_links(object);
    follower_set_state(object, 1);
    moby_l05_set_state_value(object, 1);
    if (flag)
        follower_start_random_push(object);
    if (g_feltzin_challenge_state[13] == 1)
        moby_reset_action_state(object);
}

