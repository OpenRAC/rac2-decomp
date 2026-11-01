#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; s32 w[4]; } V4_F419348;
extern s32 D_L10_001B0FB0 __attribute__((sda));
extern s32 D_L10_001B0FC0 __attribute__((sda));
extern s32 D_L10_001B0FD0 __attribute__((sda));
extern void func_00283098(void *, void *, char *);
extern void func_00282CC0(void *, void *, char *);
extern void func_002ACB48(void *, float);
extern float func_002A7878(float, float);
extern void func_L00_0033C0D0(char *, void *, void *, void *, s32);

/* Spawns three trail marks at the object's tail. */
void func_PAL_L10_0041E0F8(char *obj)
{
    V4_F419348 dir, drift, tail, mark1, mark2, mark3, alt;
    float k;

    dir.q = 0;
    dir.f[0] = -0.6f;
    dir.f[2] = 0.26f;
    dir.f[3] = 1.0f;
    drift.q = 0;
    k = 0.5f;
    if (*(u8 *)(obj + 0x20) == 1) {
        alt.q = 0;
        alt.f[0] = -0.15f;
        alt.f[2] = 0.06f;
        alt.f[3] = 1.0f;
        qcopy(&dir, &alt);
    }
    func_00283098(&tail, &dir, obj + 0xC0);
    func_00282CC0(&tail, &tail, obj + 0x10);
    tail.w[3] = 0;
    qcopy(&mark1, &tail);
    qcopy(&mark2, &tail);
    qcopy(&mark3, &tail);
    func_002ACB48(&tail, 0.1f);
    func_002ACB48(&mark1, 0.1f);
    func_002ACB48(&mark2, 0.1f);
    func_002ACB48(&mark3, 0.1f);
    drift.f[0] = -(func_002A7878(30.0f, 40.0f) * 0.020000001f) * k;
    func_L00_0033C0D0(obj, &mark1, &drift, &D_L10_001B0FB0, 1);
    drift.f[0] = -(func_002A7878(30.0f, 40.0f) * 0.020000001f) * k;
    func_L00_0033C0D0(obj, &mark2, &drift, &D_L10_001B0FC0, 1);
    drift.f[0] = -(func_002A7878(30.0f, 40.0f) * 0.020000001f) * k;
    func_L00_0033C0D0(obj, &mark3, &drift, &D_L10_001B0FD0, 1);
}
