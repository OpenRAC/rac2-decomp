/* 4 November 2026, bounded source-lifetime follow-up; not linked.
 * Current replay of the retained profile/body: 1252/1252 bytes, 0/27 USA
 * v1.01 places; only the two one/150 initialization instructions differ.
 * A common named increment for the counter/mode updates produces 1264 bytes.
 * A natural if/else replacing the two-arm switch produces 1248 bytes and
 * changes the dispatch/delay layout. Neither improves the retained switch.
 * No synthetic dependency or discarded source effect is retained. US2/PAL
 * compilation was not repeated after the US mismatch. Reopen only with
 * independent evidence for the original constant birth order.
 */
/* GPT-6.1 Sol, high effort; bounded manual reconstruction, 2026-10-29; not linked.
 * Profile: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -g
 *          -fno-gcse -fno-strength-reduce.
 * USA v1.01: 1252/1252 bytes, 0/27 places. This draft was not checked in other releases.
 * Only two instructions differ: retail initializes s0 = 1 at +0x2C and a1 = 150 at
 * +0x5C; this C initializes those same constants in the opposite order. All remaining
 * non-relocation instructions agree at level 00, including the 0x80 frame, F20 zero lifetime,
 * bounds/rollback stores, all three initialization variants and the pool scan.
 * Disabling GCSE preserves the floating zero but requires an explicit scan base,
 * displacement and shared capacity. Separate shade-result locals and paired assignments
 * recover return-register and store order. Reading the slot owner before capturing its
 * displacement, with strength reduction disabled, recovers the retail offset copy.
 * A const capacity duplicates the two limit loads; moving its initialization into the
 * loop is a tie. An explicit first-kind variable with goto dispatch hoists an extra
 * floating constant and is worse. No volatile accesses or fabricated dependencies used.
 * Reopen with evidence for the original two constant lifetimes or loop-hoisting order.
 * All declarations needed by this draft follow below.
 */
#include "common.h"

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

PoolRecord *func_L00_003F0198(char *owner, int kind, PoolVector *position, float angle) {
    PoolVector direction, offset;
    PoolRecord *slot;
    char *slotOwner;
    PoolRecord *pool = D_L00_001B2BB8;
    int displacement;
    int limit;
    int i, oldCount, random;
    float scale;
    float zero = 0.0f;
    i = 0;
    limit = 150;
    for (; i < 320; i++) {
        slotOwner = pool[i].owner;
        displacement = i * 128;
        if (slotOwner)
            continue;
        switch (kind) {
        case 0:
            oldCount = *(int *)(owner + 0x40);
            *(int *)(owner + 0x40) = oldCount + 1;
            if (oldCount + 1 == limit) {
                *(int *)(owner + 0x40) = oldCount;
                return 0;
            }
            break;
        case 1:
            oldCount = *(int *)(owner + 0x44);
            *(int *)(owner + 0x44) = oldCount + 1;
            if (oldCount + 1 == limit) {
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
            slot->b = slot->a = 90;
            slot->scale = scale * 0.7f;
            slot->strength = 0.075f;
            func_00282F20(&direction, slot->owner, 0.1f);
            func_00282CC0(&slot->position, slot->owner + 0x20, &direction);
            func_00282F20(&offset, &slot->velocity, 0.75f);
            func_00282CC0(&slot->position, &offset, &slot->position);
            slot->angularSpeed = func_002A78D8(0.05235988646745682f, 0.10471977293491364f);
            slot->mode = 2;
            slot->kind = 2;
        } else if (kind == 1) {
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
            slot->strength = func_002A7878(0.06666667f, 0.083333336f);
            random = func_002A7820(100, 120);
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
            slot->b = slot->a = 90;
            slot->scale = scale * 0.7f;
            slot->strength = 0.20833334f;
            func_00282F20(&direction, slot->owner, 0.1f);
            func_00282CC0(&slot->position, slot->owner + 0x20, &direction);
            func_00282F20(&offset, &slot->velocity, 0.75f);
            func_00282CC0(&slot->position, &offset, &slot->position);
            slot->angularSpeed = func_002A78D8(0.05235988646745682f, 0.10471977293491364f);
            slot->mode = 2;
        }
        slot->colorB = slot->colorA = 0x103080;
        slot->gravity = 0.00055555557f;
        scale = func_002A78D8(0.3141593f, 0.35633811354637146f);
        slot->randomB = slot->randomA = scale;
        slot->phase = func_002A7940();
        slot->reserved = 0;
        return slot;
    }
    return 0;
}
