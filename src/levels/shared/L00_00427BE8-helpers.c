#include "common.h"
typedef int TQ __attribute__((mode(TI)));

extern void vec_copy5_blend_first(float *dst, void *src, float x);
extern void moby_zero_five_words(char *p);
extern void func_L00_002EE0C0(char *p);
extern void cam_update_angles_to_target(char *p);

/* Copies the full aligned target vector into both state slots, records the
 * weight and refreshes the two five-float blend records and owner transform. */
/* Sets the camera's target position and blend weight, then refreshes the camera state. */
void cam_set_target_and_weight(char *camera, void *blend_source, TQ *target_vec, f32 weight_in)
{
    char *state = *(char **)(camera + 0x70);
    char *target = state + 0xB0;
    f32 weight = weight_in;

    qcopy(target, target_vec);
    qcopy(state + 0x80, target_vec);
    *(f32 *)(target + 0x18) = weight;
    vec_copy5_blend_first((float *)(state + 0x14), blend_source, weight);
    vec_copy5_blend_first((float *)(camera + 0x50), blend_source, 0.0f);
    moby_zero_five_words(state);
    func_L00_002EE0C0(state + 0x90);
    cam_update_angles_to_target(camera);
}
