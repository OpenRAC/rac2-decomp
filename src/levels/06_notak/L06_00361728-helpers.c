#include "common.h"
typedef float Vector[4] __attribute__((aligned(16)));
/* Measured resident-player prefix; the complete object extent is unknown. */
typedef struct {
    unsigned char prefix[0xD0]; Vector first, second;
    unsigned char gap[0x21A0]; char *target; int state;
    int unused; int mode;
} PlayerView;
extern PlayerView g_hero_state;
extern char *g_moby_l06_table;
extern short g_target_index_list[] __attribute__((sda));
extern float vec_distance_xy(char *, char *);

/* Find the nearest active target and fill the target's position frames. */
int moby_find_nearest_target(char *moby, char *target, float distance)
{
    char *best = g_hero_state.target;
    int kind = 0;
    int index;
    if (g_hero_state.mode == 0x18 ||
        g_hero_state.state == 0x6F) {
        best = 0;
        kind = 2;
    }
    for (index = 1; index <= g_target_index_list[0]; index++) {
        char *candidate = g_moby_l06_table + (g_target_index_list[index] << 8);
        if (candidate &&
            (*(short *)(candidate + 0xAA) == MOBY_CLASS_DECOY ||
             *(short *)(candidate + 0xAA) == 0x76C /* moby class 1900 */) &&
            *(unsigned char *)(candidate + 0x20) != 0xFE &&
            *(unsigned char *)(candidate + 0x20) != 0xFD &&
            *(unsigned char *)(candidate + 0x20) == 3) {
            float current = vec_distance_xy(moby + 0x10, candidate + 0x10);
            if (current < distance) {
                best = candidate;
                distance = current;
                kind = 1;
            }
        }
    }
    if (best) {
        *(char **)(target + 0x40) = best;
        qcopy(target, (best + 0x10));
        qcopy((target + 0x10), (best + 0xF0));
        if (best == g_hero_state.target) {
            qcopy((target + 0x20), &g_hero_state.first);
            qcopy((target + 0x30), &g_hero_state.second);
        } else {
            qcopy((target + 0x30), target);
            *(float *)(target + 0x38) += 0.6f;
            qcopy((target + 0x20), (target + 0x30));
        }
    } else {
        *(int *)(target + 0x40) = 0;
        qzero(target);
        qzero((target + 0x10));
        qzero((target + 0x30));
        qzero((target + 0x20));
    }
    *(int *)(target + 0x44) = kind;
    return kind;
}
