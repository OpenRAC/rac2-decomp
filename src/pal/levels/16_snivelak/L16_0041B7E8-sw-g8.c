#include "include_asm.h"

#include "common.h"
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define B(p, o) (*(unsigned char *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))
#define U(p, o) (*(unsigned short *)((char *)(p) + (o)))
typedef struct {
    char pre[0x80];
    float x, y;
    char pad[0x154];
    short timer;
    char pad2[0x15e];
    char *target;
    int active;
    char pad3[0x14ec];
    char *owner;
    char pad4[0xa60];
    int mode;
    char pad5[0x234];
    int flag;
} Global;
extern Global D_00189E20;
extern char D_001B9B00[];
typedef struct {
    char pre[0x74];
    unsigned char active;
    char pad[0x13];
    char *owner;
} Effect;
extern char D_00188660[];
extern int D_L16_001B1704, D_00138324 __attribute__((nosda));
extern unsigned short D_001941DC __attribute__((nosda)), D_0018CDF0 __attribute__((nosda));
extern char *D_L16_001B2B1C;
extern int D_L16_001B16C0, D_L16_001A8FB4;
extern int D_L16_001A8FB0 __attribute__((sda));
extern int D_L16_001B1A80 __attribute__((sda));
extern float D_L16_001B1A90 __attribute__((sda)), D_L16_001B1A94 __attribute__((sda));
extern void func_0029F338(char *), func_002B0178(char *, char *, char *), func_002A7750(char *, int, int);
extern void func_PAL_00289730(int, int), func_00283098(char *, char *, char *), func_00282CC0(char *, char *, char *);
extern int func_002B3868(char *), func_002E5CF8(int, int, char *);
extern void func_PAL_L00_002B9CD8(char *, char *, int, int), func_00335438(char *, char *, int, int, int);
extern float func_00282C48(float), func_00282E80(char *, char *), func_00283248(float, float), func_00283B98(float, float), func_00283BE0(float, float), func_00283C80(float, float);
extern void func_002AA548(float *, float *, float, float, float, float);
extern void func_002AAA00(float *, float *, float, float, float, float, int);
extern void func_002E59F8(int), func_L16_00416E30(char *), func_PAL_L16_0041C1F0(char *), func_L16_00416EC8(char *), func_PAL_L16_0041C470(char *), func_L16_00416E88(char *), func_PAL_L16_0041BF40(char *);
extern void func_00273318(char *, unsigned, int, int, int, int, float, float, float);
extern char *func_002A9640(char *, int, int);
extern void func_002AA2E8(float *, float, float), func_PAL_L00_002A4D58(int), func_PAL_L00_0030E648(int);
extern int func_00283CF0(float);

void func_PAL_L16_0041B7E8(char *self) {
    char buf[16];
    char *st = P(self, 0x68), *hit;
    float angle;
    int state;
    Global *g;
    switch (B(self, 0x20)) {
    case 0:
        if (I(st, 0x60) == -1) {
            func_0029F338(self);
            return;
        }
        func_002B0178(self + 0x10, self, self + 0x10);
        U(self, 0x34) |= 0x4000;
        qcopy(st + 0x70, self + 0x10);
        F(st, 0x7c) = F(self, 0xf8);
        F(st, 0x94) = 4.0f;
        func_002A7750(self, 1, -1);
        if (D_L16_001B1704 >= 2 && D_001941DC < 3)
            func_PAL_00289730(0xa0b, 0x62);
        break;
    case 1:
    case 4:
        if (func_002B3868(self))
            func_002E5CF8(3, 0, self);
        state = B(self, 0x20);
        if ((state == 4 && D_00189E20.target != self) || ((g = &D_00189E20), H(g, 0x34e) >= 17))
            B(self, 0x20) = 1;
        else if (state == 1 && g->target == self && g->active) {
            func_00283098(buf, (char *)&D_L16_001B1A80, self + 0xc0);
            func_00282CC0(buf, buf, self + 0x10);
            func_PAL_L00_002B9CD8(buf, self + 0xf0, 0x31, 0);
            D_00189E20.owner = self;
            func_00335438(D_001B9B00, D_001B9B00 + 0x10, 3, 60, 0);
            D_0018CDF0 = 0xffff;
            D_L16_001B16C0 = (int)self;
            func_002A7750(self, 2, -1);
            break;
        }
        if (func_00282C48(F(self, 0x18) - F(st, 0x78) + D_L16_001B1A90) > 0.01f)
            func_002AA548((float *)(self + 0x18), (float *)(st + 0x98), F(st, 0x78) - D_L16_001B1A90, 0.00080000004f, 0.00080000004f, 0.040000003f);
        if (func_00282E80(self + 0x10, (char *)&D_00189E20.x) > D_L16_001B1A94) {
            angle = func_00283B98(func_00283248(D_00189E20.x - F(self, 0x10), D_00189E20.y - F(self, 0x14)), 3.1415927410125732f);
            func_002AAA00((float *)(self + 0xf8), (float *)(st + 0x9c), angle, 0.0025132746f, 0.0025132746f, 0.12566373f, 0);
        }
        break;
    case 2:
        if (func_002B3868(self)) {
            func_002E5CF8(3, 0, self);
            I(st, 0x90) = 0;
        }
        angle = func_00283248(F((char *)((I(st, 0x64) << 8) + (int)D_L16_001B2B1C), 0x10) - F(self, 0x10), F((char *)((I(st, 0x64) << 8) + (int)D_L16_001B2B1C), 0x14) - F(self, 0x14));
        func_002AA548((float *)(self + 0x18), (float *)(st + 0x98), F(st, 0x78), 0.0024f, 0.0024f, 0.120000005f);
        func_002AAA00((float *)(self + 0xf8), (float *)(st + 0x9c), angle, 0.0016755164f, 0.0016755164f, 0.12566373f, 0);
        if (func_00282C48(func_00283BE0(F(self, 0xf8), angle)) < 0.174532949924469f) {
            if (I(st, 0xa4) != -1) {
                Effect *effect = (Effect *)(I(st, 0xa4) * 0x70 + (int)D_00188660);
                if (effect->owner == self && effect->active)
                    func_002E59F8(I(st, 0xa4));
            }
            I(st, 0xa4) = -1;
        } else {
            Effect *effect = (Effect *)(I(st, 0xa4) * 0x70 + (int)D_00188660);
            if (effect->owner != self || !effect->active) I(st, 0xa4) =
                func_002E5CF8(4, 4, self);
        }
        if (func_00282C48(F(self, 0x18) - F(st, 0x78)) <= F(st, 0x98) && func_00283C80(F(self, 0xf8), angle) <= 0.0872664749622345f)
            func_002A7750(self, 3, -1);
        D_0018CDF0 = 0xffff;
        func_L16_00416E30(self);
        func_PAL_L16_0041C1F0(self);
        func_L16_00416EC8(self);
        break;
    case 5:
    case 6:
        break;
    case 3:
        func_00273318(self, 0x600fff0f, 0, 0x26, -1, 4, 1.0f, 0.0f, 90.0f);
        if ((D_00138324 & 16) || D_00189E20.mode != 0x31) {
            func_L16_00416E88(self);
            func_002A7750(self, 4, -1);
            if (I(st, 0xa4) != -1) {
                Effect *effect = (Effect *)(I(st, 0xa4) * 0x70 + (int)D_00188660);
                if (effect->owner == self && effect->active)
                    func_002E59F8(I(st, 0xa4));
            }
            I(st, 0xa4) = -1;
            D_L16_001A8FB4 = 2;
            D_L16_001A8FB0 = 25;
        } else {
            func_PAL_L16_0041C470(self);
            func_PAL_L16_0041C1F0(self);
            func_L16_00416EC8(self);
            func_L16_00416E30(self);
        }
        break;
    }
    hit = func_002A9640(self, 1, 0);
    if (!hit)
        return;
    if (P(hit, 0x20) && H(P(hit, 0x20), 0xaa) == 0x12be)
        func_002AA2E8((float *)(st + 0x94), 0.0f, 1.0f);
    if (P(hit, 0x20) && (H(P(hit, 0x20), 0xaa) == 0xf79 || H(P(hit, 0x20), 0xaa) == 0x9b0 || F(st, 0x94) == 0.0f)) {
        U(self, 0x34) = (U(self, 0x34) | 0x41) & 0xefff;
        I(self, 0x98) = 0;
        if ((unsigned)(B(self, 0x20) - 2) < 2)
            func_L16_00416E88(self);
        func_002A7750(self, 6, -1);
        B(self, 0xa8) = 0xff;
        func_PAL_L16_0041BF40(self);
    } else if ((!P(hit, 0x20) || H(P(hit, 0x20), 0xaa) != 0xea7) && B(self, 0x20) == 3 && D_00189E20.mode == 0x31 && D_00189E20.timer == 0) {
        func_PAL_L00_002A4D58(func_00283CF0(F(hit, 0x2c)));
        if (D_00189E20.flag == 0) {
            func_L16_00416E88(self);
            func_002A7750(self, 4, -1);
        } else {
            D_00189E20.timer = 50;
        }
        func_PAL_L00_0030E648(300);
    }
    B(self, 0xa8) = 0xff;
}
