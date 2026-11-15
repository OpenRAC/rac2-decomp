#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } SpawnVec;
typedef struct __attribute__((packed, aligned(4))) { u64 a; u32 b; } SpawnParams;
typedef struct { char pad[0x10]; SpawnVec previous, velocity, direction; char pad40[0xC]; short trigger; char pad4e[6]; int state; char pad58[4]; float timer; char pad60[0x4]; int target; } SpawnRecord;
extern float D_001AEC64 __attribute__((sda));
extern SpawnParams D_001AEC70;
extern void func_002FE8D8(void *, void *);
extern void func_0029FCC0(void *, int, void *);
extern int func_002AF580(void *, void *, float, float, void *, int, int, int, float, float, float, int, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AB6D8(void *, void *);
extern float func_002A78D8(float, float);
extern float func_00283B98(float, float);
extern float func_002A7878(float, float);
extern void func_002AF000(void *, float, float, float);
/* Looks for a target for the Megaturret. When it finds one it starts shooting, otherwise it picks a random aim direction. */
void func_00307500(char *obj)
{
    SpawnVec origin, muzzlePos;
    SpawnParams params;
    SpawnVec angles;
    SpawnVec aimBasis[4];
    SpawnVec up;
    int targetInfo;
    SpawnRecord *vars = *(SpawnRecord **)(obj + 0x68);
    GetObjectFacingDirection(obj + 0x10, &origin);
    TransformMobyJointToWorld(obj, 0, &muzzlePos);
    if (vars->target == 0) {
        params = D_001AEC70;
        vars->target = SelectBestTargetInCone(&muzzlePos, obj + 0xC0, 6.2831855f, 6.2831855f, &targetInfo, 0, 0, 0, D_001AEC64, 0.0f, 0.0f, 0, &params);
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
            qcopy(&aimBasis[0], direction);
            FastVecCross(&aimBasis[1], &aimBasis[0], &up);
            vec_scale_to_length(&aimBasis[1], &aimBasis[1], 1.0f);
            FastVecCross(&aimBasis[2], &aimBasis[1], &aimBasis[0]);
            aimBasis[3].f[0] = 0;
            aimBasis[3].f[1] = 0;
            aimBasis[3].f[2] = 0;
            aimBasis[3].f[3] = 1;
            GetEulerAnglesFromMatrix(&aimBasis, &angles);
            {
                float angle = FastAddRotations(angles.f[2], RandomSignedFloatRange(0.78539824f, 1.5707965f));
                float elevation = RandomFloatRange(-0.1f, 0.45f);
                BuildSphericalOffset(&vars->velocity, 1.0f, angle, elevation);
            }
        }
        qcopy(&vars->previous, direction);
        vars->state = 0;
        vars->trigger = 0;
    }
}
