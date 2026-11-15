#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern s32 func_2F36F0(void *);
extern void func_3330A8(void *);
extern void func_383120(void *, void *);
extern f32 func_2F4A88(f32);
extern f32 func_2F4088(f32);
extern void func_2F3A80(void *, void *, void *);
extern void func_2F3AB0(void *, void *, void *);
extern void func_2F3AF0(void *, s32, f32);
extern s32 func_2F4BE0(f32);
extern f32 func_2F4BD0(s32);
extern void *func_32F2B0(void *);
extern void func_32F7A8(void *, void *, void *, void *, s32);
extern void *func_332F58(s32);

extern u8 *D_001FF814;

/* func_L22_002D0C98 is in the sibling file L22_002D0C98-decider.c (its own profile). */

/* VU0 macro-op helper (lqc2/sdc2 + a COP2 op): hand-written assembly. */
ASM_FUNC("asm/levels", func_L22_002F3B38);

/* Early-outs when the third float argument is positive; otherwise bends the first angle
   through one helper, feeds the second angle and the angle at the fourth pointer through
   the two placement calls, scales it by the first float argument and stores it back. */
void func_L22_00328220(u8 *position, u8 *angleRef, u8 *speedRef, u8 *directionRef, f32 factor, f32 unusedFactor, f32 limit)
{
    u8 *posPtr = position;
    u8 *angle = angleRef;
    u8 *dirPtr = directionRef;
    u8 *speed = speedRef;
    TI128 buf;
    f32 keep;
    f32 q;

    if (limit > 0.0f)
        return;
    keep = factor;
    *(f32 *)(angle + 0) = func_2F4A88(*(f32 *)(angle + 0));
    func_2F3AF0(&buf, dirPtr, *(f32 *)(speed + 0));
    posPtr += 0x10;
    func_2F3AB0(posPtr, posPtr, &buf);
    q = func_2F4088(*(f32 *)(angle + 0)) * keep;
    *(f32 *)(speed + 0) = q;
    func_2F3AF0(&buf, dirPtr, q);
    func_2F3A80(posPtr, posPtr, &buf);
}



/* Defined in L22_003300E8-qcopy.c. */

/* Allocates a kind-5 record and fills it: the quadword at the first pointer, a colour word
   from the three bytes with 0x7F in the top byte, a helper's result less 0x60, a 0x48 byte,
   the second float, the first byte at D_001FF814 and the handle, then the first float
   divided by a helper's value for the handle. Does nothing without a handle or when the
   allocation fails. */
void func_L22_00334F78(TI128 *source, u8 red, u8 green, u8 blue, s32 handle, f32 scale, f32 value)
{
    u8 *record;
    u8 *pair;
    u32 colour;

    if (handle == 0)
        return;
    record = func_332F58(5);
    if (record == 0)
        return;
    qcopy(record + 0x10, source);
    pair = record + 0x20;
    colour = (green << 8) | 0x7F000000;
    *(u32 *)(record + 0x4) = ((blue << 16) | colour) | red;
    record[0x9] = func_2F4BE0(4.0f) - 0x60;
    record[0x3] = 0x48;
    *(f32 *)(record + 0xC) = value;
    record[0x1] = 0;
    record[0x8] = 0;
    record[0x2] = *D_001FF814;
    *(s32 *)(record + 0x20) = handle;
    *(f32 *)(pair + 0x4) = scale / func_2F4BD0(handle);
}

/* Defined in L22_00334F78.c. */

void func_L22_00335078(u8 *object)
{
    u8 *rec = object;
    u8 *extra = object + 0x20;

    if (func_2F36F0(extra) != 0) {
        func_3330A8(rec);
        return;
    }
    {
        u8 *vecPtr = rec + 0x10;

        func_383120(vecPtr, vecPtr);
    }
    *(f32 *)(rec + 0xC) = *(f32 *)(rec + 0xC) + *(f32 *)(extra + 4);
    if (*(s32 *)(extra) < 6) {
        *(u32 *)(rec + 4) = (*(u32 *)(rec + 4) & 0xFFFFFF)
            | ((u32)(*(s32 *)(extra) * 127 / 6) << 24);
    }
}

/* func_L22_003398B8 is in the sibling file L22_002D0C98-g8.c (it reads $gp data). */

/* Defined in L22_003398B8-g8.c. */

/* func_L22_0039CDC0 is in L22_002D0C98-g8.c. */

/* func_L22_0039D198 is in L22_0039D198-g8.c. */
