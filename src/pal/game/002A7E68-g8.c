#include "common.h"

/* func_PAL_002A7E68, the PAL copy of func_002A7470: the same C, with one added test that
   clears +0x44 when +0x42 equals +0x43 and bit 1 of +0x60 is set. */

typedef int TI128_002A7470 __attribute__((mode(TI)));

typedef struct {
    char pad[0x48];
    unsigned char *anims[1];
} Model_002A7470;

extern void anim_start_immediate(unsigned char *, int, int);
extern int moby_alloc_object_slot(void *);
extern void func_PAL_002A2E30(void *, int);
extern void update_moby_animation_state(void *);
extern float IntToFloat(int);
extern TI128_002A7470 ref_L00_002A7470_00[];

/* Starts a blended animation on a moby: picks a free blend slot, saves the current pose into it and fades to the new animation over the given number of frames (PAL). */
void anim_start_blended_pal(unsigned char *object, int animation, int frame, int rate)
{
    int count;
    int slot;
    float reciprocal;

    count = (*(Model_002A7470 **)(object + 0x24))->anims[animation][0x10];
    if (frame >= count)
        frame = count - 1;

    if (rate <= 0) {
        anim_start_immediate(object, animation, frame);
        return;
    }

    if (object[0x42] == object[0x43] && (object[0x60] & 2))
        *(unsigned int *)(object + 0x44) = 0;

    if (0.025f < *(float *)(object + 0x44) ||
        *(unsigned int *)(object + 0x50) != 0 ||
        *(unsigned int *)(object + 0x54) != 0) {
        slot = moby_alloc_object_slot(object);
        if (slot >= 0) {
            func_PAL_002A2E30(object, slot | 0x300);
            qcopy(&ref_L00_002A7470_00[slot], object + 0x80);
            if (object[0x42] != 0xFF)
                object[0xA9] = object[0x42];
            object[0x42] = 0xFF;
            object[0x40] = slot;
        }
    }

    object[0x41] = frame;
    object[0x43] = animation;
    update_moby_animation_state(object);
    *(float *)(object + 0x48) = 1.0f;
    reciprocal = 1.0f / IntToFloat(rate);
    *(unsigned int *)(object + 0x44) = 0;
    object[0x60] &= 0xFD;
    *(float *)(object + 0x4C) = reciprocal;
    object[0x6C] = (*(Model_002A7470 **)(object + 0x24))->anims[animation][0x11];
}
