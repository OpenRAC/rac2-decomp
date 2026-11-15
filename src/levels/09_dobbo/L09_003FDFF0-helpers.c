#include "common.h"

typedef int TI __attribute__((mode(TI)));

extern int math_random_int_below(int);
extern float IntToFloat(int);
extern int math_fast_helper_a(float *, float);
extern void moby_transform_joint_point(char *, int, char *);
extern void vec_scale_to_length(float *, float *, float);

/* If the object is on screen, rebuilds its camera-facing frame and asks for it to be drawn. */
void moby_rebuild_frame_if_visible(unsigned char *moby) {
    unsigned char *mobyBytes = moby;
    unsigned char *vars = *(unsigned char **)(mobyBytes + 0x68);
    float sphere[4] __attribute__((aligned(16)));
    if (math_random_int_below(5) == 0)
        return;
    qcopy(sphere, mobyBytes + 0x10);
    sphere[3] = 4.0f;
    if (math_fast_helper_a(sphere, IntToFloat(*(short *)(mobyBytes + 0x32))) == -1)
        return;
    moby_transform_joint_point((char *)mobyBytes, 1, (char *)(vars + 0x340));
    vec_scale_to_length((float *)(vars + 0x340), (float *)(vars + 0x340), 1.0f);
    vec_scale_to_length((float *)(vars + 0x350), (float *)(vars + 0x350), 1.0f);
    vec_scale_to_length((float *)(vars + 0x360), (float *)(vars + 0x360), 1.0f);
    *(int *)(vars + 0x42C) = 2;
}
