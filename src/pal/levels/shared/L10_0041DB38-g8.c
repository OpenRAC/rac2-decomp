#include "include_asm.h"

typedef unsigned char u8;
typedef short s16;
typedef int s32;
extern char D_00188660[];
extern u8 *D_L10_001B251C __attribute__((sda));
extern u8 *D_L10_001C3B40[];
extern char ref_L10_00418D88_00[];
extern s32 func_002ED688(u8 *);
extern int func_L00_00367720(void);
extern void func_PAL_L10_0041DEA0(u8 *);
extern void func_L05_00379E60(int, int, int, int);
extern void func_PAL_L05_0037E8E0(u8 *);
extern int func_L05_0037B538(u8 *, int, int, int);
extern void func_002E59F8(s32);
extern int func_002E5CF8(int, int, char *);
extern void func_L05_0037B948(u8 *, int, float);
extern void func_PAL_L10_0041DF98(void *);
extern int func_L05_0037B888(char *);
extern void func_PAL_L05_0037DE20(char *);
extern int func_00282948(void *);
extern void func_PAL_L10_0041E0F8(u8 *);
extern int func_00277F48(void *, int, void *, int, float);
extern int func_002E5DA0(int, int, char *, int);
typedef struct { char pad0[0x104]; int f104; int f108; int pad10c; int f110; int pad114[2]; int f11C; u8 *f120; } Motion;

/* Updates the two attack modes, chooses a live target and maintains its sound. */
void func_PAL_L10_0041DB38(u8 *self) {
    char *state = *(char **)(self + 0x68);
    Motion *motion = (Motion *)func_002ED688(self);
    Motion *otherMotion;
    u8 *target, *current;
    int handle, i, count;
    switch (self[0x20]) {
    case 0:
        self[0x30] = 255;
        if (!func_L00_00367720()) return;
        func_PAL_L10_0041DEA0(self);
        if (*(int *)(state + 0x264))
            func_L05_00379E60((int)self, (int)ref_L10_00418D88_00, 0, 0);
        break;
    case 1:
        *(float *)(self + 0x2C) = 0.019999999552965164f;
        func_PAL_L05_0037E8E0(self);
        if (func_L05_0037B538(self, 0, 0, 0)) {
            handle = *(int *)(state + 0x26C);
            if (handle != -1) {
                char *e = D_00188660 + handle * 0x70;
                if (*(u8 **)(e + 0x88) == self && *(u8 *)(e + 0x74)) func_002E59F8(handle);
            }
            *(int *)(state + 0x26C) = -1;
            func_002E5CF8(1, 0, (char *)self);
        }
        if (motion->f110) {
            func_L05_0037B948(self, 0, 176.0f);
            if (*(int *)(state + 0x260) != -1) {
                motion->f11C = 1;
                motion->f120 = D_L10_001B251C + (*(int *)(state + 0x260) << 8);
            }
            if (motion->f108 && motion->f104) func_PAL_L10_0041DF98(self);
            if (func_L05_0037B888((char *)self)) func_PAL_L05_0037DE20((char *)self);
            func_00282948(state + 0x268);
            func_PAL_L10_0041E0F8(self);
        }
        break;
    case 2:
        *(float *)(self + 0x2C) = 0.07999999821186066f;
        func_PAL_L05_0037E8E0(self);
        func_L05_0037B538(self, 0, 0, 0);
        if (!motion->f110) break;
        func_L05_0037B948(self, 0, 176.0f);
        current = motion->f120;
        if (current) {
            otherMotion = (Motion *)func_002ED688(current);
            if (!otherMotion->f110) motion->f120 = 0;
        }
        if (!current || !motion->f120) {
            count = func_00277F48(self + 0x10, 0, self, 0, 80.0f);
            for (i = 0; i < count; i++) {
                target = D_L10_001C3B40[i];
                if (*(s16 *)(target + 0xAA) == 0xCBE) {
                    otherMotion = (Motion *)func_002ED688(target);
                    if (otherMotion->f110) {
                        motion->f120 = target;
                        motion->f11C = 0;
                        break;
                    }
                }
            }
        }
        if (motion->f104) func_PAL_L10_0041DF98(self);
        if (func_L05_0037B888((char *)self)) func_PAL_L05_0037DE20((char *)self);
        func_00282948(state + 0x268);
        func_PAL_L10_0041E0F8(self);
        break;
    }
    {
    char *e = D_00188660 + *(int *)(state + 0x26C) * 0x70;
    if (*(u8 **)(e + 0x88) != self || !*(u8 *)(e + 0x74))
        *(int *)(state + 0x26C) = func_002E5DA0(3, 6, (char *)self, 0xF93);
    }
}
