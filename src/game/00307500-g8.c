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
void func_00307500(char *obj)
{
    SpawnVec origin, pos;
    SpawnParams params;
    SpawnVec angles;
    SpawnVec matrix[4];
    SpawnVec up;
    int output;
    SpawnRecord *rec = *(SpawnRecord **)(obj + 0x68);
    func_002FE8D8(obj + 0x10, &origin);
    func_0029FCC0(obj, 0, &pos);
    if (rec->target == 0) {
        params = D_001AEC70;
        rec->target = SelectBestTargetInCone(&pos, obj + 0xC0, 6.2831855f, 6.2831855f, &output, 0, 0, 0, D_001AEC64, 0.0f, 0.0f, 0, &params);
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
            func_002AB6D8(&matrix, &angles);
            {
                float angle = FastAddRotations(angles.f[2], func_002A78D8(0.78539824f, 1.5707965f));
                float elevation = func_002A7878(-0.1f, 0.45f);
                func_002AF000(&rec->velocity, 1.0f, angle, elevation);
            }
        }
        qcopy(&rec->previous, direction);
        rec->state = 0;
        rec->trigger = 0;
    }
}
