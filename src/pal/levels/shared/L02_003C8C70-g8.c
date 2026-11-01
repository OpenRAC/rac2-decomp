#include "include_asm.h"

#include "common.h"
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
typedef struct {
    s32 lo;
    s32 hi;
} L02Range_C4ED8;
typedef struct {
    f32 a;
    f32 b;
} L02Pair_C4ED8;
extern L02Range_C4ED8 D_L02_001AFE90 NOT_SDA;
extern L02Pair_C4ED8 D_L02_001AFE98 NOT_SDA;
extern f32 D_L02_001AFE60[] SDATA(D_L02_001AFE60);
extern f32 D_L02_001AFE70_gp[] SDATA(D_L02_001AFE70);
extern f32 D_L02_001AFE70[] __attribute__((sda));
extern f32 D_L02_001AFE80[] __attribute__((sda));
extern int func_00282948(void *);
extern void func_00283098(void *, void *, void *);
extern void func_PAL_L02_002F1100(void *, void *, void *, int, int, int, int, float);
extern int func_002A7820(int, int);
extern int func_002E5DA0(int, int, char *, int);

void func_PAL_L02_003C8C70(u8 *self)
{
    L02Range_C4ED8 range = D_L02_001AFE90;
    L02Pair_C4ED8 speed = D_L02_001AFE98;
    f32 origin[4] __attribute__((aligned(16)));
    f32 dir0[4] __attribute__((aligned(16)));
    f32 dir1[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(self + 0x68);

    if (func_00282948(state + 0x124) == 0)
        return;
    if (*(s32 *)(state + 0x18) != 0) {
        qcopy(origin, self + 0x10);
    } else {
        func_00283098(origin, D_L02_001AFE60, self + 0xC0);
        func_00282CC0(origin, origin, self + 0x10);
    }
    func_00283098(dir0, D_L02_001AFE70_gp, self + 0xC0);
    func_00282F20(dir0, dir0, speed.a * 0.020000001f);
    func_00283098(dir1, D_L02_001AFE80, self + 0xC0);
    func_00282F20(dir1, dir1, speed.b * 0.020000001f);
    D_L02_001AFE70[1] = -D_L02_001AFE70[1];
    D_L02_001AFE80[1] = -D_L02_001AFE80[1];
    func_PAL_L02_002F1100(origin, dir0, dir1, 12, 0, 0, 0, 15.0f);
    *(s32 *)(state + 0x124) = ((s32)(func_002A7820(range.lo, range.hi)) * 5 + 2) / 6;
    func_002E5DA0(4, 0, (char *)self, 0x896);
}
