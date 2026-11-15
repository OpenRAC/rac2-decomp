/* func_002BD8B0: both 16-byte copies are qcopy(), so the 4.0f argument stays at its call
 * as in retail; the spawn returns p itself when the allocation fails, and the flag byte at
 * +2 is stored before the two halfword copies of a4. */
#include "common.h"

extern void *func_002B9030(int kind);
extern int func_00283CF0(float f);
extern int func_001163B0(void);
extern unsigned char *D_001F2594;


void *func_002BD8B0(void *a0, void *a1, int a2, int a3, int a4, int a5, float f)
{
    void *p;
    char *q;
    int v;

    if (a4 == 0)
        return 0;
    p = func_002B9030(0x15);
    if (p != 0) {
        qcopy((char *)p + 0x10, a0);
        *(int *)((char *)p + 4) = a2;
        v = FloatToInt(4.0f);
        *(unsigned char *)((char *)p + 1) = 0;
        *(float *)((char *)p + 0xC) = f;
        *(unsigned char *)((char *)p + 3) = 0x48;
        *(unsigned char *)((char *)p + 9) = (unsigned char)(v - 0x60);
        *(unsigned char *)((char *)p + 8) = (unsigned char)func_001163B0();
        q = (char *)p + 0x20;
        *(unsigned char *)((char *)p + 2) = *D_001F2594;
        *(short *)((char *)p + 0xA) = a4;
        *(short *)(q + 0x18) = a4;
        *(float *)(q + 0x1C) = f;
        *(int *)(q + 0x10) = a2;
        *(int *)(q + 0x14) = a3;
        *(short *)(q + 0x1A) = a5;
        qcopy(q, a1);
    }
    return p;
}
