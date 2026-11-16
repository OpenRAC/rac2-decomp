#include "include_asm.h"
#include "names.h"

extern float g_move_friction_step __attribute__((sda));
extern float math_fabs(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void BuildEightDirectionOffsets(void *);
extern void moby_probe_surface_and_move_pal(void *);
extern void vehicle_align_to_ground_surface_pal(void *);

void func_PAL_00328538(char *object)
{
    float vector[4];
    char *data = *(char **)(object + 0x68);
    float speed = *(float *)(data + 0x30);
    if (speed != 0.0f && *(int *)(data + 0x34)) {
        float magnitude;
        float step;
        *(float *)(data + 0x18) += speed * (0.010000001f);
        magnitude = math_fabs(*(float *)(data + 0x18));
        step = g_move_friction_step;
        if (step * (0.020000001f) < magnitude)
            *(float *)(data + 0x18) = step * *(float *)(data + 0x30) * (0.020000001f);
    } else {
        *(float *)(data + 0x18) *= 0.85f;
    }
    *(float *)(object + 0x48) = *(float *)(data + 0x18) * 25.0f;
    if (*(int *)(data + 0x34) == 0)
        *(float *)(object + 0x48) += *(float *)(data + 0x38) * 2.0f;
    vec_scale_to_length(vector, object + 0xC0, *(float *)(data + 0x18));
    FastVecAdd(object + 0x10, object + 0x10, vector);
    BuildEightDirectionOffsets(object);
    moby_probe_surface_and_move_pal(object);
    vehicle_align_to_ground_surface_pal(object);
}
