#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } SpawnVec;
typedef struct __attribute__((packed, aligned(4))) { u64 a; u32 b; } SpawnParams;
typedef struct { char pad[0x10]; SpawnVec previous, velocity, direction; char pad40[0xC]; short trigger; char pad4e[6]; int state; char pad58[4]; float timer; char pad60[0x4]; int target; } SpawnRecord;
extern float D_001AEC64 __attribute__((sda));
extern SpawnParams D_001AEC70;
extern void moby_get_facing_direction(void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern char *SelectBestTargetInCone(void *, void *, float, float, void *, int, int, int, float, float, float, int, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void mat_get_euler_angles(void *, void *);
extern float math_random_signed_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_random_float_range(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
/* Looks for a target for the Megaturret. When it finds one it starts shooting, otherwise it picks a random aim direction. */
void megaturret_find_target(char *obj)
{
    SpawnVec origin, muzzle_pos;
    SpawnParams params;
    SpawnVec angles;
    SpawnVec aim_basis[4];
    SpawnVec up;
    int target_info;
    SpawnRecord *vars = *(SpawnRecord **)(obj + 0x68);
    moby_get_facing_direction(obj + 0x10, &origin);
    moby_transform_joint_to_world(obj, 0, &muzzle_pos);
    if (vars->target == 0) {
        params = D_001AEC70;
        vars->target = SelectBestTargetInCone(&muzzle_pos, obj + 0xC0, 6.2831855f, 6.2831855f, &target_info, 0, 0, 0, D_001AEC64, 0.0f, 0.0f, 0, &params);
        if (vars->target) {
            obj[0x20] = 4;
            vars->timer = 0.0f;
        }
    }
    if (vars->trigger == 0 && vars->target == 0)
        return;
    {
        SpawnVec *direction = &vars->direction;
        if (vars->target == 0) {
            up.q = 0;
            up.f[2] = 1.0f;
            qcopy(&aim_basis[0], direction);
            FastVecCross(&aim_basis[1], &aim_basis[0], &up);
            vec_scale_to_length(&aim_basis[1], &aim_basis[1], 1.0f);
            FastVecCross(&aim_basis[2], &aim_basis[1], &aim_basis[0]);
            aim_basis[3].f[0] = 0;
            aim_basis[3].f[1] = 0;
            aim_basis[3].f[2] = 0;
            aim_basis[3].f[3] = 1;
            mat_get_euler_angles(&aim_basis, &angles);
            {
                float angle = FastAddRotations(angles.f[2], math_random_signed_float_range(0.78539824f, 1.5707965f));
                float elevation = math_random_float_range(-0.1f, 0.45f);
                vec_build_spherical_offset(&vars->velocity, 1.0f, angle, elevation);
            }
        }
        qcopy(&vars->previous, direction);
        vars->state = 0;
        vars->trigger = 0;
    }
}
