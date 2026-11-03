/* functional: high. From the 2026-10-29 near miss (1252/1252 bytes, two constant loads swapped), reread against retail: the qcopy builtin is a plain 128-bit copy, the small-data attribute dropped, typedefs renamed for the unit. */
/* func_L00_003F0198: spawns one smoke/debris particle into the 320-record pool at D_L00_001B2BB8 (records of 0x80,
   owner at +0x7C). Kinds 0 and 1 are capped at 150 live per owner (+0x40/+0x44); kind 0 and 2 puff from the owner's
   axis with a random size and spin, kind 1 starts at POSITION. Returns the record, or 0 when the pool or cap is full. */

#include "common.h"

typedef int PoolWord_3F0198 __attribute__((mode(TI)));
typedef union { PoolWord_3F0198 word; float values[4]; } PoolVector_3F0198;
typedef struct {
    PoolVector_3F0198 position, velocity;
    float gravity, strength, randomA, randomB, angularSpeed, phase;
    float x, y, z, width, height, scale;
    int color, a, b, lifetime, maximumLife, colorA, colorB, shade;
    int mode, reserved, kind;
    char *owner;
} PoolRecord_3F0198;

extern PoolRecord_3F0198 *D_L00_001B2BB8;
extern int func_002A7820(int, int);
extern int func_001163B0(void);
extern void func_002ACEC0(void *, void *, void *, float);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_002A78D8(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

PoolRecord_3F0198 *func_L00_003F0198(char *owner, int kind, PoolVector_3F0198 *position, float angle)
{
    PoolVector_3F0198 direction, offset;
    PoolRecord_3F0198 *slot;
    PoolRecord_3F0198 *pool = D_L00_001B2BB8;
    int i, count, shade, random;
    float scale;

    for (i = 0; i < 320; i++) {
        if (pool[i].owner != 0)
            continue;
        if (kind == 0) {
            count = *(int *)(owner + 0x40);
            *(int *)(owner + 0x40) = count + 1;
            if (count + 1 == 150) {
                *(int *)(owner + 0x40) = count;
                return 0;
            }
        } else if (kind == 1) {
            count = *(int *)(owner + 0x44);
            *(int *)(owner + 0x44) = count + 1;
            if (count + 1 == 150) {
                *(int *)(owner + 0x44) = count;
                return 0;
            }
        }
        slot = D_L00_001B2BB8 + i;
        slot->owner = owner;
        *(int *)(owner + 0x38) += 1;
        random = func_002A7820(95, 127);
        slot->lifetime = random;
        slot->maximumLife = random;
        random = func_001163B0();
        slot->kind = kind;
        slot->mode = random % 2 + 1;
        if (kind == 0) {
            func_002ACEC0(&slot->velocity, owner + 0x10, owner, angle);
            slot->z = 0.0f;
            slot->x = 0.0f;
            slot->y = 0.0f;
            shade = func_002A7820(0, 3);
            slot->shade = (shade << 16) + (shade << 8) + shade;
            scale = func_002A7878(0.15f, 1.25f) * 0.125f;
            slot->height = scale;
            slot->width = scale;
            scale = func_002A7878(0.5f, 1.8f);
            slot->b = 90;
            slot->a = 90;
            slot->scale = scale * 0.7f;
            slot->strength = 0.075f;
            func_00282F20(&direction, slot->owner, 0.1f);
            func_00282CC0(&slot->position, slot->owner + 0x20, &direction);
            func_00282F20(&offset, &slot->velocity, 0.75f);
            func_00282CC0(&slot->position, &offset, &slot->position);
            slot->angularSpeed = func_002A78D8(0.0523598865f, 0.104719773f);
            slot->kind = 2;
            slot->mode = 2;
        } else if (kind == 1) {
            func_002ACEC0(&slot->velocity, owner + 0x10, owner, func_002A7940());
            slot->x = 0.0f;
            slot->y = 0.0f;
            slot->z = 0.0f;
            shade = func_002A7820(0, 13);
            slot->shade = (shade << 16) + (shade << 8) + shade;
            scale = func_002A7878(0.25f, 0.5f);
            slot->height = scale;
            slot->width = scale;
            slot->scale = func_002A7878(1.0f, 1.5f);
            slot->strength = func_002A7878(0.06666667f, 0.083333336f);
            random = func_002A7820(100, 120);
            slot->b = random;
            slot->a = random;
            slot->position.word = position->word;
            slot->mode = 2;
            slot->angularSpeed = 0.0f;
        } else if (kind == 2) {
            func_002ACEC0(&slot->velocity, owner + 0x10, owner, angle);
            slot->z = 0.0f;
            slot->x = 0.0f;
            slot->y = 0.0f;
            shade = func_002A7820(0, 3);
            slot->shade = (shade << 16) + (shade << 8) + shade;
            scale = func_002A7878(0.15f, 1.25f) * 0.125f;
            slot->height = scale;
            slot->width = scale;
            scale = func_002A7878(0.5f, 1.8f);
            slot->b = 90;
            slot->a = 90;
            slot->scale = scale * 0.7f;
            slot->strength = 0.20833334f;
            func_00282F20(&direction, slot->owner, 0.1f);
            func_00282CC0(&slot->position, slot->owner + 0x20, &direction);
            func_00282F20(&offset, &slot->velocity, 0.75f);
            func_00282CC0(&slot->position, &offset, &slot->position);
            slot->angularSpeed = func_002A78D8(0.0523598865f, 0.104719773f);
            slot->mode = kind;
        }
        slot->colorB = 0x103080;
        slot->colorA = 0x103080;
        slot->gravity = 0.00055555557f;
        scale = func_002A78D8(0.3141593f, 0.356338114f);
        slot->randomB = scale;
        slot->randomA = scale;
        slot->phase = func_002A7940();
        slot->reserved = 0;
        return slot;
    }
    return 0;
}
