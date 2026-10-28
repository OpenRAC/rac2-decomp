#include "common.h"

/* Small-data unit: the bodies whose state lives at $gp-relative offsets. */

extern void func_00281EB8(void *a0, void *a1, void *a2, float f12, float f13, float f14,
                          int a3);

extern float func_002A7940(void);

extern int func_002A7820(int a0, int a1);

extern float func_002A7878(float a, float b);

extern void func_L11_00458DF0(char *a0, void *a1, void *a2, int a3, int t0, float f12,
                              float f13);

extern void func_00282F20(char *a0, void *a1, float f12);

extern void func_002AB668(void *a0, void *a1, float f12);

extern void func_00282D30(char *a0, void *a1, float f12);

extern void func_002ACDE8(void *a0, void *a1, void *a2);

extern void func_00282CC0(void *a0, void *a1, void *a2);

extern float func_00283BE0(float a, float b);

extern void func_L00_002E6CF0(void *a0, void *a1);

extern void func_L11_00459E48(char *p);

extern void func_L11_00459EA0(char *p);

extern void func_L11_0045A8C0(char *p, float *v);

extern void func_00282D08(float *out, char *a, char *b, float k);

extern float func_00282E80(char *p, float *v);

extern float func_00283248(float a, float b);

extern void func_00283410(float *matrix, float *quat);

extern void func_00280B90(char *pkt, float *matrix, int mode);

extern int func_001163B0(void);

extern int D_L11_001B2014 __attribute__((sda));

extern int D_L11_001B2020 __attribute__((sda));

/* The vector the aim helpers read, at 0x001BA780 in joba. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L11AimVector;

extern L11AimVector D_L11_001BA780;

extern void *D_L11_001B1DB4 __attribute__((sda));

extern void *D_L11_001B1DB8 __attribute__((sda));

extern float D_L11_001B1DBC __attribute__((sda));

extern void *D_L11_001B1FBC __attribute__((sda));

extern void *D_L11_001B1FC0 __attribute__((sda));

extern float D_L11_001B1FC8 __attribute__((sda));

extern float D_L11_001B1FCC __attribute__((sda));

extern float D_L11_001B1FFC __attribute__((sda));

/* The level's script gate, read through $gp. */
extern s32 D_L11_001A8FF4 __attribute__((sda));

/* The shared table of the level's live projectiles. */
extern char D_00188660[];

/* The aiming target the level's spot checks measure against. */
extern char D_L11_001BA8C0[];

extern int func_00283CF0(float);

extern void func_002A7750(void *, int, int);

extern void func_002B60B0(void *, float, float, float, float);

extern void func_002A04B8(void *, void *, void *, void *);

extern void func_002A93B0(void *);

extern float func_002A96A0(void *, void *);

extern void *func_002A9640(void *, unsigned int, int);

extern float func_00282E48(void *, void *);

extern int func_002E59B0(void *, int);

extern void func_002E59F8(int);

extern int func_002E5CF8(int, int, char *);

extern void func_00283698(void *, void *);

extern void func_002AFFD8(void *, void *, int);

extern void func_002AB800(void *, void *);

extern void func_002A7A00(void *, float, float);

extern void func_00282CF0(void *, void *, void *);

extern float func_00282DB0(void *, void *);

extern float func_00282DF0(void *);


extern float func_00283B98(float, float);

extern float func_L00_002EE290(void *);

extern void func_L11_00454B60(char *);

extern void func_L11_00454DD8(char *);

extern u8 *func_L11_004417E8(u8 *);

extern int func_L11_004461C0(u8 *, u8 *);


/* Rebuilds the state's offset block from its rotation and installs the next handler. */
void func_L11_00459D48(char *p)
{
    char *q = *(char **)(p + 0x68);
    float v[4];

    func_00282F20((char *)v, q + 0x40, 1.0f);
    func_002AB668(v, v, *(float *)(q + 0x30));
    func_00282D30(q + 0x10, q, *(float *)(q + 0x60));
    func_002ACDE8(q + 0x10, q + 0x10, v);
    *(float *)(q + 0x20) = -*(float *)(q + 0x10);
    *(float *)(q + 0x24) = -*(float *)(q + 0x14);
    *(float *)(q + 0x28) = -*(float *)(q + 0x18);
    func_00282CC0(q + 0x10, p + 0x10, q + 0x10);
    func_00282CC0(q + 0x20, p + 0x10, q + 0x20);
    *(float *)(q + 0x30) = func_00283BE0(*(float *)(q + 0x30),
                                         D_L11_001B1FFC * 0.000290888245f);
    func_L00_002E6CF0(func_L11_00459E48, p);
}

/* Aims the object's stage at the level's aim vector and dispatches the resulting packet. */
void func_L11_0045A578(char *p)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float v[4];
    char *q = *(char **)(p + 0x68);
    float s;
    int r;
    int top;

    func_L11_00459EA0(pkt);
    func_00282D08(v, q + 0x10, q + 0x20, func_002A7878(0.0f, 1.0f));

    v[0] += func_002A7878(-0.1f, 0.1f) * *(float *)(q + 0x60);
    v[1] += func_002A7878(-0.1f, 0.1f) * *(float *)(q + 0x60);
    v[2] += func_002A7878(-0.1f, 0.1f) * *(float *)(q + 0x60);

    *(long long *)(pkt + 120) = func_0027C878((char *)0xB);
    *(long long *)(pkt + 128) = 0x0000FF9000000260LL;
    *(long long *)(pkt + 112) = 0LL;

    r = func_001163B0();
    *(long long *)(pkt + 136) = ((long long)((r % 2) + 1) << 2) | 0x8000000040LL;
    top = func_002A7820(0x40, 0x7F) << 24;
    *(int *)(pkt + 76) = (D_L11_001B2014 & 0xFFFFFF) + top;
    *(int *)(pkt + 72) = (D_L11_001B2014 & 0xFFFFFF) + top;
    *(int *)(pkt + 68) = (D_L11_001B2014 & 0xFFFFFF) + top;
    *(int *)(pkt + 64) = (D_L11_001B2014 & 0xFFFFFF) + top;

    quat[3] = 0.0f;
    quat[2] = func_00283248(D_L11_001BA780.x_140 - v[0], D_L11_001BA780.y_144 - v[1]);
    quat[1] = -func_00283248(func_00282E80((char *)v, &D_L11_001BA780.x_140),
                             D_L11_001BA780.z_148 - v[2]);
    quat[0] = func_002A7940();
    func_00283410(m, quat);

    m[12] = v[0];
    m[13] = v[1];
    m[14] = v[2];
    m[15] = 1.0f;

    s = func_002A7878(0.05f, 0.15f) * *(float *)(q + 0x60);
    func_00282D30(pkt, pkt, s);
    func_00282D30(pkt + 16, pkt + 16, s);
    func_00282D30(pkt + 32, pkt + 32, s);
    func_00282D30(pkt + 48, pkt + 48, s);
    func_00280B90(pkt, m, 0);

    *(int *)(pkt + 76) = (D_L11_001B2020 & 0xFFFFFF) + top;
    *(int *)(pkt + 72) = (D_L11_001B2020 & 0xFFFFFF) + top;
    *(int *)(pkt + 68) = (D_L11_001B2020 & 0xFFFFFF) + top;
    *(int *)(pkt + 64) = (D_L11_001B2020 & 0xFFFFFF) + top;

    func_00282D30(pkt, pkt, 0.5f);
    func_00282D30(pkt + 16, pkt + 16, 0.5f);
    func_00282D30(pkt + 32, pkt + 32, 0.5f);
    func_00282D30(pkt + 48, pkt + 48, 0.5f);
    func_00280B90(pkt, m, 0);

    func_L11_0045A8C0(p, v);
}

/* The launcher's state handler: re-arms the shot, aims the head at the level's
   target and hands the launch to the level's helpers. */
void func_L11_00454508(char *p)
{
    char *q = *(char **)(p + 0x68);
    float vec0[4];
    float vec1[4];
    float vec2[4];
    float d;
    float dot;
    float len;
    int idx;
    char *ptr;
    char *entry;
    u8 *r;

    if (*(u8 *)(p + 0x20) == 0) {
        *(int *)(q + 0x18) = (int)(q + 0x60);
        *(float *)(p + 0x2C) *= 0.75f;
        *(int *)(q + 0x1DC) = -1;
        *(u8 *)(q + 0x48) = func_00283CF0(15.0f);
        *(u8 *)(q + 0x4A) = func_00283CF0(12.0f);
        *(float *)(q + 0x1D0) =
            func_002A7878(-*(float *)(q + 0x1D0), *(float *)(q + 0x1D0)) *
            0.01745329424738884f;
        *(u8 *)(p + 0x30) = 0x80;
        *(int *)(q + 0x1D4) = 1;
        *(float *)(q + 0x1D8) *= 0.01666666753590107f;
        func_002B60B0(p, 0.02777777798473835f, 1.6666667461395264f,
                      0.0011635529808700085f, 0.10471977293491364f);
        *(int *)(q + 0x98) |= 4;
        *(float *)(q + 0x60) = 0.75f;
        *(float *)(q + 0x68) = 0.75f;
        *(int *)(q + 0x64) = 0;
        *(float *)(q + 0x6C) = 0.5f;
        *(float *)(q + 0x70) = 1.134464144706726f;
        *(float *)(q + 0x90) = 0.523598849773407f;
        *(float *)(q + 0x8C) = 0.0027777778450399637f;
        func_002A04B8(p, q + 0x1F0, q + 0x1F4, q + 0x1F8);
        *(u8 *)(q + 0x28) = 3;
        *(int *)(q + 0x30) = 0;
        *(short *)(q + 0x1EC) = 0;
        func_L11_00454DD8(p);
    }
    if (*(short *)(q + 0x1FC) == 0 && *(u8 *)(p + 0x20) != 0xE &&
        D_L11_001A8FF4 == 0) {
        *(u16 *)(p + 0x34) |= 0x400;
        if (*(u8 *)(p + 0x31) != 0) {
            if (func_00282E48(p + 0x10, D_L11_001BA8C0) < 24.0f) {
                func_002A93B0(p);
                *(u8 *)(p + 0x6F) = 0x16;
            }
        }
    } else {
        *(u16 *)(p + 0x34) &= 0xFBFF;
    }
    if (*(u8 *)(p + 0x95) >= 2) {
        if (func_002E59B0(p, *(int *)(q + 0x1DC)) == 0)
            *(int *)(q + 0x1DC) = func_002E5CF8(1, 4, p);
    } else {
        if (func_002E59B0(p, *(int *)(q + 0x1DC))) {
            idx = *(int *)(q + 0x1DC);
            if (idx != -1) {
                entry = D_00188660 + idx * 0x70;
                if (*(char **)(entry + 0x88) == p && *(u8 *)(entry + 0x74) != 0)
                    func_002E59F8(idx);
            }
            *(int *)(q + 0x1DC) = -1;
        }
    }
    if (*(short *)(q + 0x1FC) != 0)
        *(int *)(q + 0x98) &= ~0x10;
    else
        *(int *)(q + 0x98) |= 0x10;
    ptr = (char *)func_002A9640(p, 0x10000, 0);
    if (ptr != 0) {
        r = *(u8 **)(ptr + 0x20);
        if (r != 0) {
            if (*(short *)(r + 0xAA) == 0xA03)
                *(int *)(ptr + 0x2C) = 0;
            else if (*(u8 *)(p + 0x31) == 0 && *(short *)(r + 0xAA) == 0xB89)
                *(int *)(ptr + 0x2C) = 0;
        }
    }
    d = func_002A96A0(p, ptr);
    *(u8 *)(p + 0xA8) = 0xFF;
    *(float *)(q + 0x20) -= d;
    if (d != 0.0f) {
        if (*(u8 *)(p + 0x20) != 3 && *(u8 *)(p + 0x20) != 0xE) {
            func_00282F20((char *)vec0, ptr + 0x10, 0.8333333730697632f);
            func_002A7A00(vec1, -0.1388888955116272f, 0.1388888955116272f);
            func_00282CC0(vec0, vec0, vec1);
            if (*(short *)(q + 0x1FC) == 0) {
                vec0[2] = func_002A7878(0.0f, 0.0f) * 0.00027777778450399637f;
                vec0[3] = 5627.9248046875f;
            } else {
                func_00282CF0(vec2, func_L11_004417E8(*(u8 **)(p + 0xB8)),
                              p + 0x10);
                vec2[2] = 0.0f;
                func_00282F20((char *)vec2, vec2, 1.0f);
                dot = func_00282DB0(vec0, vec2);
                if (dot < 0.0f) {
                    func_00282F20((char *)vec2, vec2, dot);
                    len = func_00282DF0(vec0);
                    func_00282CF0(vec0, vec0, vec2);
                    func_00282F20((char *)vec0, vec0, len);
                }
            }
            func_00282CC0(q + 0x100, q + 0x100, vec0);
            func_002A7A00(vec1, 0.0017453294713050127f, 0.006981317885220051f);
            *(float *)(q + 0x1B0) = func_00283B98(*(float *)(q + 0x1B0), vec1[0]);
            *(float *)(q + 0x1B4) = func_00283B98(*(float *)(q + 0x1B4), vec1[1]);
            *(float *)(q + 0x1B8) = func_00283B98(*(float *)(q + 0x1B8), vec1[2]);
            func_002AB800(p, q + 0x50);
            func_002A7750(p, 0xD, 4);
        }
    }
    if (*(short *)(q + 0x1FC) != 0) {
        func_00283698(q + 0x170, p + 0xC0);
        func_002AFFD8(p + 0x10, q + 0x1A0, 0);
        if (func_L11_004461C0(*(u8 **)(p + 0xB8), (u8 *)(p + 0x10)) == 0) {
            *(int *)(q + 0x20) = 0;
            func_002A7750(p, 0xE, 4);
        }
        if (*(u8 *)(p + 0x20) != 0xE) {
            len = *(float *)(p + 0x18);
            r = func_L11_004417E8(*(u8 **)(p + 0xB8));
            func_00282CF0(vec0, p + 0x10, r);
            vec0[2] = 0.0f;
            if (func_L00_002EE290(vec0) > 225.0f) {
                func_00282F20((char *)vec0, vec0, 15.0f);
                r = func_L11_004417E8(*(u8 **)(p + 0xB8));
                func_00282CC0(p + 0x10, vec0, r);
                *(float *)(p + 0x18) = len;
            }
        }
    }
    if (*(u8 *)(p + 0x20) >= 2 && *(u8 *)(q + 0x2E) == 2)
        func_L11_00454DD8(p);
    func_L11_00454B60(p);
}

extern unsigned short D_L11_001B1F84 __attribute__((sda));
extern float func_00283248(float a, float b);
extern void func_002A0F48(char *p);

/* Initialises a spawned object: clears its state flags, copies the two start vectors and the
   caller's parameters into the object and its state block, and aims it along the first vector. */
void func_L11_00458A98(char *self, int a1, int a2, int a3, float f12, float f13, void *t0,
                       float *t1, int t2)
{
    char *s1 = *(char **)(self + 0x68);

    int v;

    *(unsigned short *)(self + 0x34) = (*(unsigned short *)(self + 0x34) & 0xFFBE) | 0x1000;
    v = *(int *)(*(char **)(self + 0x24) + 0x10);
    *(unsigned short *)(self + 0x34) &= 0xEFFF;
    *(int *)(self + 0x98) = v;
    *(unsigned char *)(self + 0x30) = 0xFF;
    *(unsigned short *)(self + 0x32) = 0xFF;
    self[0x20] = 2;
    *(int *)(s1 + 0x15C) = a1;
    *(int *)(self + 0xB8) = a2;
    qcopy(self + 0x10, t0);
    qcopy(s1 + 0xC0, t1);
    *(unsigned short *)(s1 + 0x16C) = D_L11_001B1F84;
    *(int *)(s1 + 0x150) = t2;
    *(float *)(s1 + 0x4C) = f12;
    *(unsigned short *)(s1 + 0x16E) = 0;
    *(int *)(self + 0xF0) = 0;
    *(int *)(self + 0xF4) = 0;
    *(float *)(self + 0xF8) = func_00283248(t1[0], t1[1]);
    *(float *)(s1 + 0x158) = f13;
    func_002A0F48(self);
    *(int *)(s1 + 0x164) = a3;
    *(int *)(self + 0x78) = 0xFF84E643;
}
