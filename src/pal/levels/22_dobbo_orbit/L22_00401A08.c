#include "include_asm.h"

#include "common.h"
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_00325600(void *, void *, int);

/* Turns the object's frame (a three-row rotation) by a small fixed angle about z, then places it from the
   state's +0x10 block. */
void func_PAL_L22_00401A08(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float angles[4] __attribute__((aligned(16)));
    float matrix[12] __attribute__((aligned(16)));

    qzero(angles);
    angles[2] = 0.022689285f;
    func_002833F0(matrix, angles);
    func_00283738(object + 0xC0, object + 0xC0, matrix);
    func_002AFFD8(object + 0x10, state + 0x10, 0);
    func_L00_00325600(object + 0xC0, state + 0x10, 0);
}

