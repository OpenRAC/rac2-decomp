/* func_L03_0043AD30 (512 bytes, 12 places), in its own -G8 -g unit: D_L03_001B21B8 is small
 * data, D_00138284 is read by lui/lwc1 (an incomplete array), and each angle's dot product is
 * its own statement. Under -g the second one leaves a line label right after the call's delay
 * slot, and the division there gets retail's two-nop floor (docs/build/compiler-notes.md, division
 * label floor after a call). The size window is written as retail's negated tests. */

#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

/* The angle limits, the reference axis and the slot field the elevation accumulates into. */
extern f32 D_00138284[];

extern u8 D_L03_00189EA0[];

extern u8 D_L03_001B9840[];

extern f32 D_L03_001B21B8 __attribute__((sda));

extern f32 func_00282C48(f32);

extern f32 func_00282DB0(float *, float *);

extern f32 func_00282DF0(float *);

extern f32 func_002831B0(f32);

typedef struct {
    u32 occupant;
    u32 owner;
    f32 size;
    f32 level;
} AimSlot;

/* Keeps the camera target on the object the slot holds: measures the object against the
   reference axis, refuses anything outside the size window, turns the angle to the slot's
   facing into a normalised elevation and folds it into the slot's level. */
void func_L03_0043AD30(u8 *a0) {
    u8 *base = D_L03_001B9840;
    u8 *cur = *(u8 **)(base + 0x190);
    AimSlot *slot;
    f32 v[4];
    f32 size;
    f32 dot;
    f32 angle;

    if (*(short *)(cur + 0x86) != 0)
        return;
    if (func_00282C48(D_00138284[0]) > 0.05f)
        return;
    func_00282CF0(v, (float *)(a0 + 0x10), (float *)D_L03_00189EA0);
    slot = (AimSlot *)(base + 0x3A0);
    size = func_00282DF0(v);
    if (!(size < 22.0f))
        return;
    if (!(0.0f < size))
        return;
    if (!(size < slot->size))
        return;
    if (!(0.0f < v[2]))
        return;
    dot = func_00282DB0((float *)cur, v);
    angle = 1.5707964f - func_002831B0(dot / size);
    if (angle < 1.1170108f) {
        func_00282CF0(v, (float *)(a0 + 0x10), (float *)(cur + 0x30));
        size = func_00282DF0(v);
        if (size == 0.0f)
            size = 0.0001f;
        dot = func_00282DB0((float *)cur, v);
        angle = 1.5707964f - func_002831B0(dot / size);
        if (angle < 0.6283186f) {
            slot->occupant = (u32)cur;
            slot->size = size;
            slot->owner = (u32)a0;
            slot->level += D_L03_001B21B8;
            if (slot->level > 1.0f)
                slot->level = 1.0f;
        }
    }
}
