#include "include_asm.h"

#define MACRO_ADDR __attribute__((section(".sdata")))
typedef unsigned char u8;
typedef int s32;
extern u8 D_00188660[];
extern u8 D_0019B2E8[];
extern u8 D_0019B4A8[];
extern int D_001A79F0 MACRO_ADDR;
extern u8 *D_L19_001B2A1C __attribute__((sda));
extern u8 D_L19_001B2860[] MACRO_ADDR;
typedef struct { u8 pad[0x464]; u8 slot[1]; } SlotTable;
extern SlotTable D_L19_0021DDC0;
extern SlotTable D_L19_0021EA30;
extern void func_00282F20(void *, void *, float);
extern unsigned long long func_002A0488(void *, int, int, int);
extern void func_002A7750(u8 *, u8, s32);
extern int func_002E5CF8(int, int, char *);
extern void func_002E59F8(s32);
extern s32 func_002B38B8(u8 *);
extern s32 func_00283CF0(float);
extern void func_00291450(s32);
extern void func_0029F338(void *);
extern void func_L00_00310838(unsigned char *, int, int);

void func_PAL_L19_00427B30(u8 *actor)
{
    u8 *state = *(u8 **)(actor + 0x68);
    float scale = 9.77f;
    int flags;
    int step;
    if (*(short *)(actor + 0xaa) == 0x1204)
        scale = 6.2f;
    switch (actor[0x20]) {
    case 0:
        *(int *)(state + 0x14) = -1;
        actor[0x23] = 0x50;
        actor[0x20] = 1;
        *(unsigned short *)(actor + 0x34) |= 0xb0c;
        func_00282F20(actor + 0xc0, actor + 0xc0, *(float *)(state + 0xc) / scale);
        func_00282F20(actor + 0xd0, actor + 0xd0, 0.8f);
        *(float *)(actor + 0xc) *= *(float *)(state + 0xc) / scale;
        *(short *)(state + 0xa) = -1;
        *(float *)(state + 4) = 1.0f;
        func_002A0488(actor, 0x80, 0x80, 0x80);
        if (actor[0xb0] != 0xff && (D_0019B2E8[actor[0xb0] + D_001A79F0 * 16] & 0x80))
            func_002A7750(actor, 3, -1);
        break;
    case 1: {
        u8 *link = D_00188660 + *(int *)(state + 0x14) * 0x70;
        int index;
        if (*(u8 **)(link + 0x88) != actor || link[0x74] == 0)
            *(int *)(state + 0x14) = func_002E5CF8(0, 4, (char *)actor);
        index = *(int *)state;
        if (index != -1) {
            u8 *entry = D_L19_001B2A1C + index * 0x100;
            if (entry && entry[0x20] != 0xfe && entry[0x20] != 0xfd) {
                flags = D_0019B4A8[((int)(*(unsigned short *)(entry + 0xb2) << 16) >> 17) + D_001A79F0 * 0x400];
                if (*(unsigned short *)(entry + 0xb2) & 1) {
                    if ((flags >> 4) & 7)
                        goto active;
                    break;
                } else {
                    flags &= 7;
                    goto test_active;
                }
            }
        } else {
            flags = func_002B38B8(actor);
        test_active:
            if (!flags)
                break;
        }
    active:
        *(float *)(state + 4) = 1.0f;
        actor[0x20] = 2;
        break; }
    case 2: {
        int index = *(int *)(state + 0x14);
        if (index != -1) {
            u8 *entry = D_00188660 + index * 0x70;
            if (*(u8 **)(entry + 0x88) == actor && entry[0x74])
                func_002E59F8(index);
        }
        *(float *)(state + 4) -= 0.060000002f;
        *(int *)(state + 0x14) = -1;
        if (*(float *)(state + 4) < 0.0f)
            actor[0x20] = 3;
        else
            actor[0x23] = func_00283CF0(*(float *)(state + 4) * 80.0f);
        break; }
    case 3:
        if (*(short *)(state + 0xa) != -1) {
            func_00291450(*(short *)(state + 0xa));
            *(short *)(state + 0xa) = -1;
        }
        D_L19_0021DDC0.slot[*(short *)(actor + 0xb2)] = actor[0xb0] + 2;
        if (actor[0xb0] == 0xff || (!(*(D_L19_001B2860 + actor[0xb0]) & 0x80) &&
                (D_0019B2E8[actor[0xb0] + D_001A79F0 * 16] & 0x80)))
            D_L19_0021EA30.slot[*(short *)(actor + 0xb2)] = actor[0xb0] + 2;
        func_0029F338(actor);
        return;
    }
    step = 0x10;
    *(short *)(state + 8) += 0x10;
    if (*(short *)(state + 8) > 0x1000) {
        *(short *)(state + 8) -= 0x1000;
        step = -0xff0;
    } else if (*(short *)(state + 8) < 0) {
        *(short *)(state + 8) += 0x1000;
        step = 0x1010;
    }
    func_L00_00310838(*(u8 **)(actor + 0x24), step, 0);
}
