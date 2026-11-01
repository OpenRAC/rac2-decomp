#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad[0x2C8];
    u8 *child;
} HrugisPathState;
typedef int TI128 __attribute__((mode(TI)));
extern u8 *func_PAL_L05_0037DB90(s32, s32);
extern f32 func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, f32);
extern f32 func_002A7798(f32);
extern f32 func_L01_00311C18(void *, void *, void *, void *);
extern u8 *D_L10_001B2614 MACRO_ADDR;
extern u8 D_L10_00221CD0[];
extern f32 D_L10_001B0F4C NOT_SDA;
extern s32 D_L10_001B0F44 __attribute__((sda));

void func_PAL_L10_0041BDF8(u8 *obj) {
    f32 up[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 scaled[4] __attribute__((aligned(16)));
    f32 closest[4] __attribute__((aligned(16)));
    f32 correction[4] __attribute__((aligned(16)));
    u8 *s = *(u8 **)(obj + 0x68);
    u8 *best, *p, *target, *childpos;
    s32 *index;
    f32 distance, d, scale;
    s32 i;
    *(TI128 *)up = 0;
    up[2] = 1.0f;
    if (((HrugisPathState *)s)->child) return;
    p = func_PAL_L05_0037DB90(0xF8D, 1);
    ((HrugisPathState *)s)->child = p;
    distance = D_L10_001B0F4C;
    best = 0;
    for (index = (s32 *)(s + 0x2A0), i = 3; i >= 0; i--, index++) {
        p = D_L10_001B2614 + *index * 128;
        d = func_00282E48(p + 0x30, obj + 0x10);
        if (d < distance) {
            distance = d;
            best = p;
        }
    }
    if (!best) return;
    target = D_L10_001B2614 + *(s32 *)D_L10_00221CD0 * 128;
    childpos = ((HrugisPathState *)s)->child + 0x10;
    qcopy(childpos, best + 0x30);
    func_00282CF0(delta, target + 0x30, childpos);
    delta[3] = 0;
    func_00282F20(((HrugisPathState *)s)->child + 0xC0, delta, 1.0f);
    func_00282DD8(((HrugisPathState *)s)->child + 0xD0, ((HrugisPathState *)s)->child + 0xC0, up);
    *(s32 *)(((HrugisPathState *)s)->child + 0xDC) = 0;
    func_00282F20(((HrugisPathState *)s)->child + 0xD0, ((HrugisPathState *)s)->child + 0xD0, 1.0f);
    func_00282DD8(((HrugisPathState *)s)->child + 0xE0, ((HrugisPathState *)s)->child + 0xD0, ((HrugisPathState *)s)->child + 0xC0);
    *(s32 *)(((HrugisPathState *)s)->child + 0xEC) = 0;
    /* Retail keeps the saved position pointer live across these copies. */
    qcopy_nc(s + 0x260, ((HrugisPathState *)s)->child + 0x10);
    qcopy_nc(s + 0x270, obj + 0x10);
    d = func_00282E48(s + 0x260, s + 0x270);
    scale = func_002A7798(d * 0.001953129889f) * 160.0f;
    func_00282F20(scaled, delta, scale);
    func_00282CC0(s + 0x280, scaled, s + 0x260);
    func_L01_00311C18(closest, s + 0x260, s + 0x270, s + 0x280);
    func_00282CF0(correction, s + 0x280, closest);
    func_00282D30(correction, correction, -1.0f);
    func_00282CC0(s + 0x280, closest, correction);
    func_00282CF0(delta, target + 0x30, s + 0x270);
    func_00282F20(scaled, delta, scale);
    func_00282CC0(s + 0x290, scaled, s + 0x270);
    func_L01_00311C18(closest, s + 0x260, s + 0x270, s + 0x290);
    func_00282CF0(correction, s + 0x290, closest);
    func_00282D30(correction, correction, -1.0f);
    func_00282CC0(s + 0x290, closest, correction);
    func_00282CF0(delta, s + 0x260, s + 0x270);
    func_00282F20(scaled, delta, 8.0f);
    func_00282CC0(s + 0x270, scaled, s + 0x270);
    *(s32 *)(s + 0x2D4) = 0;
    *(f32 *)(s + 0x2D8) = 0.013962637f;
    D_L10_001B0F44 = 1;
}
