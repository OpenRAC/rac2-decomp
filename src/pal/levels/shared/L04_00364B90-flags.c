#include "include_asm.h"

#include "common.h"
extern float D_L04_001AD848 MACRO_ADDR, D_L04_001AD84C MACRO_ADDR;
extern unsigned char D_001A7A33 MACRO_ADDR;
extern unsigned char D_001A7A32 MACRO_ADDR;
extern void func_00282CF0(f32 *,f32 *,f32 *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern u32 func_00282978(u8 *);
extern int func_00283CF0(float);
extern void func_00282F20(float *, float *, float);
extern float func_00282DB0(void *, void *);
extern int D_001A8FF0 MACRO_ADDR;
extern float D_001A7DC0 MACRO_ADDR;
extern f32 func_002AA898(f32 *position, f32 target, f32 *velocity,
                         f32 acceleration, f32 damping, f32 limit, s32 direction);
typedef int L04Quad __attribute__((mode(TI)));
typedef struct {
    u8  field00;
    u8  field01;
    u8  field02;
    u8  field03;
    u32 field04;
    u8  field08;
    u8  field09;
    u16 field0A;
    u32 field0C;
    L04Quad field10;
    u8  pad20[0xC];
    f32 field2C;
    L04Quad field30;
} L04Spawned;
typedef struct {
    L04Quad v;
} L04Vector;
extern void *func_002B9030(s32 kind);
extern s32 func_00283CF0(f32 value);
extern s32 func_002A77E0(s32 limit);
extern void func_00282F20(f32 *dst, f32 *a, f32 len);
extern void func_00282CF0(f32 *dst, f32 *a, f32 *b);
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

void *func_PAL_L04_00364D88(void *a0, void *a1, u32 a2, f32 f3) {
    L04Spawned *p = (L04Spawned *)(u32)func_002B9030(0x5F);
    L04Vector *q;
    f32 v[4];

    if ((u32)p != 0) {
        p->field04 = 0x7F003CFF;
        p->field0C = 0x7F003CFF;
        p->field09 = (u8)(func_00283CF0(2.0f) + 0x20);
        p->field03 = 0x48;
        p->field01 = 3;
        q = (L04Vector *)((u8 *)p + 0x30);
        p->field02 = *(u8 *)ref_L04_00362940_00;
        q->v = *(L04Quad *)a1;
        *(f32 *)((u8 *)q + 0xC) = f3;
        p->field10 = *(L04Quad *)a0;
        func_00282F20(v, (f32 *)q, 0.5f);
        func_00282CF0((f32 *)((u8 *)p + 0x20), (f32 *)a0, v);
        p->field0A = (u16)a2;
        *(f32 *)((u8 *)p + 0x1C) = 0.005f;
        p->field08 = (u8)(*(u8 *)&p->field0A - 4);
        p->field2C = 1.0f;
    }
    return (u32)p;
}
