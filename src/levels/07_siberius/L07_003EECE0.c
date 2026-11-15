#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(unsigned char *, int, int);

extern void scale_vector(TI128 *, char *, float);

extern int math_fast_helper_a(TI128 *, float);

extern float mat_fast_helper_a(float, float);

/* The table is indexed in 128-byte records; position starts at offset 0x30. */
typedef struct { char bytes[128]; } EntryECE0;
extern EntryECE0 *D_L07_001B23CC __attribute__((nosda));

/* Resets the object and snaps it to its current path point. It also remembers where it started and which way it must turn to reach the path point. */
void path_reset_follower_to_point(char *moby)
{
    TI128 scratch;
    char *mobyAlias = moby;
    char *vars;
    char *definition;
    unsigned short flags;
    int pathIndex;
    char *pathPoint;
    float posY, posX;

    vars = *(char **)(moby + 0x68);
    flags = *(unsigned short *)(moby + 0x34);
    definition = *(char **)(moby + 0x24);
    *(unsigned short *)(moby + 0x34) = (flags & 0xFFBE) | 0x1000;
    *(int *)(moby + 0x98) = *(int *)(definition + 0x10);
    moby_set_state((unsigned char *)moby, 3, -1);
    *(unsigned char *)(moby + 0x30) = 0xFF;
    *(unsigned short *)(moby + 0x32) = 0xFF;

    if (*(int *)(vars + 0x98) != 0) {
        scale_vector(&scratch, mobyAlias, 0.0009765625f);
        pathIndex = math_fast_helper_a(&scratch, 128.0f);
        if (pathIndex != -1) {
            qcopy(moby + 0x10, &D_L07_001B23CC[*(int *)(vars + 0x98)].bytes[0x30]);
        }
    }

    pathIndex = *(int *)(vars + 0x94);
    pathPoint = (char *)(pathIndex * 128 + (int)D_L07_001B23CC);
    posX = *(float *)(moby + 0x10);
    posY = *(float *)(moby + 0x14);
    *(float *)(vars + 0xE8) = mat_fast_helper_a(*(float *)(pathPoint + 0x30) - posX, *(float *)(pathPoint + 0x34) - posY);
    qcopy(vars + 0xF0, moby + 0x10);
    qcopy(vars + 0xD0, &D_L07_001B23CC[*(int *)(vars + 0x94)].bytes[0x30]);
}
