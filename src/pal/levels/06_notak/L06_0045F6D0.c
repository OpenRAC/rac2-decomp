#include "include_asm.h"


extern float D_L06_001B234C __attribute__((sda));
extern float D_001B2350 __attribute__((sda));
extern int func_002A9640(char *, int, int);
extern void func_L01_003D6B00(char *, int, float, float, float, float);
extern int func_002E5CF8(int, int, char *);

void func_PAL_L06_00460E58(char *a0)
{
    char *p;
    int n;

    if (*(unsigned char *)(a0 + 0x20) == 0) {
        *(unsigned char *)(a0 + 0x20) = 1;
        *(unsigned short *)(a0 + 0x34) |= 0x800;
    }

    p = (char *)func_002A9640(a0, 0x4010000, 0);
    if (p != 0 && *(short *)(*(char **)(p + 0x20) + 0xAA) != 0xFE5) {
        n = 3;
        if (D_L06_001B234C < 0.8999999761581421f && D_001B2350 < 0.8999999761581421f)
            n = 0xE;

        func_L01_003D6B00(a0, n, 0.0f, 3.263000011444092f, 1.9739999771118164f,
                          0.14000002f);
        func_002E5CF8(0, 0, a0);
        func_0029F338(a0);
    } else {
        *(unsigned char *)(a0 + 0xA8) = 0xFF;
    }
}




#include "common.h"
extern int func_00273B70(char *);
extern void func_002A7750(char *, int, int);
extern void func_0029F338(char *);
extern void func_L06_0045C350(unsigned char *);

void func_PAL_L06_00461470(unsigned char *a0)
{
    switch (a0[0x20]) {
    case 0:
        if (func_00273B70((char *)a0) != 0) {
            func_002A7750((char *)a0, 1, -1);
            *(unsigned short *)(a0 + 0x34) |= 0x2800;
        }
        break;
    case 1:
        func_00273B70((char *)a0);
        if (a0[0x23] < 2) {
            func_0029F338((char *)a0);
        } else {
            a0[0x23] -= 2;
        }
        break;
    }
}

INCLUDE_ASM("asm/pal/levels", func_PAL_L06_00461504);



