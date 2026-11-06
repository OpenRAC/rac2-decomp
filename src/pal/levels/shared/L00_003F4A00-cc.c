/* func_PAL_L00_003F4A00, the PAL copy of func_L00_003F0680: the same C, where the frame
   counts 30, 55 and 38 become 25, 46 and 32 and the random duration is scaled for 50 Hz.
   -fno-rerun-loop-opt: the scale's divisor 6 stays in the loop. The first loop pass rejects
   it (threshold 60 * life 3 < 183 insns); a second pass would hoist it into a saved register. */
#include "common.h"

typedef struct { float x, y, z, w; } Vector;
typedef struct {
    Vector position, direction;
    float unused20, scale, spinStart, spin, spinEnd, phase;
    float offsetStart, offset, offsetEnd, sizeStart, size, sizeEnd;
    int unused50, remaining, duration, initialCount, count;
    int colorStart, color, colorEnd, unused70, state, kind;
    char *owner;
} Effect;
extern Effect *D_L00_001B2BB8 MACRO_ADDR;
extern void func_00282C88(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00283D38(int, int, float);
extern float func_002A7790(float);
extern float func_002A7798(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283B98(float, float);
extern int func_002A7820(int, int);
extern int func_00282948(void *);

void func_PAL_L00_003F4A00(char *owner)
{
    Vector displacement, velocity;
    Effect *record;
    char *object, *data;
    float numerator, denominator, fraction, first, second, curve;
    int i;

    i = 0;
    func_00282C88(&displacement);
    for (; i < 320; i++) {
        record = (Effect *)(i * sizeof(Effect) + (unsigned int)D_L00_001B2BB8);
        if (record->owner == owner) {
            numerator = func_00283CE0(record->remaining);
            denominator = func_00283CE0(record->duration);
            fraction = 1.0f - numerator / denominator;
            if (record->state == 0)
                goto interpolate;
            if (record->state == 1) {
                first = func_00283CE0(record->initialCount);
                second = func_00283CE0(record->initialCount);
                curve = func_002A7790(fraction);
                record->count = func_00283CF0(first - second * curve);
                if (record->kind != 2) {
interpolate:
                    record->color = func_00283D38(record->colorStart, record->colorEnd, fraction);
                    record->spin = record->spinStart + (record->spinEnd - record->spinStart) * fraction;
                    record->offset = record->offsetStart + (record->offsetEnd - record->offsetStart) * fraction;
                    record->size = record->sizeStart + (record->sizeEnd - record->sizeStart) * fraction;
                    func_00282F20(&displacement, &record->direction, record->scale * func_002A7798(fraction));
                } else {
                    func_00282F20(&displacement, &record->direction, record->scale);
                }
            }
            func_00282F20(&velocity, record->owner, record->offset);
            func_00282CC0(record, record, &velocity);
            if (record->kind != 1)
                func_00282CC0(record, &displacement, record);
            object = *(char **)(record->owner + 0x30);
            data = *(char **)(object + 0x68);
            record->phase = func_00283B98(record->phase, record->spin);
            if (*(unsigned char *)(object + 0x20) == 2 && *(int *)(data + 0x14) < 32 && record->kind != 2) {
                record->state = 1;
                record->duration = record->remaining = ((s32)(func_002A7820(30, 45)) * 5 + 2) / 6;
                record->sizeStart = record->size;
                record->colorStart = record->color;
                record->offsetStart = record->offset;
                record->initialCount = record->count;
                record->spinStart = record->spin;
            }
            if (func_00282948(&record->remaining) != 0) {
                if (record->state == 0) {
                    record->state = 1;
                    if (record->kind == 1) {
                        record->duration = 25;
                        record->remaining = 25;
                    } else {
                        record->duration = 46;
                        record->remaining = 46;
                    }
                } else if (record->count > 0) {
                    record->state = 2;
                    record->count--;
                } else {
                    (*(int *)(record->owner + 0x38))--;
                    switch (record->kind) {
                    case 0:
                        (*(int *)(record->owner + 0x40))--;
                        break;
                    case 1:
                        (*(int *)(record->owner + 0x44))--;
                        break;
                    }
                    record->owner = 0;
                }
            }
        }
    }
}
