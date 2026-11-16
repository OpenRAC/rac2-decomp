#include "include_asm.h"
#include "names.h"








extern int coll_sweep_from_object(char *, char *, int, int, float, float, float, int,
                          int);
extern int coll_sweep_from_object(char *, char *, int, int, float, float, float, int,
                          int);
extern float vec_distance_xy(char *, char *);
extern int moby_step_controller(char *, char *, float);
extern int moby_l01_turn_toward_target(char *, char *);

/* Draws an effect at the moby, then moves it toward a target if it is close enough, or uses the other approach when it is far away. (PAL) */
void moby_chase_target_update_pal(char *moby, char *target, float speed) {
    char *state = *(char **)(moby + 0x68);

    coll_sweep_from_object(moby, moby + 0x10, 0x04010000, 0,
                  *(float *)(state + 0x50) + 0.5f, 50.0f, 1.0f, 1, 0);
    if (vec_distance_xy(moby + 0x10, target) <= *(float *)(state + 0x84)) {
        moby_step_controller(moby, target, speed);
    } else {
        moby_l01_turn_toward_target(moby, target);
    }
}



#include "common.h"
extern void moby_set_state(int, int, int);
extern int math_random_int_range(int, int);
extern char *yeedil_boss_find_group_target(char *);
extern int math_random_int_below(int);

/* Picks the next behaviour state for an enemy based on what it did last, and remembers the choice. (PAL) */
void enemy_choose_next_state_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);
    int last_state = *(int *)(state + 0x17F4);
    int choice;

    if (last_state == 2) goto other;
    if (last_state >= 3) goto other;
    if (last_state != 1) goto other;
    choice = yeedil_boss_find_group_target(moby);
    *(int *)(state + 0x17FC) = choice;
    if (choice == 0) {
        moby_set_state(moby, 0xC, 4);
    } else {
        moby_set_state(moby, 4, 2);
    }
    goto done;
other:
    choice = math_random_int_below(2) + 2;
    *(int *)(state + 0x17F8) = choice;
    *(int *)(state + 0x1810) = ((s32)(math_random_int_range(0xB4, 0x168)) * 5 + 2) / 6;
    moby_set_state(moby, 3, 1);
done:
    *(int *)(state + 0x17F4) = *(unsigned char *)(moby + 0x95);
}

