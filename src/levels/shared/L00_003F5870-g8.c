#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern s32 ref_L00_003F5870_00 MACRO_ADDR;
extern float ref_L00_003F5870_01 __attribute__((sda));
extern int func_002AFFD8(void *, void *, int);
extern float func_00282C48(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

typedef struct {
    float offset[4];
    float position[4];
    float angle;
    float length;
    float f28;
    float f2c;
} L00Joint;

/* Sets one joint of a chain of 0x30-byte joints: its offset is the up axis (optionally
   transformed) or, past the first joint, the direction from the previous joint's position
   rotated by the joint's angle, scaled by the joint's length. */
void func_L00_003F5870(L00Joint *joints, int index)
{
    float up[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float diff[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));

    *(TI128 *)up = 0;
    up[2] = 1.0f;
    if (ref_L00_003F5870_00 != 0)
        func_002AFFD8(up, joints[index].position, 1);
    if ((float)index == 0.0f || func_00282C48(joints[index].angle) < 0.00001f) {
        func_00282D30(dir, up, joints[index].length);
    } else {
        func_00282CF0(diff, joints[index].position, joints[index - 1].position);
        func_00282F20(normal, diff, 1.0f);
        func_002AB668(normal, normal, joints[index].angle);
        func_002ACDE8(dir, up, normal);
        func_00282D30(dir, dir, joints[index].length);
    }
    func_00282CC0(joints[index].offset, joints[index].position, dir);
    joints[index].offset[3] = ref_L00_003F5870_01;
}
