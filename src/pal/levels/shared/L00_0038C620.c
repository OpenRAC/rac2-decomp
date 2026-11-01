#include "include_asm.h"

#include "common.h"

/* Raise the byte field to eight when it is below. */
void func_PAL_L00_0038C620(unsigned char *a0) {
    if (a0[0x20] < 8) {
        a0[0x20] = 8;
    }
}



extern int F6eb4f363_FUN_002A77E0(int mode);
extern float F6eb4f363_FUN_002A90F8(char *object, char *local);
extern void F6eb4f363_FUN_00282D30(char *local, int value, float scale);
extern float F6eb4f363_FUN_002A7878(float low, float high);
extern void F6eb4f363_FUN_002BF728(char *object, char *local, float amount, float base);

/* func_00303568 is defined in 00303568.c. */




/* func_00303E20 is defined in 00303E20.c. */

/* func_00304128 is defined in 00304128.c. */

/* func_00304210 is defined in 00304210-g8.c. */

/* func_00304AD0 uses the profile in 00304AD0-g8-qcopy.c. */

void func_PAL_L00_0038CF30(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (F6eb4f363_FUN_002A77E0(4))
        return;
    base = F6eb4f363_FUN_002A90F8(object + 16, local);
    F6eb4f363_FUN_00282D30(local, value, 0.25f);
    F6eb4f363_FUN_002BF728(object + 16, local, F6eb4f363_FUN_002A7878(0.05f, 0.1f) * 210000.0f, base);
}

