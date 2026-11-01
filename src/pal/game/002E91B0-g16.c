#include "include_asm.h"

#include "common.h"
extern f32 D_001AC1A0[4] __attribute__((sda));
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

/* Two puffs at the object's offset point, each with a small random drift and growth. */
void func_PAL_002E9F58(char *object)
{
    f32 position[3] __attribute__((aligned(16)));
    f32 from[3] __attribute__((aligned(16)));
    f32 to[3] __attribute__((aligned(16)));
    int i;

    func_00283098(position, D_001AC1A0, object + 0xC0);
    func_00282CC0(position, position, object + 0x10);
    for (i = 0; i < 2; i++) {
        from[0] = func_002A7878(-0.010000001f, 0.010000001f);
        from[1] = func_002A7878(-0.010000001f, 0.010000001f);
        from[2] = func_002A7878(-0.010000001f, 0.010000001f);
        from[3] = func_002A7878(0.6f, 0.8f);
        qcopy(to, from);
        to[3] = from[3] + func_002A7878(0.1f, 0.2f);
        func_002BAA28(position, from, to, 0x30C0C0C0, 0x20C0C0C0, 3, 0xD, func_002A77E0(0xA) + 7, 0x17);
    }
}
