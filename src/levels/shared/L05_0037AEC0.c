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

/* Initialises a spawned sub-object from the owner's fields and increments a shared counter, then runs three follow-up calls and conditionally two more. */
void moby_init_spawned_sub_object(char *object, int flag)
{
    char *sub;
    int **slotPtr;

    sub = moby_get_motion_data(object, flag);
    if (sub == 0)
        return;

    *(short *)(object + 50) = 511;
    *(unsigned char *)(object + 48) = 255;
    *(short *)(object + 52) = *(unsigned short *)(object + 52) & 0xfffc;
    *(int *)(object + 152) = *(int *)(*(int *)(object + 36) + 16);
    *(int *)(sub + 272) = 1;
    *(int *)(sub + 248) = 0;
    func_00282C88_2(sub + 112);
    *(int *)(sub + 268) = 0;
    *(int *)(sub + 280) = 0;
    *(int *)(sub + 252) = 0;
    *(int *)(sub + 308) = 0;
    *(int *)(sub + 332) = 1;
    *(int *)(sub + 348) = 0;
    slotPtr = *(int ***)(object + 104);
    *(float *)*slotPtr = (float)*(int *)(sub + 328);
    g_feltzin_challenge_state[4] = g_feltzin_challenge_state[4] + 1;
    moby_clear_links(object);
    follower_set_state(object, 1);
    moby_l05_set_state_value(object, 1);
    if (flag)
        follower_start_random_push(object);
    if (g_feltzin_challenge_state[13] == 1)
        moby_reset_action_state(object);
}

/* The spawned sub-object's stored pointer, or zero. */
/* Returns the stored value of an object, or zero if it has none. */
int moby_get_sub_object_stored_value(char *object, int flag)
{
    char *sub = moby_get_motion_data(object, flag);

    if (sub == 0)
        return 0;
    return *(int *)(sub + 0x110);
}

/* func_L05_0037B108 is defined in L05_0037B108.c for its absolute-symbol profile. */

/* func_L05_0037B210 is defined in L05_0037AEC0-g8.c (this unit has no $gp access for it). */

/* func_L05_0037B3A0 uses the verified one-argument state-query interface in L05_0037B3A0.c. */



/* func_L05_0037B538 is defined in L05_0037B538.c. */
