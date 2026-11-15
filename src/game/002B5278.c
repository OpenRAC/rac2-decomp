#include "include_asm.h"
#include "common.h"

/* Measured partial C views; original types and object ownership are unknown. */
typedef unsigned char QwenRecovery_84e23fd54f9f_AbiByte16;

extern int moby_step_controller(QwenRecovery_84e23fd54f9f_AbiByte16 *owner, QwenRecovery_84e23fd54f9f_AbiByte16 *input, float factor);

/* Runs the movement step on an object using its own position and the given factor. */
int moby_step_at_own_position_factor(QwenRecovery_84e23fd54f9f_AbiByte16 *owner, float factor)
{
    return moby_step_controller(owner, owner + 0x10, factor);
}


/* func_002B52A0 is defined in 002B52A0-g8.c. */

/* func_002B5678 is defined in 002B5678-copy.c. */

/* func_002B5828 is matched in 002B5828.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

typedef int TI128_002B5BC0 __attribute__((mode(TI)));
typedef union { TI128_002B5BC0 q; float f[4]; } Vec4Q_002B5BC0;

extern char g_collision_hit[];
extern int CollLine(void *, void *, int, void *, const void *);
extern int GetCollHitMaterial(void);
extern void vec_scale_to_length(char *, char *, float);
extern void vec_clear_128(void *);

/* Looks for ground under the object and stores what it found (slope, ground object, surface) in the controller. */
void coll_find_ground_below_object(char *self, char *ctl, float factor)
{
    Vec4Q_002B5BC0 v, t;
    char *data;
    int hit;

    qcopy(&v, self + 0x10);
    v.f[2] = v.f[2] + (*(float *)(ctl + 8) + 0.1f);
    if (factor != 0.0f) {
        qcopy(&t, self + 0x10);
        t.f[2] = t.f[2] - factor;
    } else {
        qcopy(&t, self + 0x10);
        t.f[2] = t.f[2] - (*(float *)(ctl + 0xC) + 0.1f);
    }
    hit = CollLine(&v, &t, 0, self, 0);
    if (hit) {
        data = g_collision_hit;
        *(float *)(ctl + 0x90) = *(float *)(data + 0x28);
        *(void **)(ctl + 0x88) = *(void **)(data + 0x18);
        *(void **)(ctl + 0x8C) = *(void **)(data + 0x1C);
        *(int *)(ctl + 0xD8) = GetCollHitMaterial();
        vec_scale_to_length(ctl + 0x50, data + 0x40, 1.0f);
    } else {
        *(float *)(ctl + 0x90) = 0.0f;
        *(void **)(ctl + 0x88) = 0;
        *(void **)(ctl + 0x8C) = 0;
        *(int *)(ctl + 0xD8) = -1;
        vec_clear_128(ctl + 0x50);
    }
}

extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);

/* Checks the ground object under the controller against the object and sets a flag if they touch. */
void coll_check_ground_object_touch(char *first, char *second) {
    void *target = *(void **)(second + 0x88);
    if (target != 0 && moby_transform_point_and_rotation_by_parent(first, target, first + 0x10, first + 0xF0, first + 0x10, first + 0xF0) != 0)
        *(unsigned int *)(second + 0x94) |= 0x40;
}

/* Returns the movement controller of an object. */
void *moby_get_controller(u8 *moby) { return *(void **)(*(u8 **)(moby + 0x68) + 0x18); }


/* func_002B5E48 is matched in 002B5E48.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_002B5EF8 is matched in 002B5EF8.c (built with -g). */


/* func_002B60B0 is matched in 002B60B0.c. */

