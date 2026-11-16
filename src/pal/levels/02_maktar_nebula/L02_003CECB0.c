#include "include_asm.h"

#include "common.h"
extern int ComputeRegionRouteHeading(char *, int, float *, char *, short, char *, char *, float, float);
extern int moby_step_controller(char *, int, float);

int enemy_follow_path_toward_point_pal(char *self, int arg1) {
    float out;
    char *p = *(char **)(self + 0x68);
    int r = ComputeRegionRouteHeading(self + 0x10, arg1, &out, p + 0x290, *(short *)(p + 0x3B6),
                              p + 0x3B8, p + 0x3BC, 0.0f, *(float *)(p + 0x50));
    moby_step_controller(self, arg1, out);
    return r;
}

