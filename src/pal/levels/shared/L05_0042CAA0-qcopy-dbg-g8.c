/* func_PAL_L05_0042CAA0 and func_PAL_L05_0042D3B8, the PAL copies of func_L05_00427090 and func_L05_00427988:
 * the same C at 50 Hz, where 1/60 becomes 0.02 and the frame count at 0x28 is scaled by 5/6. */
#include "common.h"

extern char *func_0029EFD0(int);
extern int func_00283CF0(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float D_L05_001B154C __attribute__((sda));
extern float D_L05_001B1550 __attribute__((sda));
extern int D_L05_001B1554 __attribute__((sda));
extern float D_L05_001B155C __attribute__((sda));
extern float D_L05_001B1560 __attribute__((sda));
extern float D_L05_001B1514 __attribute__((sda));
extern float D_L05_001B1518 __attribute__((sda));
extern int D_L05_001B151C __attribute__((sda));
extern float D_L05_001B1524 __attribute__((sda));
extern float D_L05_001B1528 __attribute__((sda));

char *func_PAL_L05_0042CAA0(char *pos, char *vec, int a2, char *a3, int flag, int a5)
{
    char *obj = func_0029EFD0(0x1182);

    if (obj != 0) {
        char *st = *(char **)(obj + 0x68);
        float f20;
        float f21;
        float f22;
        int count;
        int frames;

        *(unsigned char *)(obj + 0x30) = 0xFF;
        *(unsigned short *)(obj + 0x32) = 0x1FF;
        *(unsigned char *)(obj + 0x31) = 1;
        *(unsigned char *)(obj + 0x20) = 1;
        *(int *)(st + 0x24) = flag;
        f22 = (flag ? D_L05_001B1518 : D_L05_001B1514) * 0.020000001f;
        f21 = (flag ? D_L05_001B1528 : D_L05_001B1524) / f22;
        f20 = 1.0f;
        count = func_00283CF0(f21);
        frames = D_L05_001B151C;
        *(int *)(st + 0x18) = count;
        *(int *)(st + 0x10) = a2;
        *(char **)(st + 0x20) = a3;
        *(int *)(st + 0x14) = 0;
        *(float *)(st + 0x1C) = f20 / f21;
        *(int *)(st + 0x28) = ((s32)(frames) * 5 + 2) / 6;
        *(int *)(st + 0x2C) = a5;
        *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
        qcopy(obj + 0x10, pos);
        func_00282F20(st, vec, f22);
        func_00282F20(obj + 0xC0, st, f20);
        func_00282DD8(obj + 0xD0, obj + 0xC0, a3 + 0xE0);
        func_00282F20(obj + 0xD0, obj + 0xD0, f20);
        func_00282DD8(obj + 0xE0, obj + 0xD0, obj + 0xC0);
    }
    return obj;
}

char *func_PAL_L05_0042D3B8(char *pos, char *vec, int a2, char *a3, int flag)
{
    char *obj = func_0029EFD0(0x1191);

    if (obj != 0) {
        char *st = *(char **)(obj + 0x68);
        float f20;
        float f21;
        float f22;
        int count;
        int frames;

        *(unsigned char *)(obj + 0x30) = 0xFF;
        *(unsigned short *)(obj + 0x32) = 0x1FF;
        *(unsigned char *)(obj + 0x31) = 1;
        *(unsigned char *)(obj + 0x20) = 1;
        *(int *)(st + 0x24) = flag;
        f22 = (flag ? D_L05_001B1550 : D_L05_001B154C) * 0.020000001f;
        f21 = (flag ? D_L05_001B1560 : D_L05_001B155C) / f22;
        f20 = 1.0f;
        count = func_00283CF0(f21);
        frames = D_L05_001B1554;
        *(int *)(st + 0x18) = count;
        *(int *)(st + 0x10) = a2;
        *(char **)(st + 0x20) = a3;
        *(int *)(st + 0x14) = 0;
        *(float *)(st + 0x1C) = f20 / f21;
        *(int *)(st + 0x28) = ((s32)(frames) * 5 + 2) / 6;
        *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
        qcopy(obj + 0x10, pos);
        func_00282F20(st, vec, f22);
        func_00282F20(obj + 0xC0, st, f20);
        func_00282DD8(obj + 0xD0, obj + 0xC0, a3 + 0xE0);
        func_00282F20(obj + 0xD0, obj + 0xD0, f20);
        func_00282DD8(obj + 0xE0, obj + 0xD0, obj + 0xC0);
    }
    return obj;
}
