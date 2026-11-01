#include "include_asm.h"

#include "common.h"
extern void func_L01_003DC8B8(u8 *, void *, void *);
extern void func_PAL_L01_0031A4D0(void *, void *, void *);
extern void func_PAL_L01_003E10E8(u8 *, void *);
extern void func_L01_003DC9A8(void *, void *);

/* func_L01_003DCDD8 around the other move step (func_PAL_L01_0031A4D0, with the state's
   block at +0x1C0). */
void func_PAL_L01_003E1448(u8 *object, void *arg)
{
    u8 *state = *(u8 **)(object + 0x68);
    float matrix[16] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));

    if (state[0x3E4])
        func_L01_003DC8B8(object, matrix, extra);
    qcopy(position, object + 0x10);
    func_PAL_L01_0031A4D0(object, arg, state + 0x1C0);
    func_PAL_L01_003E10E8(object, position);
    if (state[0x3E4])
        func_L01_003DC9A8(matrix, extra);
}

extern s32 func_PAL_L01_00323068(u8 *, void *);

/* Runs the shared move step (func_PAL_L01_00323068) with the object's position saved before
   it; when the state's flag at +0x3E4 is set, the transform is saved before and restored
   after. */
s32 func_PAL_L01_003E14E0(u8 *object, void *arg)
{
    u8 *state = *(u8 **)(object + 0x68);
    float matrix[16] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    s32 r;

    if (state[0x3E4])
        func_L01_003DC8B8(object, matrix, extra);
    qcopy(position, object + 0x10);
    r = func_PAL_L01_00323068(object, arg);
    func_PAL_L01_003E10E8(object, position);
    if (state[0x3E4])
        func_L01_003DC9A8(matrix, extra);
    return r;
}
