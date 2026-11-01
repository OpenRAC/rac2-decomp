#include "include_asm.h"

#include "common.h"
extern void func_00282CC0(void *, void *, void *);
extern float ref_L00_002E8F80_00[][4];
extern void func_00283098(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

/* Six sparks from the table, each placed by the object's matrices and given a
   small random drift; `height` lifts the drift's z. */
void func_PAL_002E9DC8(char *object, float height)
{
    float from[3] __attribute__((aligned(16)));
    float to[3] __attribute__((aligned(16)));
    float position[3] __attribute__((aligned(16)));
    int i;

    for (i = 0; i < 6; i++) {
        from[0] = func_002A7878(-0.020000001f, 0.020000001f);
        from[1] = func_002A7878(-0.020000001f, 0.020000001f);
        from[2] = height + func_002A7878(-0.0050000004f, 0.0050000004f);
        from[3] = 0.4f;
        qcopy(to, from);
        to[3] = 0.6f;
        qcopy(position, ref_L00_002E8F80_00[i]);
        func_00283098(position, position, object + 0xC0);
        func_00282CC0(position, position, object + 0x10);
        func_002BAA28(position, from, to, 0x30F0F0F0, 0x14F0F0F0, 3, 3, func_002A77E0(3) + 3, 0x17);
    }
}
