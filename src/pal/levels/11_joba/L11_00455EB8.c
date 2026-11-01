#include "include_asm.h"

#include "common.h"
extern char *func_0029EFD0(int id);
extern float func_002A7878(float a, float b);
extern float func_002A7940(void);
extern void func_002C2210(void *, unsigned int, int, unsigned int, int, char *, float, float, float, int);
extern char D_L11_001A8F20[] __attribute__((sda));
typedef int TI128 __attribute__((mode(TI)));

/* func_L11_0044C850 is defined in L11_004465F8-aim-0044C850-g8.c. */

char *func_PAL_L11_00455EB8(char *a0, TI128 *a1, TI128 *a2, float f12)
{
    char *obj = func_0029EFD0(0xDD9);

    if (obj != 0) {
        char *st;
        float f20;

        *(unsigned char *)(obj + 0x30) = 0xFF;
        *(short *)(obj + 0x32) = 0xFF;
        obj[0x31] = 1;
        obj[0x20] = 0;
        *(long long *)(obj + 0x38) = *(long long *)(a0 + 0x38);
        qcopy(obj + 0x10, a2);
        st = *(char **)(obj + 0x68);
        qcopy(st, a1);
        *(float *)(st + 0x14) = f12;
        *(char **)(st + 0x10) = a0;
        *(float *)(st + 0x18) = func_002A7940();
        *(float *)(st + 0x1C) = func_002A7878(0.25132746f, 0.75398237f);
        *(float *)(st + 0x20) = 0.15f;
        *(unsigned char *)(obj + 0x23) = 0x80;
        *(unsigned short *)(obj + 0x34) |= 0x100;
        *(float *)(obj + 0x2C) = func_002A7878(0.005f, 0.00625f);
        *(int *)(st + 0x24) = 0;
        *(unsigned short *)(obj + 0x34) |= 0x200;
        f20 = func_002A7878(2.0f, 4.0f);
        *(unsigned short *)(obj + 0x34) |= 0x41;
        func_002C2210(obj + 0x10, 3, 0x801060E0, 0, 10, D_L11_001A8F20, f20 * 0.3f, f20, 0.0f, 0);
        func_002C2210(obj + 0x10, 3, -1, 1, -10, D_L11_001A8F20, f20 * 0.04f, f20 * 0.4f, 0.0f, 0);
    }
    return obj;
}

