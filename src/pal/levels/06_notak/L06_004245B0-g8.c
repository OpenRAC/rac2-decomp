#include "include_asm.h"

#include "common.h"
extern void func_002A7750(char *, int, int);
extern void func_PAL_002A7E68(char *, int, int, int);
extern int func_002A7820(int, int);
extern int func_002E5CF8(int, int, char *);
extern int D_001A79F0;
extern unsigned char D_0019B2E8[];
extern char *D_L06_001FE500[];
extern void func_L01_003377C8(char *);
extern void func_00282A60(char *, int, int);
extern int func_L06_00420080(char *);
extern int func_PAL_002B1A50(char *, char *, int);
extern void func_L06_0041FD60(char *);
extern void func_002AEE70(char *, char *, char *, float, float, float);
extern void func_002AEF28(char *, char *, char *, float, float, float);

int func_PAL_L06_004245B0(unsigned char *obj)
{
    char *d = *(char **)(obj + 0x68);
    int hit, old;
    if (obj[0x20] == 0) {
        if ((D_0019B2E8[obj[0xB0] + (D_001A79F0 << 4)] & 0x80) && *(int *)(d + 0x33C)) return 1;
        *(int *)(d + 0x2AC) = 0;
        *(unsigned short *)(obj + 0x34) |= 0x800;
        *(int *)(d + 0x254) = -1;
        *(int *)(d + 0xA8) = 3;
        d[0x70] = 7; d[0x71] = 5; d[0x72] = 6; d[0x76] = 6; d[0x77] = 6;
        *(float *)(d + 0x7C) = 0.120000005f;
        *(int *)(d + 0x80) = 0;
        *(float *)(d + 0x84) = 0.006f;
        *(float *)(d + 0x88) = 0.012f;
        *(float *)(d + 0x8C) = 0.006f;
        *(float *)(d + 0x90) = 2.5f; *(int *)(d + 0x94) = 0;
        *(float *)(d + 0x9C) = .4f;
        d[0xCC] = 4; d[0xCD] = 8; d[0xCE] = 4; d[0xCF] = 8;
        d[0xD2] = 4; d[0xD3] = 8; d[0xD4] = 0; d[0xD6] = 1;
        *(float *)(d + 0x2A8) = *(unsigned char *)(d + 0x34);
        d[0x28] = 3;
        *(int *)(d + 0x30) = 0; *(int *)(d + 0x258) = 0; *(int *)(d + 0x26C) = 0;
        qzero(d + 0x230);
        qcopy(d + 0x220, D_L06_001FE500[*(int *)(d + 0x274)] + 0x10);
        func_002A7750((char *)obj, 1, 0);
        if (obj[0x43] != 1) func_PAL_002A7E68((char *)obj, 1, 0, 0);
        obj[0x30] = 0x80; *(short *)(obj + 0x32) = 0x80;
        func_L01_003377C8(D_L06_001FE500[*(int *)(d + 0x274)]);
        func_L01_003377C8(D_L06_001FE500[*(int *)(d + 0x270)]);
        func_00282A60(d + 0x2B0, 0, 0x80);
    }
    *(int *)(d + 0x258) = func_L06_00420080((char *)obj);
    *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24);
    old = obj[0x95];
    hit = func_PAL_002B1A50((char *)obj, d + 0x60, 0);
    if (hit) {
        func_L06_0041FD60((char *)obj);
        if (hit < 4) func_002E5CF8(2, 0, (char *)obj);
        if (old == 1) *(int *)(d + 0x24C) = ((s32)(func_002A7820(300, 360)) * 5 + 2) / 6;
        if ((unsigned int)(hit - 4) < 2) func_002A7750((char *)obj, 8, -1);
    }
    if (*(unsigned short *)(d + 0x98) & 3) *(int *)(obj + 0x98) = 0;
    func_002AEE70((char *)obj, d + 0x280, d + 0x284, .3f, 0.027925273f, -1);
    func_002AEF28((char *)obj, d + 0x288, d + 0x28C, .1047197655f, 0.0062831864f, 0.007330384f);
    return 0;
}
