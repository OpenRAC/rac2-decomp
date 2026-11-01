#include "include_asm.h"

extern void func_00335E38(void *, float, float, float, float);
extern int func_US2_00348E68(void *);
extern int *func_00335E20(void *);
extern float D_001AE130 __attribute__((sda));
extern float D_001AE134 __attribute__((sda));
extern int D_00138344[];
extern int func_00341E90(void *);
extern int *func_00335E20(void *);
extern void func_00336320(void *);
extern void func_US2_00348E70(void *);
extern int func_002A9588(int, int, int, int, int);

void func_US2_00342E48(char *self)
{
    int count = func_US2_00348E68(self + 0x10);
    int i;
    int *slot;

    if (D_00138344[0] & 0x5000)
        func_002A9588(0, 0, 1, 0, 1);
    for (i = 0; i < count; i++) {
        float step = (float)i;
        func_00335E38(self + 0xEC, (*(float **)self)[0] + D_001AE134,
                      (*(float **)self)[1] + D_001AE130 * step, 0.0f, 0.0f);
        func_00335E38(self + 0x138, (*(float **)self)[0] + D_001AE134,
                      (*(float **)self)[1] + D_001AE130 * step, 0.0f, 0.0f);
        slot = func_00335E20(self + 0x138);
        *slot = func_00341E90(self) == i ? func_002A9588(0x20FFFEED, 0x70FFFEED, 0x14, 0, 0) : 0x55F0C070;
        func_00336320(self + 0xEC);
        func_00336320(self + 0x138);
    }
    func_US2_00348E70(self + 0x10);
}
