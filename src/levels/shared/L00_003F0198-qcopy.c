/* Takes a free record from the 128-byte pool, counts it against its owner, and fills it in one of
 * three ways by kind.
 *
 * A unit of its own for its flags: -fno-gcse keeps the floating zero in one register,
 * -fno-strength-reduce keeps the record offset a copy of the shifted index, and the position copy
 * needs -frac2-qcopy with its barrier.
 */
#include "common.h"

/* func_L00_003F0198: the 320-record pool of 128-byte records, owned through their last word. */
typedef int PoolWord128 __attribute__((mode(TI)));
typedef union { PoolWord128 word; float values[4]; } PoolVector;
typedef struct {
    PoolVector position, velocity;
    float gravity, strength, randomA, randomB, angularSpeed, phase;
    float x, y, z, width, height, scale;
    int color, a, b, lifetime, maximumLife, colorA, colorB, shade;
    int mode, reserved, kind;
    char *owner;
} PoolRecord;
extern PoolRecord *g_blast_l00_pool_2 __attribute__((sda));
extern int math_random_int_range(int, int);
extern int func_001163B0(void);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_random_signed_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

/* Finds an unused particle record in the pool of 320 and fills it with random values for one
   of three smoke or spark kinds. Returns null if the pool or the owner's limit is full. */
PoolRecord *blast_alloc_pool_record(char *owner, int kind, PoolVector *position, float angle) {
    PoolVector direction, offset;
    PoolRecord *slot;
    char *slotOwner;
    PoolRecord *pool = g_blast_l00_pool_2;
    int displacement;
    int i, oldCount, random;
    float scale;
    float zero = 0.0f;
    i = 0;
    for (; i < 320; i++) {
        /* Set before any test of the iteration, so loop.c hoists it ahead of 90, the
           direction address and 2; the 150 of the rollback tests then goes last. */
        int secondKind = 1;

        slotOwner = pool[i].owner;
        displacement = i * 128;
        if (slotOwner)
            continue;
        switch (kind) {
        case 0:
            oldCount = *(int *)(owner + 0x40);
            *(int *)(owner + 0x40) = oldCount + 1;
            if (oldCount + 1 == 150) {
                *(int *)(owner + 0x40) = oldCount;
                return 0;
            }
            break;
        case 1:
            oldCount = *(int *)(owner + 0x44);
            *(int *)(owner + 0x44) = oldCount + 1;
            if (oldCount + 1 == 150) {
                *(int *)(owner + 0x44) = oldCount;
                return 0;
            }
            break;
        }
        slot = (PoolRecord *)((char *)g_blast_l00_pool_2 + displacement);
        slot->owner = owner;
        (*(int *)(owner + 0x38))++;
        slot->lifetime = slot->maximumLife = math_random_int_range(95, 127);
        slot->mode = func_001163B0() % 2 + 1;
        slot->kind = kind;
        if (kind == 0) {
            int shade;
            math_apply_axis_rotation_to_quat(&slot->velocity, owner + 0x10, owner, angle);
            slot->x = zero;
            slot->y = zero;
            slot->z = zero;
            shade = math_random_int_range(0, 3);
            slot->shade = ((shade << 16) + (shade << 8)) + shade;
            scale = math_random_float_range(0.15f, 1.25f);
            slot->height = slot->width = scale * 0.125f;
            scale = math_random_float_range(0.5f, 1.8f);
            slot->b = slot->a = 90;
            slot->scale = scale * 0.7f;
            slot->strength = 0.075f;
            vec_scale_to_length(&direction, slot->owner, 0.1f);
            FastVecAdd(&slot->position, slot->owner + 0x20, &direction);
            vec_scale_to_length(&offset, &slot->velocity, 0.75f);
            FastVecAdd(&slot->position, &offset, &slot->position);
            slot->angularSpeed = math_random_signed_float_range(0.05235988646745682f, 0.10471977293491364f);
            slot->mode = 2;
            slot->kind = 2;
        } else if (kind == secondKind) {
            int shade;
            math_apply_axis_rotation_to_quat(&slot->velocity, owner + 0x10, owner, math_random_angle());
            slot->x = zero;
            slot->y = zero;
            slot->z = zero;
            shade = math_random_int_range(0, 13);
            slot->shade = ((shade << 16) + (shade << 8)) + shade;
            scale = math_random_float_range(0.25f, 0.5f);
            slot->height = slot->width = scale;
            slot->scale = math_random_float_range(1.0f, 1.5f);
            slot->strength = math_random_float_range(0.06666667f, 0.083333336f);
            random = math_random_int_range(100, 120);
            slot->b = slot->a = random;
            qcopy(&slot->position, position);
            slot->mode = 2;
            slot->angularSpeed = zero;
        } else if (kind == 2) {
            int shade;
            math_apply_axis_rotation_to_quat(&slot->velocity, owner + 0x10, owner, angle);
            slot->x = zero;
            slot->y = zero;
            slot->z = zero;
            shade = math_random_int_range(0, 3);
            slot->shade = ((shade << 16) + (shade << 8)) + shade;
            scale = math_random_float_range(0.15f, 1.25f);
            slot->height = slot->width = scale * 0.125f;
            scale = math_random_float_range(0.5f, 1.8f);
            slot->b = slot->a = 90;
            slot->scale = scale * 0.7f;
            slot->strength = 0.20833334f;
            vec_scale_to_length(&direction, slot->owner, 0.1f);
            FastVecAdd(&slot->position, slot->owner + 0x20, &direction);
            vec_scale_to_length(&offset, &slot->velocity, 0.75f);
            FastVecAdd(&slot->position, &offset, &slot->position);
            slot->angularSpeed = math_random_signed_float_range(0.05235988646745682f, 0.10471977293491364f);
            slot->mode = 2;
        }
        slot->colorB = slot->colorA = 0x103080;
        slot->gravity = 0.00055555557f;
        scale = math_random_signed_float_range(0.3141593f, 0.35633811354637146f);
        slot->randomB = slot->randomA = scale;
        slot->phase = math_random_angle();
        slot->reserved = 0;
        return slot;
    }
    return 0;
}
