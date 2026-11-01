#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L14_0042E5F8);

INCLUDE_ASM("asm/pal/levels", func_PAL_L14_0042ED80);

#include "common.h"
extern int func_00282948(void *);
extern void func_00325DA0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283B98(float, float);
extern void func_PAL_003273B8(void *, void *, int, void *, float);
extern void func_PAL_002B14F8(void *, void *, int, int, float);
extern int func_00282948(void *);

void func_PAL_L14_0042F0D8(unsigned char *self) {
    unsigned char *state = *(unsigned char **)(self + 0x68);
    float delta[4] __attribute__((aligned(16)));
    func_00282948(state + 0x30c);
    func_00282948(state + 0x310);
    if (*(unsigned short *)(self + 0x96) < 65535)
        ++*(unsigned short *)(self + 0x96);
    func_00325DA0(self, state + 0x308);
    func_00282CF0(delta, self + 0x10, state + 0x2d0);
    qcopy(state + 0x2d0, self + 0x10);
    if (self[0x95] == 1) {
        *(float *)(state + 0x2fc) = func_00283B98(*(float *)(state + 0x2fc), 0.25132746f);
        func_PAL_003273B8(self, state + 0x300, 1, delta, *(float *)(state + 0x2fc));
    } else {
        *(float *)(state + 0x2fc) = func_00283B98(*(float *)(state + 0x2fc), 0.013962637f);
        func_PAL_003273B8(self, state + 0x300, 0, delta, *(float *)(state + 0x2fc));
    }
    func_PAL_002B14F8(self, state + 0x230, 7, 1, 2.0f);
}


