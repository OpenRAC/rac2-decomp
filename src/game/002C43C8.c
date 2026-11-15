#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad00[0x20];
    u8 state;
    u8 pad21[0xAA - 0x21];
    s16 uid;
} Moby2C43C8;

typedef struct {
    Moby2C43C8 *moby;
    u8 joint;
    u8 spread;
    s16 uid;
    f32 scale;
    f32 dist;
} Attach2C43C8;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    f32 dir[4];
    Attach2C43C8 at;
} Effect2C43C8;

extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float IntToFloat(int);
extern void moby_transform_joint_point(void *, int, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern float math_random_float_range(float, float);
extern void part_kill(void *);

/* Updates an effect attached to a joint of another object, with a random sideways spread.
   It disappears when that object is gone or dying. */
void part_update_moby_joint_effect(Effect2C43C8 *e) {
    float mtx[16] __attribute__((aligned(16)));
    float off[4] __attribute__((aligned(16)));
    Attach2C43C8 *at = &e->at;
    Moby2C43C8 *target = at->moby;
    float size;
    float keep;
    float spread_range;
    float offset_amount;

    if (target == 0 || target->uid != at->uid || target->state == 0xFE || target->state == 0xFD) {
        part_kill(e);
        return;
    }
    size = at->scale * math_random_float_range(0.05f, 1.0f);
    keep = e->dir[3];
    moby_transform_joint_to_world(e->at.moby, at->joint, e->pos);
    moby_transform_joint_point(e->at.moby, at->joint, mtx);
    spread_range = IntToFloat(at->spread);
    offset_amount = math_random_float_range(-spread_range, spread_range);
    vec_scale_to_length(off, mtx, (offset_amount * 0.01f - 1.0f) * at->dist);
    FastVecAdd(e->dir, e->pos, off);
    e->pos[3] = size;
    e->dir[3] = keep;
}
