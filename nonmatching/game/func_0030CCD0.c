/* func_0030CCD0: beam chain update, the small cousin of the F4 family's chain loop.
   Flags tried: -O2 -G8 -ffunction-sections -g -frac2-qcopy. 1888/1888 bytes, about 12 rows off.
   Left: f20 against f21 for the first float local; preheader and latch order of s1 and fp;
   f24 against s7 in the preheader; negu t0 against mul.s f13 in the second effect call.
   The 0x78/0x7C spill slots follow gcse's bucket count (retail fits 205, 211 and 221; this
   draft has 219). D_L00_ names are level 0's: rename to the boot's before landing. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct {
    Vector start, end;
    void *target;
    float length;
    int unknown28, timer, light, fade;
    short segment;
} BeamState;
typedef struct { char pad[0x10]; Vector pos; } Thing;
typedef struct { char pad[0x10]; float height; } ThingInfo;
typedef struct { char pad[0x68]; BeamState *vars; } Actor;

extern int D_001A79F0;
extern int D_L00_001A8F00;
extern BeamState D_L00_001C5890[], D_L00_001C58E0[];
typedef union { u8 b[0x2600]; s32 i[0x980]; void *ptr[0x980]; } Hero;
extern char D_00189E20[];
extern float D_L00_001AF2E4 __attribute__((sda));
extern float D_L00_001AF2F0 __attribute__((sda)), D_L00_001AF2F4 __attribute__((sda)), D_L00_001AF2F8 __attribute__((sda));
extern float D_L00_001AF2FC __attribute__((sda)), D_L00_001AF300 __attribute__((sda)), D_L00_001AF304 __attribute__((sda));
extern float D_L00_001AF308 __attribute__((sda)), D_L00_001AF30C __attribute__((sda)), D_L00_001AF310 __attribute__((sda));
extern float D_L00_001AF314 __attribute__((sda)), D_L00_001AF318 __attribute__((sda)), D_L00_001AF31C __attribute__((sda));
extern float D_L00_001AF320 __attribute__((sda)), D_L00_001AF334 __attribute__((sda)), D_L00_001AF338 __attribute__((sda));
extern float D_L00_001AF384 __attribute__((sda));
extern Vector D_L00_0023A210[], D_L00_0023A350[], D_L00_0023A340[], D_L00_0023A4E0[];
extern float D_L00_0023A490[], D_L00_0023A620[];
extern char D_L00_001A8F20[] MACRO_ADDR;

extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00283CE0(int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern ThingInfo *func_002AB1F0(void *);
extern float func_002ABB18(float);
extern void func_002ACEC0(void *, void *, void *, float);
extern void *func_002C2210(float, float, void *, int, unsigned int, int, int, void *, int, float);
extern float func_00282DF0(void *);
extern float func_00283180(float);
extern unsigned int func_0030CAA0(void);

void func_0030CCD0(Actor *actor)
{
    Vector goal, dir, side, step, last, delta, tip;
    BeamState *s = actor->vars;
    void *target, *other;
    ThingInfo *info;
    float wob, amp, d1, z, h, len, weight, sway, was, dist, t, angle, radius, wave;
    int i, spin;
    int off4, off16;
    float *p;

    if (D_001A79F0 == 1 && D_L00_001A8F00 == 2)
        s = D_L00_001C5890;
    if (D_001A79F0 == 0x14 && D_L00_001A8F00 == 2)
        s = D_L00_001C58E0;
    len = D_L00_001AF2E4 * 0.05f;
    D_L00_001AF2FC = func_00283B98(D_L00_001AF2FC, D_L00_001AF300);
    D_L00_001AF304 = func_00283BE0(D_L00_001AF304, D_L00_001AF308);
    D_L00_001AF318 = func_00283B98(D_L00_001AF318, D_L00_001AF31C);
    other = 0;
    if (s->target == 0)
        other = ((Hero *)D_00189E20)->ptr[0x5C0 / 4];
    if (other != 0) {
        if (s->target == 0)
            s->target = other;
    }
    target = s->target;
    if (target != 0) {
        info = 0;
        if (D_L00_001A8F00 != 2)
            info = func_002AB1F0(target);
        qcopy(&goal, &((Thing *)s->target)->pos);
        if (info != 0)
            goal.f[2] += info->height;
        else
            goal.f[2] += 0.2f;
        len = func_00282E48(s, &goal) * 0.05f;
    }
    s->segment = 0x14;
    func_00282CF0(&dir, &s->end, s);
    func_00282F20(&dir, &dir, 1.0f);
    if (s->target != 0) {
        func_00282DD8(&side, &dir, D_00189E20 + 0x2C0);
        func_002ACEC0(&dir, &dir, &side, 0.17453295f);
    }
    func_00282D30(&last, &dir, len);
    qcopy(&D_L00_0023A210[0], s);
    qcopy(&D_L00_0023A210[20], s);
    i = 1;
    do {
        float fi = i;
        off4 = i * 4;
        weight = func_00283CE0(i) * 0.05f;
        radius = D_L00_001AF2F4 + (D_L00_001AF2F8 - D_L00_001AF2F4) * weight;
        radius = radius * func_00283198(func_002ABB18(D_L00_001AF2FC + fi * D_L00_001AF2F0));
        radius = radius + func_002A78D8(D_L00_001AF334, D_L00_001AF338);
        p = (float *)(off4 + (char *)D_L00_0023A490);
        was = *p;
        *p = radius;
        D_L00_0023A210[i].f[2] -= was;
        func_00282CF0(&side, &D_L00_0023A210[i], &D_L00_0023A210[i - 1]);
        func_00282D08(&step, &side, &last, 0.85f);
        d1 = func_00282DF0(&step);
        if (d1 == 0.0f) {
            qcopy(&D_L00_0023A210[i], &D_L00_0023A210[i - 1]);
        } else {
            func_00282D30(&step, &step, len / d1);
            func_00282CC0(&D_L00_0023A210[i], &D_L00_0023A210[i - 1], &step);
            qcopy(&last, &step);
        }
        D_L00_0023A210[i].f[2] += radius;
        func_00282CF0(&side, &D_L00_0023A210[i], &D_L00_0023A210[i - 1]);
        if (s->target != 0) {
            func_00282CF0(&tip, &goal, &D_L00_0023A210[i]);
            dist = func_00282DF0(&tip);
            if (dist != 0.0f) {
                if (i == 0x13) {
                    sway = 0.5f;
                    len = dist;
                } else if (i >= 0x10) {
                    sway = 0.5f;
                    h = func_00283CE0(0x13 - i);
                    len = dist / h;
                } else {
                    sway = 0.1f;
                }
                func_00282D30(&tip, &tip, len / dist);
                func_00282D08(&last, &last, &tip, sway);
            }
        }
        angle = func_002ABB18(D_L00_001AF304 + (float)i * D_L00_001AF30C);
        wave = D_L00_001AF310 * func_00283198(func_002ABB18(D_L00_001AF318 + (float)i * D_L00_001AF320));
        qcopy(&D_L00_0023A210[i + 20], &D_L00_0023A210[i]);
        wave = wave * func_00283198(angle);
        D_L00_0023A620[i] = wave;
        D_L00_0023A210[i + 20].f[2] += wave;
        wave = func_00283B98(func_00283248(side.f[0], side.f[1]), 1.5707965f);
        {
            float r2 = D_L00_001AF314 * func_00283180(angle);
            delta.f[0] = func_00283180(wave) * r2;
            delta.f[1] = func_00283198(wave) * r2;
        }
        delta.f[2] = 0.0f;
        qcopy(&D_L00_0023A4E0[i], &delta);
        func_00282CC0(&D_L00_0023A210[i + 20], &D_L00_0023A210[i + 20], &delta);
        i++;
    } while (i < 0x14);
    qcopy(&s->end, D_L00_0023A340);
    {
        float pitch = func_002A78D8(0.52359885f, 1.0471977f);
        float yaw = func_002A7878(-0.52359885f, 1.0471977f);
        func_00282D30(&tip, &dir, D_L00_001AF384);
        func_002ACEC0(&tip, &tip, D_00189E20 + 0x740, yaw);
        func_002ACEC0(&tip, &tip, D_00189E20 + 0x750, pitch);
    }
    spin = func_002A7820(1, 8);
    if (func_002A77E0(2))
        spin = -spin;
    wave = func_002A7878(0.2f, 0.6f);
    func_002C2210(wave * 0.3f, wave, s, 0xF, func_0030CAA0() | 0x7F000000, 0, spin, &tip, 0, 0.0f);
    func_002C2210(wave * 0.15f, wave * 0.5f, s, 0xF, 0x307F7F7F, 0, -spin, &tip, 0, 0.0f);
    spin = func_002A7820(1, 8);
    if (func_002A77E0(2))
        spin = -spin;
    wave = func_002A7878(0.15f, 3.0f);
    func_002C2210(wave * 0.1f, wave, &s->end, 0xC, func_0030CAA0() | 0x7F000000, 0, spin, D_L00_001A8F20, 0, 0.0f);
}
