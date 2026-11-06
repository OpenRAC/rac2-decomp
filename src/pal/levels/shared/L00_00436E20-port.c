#include "include_asm.h"

extern void func_0033AB50(char *p);

extern void func_0033AE28_2(char *p);
extern void func_L00_00430948_3(char *p, float a, float b);
extern void func_002E5E58_3(int a, int b, int c);

extern void func_US2_0033BE70 (char *object);
extern void func_L00_00430948 (char *object, float x, float y);
extern int func_002E5E58 (int a, int b, int c);


extern void Fc558ca70_FUN_0033AE28(char *p);
extern void Fc558ca70_FUN_0033B018(char *p, float a, float b);
extern void Fc558ca70_FUN_002E5E58(int a, int b, int c);
extern unsigned char D_PAL_001A7C38[] __attribute__((sda));

int func_PAL_L00_004388F8(char *a0, int a1)
{
    char *p = a0 + 8;
    float *q;
    int v;

    Fc558ca70_FUN_0033AE28(p);
    q = *(float **)(a0 + 732);
    Fc558ca70_FUN_0033B018(p, q[0], q[1]);
    if (a1 & 0x1000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 728);
        *(int *)(a0 + 728) = (v + 1) % 2;
    } else if (a1 & 0x4000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 728);
        *(int *)(a0 + 728) = (v + 1) % 2;
    } else if (a1 & 0x40) {
        Fc558ca70_FUN_002E5E58(4, 0, 0);
        switch (*(int *)(a0 + 728)) {
        case 0:
            D_PAL_001A7C38[2] = D_PAL_001A7C38[2] == 0;
            break;
        case 1:
            D_PAL_001A7C38[3] = D_PAL_001A7C38[3] == 0;
            break;
        }
    }
    return (a1 >> 6) & 1;
}


extern void Ffb202470_FUN_0033AB50(char *p);


extern void F5979c03f_FUN_0033AE28 (char *object);
extern void F5979c03f_FUN_0033B018 (char *object, float x, float y);
extern int F5979c03f_FUN_002E5E58 (int a, int b, int c);


extern void *func_US2_0033BB98(void *);
extern void *func_00347EA0(void *);


extern void *func_L00_0042C290(void *);


extern int func_0033AF48(char *p);