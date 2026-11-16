#include "common.h"

typedef int Quad_L02_00332EF0 __attribute__((mode(TI)));
extern void coll_probe_ground_ahead(void *, void *);
extern float fast_vec_dist(void *, void *);
extern u8 g_arena_anchor_pos[] MACRO_ADDR;
extern float math_facing_angle_from_vector(void *, void *, const void *);
extern float vec_get_vertical_offset(void *, void *, void *);
extern void vec_add_transformed_point(void *, void *, float, float, float);
extern int coll_is_object_well_above_ground(void *, void *);
extern void part_start_effect_default_table(void *, int, int, void *, float);

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
void coll_update_ground_contact(Self_L02_00332EF0 *self, Ctl_L02_00332EF0 *ctl, void *target, void *newpos, int adjust)
{
    int changed;
    float *position;
    float dist, near;

    changed = 0;
    coll_probe_ground_ahead(self, ctl);
    dist = fast_vec_dist(self->pos, g_arena_anchor_pos);
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
        if (ctl->f10 < math_facing_angle_from_vector(self, ctl->v50, 0)) {
            changed = 1;
            ctl->flags94 |= 4;
        }
    }
    position = self->pos;
    if (changed) {
        *(Quad_L02_00332EF0 *)position = *(Quad_L02_00332EF0 *)newpos;
        coll_probe_ground_ahead(self, ctl);
        dist = fast_vec_dist(position, g_arena_anchor_pos);
    }
    if (dist <= ctl->f90 + 0.005f) {
        vec_get_vertical_offset(self, ctl->vA0, 0);
        if (adjust)
            vec_add_transformed_point(self, position, 0.0f, 0.0f, ctl->f90 - dist);
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
        if (coll_is_object_well_above_ground(self, ctl))
            part_start_effect_default_table(self, 0, 0x10000, position, 255.0f);
    }
}
