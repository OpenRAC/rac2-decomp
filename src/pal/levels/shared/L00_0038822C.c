#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_0038822C);


extern int func_002A77E0(int mode);
extern float func_002A90F8(char *object, char *local);
extern void func_00282D30_7(char *local, int value, float scale);
extern float func_002A7878_1(float low, float high);
extern void func_002BF728(char *object, char *local, float amount, float base);

/* Family 6eb4f363e5305bed: seed body at func_PAL_L00_0038A408. */
void func_PAL_L00_0038A408(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (func_002A77E0(4))
        return;
    base = func_002A90F8(object + 16, local);
    func_00282D30_7(local, value, 0.25f);
    func_002BF728(object + 16, local, func_002A7878_1(0.05f, 0.1f) * 210000.0f, base);
}

