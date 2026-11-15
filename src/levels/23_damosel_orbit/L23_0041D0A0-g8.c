#include "include_asm.h"
#include "names.h"

/* func_L23_0041D0A0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern char *g_mothership_boss_moby __attribute__((sda));

extern int *g_path_lists[];

extern char g_hero_position[];

extern float fast_vec_dist(char *, char *);

extern int math_random_int_below(int);

extern int mothership_is_value_not_in_slots(int);

extern void mothership_project_point_onto_surface(char *, float);

/* Picks a random path point that is far enough from the hero and stores it as a spawn position. */
int boss_pick_random_spawn_point(char *outPos, int onlyAllowed, float heightOffset) {
    char *state = *(char **)(g_mothership_boss_moby + 0x68);
    char *slots = state + 0x230;
    float best = 45.0f;
    int found;
    int slotIndex;
    int j;
    int *list;
    char *p;
    int pointIndex;

    for (;;) {
        found = 0;
        slotIndex = math_random_int_below(0x2F);
        list = g_path_lists[*(int *)(slots + (slotIndex << 2))];
        p = (char *)list + 0x10;
        for (j = 0; j < *list; j++) {
            if (fast_vec_dist(g_hero_position, p) < best) {
                found = 1;
                break;
            }
            p += 0x10;
        }
        if (found)
            continue;
        if (onlyAllowed == 0)
            continue;
        if (mothership_is_value_not_in_slots(slotIndex) == 0)
            continue;
        break;
    }
    pointIndex = math_random_int_below(*list - 1);
    *(TI128 *)outPos = *(TI128 *)((char *)list + pointIndex * 16 + 0x10);
    mothership_project_point_onto_surface(outPos, heightOffset);
    return 1;
}
