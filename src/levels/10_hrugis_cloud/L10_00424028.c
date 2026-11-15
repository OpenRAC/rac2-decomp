#include "include_asm.h"
#include "common.h"


typedef int TI128 __attribute__((mode(TI)));

extern int func_337518(int a0, char *a1, int a2);

extern void func_42DF10(void *a0);

extern void *D_L10_001ADE90 __attribute__((sda));

extern int func_32AC10(int a0);


extern float func_309B38(float f12, float f13);

extern float func_309B80(float f12, float f13);


/* Checks a cloud object against a world test and returns true when it is blocked. */
int cloud_check_object_blocked(int object) {
    return func_337518(object, (char *)0x230000, 0) != 0;
}

/* Spawns the given number of cloud objects. */
void cloud_spawn_objects(int count, void *arg) {
    int i;

    if (count > 0) {
        i = count;
        do {
            func_42DF10(arg);
            i--;
        } while (i != 0);
    }
}

/* Returns the pointer kept in a level global. */
void *level_get_global_pointer(void) {
    return D_L10_001ADE90;
}

extern char *D_L10_001B2528;
extern void func_32AF78(void *a0);


/* func_L10_00425798 is defined in L10_00425798-flags.c. */

/* func_L10_00424028 is defined in L10_00424028-g8.c. */


/* func_L10_00424528 is defined in L10_00424528-g8.c. */

/* func_L10_00424CD0 is defined in L10_00424028-hud-g8.c. */

/* func_L10_00425508 is defined in L10_00424028-reward-g8.c. */


/* func_L10_00424448 is defined in L10_00424448-g8.c. */

/* func_L10_0042B500 is defined in L10_00424028-cloud-g8.c. */

extern u8 *CreateMoby(s32);
extern f32 FastAddRotations(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);

#define L10_PARTNER(state) (*(u8 **)((state) + 4))

/* Two-state update of a cloud body with a kind-0x11CD partner. State 0 sets the body up
   (size 512, alpha 0xFF/0x1FF, scale from its class), spawns the partner the same way and
   moves the body up 6 (facing pi) or down 6 by the state flag; both states then ease the
   +0xF8 value with one of two helpers and copy the angle, that value and the position to
   the partner. */
void cloud_body_update(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);

    switch (object[0x20]) {
    case 0:
        object[0x20] = 1;
        *(u16 *)(object + 0x32) = 0x1FF;
        object[0x30] = 0xFF;
        *(f32 *)(object + 0x10) = 512.0f;
        *(f32 *)(object + 0x14) = 512.0f;
        *(f32 *)(object + 0x18) = 512.0f;
        *(s32 *)(object + 0x1C) = 0;
        *(f32 *)(object + 0x2C) = *(f32 *)(*(u8 **)(object + 0x24) + 0x24) * 4.0f;
        L10_PARTNER(state) = CreateMoby(0x11CD /* moby class 4557 */);
        L10_PARTNER(state)[0x30] = 0xFF;
        *(u16 *)(L10_PARTNER(state) + 0x32) = 0x1FF;
        *(f32 *)(L10_PARTNER(state) + 0x2C) =
            *(f32 *)(*(u8 **)(L10_PARTNER(state) + 0x24) + 0x24) * 4.0f;
        if (*(s32 *)state != 0) {
            *(f32 *)(object + 0x18) += 6.0f;
            *(f32 *)(object + 0xF0) = 3.1415927f;
        } else {
            *(f32 *)(object + 0x18) -= 6.0f;
        }
    case 1:
        if (*(s32 *)state != 0)
            *(f32 *)(object + 0xF8) = FastAddRotations(*(f32 *)(object + 0xF8), 0.0049087391f);
        else
            *(f32 *)(object + 0xF8) = fast_subtract_rotations(*(f32 *)(object + 0xF8), 0.0049087391f);
        *(f32 *)(L10_PARTNER(state) + 0xF0) = *(f32 *)(object + 0xF0);
        *(f32 *)(L10_PARTNER(state) + 0xF8) = *(f32 *)(object + 0xF8);
        qcopy(L10_PARTNER(state) + 0x10, object + 0x10);
        break;
    }
}

#undef L10_PARTNER

/* func_L10_0042BE20 is defined in L10_00424028-g8.c (this unit has no $gp access for it). */

/* func_L10_0042BEE0 is in the sibling file L10_00424028-g8.c (it reads $gp data). */

/* func_L10_0042DF10 is defined in L10_0042DF10-g8.c. */

/* func_L10_0042E100 is defined in L10_0042E100-g16.c. */

/* Defined in L10_0042E4D0.c. */

/* func_L10_0042E660 is defined in L10_0042E660-g8.c. */
