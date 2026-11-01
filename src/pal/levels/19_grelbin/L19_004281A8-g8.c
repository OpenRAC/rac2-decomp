#include "include_asm.h"

#include "common.h"
#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)
extern char D_00189E20[];
extern char *D_L19_001B1EAC __attribute__((sda));
extern float D_L19_001B1E94 __attribute__((sda));
extern float D_L19_001B1E98 __attribute__((sda));
extern float D_L19_001B1E9C __attribute__((sda));
extern float D_L19_001B1EA4 __attribute__((sda));
extern float D_L19_001B1EA8 __attribute__((sda));
extern int D_L19_001B258C;
extern char D_L19_001B9A40[];
extern int func_002ACBC8(char *, int);
extern void func_002AF000(float *, float, float, float);
extern void func_00282CC0(float *, float *, char *);
extern char *func_PAL_L00_002D7850(int);
extern void func_L00_002D7140(char *);
extern void func_00282CF0(char *, float *, char *);

/* Per-frame update of the carried-object marker: arms it, tracks a linked flag, and while the hero is in state 0x31 places and sizes the marker from the grabbed object's bounds. */
void func_PAL_L19_004281A8(char *obj) {
    float a[4];
    float b[4];
    char *hero_ptr;

    int *link = FLD(obj, int *, 0x68);

    switch (FLD(obj, u8, 0x20)) {
    case 0:
        D_L19_001B1EAC = 0;
        FLD(obj, u8, 0x20) = 1;
        FLD(obj, u8, 0x30) = 0xFF;
        return;
    case 1:
        if (link[0] != -1) {
            if (func_002ACBC8(D_L19_001B9A40, link[0]) != 0) {
                D_L19_001B258C = 2;
            } else if (D_L19_001B258C == 2) {
                D_L19_001B258C = 0;
            }
        }
        break;
    default:
        return;
    }
    if (FLD(D_00189E20, int, 0x2294) == 0x31 && (hero_ptr = FLD(D_00189E20, char *, 0x1830)) != 0) {
        func_002AF000(a, D_L19_001B1E94, FLD(hero_ptr, float, 0xF8), -FLD(hero_ptr, float, 0xF4) * 0.5f);
        func_00282CC0(b, a, FLD(D_00189E20, char *, 0x1830) + 0x10);
        if (D_L19_001B1EAC == 0) {
            D_L19_001B1EAC = func_PAL_L00_002D7850(5);
            if (D_L19_001B1EAC == 0) {
                return;
            }
        }
        if (FLD(FLD(D_00189E20, char *, 0x1830), s16, 0xAA) == 0x905) {
            FLD(D_L19_001B1EAC, float, 0) = D_L19_001B1E98;
            FLD(D_L19_001B1EAC, float, 0xC) = -1.0f;
            FLD(D_L19_001B1EAC, float, 8) = -1.0f;
        } else {
            FLD(D_L19_001B1EAC, float, 0) = D_L19_001B1E9C;
            FLD(D_L19_001B1EAC, float, 0xC) = D_L19_001B1EA4;
            FLD(D_L19_001B1EAC, float, 8) = D_L19_001B1EA8;
        }
        FLD(D_L19_001B1EAC, u8, 0x1F) = 1;
        func_00282CF0(D_L19_001B1EAC + 0x20, b, D_L19_001B9A40);
        return;
    }
    if (D_L19_001B1EAC != 0) {
        func_L00_002D7140(D_L19_001B1EAC);
        D_L19_001B1EAC = 0;
    }
}

extern int D_L19_001A8F00 __attribute__((sda));
extern u8 D_001A7BDC[] __attribute__((sda));
extern int D_L19_001B2724[4] __attribute__((sda));
extern char *D_L19_001B2B0C[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern char D_00189EA0[];
extern char D_L19_001BFC40[];
extern void func_L04_00423178(char *a0);
extern void func_0029F338(char *a0);
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern void func_L01_003128C0(char *a0);
extern s32 func_002ACBC8(char *a0, s32 a1);
extern s32 func_00288AA0(char *a0, s32 a1);
extern void func_L01_003246D0(char *a0);
extern void func_00288BE8(char *a0);
extern s32 func_002F5D10(void);
extern void func_002AD7B8(s32 a0);
extern void func_PAL_002AFC10(s32 a0);
extern void func_PAL_L00_002B9CD8(char *a0, char *a1, s32 a2, s32 a3);
extern void func_002A0430(s32 a0);
extern void func_002DF3F8(char *a0, char *a1);
extern void func_0029B3E0(s32 a0, s32 a1);

void func_PAL_L19_00429220(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);
    u8 id;

    func_L04_00423178(a0);
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(s32 *)(a0 + 0x98) = 0;
        *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
        if (D_001A7BDC[0] != 0) {
            func_0029F338(a0);
        } else {
            func_002A7750(a0, 1, -1);
            func_L01_003128C0(a0);
        }
        break;
    case 1:
        if (func_002ACBC8(D_00189EA0, *(s32 *)(s1 + 0x120)) != 0) {
            if (func_00288AA0(D_L19_001BFC40, 0x96) != 0) {
                func_00288AA0(D_L19_001BFC40, 0x14);
                func_00288AA0(D_L19_001BFC40, 0x97);
                func_L01_003246D0(a0);
                func_00288BE8(D_L19_001BFC40);
                func_002A7750(a0, 2, -1);
            }
        }
        break;
    case 2:
        D_L19_001B2724[1] = 1;
        if (D_L19_001A8F00 == 2) {
            *(u8 *)(a0 + 0x31) = 0;
            *(u16 *)(a0 + 0x34) |= 1;
        }
        if (func_002F5D10() == 0) {
            D_L19_001B2724[1] = 0;
            func_002AD7B8(0x14);
            func_PAL_002AFC10(0x14);
            func_PAL_L00_002B9CD8(D_L19_001B2B0C[0] + (*(s32 *)(s1 + 0x120) << 7) + 0x30,
                        D_L19_001B2B0C[0] + (*(s32 *)(s1 + 0x120) << 7) + 0x70, 0, 1);
            *(u16 *)(a0 + 0x34) &= 0xFFFE;
            *(u8 *)(a0 + 0x31) = 1;
            if (*(u8 *)(a0 + 0xB0) != 0xFF) {
                id = *(u8 *)(a0 + 0xB0);
                if ((D_0019B2E8[id + (D_001A79F0[0] << 4)] & 0x80) == 0)
                    func_002A0430(id);
                func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
                func_0029B3E0(0, -1);
            } else {
                func_0029B3E0(0, -1);
            }
            func_0029F338(a0);
        }
        break;
    }
}
