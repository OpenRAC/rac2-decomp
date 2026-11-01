#include "include_asm.h"

#include "common.h"
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002B60B0(void *, float, float, float, float);

/* Positions A0 with four angles, then moves it kind six to kind two of length ten. */
void func_PAL_L02_003D55D8(char *a0) {
    func_002B60B0(a0, 0.008f, 0.038000003f,
                  0.010053098f, 1.0053098f);
    func_002A7750(a0, 6, 3);
    if (*(unsigned char *)(a0 + 0x43) != 2)
        func_PAL_002A7E68(a0, 2, 0, 8);
}


/* Positions A0 with four angles, then moves it kind ten to kind six of length five. */
void func_PAL_L02_003D5660(char *a0) {
    func_002B60B0(a0, 0.008f, 0.080000006f,
                  0.005026549f, 0.5026549f);
    func_002A7750(a0, 10, 4);
    if (*(unsigned char *)(a0 + 0x43) != 6)
        func_PAL_002A7E68(a0, 6, 0, 4);
}

