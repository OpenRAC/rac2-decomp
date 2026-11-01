#include "include_asm.h"

#include "common.h"
extern float D_L04_001AD848 MACRO_ADDR, D_L04_001AD84C MACRO_ADDR;
extern unsigned char D_001A7A33 MACRO_ADDR;
extern unsigned char D_001A7A32 MACRO_ADDR;
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern u32 func_00282978(u8 *);
extern int func_00283CF0(float);
extern float func_00282DB0(void *, void *);
extern int D_001A8FF0 MACRO_ADDR;
extern float D_001A7DC0 MACRO_ADDR;
extern f32 func_002AA898(f32 *position, f32 target, f32 *velocity,
                         f32 acceleration, f32 damping, f32 limit, s32 direction);
typedef struct {
    u8 pad00[0x7A8];
    f32 field7A8;
    f32 field7AC;
    f32 field7B0;
    f32 field7B4;
    u8 pad7B8[0x2290 - 0x7B8];
    u32 field2290;
    u32 field2294;
} D00189E20;
extern D00189E20 D_00189E20;
extern void func_002AEE70(u32 a0, void *a1, void *a2, f32 f0, f32 f1, f32 f2);
extern s32 func_00283CF0(f32 value);
extern s32 func_002A77E0(s32 limit);
extern u32 ref_L04_00362768_00;
extern u32 ref_L04_00362940_00;
extern s32 func_002A8600(u32 *out, s32 kind, s32 arg2, s32 arg3);
extern s32 func_002A86E8(u32 *out, u32 value, s32 arg2, s32 arg3);
extern f32 func_00282DB0(void *a, void *b);
extern f32 func_00282C10(f32 x);
extern f32 func_00283248(f32 a, f32 b);
extern s32 func_001163B0(void);
extern u8 *ref_L04_00358868_00[];
extern s32 func_00283CF0(f32);
extern f32 func_002A7878(f32, f32);
extern s32 func_002A77E0(s32);
extern f32 D_002A7A40[];
extern f32 D_002A7BC0[];
extern s32 D_002A7D90[];
extern f32 func_30F3A0(f32 x);
extern f32 func_30F3B8(f32 x);
extern f32 func_30FE40(f32 a, f32 b);
extern u32 func_00282978(u8 *ptr);
extern f32 D_L04_0023CA50[];
extern f32 D_L04_0023CD70[];
extern f32 D_L04_0023D220[];
extern f32 D_L04_0023D540[];
extern u8 D_L04_0023D158[];
extern u16 D_L04_0023D860[];
extern u16 D_L04_0023D9F0[];
extern u16 D_L04_0023DB80[];
#define MACRO_ADDR __attribute__((section(".sdata")))
extern s32 D_L04_001B2E70 MACRO_ADDR;
extern u16 D_L04_001B2E74 MACRO_ADDR;
extern f32 func_002A78D8(f32 a0, f32 a1);
extern f32 func_002A7878(f32 a0, f32 a1);
extern f32 D_L04_0023CA50[];
extern f32 D_L04_0023CD70[];
extern f32 D_L04_0023D220[];
extern f32 D_L04_0023D540[];
extern u8 D_L04_0023D158[];
extern u16 D_L04_0023D860[];
extern u16 D_L04_0023D9F0[];
extern u16 D_L04_0023DB80[];
extern s32 D_L04_001B2E70;
extern u16 D_L04_001B2E74;
extern f32 func_002A78D8(f32 a0, f32 a1);
extern f32 func_002A7878(f32 a0, f32 a1);
extern u32 D_L04_001B2E84 __attribute__((sda));

void func_PAL_L04_002CE778(void) {
    if (D_00189E20.field2294 != 0x7C)
        return;
    func_002AEE70(D_00189E20.field2290, &D_00189E20.field7A8, &D_00189E20.field7AC,
                  0.3f, 0.13962635f, -1.0f);
}

extern void func_002AEF28(u32 a0, void *a1, void *a2, f32 f0, f32 f1, f32 f2);

void func_PAL_L04_002CE7D8(void) {
    if (D_00189E20.field2294 != 0x7C)
        return;
    func_002AEF28(D_00189E20.field2290, &D_00189E20.field7B0, &D_00189E20.field7B4,
                  0.174532949924469f, 0.031415932f, 0.04188791f);
}
