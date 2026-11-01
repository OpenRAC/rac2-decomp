#include "include_asm.h"

#include "common.h"
extern float func_002A7878(float a, float b);
extern void func_00282F20(char *a0, void *a1, float f12);
extern void func_00282CC0(void *a0, void *a1, void *a2);
extern s32 D_L11_001A8FF4 __attribute__((sda));
extern char D_00188660[];
extern char D_L11_001BA8C0[];
extern int func_00283CF0(float);
extern void func_002A7750(void *, int, int);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_002A04B8(void *, void *, void *, void *);
extern void func_002A93B0(void *);
extern float func_PAL_002AA108(void *, void *);
extern void *func_002A9640(void *, unsigned int, int);
extern float func_00282E48(void *, void *);
extern int func_002E59B0(void *, int);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, char *);
extern void func_00283698(void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_PAL_002AC290(void *, void *);
extern void func_002A7A00(void *, float, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00282DF0(void *);
extern float func_00283B98(float, float);
extern float func_L00_002EE290(void *);
extern void func_L11_00454B60(char *);
extern void func_PAL_L11_0045A9A8(char *);
extern u8 *func_L11_004417E8(u8 *);
extern int func_L11_004461C0(u8 *, u8 *);

/* The launcher's state handler: re-arms the shot, aims the head at the level's
   target and hands the launch to the level's helpers. */
void func_PAL_L11_0045A0D8(char *p)
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
        *(float *)(q + 0x1D8) *= 0.020000001f;
        func_002B60B0(p, 0.040000003f, 2.0000002f,
                      0.0016755164f, 0.12566373f);
        *(int *)(q + 0x98) |= 4;
        *(float *)(q + 0x60) = 0.75f;
        *(float *)(q + 0x68) = 0.75f;
        *(int *)(q + 0x64) = 0;
        *(float *)(q + 0x6C) = 0.5f;
        *(float *)(q + 0x70) = 1.134464144706726f;
        *(float *)(q + 0x90) = 0.523598849773407f;
        *(float *)(q + 0x8C) = 0.004f;
        func_002A04B8(p, q + 0x1F0, q + 0x1F4, q + 0x1F8);
        *(u8 *)(q + 0x28) = 3;
        *(int *)(q + 0x30) = 0;
        *(short *)(q + 0x1EC) = 0;
        func_PAL_L11_0045A9A8(p);
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
    d = func_PAL_002AA108(p, ptr);
    *(u8 *)(p + 0xA8) = 0xFF;
    *(float *)(q + 0x20) -= d;
    if (d != 0.0f) {
        if (*(u8 *)(p + 0x20) != 3 && *(u8 *)(p + 0x20) != 0xE) {
            func_00282F20((char *)vec0, ptr + 0x10, 1.2f);
            func_002A7A00(vec1, -0.2f, 0.2f);
            func_00282CC0(vec0, vec0, vec1);
            if (*(short *)(q + 0x1FC) == 0) {
                vec0[2] = func_002A7878(0.0f, 0.0f) * 0.00040000002f;
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
            func_002A7A00(vec1, 0.0025132746f, 0.010053098f);
            *(float *)(q + 0x1B0) = func_00283B98(*(float *)(q + 0x1B0), vec1[0]);
            *(float *)(q + 0x1B4) = func_00283B98(*(float *)(q + 0x1B4), vec1[1]);
            *(float *)(q + 0x1B8) = func_00283B98(*(float *)(q + 0x1B8), vec1[2]);
            func_PAL_002AC290(p, q + 0x50);
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
        func_PAL_L11_0045A9A8(p);
    func_L11_00454B60(p);
}
