#include "include_asm.h"
#include "names.h"

/* Update two linked parts from a valid parent and propagate object state and color. */
typedef struct DobboPartsObject252 DobboPartsObject252;

typedef struct DobboPartsDescriptor252 {
    unsigned char gap0[0x2f0];
    DobboPartsObject252 *parts[2];
    DobboPartsObject252 *parent;
} DobboPartsDescriptor252;

struct DobboPartsObject252 {
    unsigned char gap0[0x20];
    unsigned char status;
    unsigned char gap21[0x10];
    unsigned char disabled;
    unsigned char gap32[2];
    unsigned short flags;
    unsigned char gap36[0x32];
    DobboPartsDescriptor252 *descriptor;
    unsigned char gap6c[0x3e];
    short class_code;
};

extern void moby_copy_joint_transform_to_object(void *, void *, int, int);

extern void moby_copy_color(void *, void *);

typedef float f32;

typedef unsigned char u8;

typedef int s32;

typedef struct {
    u8 field00[0x1f0];
    f32 field1F0[4];
    u8 field200[0xe0];
    f32 field2E0;
    u8 field2E4[4];
    f32 field2E8;
} NativeAngleState __attribute__((aligned(16)));

typedef struct {
    u8 field00[0x10];
    f32 field10[4];
    u8 field20[0x48];
    NativeAngleState *field68;
} NativeAngleOwner __attribute__((aligned(16)));

extern void FastVecSub(f32 *output, const f32 *left, const f32 *right);

extern void vec_transform_by_object_or_given(NativeAngleOwner *owner, f32 *output, const f32 *input, s32 mode);

extern f32 mat_fast_helper_a(f32 x, f32 y);

extern f32 vec_length_xy(const f32 *vector);

extern void FastVecSub(float *, const float *, const float *);

/* validate descriptorparent classD0E/status then attach two optionalparts, propagate flag/disabled state and original packed-color helper */
/* Attaches the two arm parts to the torso and copies the on or off state to them. */
void trooper_attach_arm_parts(DobboPartsObject252 *object)
{
    DobboPartsDescriptor252 *descriptor = object->descriptor;
    DobboPartsObject252 *parent = descriptor->parent;
    int i;
    if (!parent || parent->class_code != 0xd0e /* Megacorp Trooper Torso */ || parent->status == 0xfe || parent->status == 0xfd)
        return;
    for (i = 0; i < 2; ++i) {
        if (descriptor->parts[i]) {
            moby_copy_joint_transform_to_object(descriptor->parent, descriptor->parts[i], i, i == 1 ? 6 : 0);
            if (object->disabled) {
                descriptor->parts[i]->flags &= ~1U;
                descriptor->parts[i]->disabled = 1;
            } else {
                descriptor->parts[i]->flags |= 1;
                descriptor->parts[i]->disabled = 0;
            }
            moby_copy_color(object, descriptor->parts[i]);
        }
    }
}


/* func_L09_003F9708 lives in L09_003F9708-g8.c. */

extern s32 func_33E658(s32 moby);

/* Refreshes the cached 16-bit handle of the state's 0x2DC entry. */
/* Toggles the enemy's cached path handle between empty and the current path. */
s32 path_toggle_handle_cache(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    short cachedHandle = *(short *)(vars + 0x1CA);

    if (cachedHandle != 0) {
        *(short *)(vars + 0x1CA) = 0;
        return 0;
    }
    *(short *)(vars + 0x1CA) = func_33E658(*(s32 *)(vars + 0x2DC));
    return 1;
}

/* func_L09_003F9970 lives in L09_003F9970.c. */

/* func_L09_003F9A70 is in the sibling -g8 unit. */

/* func_L09_003F9D08 is in the sibling activation unit. */


/* computes a local target direction and stores bounded horizontal and vertical angles through the original math helpers */
/* Turns the object to face its target, with limits on how far it can turn left, right, up and down. */
void moby_turn_toward_target_limited(NativeAngleOwner *owner) {
    f32 direction[4] __attribute__((aligned(16)));
    NativeAngleState *state = owner->field68;
    f32 angle, xy_length;
    FastVecSub(direction, state->field1F0, owner->field10);
    vec_transform_by_object_or_given(owner, direction, direction, 0);
    angle = mat_fast_helper_a(direction[0], direction[1]);
    state->field2E0 = angle;
    if (0.78539824f < angle) state->field2E0 = 0.78539824f;
    else if (angle < -0.78539824f) state->field2E0 = -0.78539824f;
    xy_length = vec_length_xy(direction);
    angle = -mat_fast_helper_a(xy_length, direction[2]);
    state->field2E8 = angle;
    if (0.52359885f < angle) state->field2E8 = 0.52359885f;
    else if (angle < -0.52359885f) state->field2E8 = -0.52359885f;
}

/* func_L09_00410200 is in L09_003F9468-dust-g8.c. */

/* func_L09_00410608 lives in L09_00410608-g8.c. */

/* func_L09_00410B40 lives in the sibling small-data unit (L09_003F9468-g8.c). */

/* func_L09_00410BC8 lives in L09_00410BC8-sprites.c. */

/* func_L09_0041A700 lives in the sibling small-data unit (L09_003F9468-g8.c). */
