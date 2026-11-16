#include "include_asm.h"
#include "names.h"








extern int coll_sweep_from_object(char *, char *, int, int, float, float, float, int,
                          int);
extern int coll_sweep_from_object(char *, char *, int, int, float, float, float, int,
                          int);
extern float vec_distance_xy(char *, char *);
extern int moby_step_controller(char *, char *, float);
extern int moby_l01_turn_toward_target(char *, char *);

void moby_chase_target_update_pal(char *arg0, char *arg1, float f) {
    char *state = *(char **)(arg0 + 0x68);

    coll_sweep_from_object(arg0, arg0 + 0x10, 0x04010000, 0,
                  *(float *)(state + 0x50) + 0.5f, 50.0f, 1.0f, 1, 0);
    if (vec_distance_xy(arg0 + 0x10, arg1) <= *(float *)(state + 0x84)) {
        moby_step_controller(arg0, arg1, f);
    } else {
        moby_l01_turn_toward_target(arg0, arg1);
    }
}



#include "common.h"
extern void moby_set_state(int, int, int);
extern int math_random_int_range(int, int);
extern char *yeedil_boss_find_group_target(char *);
extern int math_random_int_below(int);

void func_PAL_L20_00448650(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    int v = *(int *)(state + 0x17F4);
    int r;

    if (v == 2) goto other;
    if (v >= 3) goto other;
    if (v != 1) goto other;
    r = yeedil_boss_find_group_target(arg0);
    *(int *)(state + 0x17FC) = r;
    if (r == 0) {
        moby_set_state(arg0, 0xC, 4);
    } else {
        moby_set_state(arg0, 4, 2);
    }
    goto done;
other:
    r = math_random_int_below(2) + 2;
    *(int *)(state + 0x17F8) = r;
    *(int *)(state + 0x1810) = ((s32)(math_random_int_range(0xB4, 0x168)) * 5 + 2) / 6;
    moby_set_state(arg0, 3, 1);
done:
    *(int *)(state + 0x17F4) = *(unsigned char *)(arg0 + 0x95);
}

