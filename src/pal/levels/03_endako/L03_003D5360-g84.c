#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad0[0x80];
    char position[0x10];
    char pad90[0x33C - 0x90];
    char *object;
    int active;
    char pad344[0x22B4 - 0x344];
    unsigned char mode;
    char pad22B5[0x24FC - 0x22B5];
    unsigned short flag;
} EndakoPlayerState;
typedef struct {
    char pad0[6];
    unsigned char first;
    unsigned char second;
    char pad8[0xA2 - 8];
    unsigned char seen;
} EndakoFlags;
typedef struct {
    char pad0[0x30];
    char position[0x10];
    char pad40[0x30];
    char rotation[0x10];
} EndakoPlacement;
extern EndakoPlayerState D_00189E20;
extern EndakoFlags D_001395B8;
extern char D_0019B2E8[];
extern u8 D_001A7AF8[] MACRO_ADDR;
extern int D_001A79F0, D_L03_001A8F00;
extern char *D_L03_001B2A1C;
extern EndakoPlacement *D_L03_001B2B0C;
extern char D_L03_001BFB80[];
extern char D_L03_001B0650[] SDATA(D_L03_001B0650);
extern float D_L03_001B0664, D_L03_001B0668;
extern void func_002A7750(), func_L01_00323310(), func_002B37E8(), func_002A7398();
extern void func_002A0F48(), func_L00_003672F8(), func_PAL_L02_003294D8(), func_L02_0031F858();
extern void func_PAL_L00_002B9CD8(), func_L02_002B5F50(), func_0029F338(), func_002A0430();
extern void func_00288BE8(), func_002F5CB8(), func_PAL_002F6C18();
extern void func_PAL_L03_003D61B8(), func_PAL_L03_003D6298(), func_PAL_L03_003D6150();
extern char *func_0029EFD0();
extern int func_002ACBC8(), func_00288AA0(), func_002B38B8();
extern float func_00283B98(float, float), func_00283198(float);
extern int func_00283D38(int, int, float);
#define I(p, o) (*(int *)((p) + (o)))
#define H(p, o) (*(unsigned short *)((p) + (o)))
#define B(p, o) (*(unsigned char *)((p) + (o)))
#define P(p, o) (*(char **)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))

void func_PAL_L03_003D5B68(char *obj)
{
    char *v = P(obj, 0x68);
    int state = B(obj, 0x20);

    switch (state) {
    case 0: {
        char *p;

        B(obj, 0x30) = 255;
        if (!(B(D_0019B2E8, B(obj, 0xB0) + (D_001A79F0 << 4)) & 128)) {
            if (D_00189E20.mode == 1) {
                func_002A7750(obj, 2, -1);
                func_L01_00323310(I(v, 0x20), -1);
            } else {
                func_002A7750(obj, 1, -1);
                {
                    char *existing = D_L03_001B2A1C + (I(v, 0) << 8);
                    I(existing, 0x98) = 0;
                    H(existing, 0x34) = (H(existing, 0x34) | 0x41) & ~0x1000;
                }
                p = func_0029EFD0(0x57);
                func_002B37E8(p, obj);
                qcopy_nc(p + 0x10, D_L03_001B2B0C[I(v, 4)].position);
                qcopy_nc(p + 0xF0, D_L03_001B2B0C[I(v, 4)].rotation);
                H(p, 0x32) = 0x30;
                H(p, 0x34) |= 2;
                func_002A7398(p, 0x13, 0);
                I(p, 0x98) = 0;
                qcopy_nc(p + 0x10, D_L03_001B0650);
                F(p, 0xF4) = D_L03_001B0664;
                F(p, 0xF8) = D_L03_001B0668;
                func_002A0F48(p);
                P(v, 0x2C) = p;
                if (D_001395B8.first) {
                    func_L00_003672F8();
                    func_PAL_L02_003294D8(I(v, 0x18), I(v, 0x1C));
                }
            }
            func_L02_0031F858(I(v, 0xC), 1);
            D_00189E20.flag = 1;
        } else {
            if (!D_001395B8.seen) {
                func_L00_003672F8();
                func_PAL_L00_002B9CD8(obj + 0x10, obj + 0xF0, 0, 1);
            }
            if (D_00189E20.mode == 1) {
                func_L01_00323310(I(v, 0x24), -1);
                func_L02_002B5F50(0);
                func_0029F338(D_L03_001B2A1C + (I(v, 0) << 8));
                func_002A0430(B(obj, 0xB0));
                func_PAL_L00_002B9CD8(obj + 0x10, obj + 0xF0, 0, 1);
            }
            /* Resident flag bytes, 8 bytes further on in USA v2.00. A symbol-plus-offset
               .sdata address is neither split nor a one-insn operand, so each store stays
               retail's lui $at/sb macro (see L00_002CAB08.c). */
            D_001A7AF8[2] = 1;
            D_001A7AF8[0x3A] = 1;
            D_001A7AF8[3] = 1;
            D_001A7AF8[0x3B] = 1;
            D_001A7AF8[4] = 1;
            D_001A7AF8[0x3C] = 1;
            D_00189E20.flag = 0;
            func_L02_0031F858(I(v, 8), 1);
            func_L02_0031F858(I(v, 0xC), 0);
            func_0029F338(obj);
        }
        return;
    }
    case 1:
        if (!D_001395B8.first
            && func_002ACBC8(D_00189E20.position, I(v, 4))
            && func_00288AA0(D_L03_001BFB80, 0x31)) {
            func_00288BE8(D_L03_001BFB80);
            func_002F5CB8(func_PAL_L03_003D6150, obj);
            D_001395B8.first = state;
        }
        if (D_L03_001A8F00 != 2) {
            {
                u32 timer = H(P(v, 0x2C), 0x96);
                u32 old = timer++;
                H(P(v, 0x2C), 0x96) = timer;
                if (old >= 4) {
                    H(P(v, 0x2C), 0x34) &= ~0x41;
                    H(P(v, 0x2C), 0x34) |= 0x1000;
                    I(P(v, 0x2C), 0x98) = I(P(P(v, 0x2C), 0x24), 0x10);
                }
            }
        } else {
            H(P(v, 0x2C), 0x34) |= 0x41;
            H(P(v, 0x2C), 0x34) &= ~0x1000;
            I(P(v, 0x2C), 0x98) = 0;
        }
        if (func_002B38B8(obj)) {
            H(P(v, 0x2C), 0x34) |= 0x41;
            H(P(v, 0x2C), 0x34) &= ~0x1000;
            I(P(v, 0x2C), 0x98) = 0;
            if (D_001395B8.second)
                func_PAL_L03_003D61B8(obj);
            else if (func_00288AA0(D_L03_001BFB80, 0x32)) {
                func_00288BE8(D_L03_001BFB80);
                func_002F5CB8(func_PAL_L03_003D61B8, obj);
            }
            func_PAL_002F6C18();
            func_002A7750(obj, 2, -1);
            return;
        } else if (D_00189E20.mode == 1) {
            char *p;

            func_L01_00323310(I(v, 0x20), -1);
            p = D_L03_001B2A1C + (I(v, 0) << 8);
            H(p, 0x34) = (H(p, 0x34) & ~0x41) | 0x1000;
            I(p, 0x98) = I(P(p, 0x24), 0x10);
            H(P(v, 0x2C), 0x34) |= 0x41;
            H(P(v, 0x2C), 0x34) &= ~0x1000;
            I(P(v, 0x2C), 0x98) = 0;
            func_002A7750(obj, 2, -1);
            return;
        }
        return;
    case 2:
        if (D_00189E20.object == obj && D_00189E20.active) {
            func_L02_0031F858(I(v, 8), 1);
            func_L02_0031F858(I(v, 0xC), 0);
            if (func_00288AA0(D_L03_001BFB80, 0x33)) {
                func_00288BE8(D_L03_001BFB80);
                func_002F5CB8(func_PAL_L03_003D6298, obj);
                func_002A7750(obj, 3, -1);
            }
            return;
        }
        break;
    default:
        return;
    }
    {
        F(v, 0x30) = func_00283B98(F(v, 0x30), 0.12915438f);
        state = func_00283D38(0x808C8C8C, 0x80282828,
            func_00283198(F(v, 0x30)) * 0.5f + 0.5f);
        I(obj, 0x78) = func_00283D38(I(obj, 0x78), state, 0.18f);
    }
}
