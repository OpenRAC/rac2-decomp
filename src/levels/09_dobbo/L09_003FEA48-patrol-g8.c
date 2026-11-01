#include "common.h"

/* The gate suppresses updates between its two height bands. */
typedef struct {
    int state;
    char pad04[8];
    int active;
    char pad10[0x18];
    float low;
    char pad2c[0xC];
    float high;
} DobboUpdateGate;
extern DobboUpdateGate D_L09_001C9F80;
extern char D_00188660[];
extern char D_00189E20[];
extern char D_L09_001A8F20[] __attribute__((sda));
extern char *D_L09_001B11B4 __attribute__((sda));
extern char *D_L09_001B11BC __attribute__((sda));
extern int D_L09_001B2388[] __attribute__((sda));
extern char D_L09_001BFE60[];
extern char *D_L09_001C3EC0[];
extern char *D_L09_001FE6C0[];
extern void func_L09_003FE670(char *);
extern void func_L09_003FE2D8(char *);
extern void func_L09_003FE4D0(char *);
extern void func_L09_003FEA48(char *);
extern void func_L09_003FE918(char *);
extern void func_L09_003FE978(char *);
extern void func_L09_003FEAE8(char *);
extern void func_L09_003FECF0(char *);
extern int func_L09_003FE0C0(char *, int);
extern void func_L09_003FDC58(char *);
extern void func_L09_003FDD80(char *);
extern void func_L09_003FDED8(char *);
extern void func_L09_003FDFF0(char *);
extern void func_L08_002F2D10(void (*)(char *), char *);
extern void func_002AEC48(void *, void *, int, float, float);
extern float func_00283B98(float, float);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_002E59F8(int);
extern int func_002E5CF8(void *, int, void *);
extern void func_00282D08(void *, void *, void *, float);
extern int func_00277F48(void *, int, int, int, float);
extern int func_002761F8(void *, void *, int, int, int);
extern float func_00283CE0(int);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_002AA3A8(void *, float, void *, float, float, float);
extern int func_002C9218(int, void *, void *, float);
extern int func_L00_00341FA8(void *, void *, void *, void *, void *, int, float, float, float);
extern int func_00283DB8(void *, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_002A78D8(float, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_002B0A68(void *, float, int, float, float, void *, float, int);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282C48(float);
extern int func_00282978(void *);
extern int func_00277258(void *, int, void *, float);
extern void func_002A6C58(void *, int, int);
extern void func_0029F338(void *);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void *func_002BD8B0(void *, void *, int, int, int, int, float);
extern char *func_002BDCE8(void *, float, float, float, int, void *, float, int, int);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))

/* State 1 patrols and picks a target (hero or classes 0xCB, 0x76C, 0xEB0), state 2 falls or lands,
 * state 3 chases, state 4 starts breaking up, state 6 is falling debris that vanishes out of
 * bounds and explodes on timeout or contact. */
void func_L09_003FEF00(char *obj)
{
    float a[4], b[4], previous[4];
    char *data = P(obj, 0x68);
    if (D_L09_001C9F80.active) {
        if (F(obj, 0x18) < D_L09_001C9F80.low && D_L09_001C9F80.state == 1) return;
        if (D_L09_001C9F80.low < F(obj, 0x18) && D_L09_001C9F80.state == 0) return;
        if (D_L09_001C9F80.active == 2) {
            if (D_L09_001C9F80.high < F(obj, 0x18) && D_L09_001C9F80.state == 1) return;
            if (F(obj, 0x18) < D_L09_001C9F80.high && D_L09_001C9F80.state == 2) return;
        }
    }
    if (B(obj, 0x20) == 0) func_L09_003FE670(obj);
    if (B(data, 0x2E) == 2) {
        I(data, 0x42C) = 0;
        func_002A6C58(obj, 0, 3);
        func_0029F338(obj);
        return;
    }
    {
        if (B(obj, 0x20) == 5) {
            func_L09_003FE2D8(obj);
            func_L08_002F2D10(func_L09_003FE4D0, obj);
            return;
        }
        I(data, 0x42C) = 0;
        func_L09_003FEA48(obj);
        if ((unsigned)(B(obj, 0x20) - 1) < 3) H(data, 0x420) = 0;
        switch (B(obj, 0x20)) {
        case 0: goto tail;
        case 1: {
            int live, count, i;
            I(obj, 0x78) = 0xFFAAAAAA;
            {
                char *entry = (char *)((int)D_00188660 + I(data, 0x3F0) * 0x70);
                if (P(entry, 0x88) != obj || !B(entry, 0x74))
                    I(data, 0x3F0) = func_002E5CF8(D_L09_001B11B4, 4, obj);
            }
            if (B(data, 0x440)) {
                B(data, 0x440) = 0;
                func_002A7750(obj, 3, -1);
                {
                    int sound = I(data, 0x3F0);
                    if (sound != -1) {
                        {
                            char *entry = (char *)((int)D_00188660 + sound * 0x70);
                            if (P(entry, 0x88) == obj && B(entry, 0x74)) func_002E59F8(sound);
                        }
                    }
                }
                I(data, 0x3F0) = -1;
                {
                    char *entry = (char *)((int)D_00188660 + I(data, 0x3F0) * 0x70);
                    if (P(entry, 0x88) != obj || !B(entry, 0x74))
                        I(data, 0x3F0) = func_002E5CF8(D_L09_001B11BC, 4, obj);
                }
                H(data, 0x412) = 600;
            }
            H(data, 0x422) = 0;
            H(data, 0x420) = 1;
            live = func_L09_003FE0C0(obj, 1);
            func_L09_003FDC58(obj);
            func_L09_003FDD80(obj);
            func_L09_003FDED8(obj);
            if (live) {
                func_00282D08(a, data + 0x330, data + 0x370, 0.5f);
                qcopy(b, data + 0x330);
                count = func_00277F48(a, 0, 0, 0, F(data, 0x434) * 0.48f);
                if (!count) count = func_00277F48(b, 0, 0, 0, F(data, 0x434) * 0.9f);
                if (count) {
                    for (i = 0; i < count; i++) {
                        char *candidate = D_L09_001C3EC0[i];
                        char *hero = D_00189E20;
                        if (candidate != P(hero, 0x2290)) {
                            int first = 0xCB;
                            int kind;
                            if (!candidate) continue;
                            kind = H(candidate, 0xAA);
                            if (kind != first && kind != 0x76C && kind != 0xEB0) continue;
                        }
                        {
                            func_L09_003FE978(obj);
                            candidate = D_L09_001C3EC0[i];
                            P(data, 0x3AC) = candidate;
                            I(data, 0x44C) = H(candidate, 0xAA);
                            func_002A7750(obj, 3, -1);
                            {
                                int sound = I(data, 0x3F0);
                                if (sound != -1) {
                                    {
                                        char *entry = (char *)((int)D_00188660 + sound * 0x70);
                                        if (P(entry, 0x88) == obj && B(entry, 0x74)) func_002E59F8(sound);
                                    }
                                }
                            }
                            I(data, 0x3F0) = -1;
                            {
                                char *entry = (char *)((int)D_00188660 + I(data, 0x3F0) * 0x70);
                                if (P(entry, 0x88) != obj || !B(entry, 0x74))
                                    I(data, 0x3F0) = func_002E5CF8(D_L09_001B11BC, 4, obj);
                            }
                            H(data, 0x412) = 600;
                            if (D_L09_001C3EC0[i] != P(hero, 0x2290)) break;
                        }
                    }
                }
            }
            break;
        }
        case 2:
            if (F(data, 0x20) <= 0.0f) {
                int live;

                if (B(obj, 0x43)) func_002A7470(obj, 0, 0, 10);
                live = I(data, 0x3F0);
                if (live != -1) {
                    {
                        char *entry = (char *)((int)D_00188660 + live * 0x70);
                        if (P(entry, 0x88) == obj && B(entry, 0x74)) func_002E59F8(live);
                    }
                }
                I(data, 0x3F0) = -1;
                func_002A7750(obj, 4, -1);
            } else if (B(obj, 0x60) & 2) {
                if (B(obj, 0x43)) func_002A7470(obj, 0, 0, 10);
                H(data, 0x412) = 600;
                func_002A7750(obj, 3, -1);
            }
            break;
        case 3: {
            char *target;
            I(obj, 0x78) = 0xFF00FFFF;
            target = P(data, 0x3AC);
            if (target && H(target, 0xAA) == I(data, 0x44C) &&
                B(target, 0x20) != 0xFE && B(target, 0x20) != 0xFD) {
                float phase, angle1, angle2, step1, step2;
                H(data, 0x420) = 1;
                H(data, 0x422) = 1;
                func_L09_003FE0C0(obj, 1);
                qcopy(a, P(data, 0x3AC) + 0x10);
                a[2] += 0.5f;
                qcopy(b, a);
                b[2] -= 4.0f;
                if (func_002761F8(a, b, 0x12, 0, 0)) qcopy(a, D_L09_001BFE60);
                else a[2] -= 0.5f;
                qcopy(previous, data + 0x390);
                phase = func_00283CE0(D_L09_001B2388[0]) + H(obj, 0xB2) * 36;
                angle1 = func_002ABB18(phase * 0.025f);
                angle2 = func_002ABB18(phase * 0.016666668f);
                step1 = func_00283198(angle1) + 1.5f;
                step2 = func_00283198(angle2) + 1.5f;
                a[0] += func_00283198(angle2);
                a[1] += func_00283180(angle2);
                func_002AA3A8(data + 0x390, a[0], data + 0x3A0, step1 * 0.003f, 0.2f, 0.0f);
                func_002AA3A8(data + 0x394, a[1], data + 0x3A4, step2 * 0.003f, 0.2f, 0.0f);
                if (I(data, 0x444) != -1) {
                    if (func_002C9218(I(data, 0x444), data + 0x390, data + 0x390, F(data, 0x434) * 1.3f)) {
                        F(data, 0x3A0) = F(data, 0x390) - previous[0];
                        F(data, 0x3A4) = F(data, 0x394) - previous[1];
                        B(data, 0x441) = 1;
                    } else B(data, 0x441) = 0;
                }
            } else {
                char *replacement = P(data, 0x150);
                P(data, 0x3AC) = replacement;
                if (replacement && B(replacement, 0x20) != 0xFE && B(replacement, 0x20) != 0xFD)
                    I(data, 0x44C) = H(replacement, 0xAA);
            }
            func_L00_00341FA8(D_L09_001FE6C0[I(data, 0x314)], data + 0x390, a,
                             data + 0x324, data + 0x3EC, 1, 20.0f, 5.0f, 0.0f);
            func_L09_003FDD80(obj);
            qcopy(a, obj + 0x10);
            a[3] = 4.0f;
            if (func_00283DB8(a, func_00283CE0(H(obj, 0x32))) >= 0) {
                float *dst;
                func_0029FCC0(obj, 8, b);
                dst = (float *)(data + 0x3F4);
                dst[0] = b[0];
                dst[1] = b[1];
                dst[2] = b[2];
                I(data, 0x42C) |= 8;
                func_L09_003FDED8(obj);
            }
            if (I(data, 0x154) != 1) {
                if (H(data, 0x412) == 0) {
                    int live;

                    func_002A7750(obj, 1, -1);
                    live = I(data, 0x3F0);
                    if (live != -1) {
                        {
                            char *entry = (char *)((int)D_00188660 + live * 0x70);
                            if (P(entry, 0x88) == obj && B(entry, 0x74)) func_002E59F8(live);
                        }
                    }
                    I(data, 0x3F0) = -1;
                    {
                        char *entry = (char *)((int)D_00188660 + I(data, 0x3F0) * 0x70);
                        if (P(entry, 0x88) != obj || !B(entry, 0x74))
                            I(data, 0x3F0) = func_002E5CF8(D_L09_001B11B4, 4, obj);
                    }
                }
            }
            if (I(data, 0x154) == 1) {
                if (P(data, 0x3AC)) P(data, 0x3AC) = P(data, 0x150);
                B(data, 0x42B) = 1;
            }
            break;
        }
        case 4: {
            int live;

            H(data, 0x410) = 180;
            func_L09_003FE978(obj);
            live = I(data, 0x3F0);
            if (live != -1) {
                {
                    char *entry = (char *)((int)D_00188660 + live * 0x70);
                    if (P(entry, 0x88) == obj && B(entry, 0x74)) func_002E59F8(live);
                }
            }
            I(data, 0x3F0) = -1;
            func_002ABBB8(obj, data + 0x400, obj + 0x10, 0.0f, 0.0f, 5, 2, 4,
                         4.0f, 2.0f, 9.0f, 1.0f, 1, 15.0f, 1, 5, -1, 0, 0x810001);
            func_00282CF0(a, obj + 0x10, (D_00189E20 + 0x80));
            a[2] = 0.0f;
            func_00282F20(a, a, func_002A7878(0.075f, 0.2f));
            func_00282DD8(b, D_00189E20 + 0x2C0, a);
            func_002ACEC0(data + 0x400, a, D_00189E20 + 0x2C0, func_002A78D8(0.698131799697876f, 1.2217305898666382f));
            F(data, 0x408) = func_002A7878(0.1f, 0.2f);
            func_002B0A68(obj, 3.0f, 0x7F, 6.0f, 3.0f, D_L09_001A8F20, 6.0f, 0xFF);
            F(obj, 0x2C) *= 0.1f;
            F(data, 0x280) = 10.0f;
            F(data, 0x414) = func_002A78D8(0.0f, 0.0872664749622345f);
            F(data, 0x418) = func_002A78D8(0.0f, 0.0872664749622345f);
            F(data, 0x41C) = func_002A78D8(0.0f, 0.0872664749622345f);
            F(obj, 0xF0) = func_00283B98(F(obj, 0xF0), func_002A78D8(0.0f, 0.78539824f));
            F(obj, 0xF4) = func_00283B98(F(obj, 0xF4), func_002A78D8(0.0f, 0.78539824f));
            func_002A7750(obj, 6, -1);
            func_L09_003FDFF0(obj);
            return;
        }
        case 5: goto tail;
        case 6: {
            int i;
            char *vel = data + 0x400;
            func_00282CC0(obj + 0x10, obj + 0x10, vel);
            if (func_00282C48(F(data, 0x400)) > 0.05f) F(data, 0x400) *= 0.97f;
            if (func_00282C48(F(data, 0x404)) > 0.05f) F(data, 0x404) *= 0.97f;
            if (F(data, 0x408) > 0.0f) F(data, 0x408) *= 0.97f;
            F(data, 0x408) -= 0.003f;
            F(obj, 0xF8) = func_00283B98(F(obj, 0xF8), F(data, 0x41C));
            F(data, 0x280) = 10.0f;
            if (F(obj, 0x10) < 2.0f || F(obj, 0x10) > 1021.0f ||
                F(obj, 0x14) < 2.0f || F(obj, 0x14) > 1021.0f ||
                F(obj, 0x18) < 2.0f || F(obj, 0x18) > 1021.0f) {
                func_0029F338(obj);
                return;
            }
            if (func_00282978(data + 0x410) || func_00277258(obj + 0x10, 0, obj, 0.5f)) {
                func_002ABBB8(obj, data + 0x400, obj + 0x10, 2.0f, 1.0f, 5, 2, 4,
                             2.0f, 1.0f, 9.0f, 1.0f, 1, 15.0f, 1, 5, -1, 0, 0x810001);
                func_002A6C58(obj, 0, 3);
                func_0029F338(obj);
                return;
            }
            func_002BD8B0(obj + 0x10, D_L09_001A8F20, 0x4F007FFF, 0x1FFFFFFF,
                         func_002A7820(10, 20), 1, 60000.0f);
            for (i = -2; i < 0; i++) {
                int spin = func_002A77E0(6);
                float energy;
                int colour, tint;
                char *particle;
                if (func_002A77E0(2)) spin = -spin;
                energy = func_002A7878(40000.0f, 100000.0f);
                colour = func_002A7820(0x30, 0xFF);
                tint = (colour << 8) | 0x60000000;
                colour = colour | ((colour << 16) | tint);
                particle = func_002BDCE8(obj + 0x10, 0.025f, 1.0f, 1.0f, spin, D_L09_001A8F20,
                                       energy, colour, 0);
                if (particle) {
                    char *extra = particle + 0x20;
                    B(particle, 3) = 0x44;
                    H(particle, 0xA) = 60;
                    I(extra, 4) = 2;
                    B(extra, 0xA) = 0x60;
                    B(extra, 0xB) = B(particle, 0xA);
                }
            }
            func_L09_003FDFF0(obj);
            return;
        }
        }
    }
tail:
    func_L09_003FE918(obj);
    func_002AEC48(obj, data + 0x210, 0, 0.15f, 0.3f);
    func_L09_003FEAE8(obj);
    F(data, 0x2F8) = func_00283B98(F(data, 0x2D8), 0.05235988646745682f);
    func_002AEC48(obj, data + 0x290, 11, 0.15f, 0.3f);
    func_L09_003FECF0(obj);
}
