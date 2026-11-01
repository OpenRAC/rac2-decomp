#include "include_asm.h"

#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
extern int func_002B4038(int, int);
extern void func_0029F338(void *);
extern void func_00300190(void *, void *);
extern void func_L00_003A85A0(char *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_PAL_L00_003ABDC8(void *, int);
extern int func_PAL_L00_003AB850(char *, void *);
extern int func_00282978(void *);

/* Advance a moving effect, clip its path and schedule its next update. */
void func_PAL_L00_003AB5D0(char *moby)
{
    float previous[4], midpoint[4];
    char *state = *(char **)(moby + 0x68);
    char *position;
    if (!func_002B4038(0x5CB, *(short *)(state + 0x1A))) {
        func_0029F338(moby);
        return;
    }
    if (*(unsigned char *)(moby + 0x20) == 2) {
        func_00300190(moby + 0x10, moby + 0x10);
        func_L00_003A85A0(moby);
        return;
    }
    if (*(short *)(state + 0x12) == 1) {
        *(VectorBits *)previous = *(VectorBits *)(state + 0x30);
        position = moby + 0x10;
    } else {
        *(VectorBits *)previous = *(VectorBits *)(moby + 0x10);
        position = moby + 0x10;
    }
    func_00282CC0(position, position, state);
    if (*(short *)(state + 0x12) == 1)
        func_00282CC0(state + 0x30, state + 0x30, state + 0x20);
    if (*(unsigned char *)(moby + 0x20) == 0)
        *(unsigned char *)(moby + 0x20) = 1;
    else
        func_PAL_L00_003ABDC8(previous, *(short *)(state + 0x1A));
    func_00282D08(midpoint, previous, position, 0.5f);
    func_PAL_L00_003ABDC8(midpoint, *(short *)(state + 0x1A));
    if (*(float *)(moby + 0x10) < 2.0f || *(float *)(moby + 0x10) > 1021.0f ||
        *(float *)(moby + 0x14) < 2.0f || *(float *)(moby + 0x14) > 1021.0f ||
        *(float *)(moby + 0x18) < 2.0f || *(float *)(moby + 0x18) > 1021.0f ||
        func_PAL_L00_003AB850(moby, previous) || func_00282978(state + 0x10))
        *(unsigned char *)(moby + 0x20) = 2;
    else
        func_L00_003A85A0(moby);
}
