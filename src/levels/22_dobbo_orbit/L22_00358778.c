#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern s32 D_L22_001B2128 __attribute__((sda));
extern u8 D_L22_001A7A78 __attribute__((sda));
extern s32 D_L22_001A903C __attribute__((sda));

extern void func_31FBB8();
extern void func_3300E8();
extern s32 D_L22_0018B6A8 __attribute__((sda));

extern s32 func_2F36F0(s32);
extern void func_2F3720();
extern void func_2F3AB0(void *, void *, void *);
extern void func_2F3D60(void *, void *, f32);
extern void func_2F3A80(void *, void *, void *);
extern void func_2F9E20(s32, s32);
extern void func_32F330(s32, s32);
extern void func_3A2988(void *, f32);
extern void func_2F4788(s32, s32, f32);
extern f32 func_2F4AD0(f32, f32);
extern void func_3167E8(s32, s32, s32);
extern void func_362E98(s32, s32, s32);
extern void func_32AE80(s32, s32);

extern void func_L22_003E87B8(s32, s32, s32);
extern void func_L22_003FA1D0(s32, s32, s32);

INCLUDE_ASM("asm/levels", func_L22_00358778);

INCLUDE_ASM("asm/levels", func_L22_00385F40);

INCLUDE_ASM("asm/levels", func_L22_0038FBE0);

INCLUDE_ASM("asm/levels", func_L22_0038FFF8);

INCLUDE_ASM("asm/levels", func_L22_003955D8);

/* func_L22_003A6620 lives in the -g8 sibling file (it reaches a global through $gp). */

INCLUDE_ASM("asm/levels", func_L22_003B9450);


INCLUDE_ASM("asm/levels", func_L22_003D0840);

/* func_L22_003E87B8 is in L22_003E87B8.c. */

void func_L22_003E8830(s32 a0) {
    s32 x = *(u32 *)(a0 + 0x68);

    func_L22_003E87B8(a0, x, x);
    *(u8 *)(a0 + 0x30) = 0xFF;
}

INCLUDE_ASM("asm/levels", func_L22_003FA1D0);

void func_L22_003FA2A8(s32 a0) {
    s32 x = *(u32 *)(a0 + 0x68);

    func_L22_003FA1D0(a0, x, x);
    *(u8 *)(a0 + 0x30) = 0xFF;
}


INCLUDE_ASM("asm/levels", func_L22_0040C888);

INCLUDE_ASM("asm/levels", func_L22_0040D638);

void func_L22_0040DA80(s32 a0) {
    s32 s1 = a0;
    s32 s0 = *(u32 *)(s1 + 0x68);

    func_2F36F0(s0 + 0x258);
    func_2F3720(s0 + 0x25C);
    if (*(u16 *)(s1 + 0x96) <= 0xFFFE)
        *(u16 *)(s1 + 0x96) = *(u16 *)(s1 + 0x96) + 1;
    if (*(u8 *)(s0 + 0x211) == 0)
        func_3167E8(s1, 7, s0 + 0x210);
    func_2F4788(s0 + 0x220, 2, *(f32 *)(s0 + 0x26C));
    *(f32 *)(s0 + 0x26C) = func_2F4AD0(*(f32 *)(s0 + 0x26C), 0.41597018f);
}


void func_L22_0040DC40(s32 a0, s32 a1, s32 a2, f32 f12) {
    u8 buf[0x10];
    u8 buf2[0x10];
    f32 v = f12;

    func_2F3AB0(buf, (void *)a1, (void *)(a0 + 0x10));
    v = v * 0.016666668f;
    func_2F3D60(buf, buf, v);
    if (a2 != 0) {
        func_2F3A80(buf2, (void *)(a0 + 0x10), buf);
        func_3A2988(buf2, 7.2f);
        func_2F3AB0(buf, buf2, (void *)(a0 + 0x10));
        func_2F3D60(buf, buf, v);
    }
    func_32F330(a0, a1);
    func_3300E8(a0, buf);
}

/* The existing implementation is in L22_0040DD20-rc2.c. */

/* Spawns moby 0xF5D at pos moving along vel: copies both in, sets its colour and life
   from *scale, and builds its three-point trail (vel, vel + offset from the pos's
   reference point, and that again) with zeroed fourth components. */
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

TrailMoby0040DE00 *func_L22_0040DE00(float *pos, float *vel, float *scale)
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
        vars->life = 0x50;
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

extern u8 *D_L22_001AF314[] __attribute__((sda));
extern f32 D_L22_001B2A98 __attribute__((sda));
extern void func_0029FCC0(void *, s32, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);

void func_L22_0040DB20(u8 *a0, f32 *a1, f32 f12) {
    f32 vec1[4] __attribute__((aligned(16)));
    f32 vec2[4] __attribute__((aligned(16)));
    f32 scale = f12;

    if (D_L22_001AF314[0] != 0 && *(f32 *)(*(u8 **)(D_L22_001AF314[0] + 0x68) + 0x20) <= 0.0f) {
        return;
    }
    func_0029FCC0(a0, 2, vec1);
    if (scale == 0.0f) {
        scale = D_L22_001B2A98;
    }
    func_00282CF0(vec2, a1, vec1);
    func_00282F20(vec2, vec2, 0.6666667f);
    func_L22_0040DE00(vec1, vec2, &scale);
    func_0029FCC0(a0, 3, vec1);
    func_00282CF0(vec2, a1, vec1);
    func_00282F20(vec2, vec2, 0.6666667f);
    func_L22_0040DE00(vec1, vec2, &scale);
}

typedef struct { u8 pad[0x18]; u8 *target; } G1C00C0;
extern G1C00C0 D_001C00C0;
extern u8 *D_0018C0B0;
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_00282F20(void *, void *, f32);
extern void func_002A8C00(void *, void *, int, void *, f32);
extern void func_002A8E20(void *, void *);
extern void func_L22_0040E2B0(void *, s32, s32);

void func_L22_0040DF28(u8 *a0, u8 *a1) {
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
    func_L22_0040E2B0(a0 + 0x10, 10, 1);
    if (D_001C00C0.target == 0) {
        qcopy(buf, a0 + 0x10);
        func_L22_0040E2B0(buf, 15, 0);
    }
    a0[0x20] = 2;
}

/* func_L22_0040E098 uses the profile in L22_0040E098-g8.c. */

INCLUDE_ASM("asm/levels", func_L22_0040F1C0);

INCLUDE_ASM("asm/levels", func_L22_004135F8);

INCLUDE_ASM("asm/levels", func_L22_00413B70);


