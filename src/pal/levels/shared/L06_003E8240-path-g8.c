/* func_PAL_L06_003E8240, the PAL copy of func_L06_003E4BE0: the same C, where 1.0f / 60.0f becomes
   0.020000001f; 0.00027777778450399637f becomes 0.00040000002f; 0.000004848137291264255f becomes
   6.981318e - 06f; 0.20943954586982727f becomes 0.25132746f; 0.0002908882452175021f becomes
   0.0003490659f. */
#include "common.h"
typedef int L06Qword __attribute__((mode(TI)));
typedef union { L06Qword bits; float f[4]; } L06Vector;
extern char *D_L06_001FE500[];
extern u8 D_L06_001DB610[];
extern char D_00188660[];
extern float D_L06_001AF528 __attribute__((sda));
extern float D_L06_001AF52C __attribute__((sda));
extern float D_L06_001AF530 __attribute__((sda));
extern float D_L06_001AF534 __attribute__((sda));
extern float D_L06_001AF538 __attribute__((sda));
extern float D_L06_001AF53C __attribute__((sda));
extern float D_L06_001AF540 __attribute__((sda));
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282E20(void *);
extern float func_00282E48(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283248(float, float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern float func_002AAA00(void *, void *, int, float, float, float, float);
extern int func_002E59B0(void *, int);
extern int func_002E5DA0(int, int, void *, int);
extern void func_002E59F8(int);

int func_PAL_L06_003E8240(char *moby, int path, int *sound)
{
    L06Vector target, delta;
    float height;
    char **route = &D_L06_001FE500[path];
    char *st = *(char **)(moby + 0x68);
    int done = 0;
    float limit, angle;
    int handle;
    u8 *slot;
    float *yaw;
    int point = *(int *)(st + 0x64);
    char *node = *route;
    height = 0;
    qcopy(&target, node + point * 16 + 0x10);
    *(float *)(st + 0x108) = target.f[2];
    *(float *)(st + 0xEC) = 0;
    *(float *)(st + 0xE8) = 0;
    func_00282CF0(&delta, &target, moby + 0x10);
    if (func_00282DF0(&delta) < D_L06_001AF528 * (0.020000001f) * 2.0f) {
        ++*(int *)(st + 0x64);
        done = *(int *)(st + 0x64) == *(int *)*route;
    }
    limit = func_00282E48(moby + 0x10, *route + *(int *)*route * 16);
    func_002AA548(&height, st + 0x60, limit,
        D_L06_001AF52C * 0.00040000002f,
        D_L06_001AF52C * 0.00040000002f,
        D_L06_001AF528 * (0.020000001f));
    func_00282F20(&delta, &delta, *(float *)(st + 0x60));
    func_00282CC0(moby + 0x10, &delta, moby + 0x10);
    angle = -func_00283248(func_00282E20(&delta), delta.f[2]);
    if (angle > 0.2617994248867035f) angle = 0.2617994248867035f;
    else if (angle < -0.2617994248867035f) angle = -0.2617994248867035f;
    yaw = (float *)(moby + 0xF8);
    func_002AAA00(moby + 0xF4, st + 0x6C, 0, angle,
        D_L06_001AF538 * 6.981318e-06f,
        D_L06_001AF538 * 6.981318e-06f, 0.25132746f);
    angle = func_00283248(target.f[0] - *(float *)(moby + 0x10), target.f[1] - *(float *)(moby + 0x14));
    func_002AAA00(yaw, st + 0x68, 0, angle,
        D_L06_001AF530 * 6.981318e-06f,
        D_L06_001AF530 * 6.981318e-06f,
        D_L06_001AF534 * 0.0003490659f);
    func_002AAA00(moby + 0xF0, st + 0x70, 0,
        *(float *)(st + 0x68) * *(float *)(st + 0x60) * D_L06_001AF540,
        D_L06_001AF53C * 6.981318e-06f,
        D_L06_001AF53C * 6.981318e-06f, 0.25132746f);
    if (!done) {
        if (!func_002E59B0(moby, *sound) && D_L06_001DB610[0] != 0xFF)
            *sound = func_002E5DA0(0, 4, moby, 0x330);
    } else {
        handle = *sound;
        if (handle != -1) {
            slot = (u8 *)D_00188660 + handle * 0x70;
            if (*(char **)(slot + 0x88) == moby && slot[0x74]) func_002E59F8(handle);
        }
        *sound = -1;
    }
    return done;
}
