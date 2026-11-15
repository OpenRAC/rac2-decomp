#include "include_asm.h"
#include "names.h"

typedef struct { char pad[0x68]; float angle; } Slot_002B5EF8;

typedef struct {
    char pad0[0x38];
    unsigned int flags;                 /* 0x38 */
    char pad1[0x48 - 0x3C];
    Slot_002B5EF8 *left;                /* 0x48 */
    Slot_002B5EF8 *right;               /* 0x4C */
} Rec_002B5EF8;

extern float func_00283BE0(float, float);
extern float func_00283B98(float, float);

/* Tilts the left and right foot parts of an object to match how much it is turning. */
void func_002B5EF8(char *self, Rec_002B5EF8 *ctl, float x)
{
    float limit, leftWeight, rightWeight, inv, d;

    if (ctl->left == 0 && ctl->right == 0)
        return;
    if (ctl->flags & 0x10)
        return;
    leftWeight = 0.0f;
    if (ctl->left != 0)
        leftWeight = 1.0f;
    rightWeight = 0.0f;
    if (ctl->right != 0)
        rightWeight = 1.0f;
    inv = 1.0f / (leftWeight + rightWeight);
    leftWeight *= inv;
    rightWeight *= inv;
    limit = 1.5707965f;
    d = fast_subtract_rotations(x, *(float *)(self + 0xF8));
    if (limit < d)
        d = limit;
    else if (d < -limit)
        d = -limit;
    if (*(unsigned short *)(self + 0x34) & 0x8000)
        d = -d;
    if (ctl->left != 0) {
        ctl->left->angle = FastAddRotations(d * leftWeight, ctl->left->angle);
        if (limit < ctl->left->angle)
            ctl->left->angle = limit;
        else if (ctl->left->angle < -limit)
            ctl->left->angle = -limit;
    }
    if (ctl->right != 0) {
        ctl->right->angle = FastAddRotations(d * rightWeight, ctl->right->angle);
        if (limit < ctl->right->angle)
            ctl->right->angle = limit;
        else if (ctl->right->angle < -limit)
            ctl->right->angle = -limit;
    }
}
