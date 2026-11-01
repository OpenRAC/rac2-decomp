#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern float D_L00_001AFFA4 MACRO_ADDR;
extern int func_00282948(int *);
extern void func_0029F338(void *);
extern void func_00282C88(Quad *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);

/* Moves the child down its owner's local axis, fading it near the end of its life. */
void func_PAL_L00_003A1B30(char *actor) {
    char *state = *(char **)(actor + 0x68);
    char *owner, *ownerState;
    *(float *)(state + 4) += (D_L00_001AFFA4 + D_L00_001AFFA4) * 0.020000001f;
    if (func_00282948((int *)(state + 8)) || D_L00_001AFFA4 * 1.1f <= *(float *)(state + 4)) {
        func_0029F338(actor);
        return;
    }
    owner = *(char **)state;
    if (!owner || *(short *)(owner + 0xAA) != 0xA5D || *(unsigned char *)(owner + 0x20) == 0xFE || *(unsigned char *)(owner + 0x20) == 0xFD) {
        func_0029F338(actor);
        return;
    }
    ownerState = *(char **)(owner + 0x68);
    func_00282C88((Quad *)(actor + 0x10));
    *(float *)(actor + 0x14) = -*(float *)(state + 4);
    func_00283098(actor + 0x10, actor + 0x10, *(char **)state + 0xC0);
    func_00282CC0(actor + 0x10, actor + 0x10, ownerState);
    *(Quad *)(actor + 0xF0) = *(Quad *)(*(char **)state + 0xF0);
    if (*(float *)(state + 4) > D_L00_001AFFA4)
        *(unsigned char *)(actor + 0x23) = func_00283CF0((1.0f - (*(float *)(state + 4) - D_L00_001AFFA4) * 10.0f) * 127.0f);
    *(float *)(actor + 0x2C) = *(float *)(state + 0xC) * 0.1f + (*(float *)(state + 0xC) * *(float *)(state + 4)) / D_L00_001AFFA4;
}
