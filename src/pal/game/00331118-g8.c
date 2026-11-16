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
extern void SweepMobyArcProbe_pal(void *);
extern void vehicle_settle_on_ground_pal(void *);

/* Steers and moves the ridden vehicle by the stick: updates its speed, moves it along its forward
   direction, and runs the ground probe and settle steps (PAL: 50 Hz rates). */
void vehicle_update_speed_and_move_pal(char *object)
{
    char *vars = *(char **)(object + 0x68);
    float speed;
    int steering;
    char step[16];

    if (g_stick_length != 0.0f && g_vehicle_steer_active_flag != 0) {
        speed = *(float *)(vars + 0x58) + g_stick_length * (0.010000001f);
        *(float *)(vars + 0x58) = speed;
        if (math_fabs(speed) > g_vehicle_max_speed * (0.020000001f))
            *(float *)(vars + 0x58) = g_vehicle_max_speed * ref_L00_0032FEA8_00 * (0.020000001f);
    } else {
        *(float *)(vars + 0x58) = *(float *)(vars + 0x58) * 0.85f;
    }

    steering = g_vehicle_steer_active_flag;
    speed = *(float *)(vars + 0x58) * 25.0f;
    *(float *)(object + 0x48) = speed;
    if (steering == 0)
        *(float *)(object + 0x48) = speed + (g_vehicle_steer_damping + g_vehicle_steer_damping);

    vec_scale_to_length(step, object + 0xC0, *(float *)(vars + 0x58));
    FastVecAdd(object + 0x10, object + 0x10, step);
    BuildObjectBasisVectors(object);
    SweepMobyArcProbe_pal(object);
    vehicle_settle_on_ground_pal(object);
}
