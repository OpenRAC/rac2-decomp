#include "include_asm.h"

extern void func_0033AB50(char *p);

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *func_PAL_L00_00436E20(char *object)
{
    func_0033AB50(object + 8);
    return object;
}

extern void Ffb202470_FUN_0033AB50(char *p);

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_L00_004371C0(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_L00_004374C0(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_L00_00437A48(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


extern void Fc558ca70_FUN_0033AE28(char *p);
extern void Fc558ca70_FUN_0033B018(char *p, float a, float b);
extern void Fc558ca70_FUN_002E5E58(int a, int b, int c);
extern volatile unsigned char Fc558ca70_D_001A7B95 __attribute__((sda));
extern volatile unsigned char Fc558ca70_D_001A7B94 __attribute__((sda));

int func_PAL_L00_00437BA8(char *a0, int a1)
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
            Fc558ca70_D_001A7B95 = Fc558ca70_D_001A7B95 == 0;
            break;
        case 1:
            Fc558ca70_D_001A7B94 = Fc558ca70_D_001A7B94 == 0;
            break;
        }
    }
    return (a1 >> 6) & 1;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_L00_004384D0(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_L00_00438798(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



INCLUDE_ASM("asm/pal/levels", func_PAL_L00_004388F8);



/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_L00_00438B60(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00438CC0);

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_L00_00438E58(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00438FB8);

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_L00_00439098(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



INCLUDE_ASM("asm/pal/levels", func_PAL_L00_004391F8);

extern void *func_PAL_0033CA78(void *);
extern void *func_00347EA0(void *);

void *func_PAL_L00_004392D8(char *object) {
    func_PAL_0033CA78(object + 0x8);
    func_00347EA0(object + 0x2E0);
    return object;
}


extern void *func_L00_0042C290(void *);

void *func_PAL_L00_00439630(char *object) {
    func_PAL_0033CA78(object + 0x8);
    func_L00_0042C290(object + 0x2E0);
    return object;
}


extern int func_0033AF48(char *p);

int func_PAL_L00_004397D0(char *p)
{
    return func_0033AF48(p + 8);
}

