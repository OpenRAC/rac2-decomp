#include "include_asm.h"

extern char *D_001A8CFC;
extern int func_US2_00349728(void *, int);

int func_US2_0029CFA0(int value) {
    if (D_001A8CFC != 0)
        return func_US2_00349728(D_001A8CFC + 0x39160, value);
    return 0;
}

extern int func_US2_00347B88(void *, int);

int func_US2_0029D040(int value) {
    if (D_001A8CFC != 0)
        return func_US2_00347B88(D_001A8CFC + 0x39620, value);
    return 0;
}

/* func_US2_0029CC48, the v2.00 copy of func_L00_0030CF60: the same call, with the camera's
   projection scale set around it, as the tail of func_0029BF08 does in v1.01. */
typedef struct { char pad[0xB0]; float scale; } CamCc;
extern CamCc ref_L00_0030CFE0_01;
extern void func_0027AB40(void);
extern void func_US2_0034F220(void *);

void func_US2_0029CC48(void)
{
    if (D_001A8CFC != 0) {
        float saved = ref_L00_0030CFE0_01.scale;

        ref_L00_0030CFE0_01.scale = 0.62f;
        func_0027AB40();
        func_US2_0034F220(D_001A8CFC + 0x36F28);
        ref_L00_0030CFE0_01.scale = saved;
        func_0027AB40();
    }
}
