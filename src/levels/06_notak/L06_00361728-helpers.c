#include "common.h"
typedef float Vector[4] __attribute__((aligned(16)));
/* Measured resident-player prefix; the complete object extent is unknown. */
typedef struct {
    unsigned char prefix[0xD0]; Vector first, second;
    unsigned char gap[0x21A0]; char *target; int state;
    int unused; int mode;
} PlayerView;
extern PlayerView D_00189E20;
extern char *D_L06_001B281C;
extern short D_L06_001B2970[] __attribute__((sda));
extern float func_00282E80(char *, char *);

/* Find the nearest active target and fill the target's position frames. */
int func_L06_00361728(char *moby, char *target, float distance)
{
    char *best = gHeroState.target;
    int kind = 0;
    int index;
    if (gHeroState.mode == 0x18 ||
        gHeroState.state == 0x6F) {
        best = 0;
        kind = 2;
    }
    for (index = 1; index <= D_L06_001B2970[0]; index++) {
        char *candidate = D_L06_001B281C + (D_L06_001B2970[index] << 8);
        if (candidate &&
            (*(short *)(candidate + 0xAA) == 0xCB /* Decoy */ ||
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
        if (best == gHeroState.target) {
            qcopy((target + 0x20), &gHeroState.first);
            qcopy((target + 0x30), &gHeroState.second);
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
