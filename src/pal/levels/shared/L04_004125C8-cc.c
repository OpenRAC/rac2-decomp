/* func_PAL_L04_004125C8, the PAL copy of func_L04_0040DF90: the same C. */
#include "common.h"
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern unsigned char D_00188660[];
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern int func_L01_00355BA0(int, int);
extern int func_002E5F40(int, int);

void func_PAL_L04_004125C8(unsigned char *m, unsigned char *p)
{
    float elapsed, amount, original;
    if (*(int *)(p + 0x32c) && func_00282948(p + 0x324)) {
        int handle = *(int *)(p + 0x328);
        if (handle != -1) {
            unsigned char *record = D_00188660 + handle * 0x70;
            if (*(void **)(record + 0x88) == m && record[0x74])
                func_002E59F8(handle);
        }
        *(int *)(p + 0x32c) = 0;
        *(int *)(p + 0x328) = -1;
        *(int *)(p + 0x324) = 0;
    }
    elapsed = *(float *)(p + 0x30c) + *(float *)(p + 0x27c) - 0.060000002f;
    if (elapsed < 0.0f) elapsed = 0.0f;
    if (!func_002E59B0(m, *(int *)(p + 0x330))) {
        if (m[0x20] == 3)
            *(int *)(p + 0x330) = func_002E5CF8(20, 5, m);
        else
            *(int *)(p + 0x330) = func_002E5CF8(0, 5, m);
    }
    if (!func_002E59B0(m, *(int *)(p + 0x334))) {
        if (m[0x20] == 3)
            *(int *)(p + 0x334) = func_002E5CF8(21, 5, m);
        else
            *(int *)(p + 0x334) = func_002E5CF8(1, 5, m);
    }
    if (func_002E59B0(m, *(int *)(p + 0x330))) {
        amount = elapsed * 2.4999998f;
        if (amount > 1.0f) amount = 1.0f;
        amount = 1.0f - amount;
        func_L01_00355BA0(*(int *)(p + 0x330), func_00283CF0(func_00283CE0(1024) * amount));
        amount = elapsed * 2.4999998f;
        if (amount > 1.0f) amount = 1.0f;
        func_002E5F40(*(int *)(p + 0x330), func_00283CF0(amount * 2816.0f));
    }
    if (func_002E59B0(m, *(int *)(p + 0x334))) {
        float limit;
        /* Same line on purpose: under -g a line note between the load and the
         * division adds a second nop. */
        amount = elapsed / (limit = 0.54f);
        original = amount;
        limit = 0.85f;
        if (amount < limit) {
            amount = amount * 0.9411764f + 0.2f;
        } else {
            amount -= limit;
            amount = (1.0f - amount) * 0.8f + 0.2f;
        }
        func_L01_00355BA0(*(int *)(p + 0x334), func_00283CF0(func_00283CE0(1024) * amount));
        amount = (1.0f - original) * -2816.0f;
        func_002E5F40(*(int *)(p + 0x334), func_00283CF0(amount));
    }
}
