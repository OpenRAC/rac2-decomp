#include "include_asm.h"

#include "common.h"
extern int ComputeRegionRouteHeading(char *, int, float *, char *, short, char *, char *, float, float);
extern int moby_step_controller(char *, int, float);

/* Walks the enemy along its path toward a point and turns it to face the way it is going. Returns the path result (PAL copy). */
int enemy_follow_path_toward_point_pal(char *self, int target_point) {
    float heading;
    char *vars = *(char **)(self + 0x68);
    int result = ComputeRegionRouteHeading(self + 0x10, target_point, &heading, vars + 0x290, *(short *)(vars + 0x3B6),
                              vars + 0x3B8, vars + 0x3BC, 0.0f, *(float *)(vars + 0x50));
    moby_step_controller(self, target_point, heading);
    return result;
}

