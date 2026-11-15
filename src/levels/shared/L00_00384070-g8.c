#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type, p, off) (*(type *)((char *)(p) + (off)))

extern int func_002A77E0(int);
extern char *func_0029EFD0(int);
extern void func_002B37E8(void *, void *);
extern void func_002A7398(signed char *, int, int);
extern void func_002AEC18(void *, int);

extern Vector4 D_L00_001AED70[2] __attribute__((sda));
extern Vector4 D_L00_001AED90 __attribute__((sda));
extern float D_L00_001AEDA0[2] __attribute__((sda));
extern int D_L00_001AEDA8[2] __attribute__((sda));
extern Vector4 D_L00_001AED50 __attribute__((sda));
extern char *D_L00_00232A60[24];

/* Create the two attached objects and the twenty-four optional table entries. */
int func_L00_00384070(char *owner)
{
    char *work = FIELD(char *, owner, 0x68);
    char **slot = (char **)(work + 0x48);
    int i = 0, result = 0;
    int j;
    Vector4 *basis;

    FIELD(int, work, 0x68) = func_002A77E0(255);
    do {
        *slot = CreateMoby(0xCB2);
        func_002B37E8(*slot, 0);
        func_002A7398((signed char *)*slot, 1, 0);
        FIELD(unsigned short, *slot, 0x34) |= 0x4002;
        FIELD(unsigned char, *slot, 0xBC) = i;
        qcopy(*slot + 0xF0, &D_L00_001AED90);
        qcopy(work + i * 16, &D_L00_001AED70[i]);
        qzero(work + 0x20 + i * 16);
        FIELD(float, *slot, 0x2C) =
            FIELD(float, FIELD(char *, *slot, 0x24), 0x24) * D_L00_001AEDA0[i];
        func_002AEC18(*slot, D_L00_001AEDA8[i]);
        ++i;
        ++slot;
    } while (i < 2);
    FIELD(float, work, 0x74) = 0.5f;
    slot = D_L00_00232A60;
    basis = &D_L00_001AED50;
    j = 23;
    do {
        *slot = CreateMoby(0xE7D);
        if (*slot) {
            func_002B37E8(*slot, 0);
            result = func_002A77E0(FIELD(unsigned char,
                FIELD(char *, FIELD(char *, *slot, 0x24), 0x50), 0x10));
            func_002A7398((signed char *)*slot, 2, result);
            FIELD(unsigned short, *slot, 0x34) |= 0x4002;
            qcopy(*slot + 0xF0, basis);
        }
        --j;
        ++slot;
    } while (j >= 0);
    if (FIELD(char *, work, 0x48) != 0 && FIELD(char *, work, 0x4C) != 0)
        return 1;
    return 0;
}
