#include "names.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern char g_hero_state[];
extern char g_scalar_transition_state[];
extern void vec_scale_to_length(float *, float *, float);
extern void cam_compute_aim_angles(float *, float *, float *, float *, float *, float *);

/* Rebuilds the camera look-at data from the hero's current view. */
void cam_rebuild_look_at_from_hero(void)
{
    Vector first;
    Vector second;
    Vector third;
    char *resident = g_hero_state;
    char *camera = g_scalar_transition_state + 0x290;

    vec_scale_to_length(first.f, (float *)(*(char **)(resident + 0x2290) + 0xC0), 1.0f);
    vec_scale_to_length(second.f, (float *)(*(char **)(resident + 0x2290) + 0xD0), 1.0f);
    vec_scale_to_length(third.f, (float *)(*(char **)(resident + 0x2290) + 0xE0), 1.0f);
    *(Quad *)(camera + 0x90) = first.q;
    *(Quad *)(camera + 0xA0) = third.q;
    cam_compute_aim_angles((float *)(camera + 0x70), (float *)(camera + 0xC0),
                 (float *)(resident + 0x80), first.f, second.f, third.f);
    *(Quad *)(camera + 0xB0) = *(Quad *)(camera + 0xD0);
}
