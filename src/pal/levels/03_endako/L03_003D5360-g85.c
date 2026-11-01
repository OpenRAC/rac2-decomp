#include "include_asm.h"

#include "common.h"
extern f32  D_L03_001B0340 __attribute__((sda));
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern s32  func_31BA30(s32 a0, s32 a1);
extern s32  func_31B9F0(s32 a0);
extern f32  func_2F0000(f32 a0, f32 a1);
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern f32  func_2EF670(f32 a0, f32 a1);
extern f32  func_2EF110(f32 *a0);
extern f32 D_L03_001B0350[] SDATA(D_L03_001B0350);
extern f32 D_L03_001B0648 __attribute__((sda));
extern u32 D_L03_001B3458;
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern s32  func_002B38B8(char *a0);
extern s32  func_002E5CF8(s32 a0, s32 a1, char *a2);
extern u8  *D_L03_001B2A1C;
extern u8   D_00188660[];
extern s32  D_L03_001B0438 __attribute__((sda));
extern f32  D_L03_001B043C __attribute__((sda));
extern s32  D_L03_001B0674 __attribute__((sda));
extern char D_00189EA0[];
extern char D_L03_001B9980[];
typedef struct {
    s32 index;
    u8 pad04[0x14];
    f32 f18;
    f32 f1C;
    f32 f20;
} L03_22C8State;
typedef struct {
    u32 field00;
    u8 pad04[0xC];
} L03_22C8Entry;
extern L03_22C8Entry *D_L03_001FE700[];
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern void func_0029F338(char *a0);
extern s32  func_002A8AF0(char *a0, void *a1, u32 a2);
extern void func_00335438(char *a0, char *a1, s32 a2, s32 a3, s32 a4);
extern void func_L03_003D2518(char *a0, f32 *a1, f32 *a2);
extern void func_00282CF0(void *, void *, void *);
extern f32  func_00282DF0(f32 *a0);
extern void func_002AAC80(f32 *a0, f32 a1, f32 a2, f32 a3, f32 a4);
extern void func_00282F20(f32 *a0, f32 *a1, f32 a2);
extern void func_00282CC0(void *, void *, void *);
extern void func_00335370(char *a0);
extern f32 func_002AAA00(char *a0, f32 *a1, f32 a3, f32 a4, f32 a5, f32 a6, s32 a2);
extern void func_003353C8(char *a0);
extern void func_003355A8(s32 a0);

void func_PAL_L03_003D6468(char *a0)
{
    L03_22C8State *s2 = *(L03_22C8State **)(a0 + 0x68);
    f32 v0[4] __attribute__((aligned(16)));
    f32 v1[4] __attribute__((aligned(16)));
    f32 v2[4] __attribute__((aligned(16)));
    f32 k;
    f32 len;
    f32 one;
    f32 k2;

    if (D_L03_001B0674 != 0) {
        return;
    }
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        func_002A7750(a0, 1, -1);
        if (s2->index == -1) {
            func_0029F338(a0);
        }
        break;
    case 1:
        if (func_002A8AF0(D_00189EA0, ((u8 *)D_L03_001FE700[s2->index] + 0x10), D_L03_001FE700[s2->index]->field00) != 0) {
            func_00335438(D_L03_001B9980, D_L03_001B9980 + 0x10, 1, 0, 0);
            func_002A7750(a0, 2, -1);
        }
        break;
    case 2:
        k = 0.004f;
        func_L03_003D2518(a0, v0, v1);
        one = 1.0f;
        func_00282CF0(v2, v0, D_L03_001B9980);
        k2 = 0.0012566373f;
        len = func_00282DF0(v2);
        func_002AAC80(&s2->f18, len, k, k, one);
        func_00282F20(v2, v2, s2->f18);
        func_00282CC0(D_L03_001B9980, v2, D_L03_001B9980);
        func_00335370(D_L03_001B9980);
        func_002AAA00(D_L03_001B9980 + 0x14, &s2->f1C, v1[1], k2, k2, one, 0);
        func_002AAA00(D_L03_001B9980 + 0x18, &s2->f20, v1[2], k2, k2, one, 0);
        func_003353C8(D_L03_001B9980 + 0x10);
        if (func_002A8AF0(D_00189EA0, ((u8 *)D_L03_001FE700[s2->index] + 0x10), D_L03_001FE700[s2->index]->field00) == 0) {
            func_003355A8(1);
            func_002A7750(a0, 1, -1);
        }
        break;
    }
}
