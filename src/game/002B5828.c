#include "include_asm.h"
#include "names.h"

/* func_002B5828 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int Quad_002B5828 __attribute__((mode(TI)));
extern void coll_find_ground_below_object(void *, void *, float);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(void *, void *);
extern int coll_check_object_inside_polygon(void *);
extern void anim_start_blended(void *, int, int, int);
extern int coll_is_object_well_above_ground(void *, void *);
extern void part_start_effect_default_table(void *, int, int, void *, float);

typedef struct {
    char pad0[0x10];
    float pos[3];                 /* 0x10 */
    char pad1[0x43 - 0x1C];
    unsigned char b43;            /* 0x43 */
    char pad2[0x48 - 0x44];
    float f48;                    /* 0x48 */
} Self_002B5828;

typedef struct {
    char pad0[0x08];
    float f08, f0C, f10;          /* 0x08 .. 0x10 */
    char pad1[0x28 - 0x14];
    float f28;                    /* 0x28 */
    char pad2[0x34 - 0x2C];
    float f34;                    /* 0x34 */
    unsigned flags38;             /* 0x38 */
    char pad3[0x50 - 0x3C];
    float v50[3];                 /* 0x50 */
    char pad4[0x90 - 0x5C];
    float f90;                    /* 0x90 */
    unsigned flags94;             /* 0x94 */
    char pad5[0x9C - 0x98];
    int flags9C;                  /* 0x9C */
    char pad6[0xA8 - 0xA0];
    float fA8;                    /* 0xA8 */
    char pad7[0xB0 - 0xAC];
    float speed;                  /* 0xB0 */
    float fB4;                    /* 0xB4 */
    char pad8[0xC0 - 0xB8];
    short hC0, hC2;               /* 0xC0 */
    char pad9[0xCC - 0xC4];
    float fCC;                    /* 0xCC */
    float fD0, fD4;               /* 0xD0 */
    char padA[0xE6 - 0xD8];
    unsigned char bE6, bE7, bE8, bE9, bEA;   /* 0xE6 */
} Ctl_002B5828;

/* Checks the object against the ground after moving: marks falls, climbs and slopes, resets a bad position, and plays or changes animations to match. */
void moby_update_ground_contact(Self_002B5828 *self, Ctl_002B5828 *ctl, void *target, void *newpos)
{
    int changed;
    float *position;
    float angle, dist, div, ratio;
    unsigned char b;

    coll_find_ground_below_object(self, ctl, 0.0f);
    changed = 0;
    if (self->pos[2] < ctl->f90 - ctl->f08) {
        changed = 1;
        ctl->flags94 |= 2;
    }
    if (((ctl->flags38 ^ 1) & 1) && ctl->hC2 < 5) {
        if (ctl->f90 + ctl->f0C < self->pos[2]) {
            changed = 1;
            ctl->flags94 |= 1;
        }
    }
    if (ctl->hC0 != 0) {
        angle = mat_fast_helper_a(ctl->v50[2], vec_length_xy(ctl->v50));
        if (ctl->f10 < angle) {
            changed = 1;
            ctl->flags94 |= 4;
        }
    }
    position = self->pos;
    if (changed) {
        *(Quad_002B5828 *)position = *(Quad_002B5828 *)newpos;
        coll_find_ground_below_object(self, ctl, 0.0f);
    }
    if (self->pos[2] <= ctl->f90) {
        if (ctl->f90 <= self->pos[2] - ctl->fA8)
            self->pos[2] = ctl->f90;
        ctl->hC2 = 0;
        ctl->hC0++;
    } else {
        ctl->hC0 = 0;
        ctl->hC2++;
    }
    dist = vec_distance_xy(position, target);
    ctl->fCC = dist;
    if (dist <= ctl->f34)
        ctl->flags94 |= 0x80;
    if (ctl->flags9C & 1) {
        if (coll_check_object_inside_polygon(self))
            ctl->flags9C &= ~1;
        else
            ctl->flags94 |= 0x100;
    }
    if (ctl->flags38 & 0x80) {
        if (self->b43 == ctl->bE8 || self->b43 == ctl->bE9) {
            div = ctl->fD0 != 0.0f ? ctl->fD0 : ctl->f28;
            ratio = ctl->speed / div;
            self->f48 = ratio;
            if (ctl->fD4 < ratio)
                self->f48 = ctl->fD4;
            else if (ratio < 1.0f / ctl->fD4)
                self->f48 = 1.0f / ctl->fD4;
        }
    }
    if (ctl->flags38 & 0x40) {
        if ((ctl->flags9C & 2) && ctl->fB4 != 0.0f) {
            if (self->b43 == ctl->bE8 || self->b43 == ctl->bE9) {
                ctl->bEA = self->b43;
                anim_start_blended(self, 0.0f < ctl->fB4 ? ctl->bE6 : ctl->bE7, 0, 10);
            }
        } else {
            if (self->b43 == ctl->bE6 || self->b43 == ctl->bE7) {
                if (ctl->bEA != 0xFF)
                    anim_start_blended(self, ctl->bEA, 0, 10);
            }
        }
    }
    if (ctl->flags38 & 0x200) {
        if (coll_is_object_well_above_ground(self, ctl))
            part_start_effect_default_table(self, 0, 0x10000, position, 255.0f);
    }
}
