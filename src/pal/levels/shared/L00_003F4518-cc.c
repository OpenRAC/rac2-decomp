/* func_PAL_L00_003F4518, the PAL copy of func_L00_003F0198: the same C. */
/* Takes a free record from the 128-byte pool, counts it against its owner, and fills it in one of
 * three ways by kind.
 *
 * A unit of its own for its flags: -fno-gcse keeps the floating zero in one register,
 * -fno-strength-reduce keeps the record offset a copy of the shifted index, and the position copy
 * needs -frac2-qcopy with its barrier.
 */
#include "common.h"

/* func_PAL_L00_003F4518: the 320-record pool of 128-byte records, owned through their last word. */
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
extern PoolRecord *D_L00_001B2BB8 __attribute__((sda));
extern int func_002A7820(int, int);
extern int func_001163B0(void);
extern void func_002ACEC0(void *, void *, void *, float);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_002A78D8(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

PoolRecord *func_PAL_L00_003F4518(char *owner, int kind, PoolVector *position, float angle) {
    PoolVector direction, offset;
    PoolRecord *slot;
    char *slotOwner;
    PoolRecord *pool = D_L00_001B2BB8;
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
        slot = (PoolRecord *)((char *)D_L00_001B2BB8 + displacement);
        slot->owner = owner;
        (*(int *)(owner + 0x38))++;
        slot->lifetime = slot->maximumLife = func_002A7820(95, 127);
        slot->mode = func_001163B0() % 2 + 1;
        slot->kind = kind;
        if (kind == 0) {
            int shade;
            func_002ACEC0(&slot->velocity, owner + 0x10, owner, angle);
            slot->x = zero;
            slot->y = zero;
            slot->z = zero;
            shade = func_002A7820(0, 3);
            slot->shade = ((shade << 16) + (shade << 8)) + shade;
            scale = func_002A7878(0.15f, 1.25f);
            slot->height = slot->width = scale * 0.125f;
            scale = func_002A7878(0.5f, 1.8f);
            slot->b = slot->a = 75;
            slot->scale = scale * 0.7f;
            slot->strength = 0.09f;
            func_00282F20(&direction, slot->owner, 0.1f);
            func_00282CC0(&slot->position, slot->owner + 0x20, &direction);
            func_00282F20(&offset, &slot->velocity, 0.75f);
            func_00282CC0(&slot->position, &offset, &slot->position);
            slot->angularSpeed = func_002A78D8(0.062831864f, 0.12566373f);
            slot->mode = 2;
            slot->kind = 2;
        } else if (kind == secondKind) {
            int shade;
            func_002ACEC0(&slot->velocity, owner + 0x10, owner, func_002A7940());
            slot->x = zero;
            slot->y = zero;
            slot->z = zero;
            shade = func_002A7820(0, 13);
            slot->shade = ((shade << 16) + (shade << 8)) + shade;
            scale = func_002A7878(0.25f, 0.5f);
            slot->height = slot->width = scale;
            slot->scale = func_002A7878(1.0f, 1.5f);
            slot->strength = func_002A7878(0.080000006f, 0.10000001f);
            random = func_002A7820(83, 100);
            slot->b = slot->a = random;
            qcopy(&slot->position, position);
            slot->mode = 2;
            slot->angularSpeed = zero;
        } else if (kind == 2) {
            int shade;
            func_002ACEC0(&slot->velocity, owner + 0x10, owner, angle);
            slot->x = zero;
            slot->y = zero;
            slot->z = zero;
            shade = func_002A7820(0, 3);
            slot->shade = ((shade << 16) + (shade << 8)) + shade;
            scale = func_002A7878(0.15f, 1.25f);
            slot->height = slot->width = scale * 0.125f;
            scale = func_002A7878(0.5f, 1.8f);
            slot->b = slot->a = 75;
            slot->scale = scale * 0.7f;
            slot->strength = 0.25000003f;
            func_00282F20(&direction, slot->owner, 0.1f);
            func_00282CC0(&slot->position, slot->owner + 0x20, &direction);
            func_00282F20(&offset, &slot->velocity, 0.75f);
            func_00282CC0(&slot->position, &offset, &slot->position);
            slot->angularSpeed = func_002A78D8(0.062831864f, 0.12566373f);
            slot->mode = 2;
        }
        slot->colorB = slot->colorA = 0x103080;
        slot->gravity = 0.00080000004f;
        scale = func_002A78D8(0.37699118f, 0.42760575f);
        slot->randomB = slot->randomA = scale;
        slot->phase = func_002A7940();
        slot->reserved = 0;
        return slot;
    }
    return 0;
}
