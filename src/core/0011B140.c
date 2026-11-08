#include "common.h"

extern void func_0011AF90(volatile unsigned int *, volatile long *);
extern int func_0011F5E0(void);
extern void func_0011F628(void);

/* rac1-decomp src/core/00118A40.c: wait_vblank_csr (VSync2, glue.o) */
/* Arms an asynchronous flag and result through func_0011AF90, clears INTC_STAT's VBlank-start
   bit with interrupts off, polls until that bit or the flag is set, clears the bit again and
   returns the 64-bit result. flag and result are both written behind the compiler's back. */
long func_0011B140(void)
{
    volatile unsigned int flag;
    volatile long result;
    int old;

    flag = 0;
    func_0011AF90(&flag, &result);

    old = func_0011F5E0();
    I_STAT = 4;
    CpuSync();
    if (old) {
        func_0011F628();
    }
    while ((I_STAT & 4) == 0 && flag == 0) {
    }

    old = func_0011F5E0();
    I_STAT = 4;
    CpuSync();
    if (old) {
        func_0011F628();
    }
    return result;
}
