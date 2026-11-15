#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
extern u8 D_L03_00188660[];
extern void AttachManipulator(void *entity, int id, void *target);
extern void build_axis_rotation_quaternion(void *target, int a, float f);
extern float fast_subtract_rotations(float f0, float f1);
extern void moby_update_eased_node(void *entity, void *target, int a, float f0, float f1);
extern void endako_boss_blend_parts(u8 *entity);
extern u8 *D_L03_001B2A1C __attribute__((sda));
extern u8 *D_L03_001FB5A0[];
extern u8 D_001A7B08[0x40] __attribute__((sda));

/* func_L03_003F64E8 lives in L03_003F64E8-g8.c */

/* steps the entity's two blend channels and its rate */
void func_PAL_L03_003FAE88(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);

    if (*(u8 *)(state + 0xD1) == 0) AttachManipulator(entity, 7, state + 0xD0);
    build_axis_rotation_quaternion(state + 0xE0, 2, *(float *)(state + 0x338));
    *(float *)(state + 0x338) = fast_subtract_rotations(*(float *)(state + 0x338), 0.49916422f);
    moby_update_eased_node(entity, state + 0x110, 0, 0.0432f, 0.43200004f);
    moby_update_eased_node(entity, state + 0x190, 1, 0.0432f, 0.43200004f);
}

