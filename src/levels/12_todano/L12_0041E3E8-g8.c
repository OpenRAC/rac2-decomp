#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern f32 D_L12_001B1F50 __attribute__((sda));
extern f32 D_L12_001B1F58 __attribute__((sda));
extern f32 D_L12_001B1F60 __attribute__((sda));
extern s32 D_L12_001B1FA0 __attribute__((sda));
extern f32 D_L12_001B1FB0 __attribute__((sda));
extern f32 D_L12_001B1FB4 __attribute__((nosda));
extern f32 D_L12_001B1FB8 __attribute__((nosda));
extern char D_L12_001B1F80[];

extern void func_002A7750(void *, int, int);
extern void *func_002A9640(void *, int, int);
extern s32 func_002E5CF8(s32, s32, s32);
extern void func_0029F338(void *);
extern void func_L00_0032A258(void *, void *, void *, void *, int, int, int, int, int, unsigned char, int);
extern void func_L00_00324F18(void *, void *, float, float, float);
extern void func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);

void func_L12_00421110(u8 *a0)
{
    s32 *s = *(s32 **)(a0 + 0x68);
    f32 pos[4];

    switch (a0[0x20]) {
    case 0:
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (func_002A9640(a0, 0x4010000, 0) != 0 && *s == 0) {
            func_002A7750(a0, 2, -1);
            func_002E5CF8(0, 0, (s32)a0);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        func_L00_0032A258(a0, &D_L12_001B1F60, &D_L12_001B1F58, &D_L12_001B1F50, 0xFFFF, 0,
                          D_L12_001B1FA0, 0, 1, 0xFF, 0);
        func_L00_0032A258(a0, D_L12_001B1F80, &D_L12_001B1F58, &D_L12_001B1F50, 0xFFFF, 0,
                          D_L12_001B1FA0, 1, 0x1FE, 0xFF, 0);
        func_L00_00324F18(a0, pos, D_L12_001B1FB0, D_L12_001B1FB4, D_L12_001B1FB8);
        func_0032C700(pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, *(f32 *)(a0 + 0x2C) * 20.0f, 20.0f,
                      1, 0, 1, 0);
        func_0029F338(a0);
        break;
    }
}

extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern s32 D_L12_001B29C8 __attribute__((sda));
extern u8 *D_L12_001B090C __attribute__((nosda));
extern u8 *D_L12_001B1360 __attribute__((nosda));
extern float func_00283CE0(int);
extern int func_L01_0031BC68(int, int, float);
extern int func_002ACBC8(void *, int);
extern void func_L00_003294F0(u8 *, s32);
extern int func_L12_00404778(void);

void func_L12_00420660(u8 *a0)
{
    s32 *s = *(s32 **)(a0 + 0x68);
    u8 *rec;
    u8 *obj;
    f32 phase, d;

    switch (a0[0x20]) {
    case 0:
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        rec = D_L12_001B2E9C + (s[1] << 8);
        if (rec[0x31] != 0) {
            phase = func_00283CE0(D_L12_001B29C8 % 60);
            d = func_00283CE0(60);
            phase *= 6.2831855f;
            phase /= d;
            *(s32 *)(rec + 0x78) = func_L01_0031BC68(0x802020A0, 0x80202050, phase - 3.1415927f);
        }
        if (s[0] == -1)
            break;
        obj = D_L12_001B090C;
        if (obj != 0) {
            if (func_002ACBC8(obj + 0x10, s[0])) {
                *(s32 *)(rec + 0x78) = 0x80A02020;
                func_002A7750(a0, 2, -1);
                if (s[2] != -1)
                    func_L00_003294F0(D_L12_001B2E9C + (s[2] << 8), 1);
            }
        } else if (func_L12_00404778()) {
            if (func_002ACBC8(D_L12_001B1360 + 0x10, s[0])) {
                *(s32 *)(rec + 0x78) = 0x80A02020;
                func_002A7750(a0, 2, -1);
                if (s[2] != -1)
                    func_L00_003294F0(D_L12_001B2E9C + (s[2] << 8), 1);
            }
        }
        break;
    }
}

extern s32 D_L12_001B22D0 __attribute__((sda));
extern f32 D_L12_001B2280 __attribute__((sda));
extern f32 D_L12_001B2288 __attribute__((sda));
extern f32 D_L12_001B22B0 __attribute__((sda));
extern int func_002A7820(int, int);
extern int func_00273B70(unsigned char *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002E5DA0(int, int, void *, int);
extern u8 *func_0029EFD0(int);
extern void func_00282AB0(void *, void *, int);

void func_L12_00429868(u8 *a0)
{
    s32 *s = *(s32 **)(a0 + 0x68);
    s32 life;
    u8 *obj;
    u16 flags;
    f32 v[4];

    int state = a0[0x20];

    switch (state) {
    case 0:
        *(s16 *)((u8 *)s + 0x34) = func_002A7820(20, 50);
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        life = *(s16 *)((u8 *)s + 0x34);
        if (life < 0 || func_00273B70(a0)) {
            func_00283098(v, (u8 *)s + 0x20, a0 + 0xC0);
            obj = 0;
            func_00282CC0(v, a0 + 0x10, v);
            func_0032C700(v, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, state, state, 0, 0);
            func_002E5DA0(2, 0, a0, 0x12B1);
            flags = *(u16 *)(a0 + 0x7C);
            if (flags & 1)
                obj = func_0029EFD0(0x12E0);
            else if (flags & 2)
                obj = func_0029EFD0(0x12E1);
            else if (flags & 4)
                obj = func_0029EFD0(0x12E2);
            if (obj != 0) {
                qcopy(obj + 0x10, v);
                *(f32 *)(obj + 0x2C) = *(f32 *)(*(u8 **)(obj + 0x24) + 0x24) *
                                       (*(f32 *)(a0 + 0x2C) / *(f32 *)(*(u8 **)(a0 + 0x24) + 0x24));
                func_00282AB0(obj + 0xC0, a0 + 0xC0, 0x18);
                func_L00_0032A258(obj, &D_L12_001B22B0, &D_L12_001B2288, &D_L12_001B2280, 0xFF, -1,
                                  D_L12_001B22D0, 0xF, 0xFF, 0xFF, 0);
                func_0029F338(obj);
            }
            func_0029F338(a0);
        } else {
            *(s16 *)((u8 *)s + 0x34) = life - 1;
        }
        break;
    }
}
