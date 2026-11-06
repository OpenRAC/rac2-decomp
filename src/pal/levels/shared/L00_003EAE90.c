#include "include_asm.h"
#include "common.h"

/* func_PAL_L00_003EAE90, the PAL copy of func_L00_003E6C10: the same C, where the
   fade threshold 38 becomes 32, the fade length is scaled to 50 Hz and 30/55 become 25/46.
   The twin of func_L00_003F0680 over its own effect table; the offset step follows a
   direction taken from the owner's object (func_002AFFD8).
   -fno-rerun-loop-opt: retail loads the divisor 6 at the division. The second loop pass
   would hoist it out of the loop (life 3 * threshold about 61 >= 181 insns) and reload would
   then load it twice. */

typedef struct { float x, y, z, w; } Vector;
typedef struct {
    Vector position, direction;
    float unused20, scale, spinStart, spin, spinEnd, phase;
    float offsetStart, offset, offsetEnd, sizeStart, size, sizeEnd;
    int unused50, remaining, duration, initialCount, count;
    int colorStart, color, colorEnd, unused70, state, kind;
    char *owner;
} Effect;
extern Effect *D_L00_001B2B54 MACRO_ADDR;
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
extern void func_002AFFD8(void *, void *, int);

void func_PAL_L00_003EAE90(char *owner)
{
    Vector displacement, axis, velocity;
    Effect *record;
    char *object, *data;
    float numerator, denominator, fraction, first, second, curve;
    int i;

    i = 0;
    func_00282C88(&displacement);
    for (; i < 320; i++) {
        record = (Effect *)(i * sizeof(Effect) + (unsigned int)D_L00_001B2B54);
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
            func_002AFFD8(*(char **)(owner + 0x30) + 0x10, &axis, 1);
            func_00282F20(&velocity, &axis, record->offset);
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
next:;
    }
}
