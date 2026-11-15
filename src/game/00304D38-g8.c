#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } SpawnVec;
typedef struct __attribute__((packed, aligned(4))) { u64 a; u32 b; } SpawnParams;
typedef struct { char pad[0x10]; SpawnVec previous, velocity, direction; char pad40[0xC]; short trigger; char pad4e[6]; int state; char pad58[4]; float timer; char pad60[0x8]; int target; } SpawnRecord;
extern float D_001AEC04 __attribute__((sda));
extern SpawnParams D_001AEC10;
extern void moby_get_facing_direction(void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern int SelectBestTargetInCone(void *, void *, float, float, void *, int, int, int, float, float, float, int, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void mat_get_euler_angles(void *, void *);
extern float math_random_signed_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_random_float_range(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
/* Looks for a target for the thrown object and, when it has one, launches it toward it with a random upward kick. */
void projectile_launch_at_target(char *obj)
{
    SpawnVec origin, pos;
    SpawnParams params;
    SpawnVec angles;
    SpawnVec matrix[4];
    SpawnVec up;
    int output;
    SpawnRecord *rec = *(SpawnRecord **)(obj + 0x68);
    moby_get_facing_direction(obj + 0x10, &origin);
    moby_transform_joint_to_world(obj, 0, &pos);
    if (rec->target == 0) {
        params = D_001AEC10;
        rec->target = SelectBestTargetInCone(&pos, obj + 0xC0, 6.2831855f, 6.2831855f, &output, 0, 0, 0, D_001AEC04, 0.0f, 0.0f, 0, &params);
        if (rec->target) {
            obj[0x20] = 4;
            rec->timer = 0.0f;
        }
    }
    if (rec->trigger == 0 && rec->target == 0)
        return;
    {
        SpawnVec *direction = &rec->direction;
        if (rec->target == 0) {
            up.q = 0;
            up.f[2] = 1.0f;
            qcopy(&matrix[0], direction);
            FastVecCross(&matrix[1], &matrix[0], &up);
            vec_scale_to_length(&matrix[1], &matrix[1], 1.0f);
            FastVecCross(&matrix[2], &matrix[1], &matrix[0]);
            matrix[3].f[0] = 0;
            matrix[3].f[1] = 0;
            matrix[3].f[2] = 0;
            matrix[3].f[3] = 1;
            mat_get_euler_angles(&matrix, &angles);
            {
                float angle = FastAddRotations(angles.f[2], math_random_signed_float_range(0.78539824f, 1.5707965f));
                float elevation = math_random_float_range(-0.1f, 0.45f);
                vec_build_spherical_offset(&rec->velocity, 1.0f, angle, elevation);
            }
        }
        qcopy(&rec->previous, direction);
        rec->state = 0;
        rec->trigger = 0;
    }
}
