#include "include_asm.h"

#include "common.h"
#define B(p, o) (*(unsigned char *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))
#define U(p, o) (*(unsigned short *)((char *)(p) + (o)))
#define W(p, o) (*(int *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
extern char D_L12_001B9E00[];
extern int func_00283CF0(float);
extern float func_00282E48(void *, void *);
extern void func_0029F338(void *);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002A93B0(void *);
extern int func_PAL_002B1A50(void *, void *, int);
extern int func_002B3BA8(void *, int, int, int, float, float);
extern int func_00282978(void *);
extern float func_00282E80(void *, void *);
extern float func_00283CE0(int);
extern int func_L01_0031BC68(int, int, float);
extern void func_PAL_002B14F8(void *, void *, int, int, float);
extern void func_0026FEB8(const char *, ...);
extern int func_002B3868(void *);
extern int func_002B3890(void *);
extern int func_002B38B8(void *);
extern int func_002761F8(void *, void *, int, int, int);
extern char *D_L12_001FEAC0[];
extern char D_L12_001B0B70[];
extern unsigned short D_L12_001B0B00 __attribute__((sda));
extern float D_L12_001B0B68 __attribute__((sda));
extern float D_L12_001B0B64 __attribute__((sda));
extern int D_L12_001B29C8 __attribute__((sda));
extern char *D_L12_001C0258 NOT_SDA;
extern char *D_0018C0B0 NOT_SDA;

void func_PAL_L12_003E7E08(char *obj) {
    char *s = P(obj, 0x68);
    unsigned char oldstate, oldanim;
    int result;
    float angle;
    float pos[4];
    if (!B(obj, 0x20)) {
        H(P(obj, 0x24), 0x46) = 5;
        U(obj, 0x34) |= 0x1000;
        F(s, 0x30) = 2.25f;
        B(s, 0x48) = func_00283CF0(20.0f);
        B(s, 0x4A) = func_00283CF0(24.0f);
        B(s, 0x70) = 17;
        W(s, 0xA8) = 3;
        B(s, 0x71) = 4;
        B(s, 0x72) = 5;
        B(s, 0x76) = 6;
        F(s, 0x7C) = 0.20000002f;
        F(s, 0x80) = 0.080000006f;
        F(s, 0x88) = 0.010000001f;
        F(s, 0x8C) = F(s, 0x84) = 0.006f;
        F(s, 0x94) = F(s, 0x90) = 0.5f;
        F(s, 0x9C) = 0.4f;
        B(s, 0xCD) = 26;
        B(s, 0xCE) = 8;
        B(s, 0xCF) = B(s, 0xCC) = 11;
        B(s, 0xD2) = 10;
        B(s, 0xD3) = 17;
        B(s, 0xD5) = 1;
        if (W(s, 0x158) == -1) {
            func_0029F338(obj);
            return;
        }
        W(s, 0x1A8) |= 0x15;
        B(s, 0x28) = 3;
        F(s, 0x1A4) = 0.3f;
        F(s, 0x170) = 1.25f;
        F(s, 0x17C) = F(s, 0x178) = F(s, 0x174) = 2.0f;
        F(s, 0x180) = 3.1415929794311523f;
        F(s, 0x1A0) = 0.523598849773407f;
        F(s, 0x19C) = 0.008f;
        B(s, 0xD6) = 1;
        func_002A7750(obj, 5, 0);
        if (B(obj, 0x43))
            func_PAL_002A7E68(obj, 0, 0, 0);
        W(s, 0x154) = W(s, 0x150);
        if (W(s, 0x164) == -1)
            qcopy(obj + 0x10, D_L12_001FEAC0[W(s, 0x158)] + 0x10);
        else
            qcopy(obj + 0x10, D_L12_001FEAC0[W(s, 0x164)] + 0x10);
        if (W(s, 0x164) != -1)
            func_002A7750(obj, 2, 7);
        if (P(s, 0x294))
            W(P(s, 0x294), 0) = -1;
    }
    if (B(obj, 0x31) && func_00282E48(obj + 0x10, D_L12_001B9E00) < 24.0f) {
        func_002A93B0(obj);
        B(obj, 0x6F) = 22;
    }
    if (W(s, 0x2A0) && func_002B38B8(obj))
        func_002A7750(obj, 24, 4);
    oldstate = B(obj, 0x20);
    oldanim = B(obj, 0x95);
    result = func_PAL_002B1A50(obj, s + 0x60, 0);
    if (result) {
        if (result == 4) {
            func_0026FEB8(D_L12_001B0B70);
            W(s, 0x278) = 5;
        } else
            W(s, 0x278) = 1;
        B(obj, 0x20) = oldstate;
        B(obj, 0x95) = oldanim;
        func_002B3868(obj);
        func_002B3890(obj);
        H(s, 0x26) = D_L12_001B0B00;
        H(s, 0x274) = 125;
    }
    if (func_00282978(s + 0x274)) {
        if (W(s, 0x278) != 1)
            W(s, 0x278) = 0;
        else
            H(s, 0x274) = 42;
    }
    H(s, 0x276) = func_002B3BA8(obj, W(s, 0x150), 0, 0, 6.0f, 0.0f);
    W(s, 0x270) = W(s, 0x140);
    if (P(s, 0x140) && func_00282E80(P(s, 0x140) + 0x10, obj + 0x10) < 16.0f) {
        qcopy(pos, obj + 0x10);
        pos[2] += D_L12_001B0B68;
        if (!func_002761F8(pos, s + 0x130, 16, 0, 0) || D_L12_001C0258 == D_0018C0B0) {
            if (H(s, 0x276) != 1)
                H(s, 0x276) = 1;
        }
    }
    if (B(obj, 0x31)) {
        angle = func_00283CE0(D_L12_001B29C8 % 50);
        angle = angle * 6.2831854820251465f / func_00283CE0(50) - 3.1415927410125732f;
        W(obj, 0x78) = func_L01_0031BC68(0x80808080, 0x80303030, angle);
    }
    func_PAL_002B14F8(obj, s + 0x2B0, 1, 1, D_L12_001B0B64);
}
