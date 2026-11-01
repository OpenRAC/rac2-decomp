#include "include_asm.h"

#include "common.h"
extern void func_00282F20(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282DD8(void *, void *, void *);
extern u8 *D_0018C0B0;
extern u8 D_L22_001A7A78 __attribute__((sda));
extern f32 func_2F4AD0(f32, f32);
typedef struct {
    float vel[4];
    int life;
    int f14;
    int f18;
    float scale;
} TrailVars0040DE00;
typedef struct {
    u8 pad0[0x10];
    float pos[4];
    u8 flag20;
    u8 pad21[0xF];
    u8 alpha;
    u8 pad31;
    short colour;
    u8 pad34[0x34];
    TrailVars0040DE00 *vars;
    u8 pad6C[0x54];
    float p0[4];
    float p1[4];
    float p2[4];
} TrailMoby0040DE00;
extern void func_002AFFD8(void *, void *, int);
extern TrailMoby0040DE00 *func_0029EFD0(int);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern u8 *D_L22_001AF314[] __attribute__((sda));
extern f32 D_L22_001B2A98 __attribute__((sda));
extern void func_00282F20(void *, void *, f32);
extern u8 *D_0018C0B0;
extern void func_00282F20(void *, void *, f32);

TrailMoby0040DE00 *func_PAL_L22_00412B98(float *pos, float *vel, float *scale)
{
    float ref[4];
    float scaled[4];
    TrailMoby0040DE00 *moby;
    TrailVars0040DE00 *vars;

    func_002AFFD8(pos, ref, 1);
    moby = func_0029EFD0(0xF5D);
    if (moby != 0) {
        vars = moby->vars;
        vars->scale = *scale;
        vars->life = 0x43;
        moby->alpha = 0xFF;
        moby->colour = 0xFF;
        moby->flag20 = 0;
        qcopy(moby->pos, pos);
        qcopy(vars->vel, vel);
        vars->f18 = 0;
        vars->f14 = 0;
        func_00282F20(scaled, vel, 1.0f);
        qcopy(moby->p0, scaled);
        func_00282DD8(moby->p1, moby->p0, ref);
        func_00282F20(moby->p1, moby->p1, 1.0f);
        func_00282DD8(moby->p2, moby->p1, moby->p0);
        moby->p0[3] = moby->p1[3] = moby->p2[3] = 0.0f;
    }
    return moby;
}


extern s32 func_002A77E0(s32 a0);
extern s32 func_002E5DA0(s32 a0, s32 a1, char *a2, s32 a3);
extern s32 func_002E5CF8(s32 a0, s32 a1, char *a2);
extern int func_002A77E0(int);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_002A8E20(void *, void *);
extern s32 D_L22_001B2128 __attribute__((sda));
extern s32 D_L22_001A903C __attribute__((sda));
extern s32 D_L22_0018B6A8 __attribute__((sda));
extern s32 func_2F36F0(s32);
typedef struct { u8 pad[0x18]; u8 *target; } G1C00C0;
extern G1C00C0 D_001C00C0;
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_002A8C00(void *, void *, int, void *, f32);
extern void func_002A8E20(void *, void *);
extern void func_PAL_L22_00413048(void *, s32, s32);

void func_PAL_L22_00412CC0(u8 *a0, u8 *a1) {
    u8 *s0 = *(u8 **)(a0 + 0x68);
    u8 vec[16] __attribute__((aligned(16)));
    u8 ev[0x30] __attribute__((aligned(16)));
    u8 buf[16] __attribute__((aligned(16)));
    u8 *target;

    if (func_002761F8(a1, a0 + 0x10, 0, a0, 0) == 0) {
        return;
    }
    target = D_001C00C0.target;
    if (target == 0) {
        return;
    }
    if (*(s16 *)(target + 0xAA) == 0xEDD || *(s16 *)(target + 0xAA) == 0xE0B) {
        return;
    }
    if (target == D_0018C0B0 && !(*(f32 *)(s0 + 0x1C) < 50.0f)) {
        return;
    }
    if (*(f32 *)(s0 + 0x1C) >= 50.0f) {
        *(f32 *)(s0 + 0x1C) = 50.1f;
    }
    func_00282F20(vec, s0, 1.0f);
    func_002A8C00(ev, a0, 0x8B0003, vec, *(f32 *)(s0 + 0x1C));
    ev[0x18] = 5;
    ev[0x19] = 3;
    *(u16 *)(ev + 0x1A) = *(u16 *)(a0 + 0xAA);
    func_002A8E20(D_001C00C0.target, ev);
    func_PAL_L22_00413048(a0 + 0x10, 10, 1);
    if (D_001C00C0.target == 0) {
        qcopy(buf, a0 + 0x10);
        func_PAL_L22_00413048(buf, 15, 0);
    }
    a0[0x20] = 2;
}

