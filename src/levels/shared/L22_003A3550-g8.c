#include "include_asm.h"
#include "names.h"

/* func_L22_003A3550 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern char *ref_L22_003A3550_00 __attribute__((sda));

extern int *g_ship_path_table[];

extern char g_hero_position[];

extern float func_002F3C40(char *, char *);

extern int math_random_int_below(int);

extern int list_is_key_missing(int);

extern void arena_push_point_out(char *, float);

/* Picks a random lane point that is not close to the ship and returns it, pushed out by the given distance. */
int lane_pick_random_point_away_from_ship(char *outPoint, int requireAllowed, float extra) {
    char *state = *(char **)(ref_L22_003A3550_00 + 0x68);
    char *slots = state + 0x2A0;
    float best = 45.0f;
    int found;
    int laneIndex;
    int j;
    int *lane;
    char *point;
    int pointIndex;

    for (;;) {
        found = 0;
        laneIndex = math_random_int_below(0x20);
        lane = g_ship_path_table[*(int *)(slots + (laneIndex << 2))];
        point = (char *)lane + 0x10;
        for (j = 0; j < *lane; j++) {
            if (func_002F3C40(g_hero_position, point) < best) {
                found = 1;
                break;
            }
            point += 0x10;
        }
        if (found)
            continue;
        if (requireAllowed == 0)
            continue;
        if (list_is_key_missing(laneIndex) == 0)
            continue;
        break;
    }
    pointIndex = math_random_int_below(*lane - 1);
    *(TI128 *)outPoint = *(TI128 *)((char *)lane + pointIndex * 16 + 0x10);
    arena_push_point_out(outPoint, extra);
    return 1;
}
