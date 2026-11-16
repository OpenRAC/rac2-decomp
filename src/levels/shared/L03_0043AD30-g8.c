#include "names.h"
/* func_L03_0043AD30 (512 bytes, 12 places), in its own -G8 -g unit: D_L03_001B21B8 is small
 * data, D_00138284 is read by lui/lwc1 (an incomplete array), and each angle's dot product is
 * its own statement. Under -g the second one leaves a line label right after the call's delay
 * slot, and the division there gets retail's two-nop floor (docs/build/compiler-notes.md, division
 * label floor after a call). The size window is written as retail's negated tests. */

#include "include_asm.h"
#include "names.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

/* The angle limits, the reference axis and the slot field the elevation accumulates into. */
extern f32 g_stick_axis_y[];

extern u8 g_hero_l03_position[];

extern u8 g_hero_l03_state_alias[];

extern f32 g_aim_candidate_level_step __attribute__((sda));

extern f32 math_fabs(f32);

extern f32 FastVecDot(float *, float *);

extern f32 FastVecLength(float *);

extern f32 math_fast_angle_helper(f32);

typedef struct {
    u32 occupant;
    u32 owner;
    f32 size;
    f32 level;
} AimSlot;

/* Keeps the camera target on the object the slot holds: measures the object against the
   reference axis, refuses anything outside the size window, turns the angle to the slot's
   facing into a normalised elevation and folds it into the slot's level. */
/* Checks whether this object is close enough and in front of the camera to become its aim target, and builds up the camera slot value. */
void cam_update_aim_target_candidate(u8 *moby) {
    u8 *base = g_hero_l03_state_alias;
    u8 *cur = *(u8 **)(base + 0x190);
    AimSlot *slot;
    f32 offset[4];
    f32 size;
    f32 dot;
    f32 angle;

    if (*(short *)(cur + 0x86) != 0)
        return;
    if (math_fabs(g_stick_axis_y[0]) > 0.05f)
        return;
    FastVecSub(offset, (float *)(moby + 0x10), (float *)g_hero_l03_position);
    slot = (AimSlot *)(base + 0x3A0);
    size = FastVecLength(offset);
    if (!(size < 22.0f))
        return;
    if (!(0.0f < size))
        return;
    if (!(size < slot->size))
        return;
    if (!(0.0f < offset[2]))
        return;
    dot = FastVecDot((float *)cur, offset);
    angle = 1.5707964f - math_fast_angle_helper(dot / size);
    if (angle < 1.1170108f) {
        FastVecSub(offset, (float *)(moby + 0x10), (float *)(cur + 0x30));
        size = FastVecLength(offset);
        if (size == 0.0f)
            size = 0.0001f;
        dot = FastVecDot((float *)cur, offset);
        angle = 1.5707964f - math_fast_angle_helper(dot / size);
        if (angle < 0.6283186f) {
            slot->occupant = (u32)cur;
            slot->size = size;
            slot->owner = (u32)moby;
            slot->level += g_aim_candidate_level_step;
            if (slot->level > 1.0f)
                slot->level = 1.0f;
        }
    }
}
