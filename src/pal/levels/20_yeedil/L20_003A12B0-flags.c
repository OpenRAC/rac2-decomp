#include "include_asm.h"
#include "names.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern float vec_distance_xy(const void *, const void *);
extern void object_swing_along_arc_pal(unsigned char *);

/* Turns the trooper toward its target, tilts it up or down to aim, then runs the move step. */
void trooper_aim_at_target_pal(unsigned char *object) {
    Vector position;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    if (*(unsigned short *)(object + 0x96) < 65000)
        ++*(unsigned short *)(object + 0x96);
    *(float *)(state + 0xF8) = mat_fast_helper_a(*(float *)(state + 0x50) - *(float *)(object + 0x10),
                                           *(float *)(state + 0x54) - *(float *)(object + 0x14));
    *(float *)(state + 0xF8) = fast_subtract_rotations(*(float *)(state + 0xF8), *(float *)(object + 0xF8));
    moby_update_eased_node(object, state + 0x90, 0, 0.0432f, 0.43200004f);
    position.q = *(Quadword *)(object + 0x10);
    position.f[2] += 2.0f;
    *(float *)(state + 0x174) = -mat_fast_helper_a(vec_distance_xy(&position, state + 0x50),
                                            *(float *)(state + 0x58) - position.f[2]);
    moby_update_eased_node(object, state + 0x110, 1, 0.0432f, 0.43200004f);
    object_swing_along_arc_pal(object);
}
