#include "include_asm.h"
#include "common.h"

extern char *ref_L01_0042A568_00[];
extern float func_00282E48(void *, void *);

/* The ship's docking state: 1 when it has come to rest on the pad, 4 when it is
   still too far out, plus 2 while the pad's beacon is lit and the ship can see it. */
int func_L01_0042A568(void)
{
    char *ship = ref_L01_0042A568_00[0];
    char *motion = *(char **)(ship + 0x70);
    u8 state = *(u8 *)(ship + 0x88);
    int result = 0;
    char *pad = motion + 0xE0;
    float *spin = (float *)(motion + 0x30);
    float *vel = (float *)motion;
    char *dock = motion + 0x80;
    float d;

    if (state == 2 || state == 3) {
        result = *(int *)(motion + 0xE0) == 0;
    } else if (state != 1 && vel[0] < 0.001f && vel[1] < 0.001f && vel[2] < 0.001f
               && spin[0] < 0.0001f && spin[1] < 0.0001f && spin[2] < 0.0001f) {
        d = fast_vec_dist(ship + 0x30, dock);
        if (d < 0.01f)
            result = 1;
        else if (*(int *)(pad + 0x40) != 0 && 0.1f < d)
            result = 4;
    }
    if (*(int *)(pad + 0x40) != 0 && *(u8 *)(ship + 0x89) != 0)
        result |= 2;
    return result;
}
