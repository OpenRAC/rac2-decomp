#include "include_asm.h"
#include "names.h"

extern float g_stick_length;
extern float ref_L00_0032FEA8_00 __attribute__((sda));
extern int g_vehicle_steer_active_flag;
extern float g_vehicle_steer_damping;
extern float g_vehicle_max_speed __attribute__((sda));
extern float math_fabs(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void BuildObjectBasisVectors(void *);
extern void func_PAL_00331CF0(void *);
extern void func_PAL_00332038(void *);

void func_PAL_00331A48(char *object)
{
    char *data = *(char **)(object + 0x68);
    float value;
    int flag;
    char buffer[16];

    if (g_stick_length != 0.0f && g_vehicle_steer_active_flag != 0) {
        value = *(float *)(data + 0x58) + g_stick_length * (0.010000001f);
        *(float *)(data + 0x58) = value;
        if (math_fabs(value) > g_vehicle_max_speed * (0.020000001f))
            *(float *)(data + 0x58) = g_vehicle_max_speed * ref_L00_0032FEA8_00 * (0.020000001f);
    } else {
        *(float *)(data + 0x58) = *(float *)(data + 0x58) * 0.85f;
    }

    flag = g_vehicle_steer_active_flag;
    value = *(float *)(data + 0x58) * 25.0f;
    *(float *)(object + 0x48) = value;
    if (flag == 0)
        *(float *)(object + 0x48) = value + (g_vehicle_steer_damping + g_vehicle_steer_damping);

    vec_scale_to_length(buffer, object + 0xC0, *(float *)(data + 0x58));
    FastVecAdd(object + 0x10, object + 0x10, buffer);
    BuildObjectBasisVectors(object);
    func_PAL_00331CF0(object);
    func_PAL_00332038(object);
}
