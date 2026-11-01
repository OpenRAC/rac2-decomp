#include "include_asm.h"

#include "common.h"
extern void func_00282C88(void *);
extern void func_002A7A00(void *, float, float);
extern float func_002A7878(float, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern u8 *D_L02_001B359C_tbl[] __asm__("D_L02_001B359C") __attribute__((sda));
typedef struct {
    f32 x;
    f32 y;
} L02Pair_CF1B8;
typedef struct {
    s32 a;
    s32 b;
} L02Range_CF1B8;
extern L02Pair_CF1B8 D_L02_001B00D0;
extern L02Pair_CF1B8 D_L02_001B00D8;
extern L02Range_CF1B8 D_L02_001B00E0;
typedef struct {
    L02Range_CF1B8 r[2];
} L02Ranges_CF1B8;
extern L02Ranges_CF1B8 D_L02_001B00E8;
extern void func_00282C88(void *);
extern int func_002A77E0(int);
extern void *func_002C3150(void *, void *, int, int, int, int, float);
extern void func_002A7A00(void *, float, float);

void func_PAL_L02_003D31A0(u8 *self)
{
    L02Pair_CF1B8 speed = D_L02_001B00D0;
    L02Pair_CF1B8 size = D_L02_001B00D8;
    L02Range_CF1B8 kind = D_L02_001B00E0;
    L02Ranges_CF1B8 count = D_L02_001B00E8;
    f32 vel[4] __attribute__((aligned(16)));
    f32 pos[4] __attribute__((aligned(16)));
    s32 i;

    func_00282C88(vel);
    func_002C3150(self + 0x10, vel, kind.a, ((s32)(func_002A7820(count.r[0].a, count.r[0].b)) * 5 + 2) / 6 & 0xFF,
                  func_002A77E0(0xFF) & 0xFF, 0, size.x);
    for (i = 0; i < 1; i++) {
        func_002A7A00(pos, 0.0f, 0.5f);
        func_00282CC0(pos, pos, self + 0x10);
        vel[2] = -(func_002A7878(speed.x, speed.y) * 0.020000001f);
        func_002C3150(pos, vel, kind.b, ((s32)(func_002A7820(count.r[1].a, count.r[1].b)) * 5 + 2) / 6 & 0xFF,
                      func_002A77E0(0xFF) & 0xFF, 0, size.y);
    }
}

