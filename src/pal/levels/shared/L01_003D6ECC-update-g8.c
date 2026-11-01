#include "include_asm.h"

#include "common.h"
extern void func_PAL_L01_0031C9C0(void *, void *, int, float, float, float);
extern float func_00283CE0(int);
extern int func_L01_0031BC68(int, int, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern char *D_0018A3E0 NOT_SDA;
extern int D_001A79F0;
extern unsigned short D_0018CCB8 NOT_SDA;
extern int D_L01_001B2088 __attribute__((sda));
extern int D_L01_001B05C0 __attribute__((sda));
extern int D_L01_001B05C4;

void func_PAL_L01_003D6ECC(unsigned char *m) {
    float pos[4], rot[4], delta[4];
    char *p = *(char **)(m + 0x68);
    qcopy_nc(pos, m + 0x10);
    qcopy_nc(rot, m + 0xF0);
    switch ((unsigned char)m[0x20]) {
    case 0:
    *(unsigned short *)(m + 0x34) |= 0x1000;
    *(int *)(p + 0xDC) |= 1;
    m[0x20] = 1;
    if (*(short *)(m + 0xAA) == 0xE2A) *(float *)(p + 0x88) = 12.0f;
    break;
    case 1: {
    float scale = *(float *)(m + 0x2C)/ *(float *)(*(char **)(m + 0x24) + 0x24);
    func_PAL_L01_0031C9C0(m, p + 0x50, *(int *)(p + 0xE0), *(float *)(p + 0xEC)*scale, *(float *)(p + 0xE4)*scale, *(float *)(p + 0xE8)*scale);
    if (D_0018A3E0 == m && D_001A79F0 == 2) D_0018CCB8 = 0xFFFF;
    break;
    }
    }
    if ((unsigned char)m[0x31]) {
    float angle = func_00283CE0(D_L01_001B2088%50);
    angle = angle*6.2831854820251465f/func_00283CE0(50)-3.1415927410125732f;
    *(int *)(m + 0x78) = func_L01_0031BC68(D_L01_001B05C0, D_L01_001B05C4, angle);
    }
    func_00282CF0(delta, m + 0x10, pos);
    func_002AD6F0(p + 0xA0, delta, rot, m + 0xF0);
}
