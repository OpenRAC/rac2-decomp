#include "names.h"
/* func_L14_003E4EA0 is a unit of its own: it reads four float constants through $gp (hence
   -g8), and it is built with -g, whose line label in front of the `mul.s` before the second
   division makes the assembler pad that `div.s` with retail's `nop` (the division-floor class
   of docs/build/compiler-notes.md, as in func_L23_004160B0). func_00282C48 is `fabs`. The state
   block is read as a halfword key table at +0x00, with the current position at +0x14 and the
   current key index at +0x16: the span runs from the key to the previous one (index != 0), or
   to one of three words (index == 0). Computing both results before the two stores gives
   retail's store order. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef int s32;

extern float D_L14_001B05C8 __attribute__((sda));
extern float D_L14_001B05CC __attribute__((sda));
extern float D_L14_001B05C0 __attribute__((sda));
extern float D_L14_001B05C4 __attribute__((sda));
extern float func_00282C48(float);

/* Blends two numbers on a linked object based on how far its position has moved between two key points. */
void func_L14_003E4EA0(char *self)
{
    char *state = *(char **)(self + 0x68);
    char *linked = *(char **)(state + 0x30);
    char *linkedVars;
    int nextKey;
    int wrapCount;
    u16 position;
    u16 keyIndex;
    float keyStart;
    float span;
    float ratioA;
    float ratioB;
    float blendA;
    float out0;
    float out1;

    if (linked == 0)
        return;
    linkedVars = *(char **)(linked + 0x68);
    keyIndex = *(u16 *)(state + 0x16);
    if (*(s16 *)(state + 0x16) == 0) {
        wrapCount = *(int *)(state + 0x34);
        if (wrapCount > 0) {
            nextKey = wrapCount;
            position = *(u16 *)(state + 0x14);
        } else if (*(int *)(state + 0x38) >= 0) {
            position = *(u16 *)(state + 0x14);
            nextKey = *(int *)(*(char **)(*(char **)(state + 0x3C) + 0x68) + 0x34);
        } else {
            nextKey = *(s16 *)(state + 0x14);
            position = *(u16 *)(state + 0x14);
        }
    } else {
        position = *(u16 *)(state + 0x14);
        nextKey = *(s16 *)(state + *(s16 *)(state + 0x16) * 2 - 2);
    }
    keyStart = (float)*(s16 *)(state + (s16)keyIndex * 2);
    span = (float)(nextKey - *(s16 *)(state + (s16)keyIndex * 2));
    ratioA = FloatAbs((D_L14_001B05C8 - 1.0f) - (D_L14_001B05C8 + D_L14_001B05C8 - 2.0f) * ((float)(s16)position - keyStart) / span);
    blendA = D_L14_001B05C8 - ratioA;
    ratioB = FloatAbs((D_L14_001B05CC - 1.0f) - (D_L14_001B05CC + D_L14_001B05CC - 2.0f) * ((float)*(s16 *)(state + 0x14) - keyStart) / span);
    out0 = blendA * D_L14_001B05C0;
    out1 = (D_L14_001B05CC - ratioB) * D_L14_001B05C4;
    *(float *)(linkedVars + 0x40) = out0;
    *(float *)(linkedVars + 0x44) = out1;
}
