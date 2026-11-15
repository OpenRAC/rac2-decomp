#include "common.h"

typedef int Quad_L02_00332EF0 __attribute__((mode(TI)));
extern void func_L02_00333300(void *, void *);
extern float func_00282E48(void *, void *);
extern u8 D_L02_001B3210[] MACRO_ADDR;
extern float func_L02_00329410(void *, void *, const void *);
extern float func_002AFF38(void *, void *, void *);
extern void func_002AFD88(void *, void *, float, float, float);
extern int func_002B63C0(void *, void *);
extern void func_002A90C8(void *, int, int, void *, float);

typedef struct {
    char pad0[0x10];
    float pos[4];                 /* 0x10 */
} Self_L02_00332EF0;

typedef struct {
    char pad0[0x08];
    float f08, f0C, f10;          /* 0x08 .. 0x10 */
    char pad1[0x34 - 0x14];
    float f34;                    /* 0x34 */
    unsigned flags38;             /* 0x38 */
    char pad3[0x50 - 0x3C];
    float v50[4];                 /* 0x50 */
    char pad4[0x90 - 0x60];
    float f90;                    /* 0x90 */
    unsigned flags94;             /* 0x94 */
    char pad5[0xA0 - 0x98];
    char vA0[0x20];               /* 0xA0 */
    short hC0, hC2;               /* 0xC0 */
    char pad9[0xCC - 0xC4];
    float fCC;                    /* 0xCC */
} Ctl_L02_00332EF0;

/* Checks how far an object is from the ground and from its target and sets the contact flags. It counts frames on and off the ground and snaps the object to the ground when asked. */
void func_L02_00332EF0(Self_L02_00332EF0 *self, Ctl_L02_00332EF0 *ctl, void *target, void *newpos, int adjust)
{
    int changed;
    float *position;
    float dist, near;

    changed = 0;
    ProbeGroundAhead(self, ctl);
    dist = fast_vec_dist(self->pos, D_L02_001B3210);
    if (dist < ctl->f90 - ctl->f08) {
        changed = 1;
        ctl->flags94 |= 2;
    }
    if (((ctl->flags38 ^ 1) & 1) && ctl->hC2 < 5) {
        if (ctl->f90 + ctl->f0C < dist) {
            changed = 1;
            ctl->flags94 |= 1;
        }
    }
    if (ctl->hC0 != 0) {
        if (ctl->f10 < ComputeFacingAngleFromVector(self, ctl->v50, 0)) {
            changed = 1;
            ctl->flags94 |= 4;
        }
    }
    position = self->pos;
    if (changed) {
        *(Quad_L02_00332EF0 *)position = *(Quad_L02_00332EF0 *)newpos;
        ProbeGroundAhead(self, ctl);
        dist = fast_vec_dist(position, D_L02_001B3210);
    }
    if (dist <= ctl->f90 + 0.005f) {
        GetVerticalOffset(self, ctl->vA0, 0);
        if (adjust)
            AddTransformedPointToVector(self, position, 0.0f, 0.0f, ctl->f90 - dist);
        ctl->hC2 = 0;
        ctl->hC0++;
    } else if (ctl->f90 + ctl->f0C <= dist) {
        ctl->hC0 = 0;
        ctl->hC2++;
    }
    near = fast_vec_dist(position, target);
    ctl->fCC = near;
    if (near <= ctl->f34)
        ctl->flags94 |= 0x80;
    if (ctl->flags38 & 0x200) {
        if (IsObjectWellAboveGround(self, ctl))
            StartEffectWithDefaultTable(self, 0, 0x10000, position, 255.0f);
    }
}
