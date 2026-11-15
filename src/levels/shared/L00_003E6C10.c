#include "include_asm.h"
#include "common.h"

/* func_L00_003E6C10: the twin of func_L00_003F0680 over its own effect table; the
   offset step follows a direction taken from the owner's object (func_002AFFD8). */

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

/* Updates every glow particle owned by one object: it fades the colour and size, moves the particle with the object, and frees it when it has run out. */
void func_L00_003E6C10(char *owner)
{
    Vector displacement, axis, velocity;
    Effect *record;
    char *object, *data;
    float numerator, denominator, fraction, first, second, curve;
    int i;

    i = 0;
    ClearVector128(&displacement);
    for (; i < 320; i++) {
        record = (Effect *)(i * sizeof(Effect) + (unsigned int)D_L00_001B2B54);
        if (record->owner == owner) {
            numerator = IntToFloat(record->remaining);
            denominator = IntToFloat(record->duration);
            fraction = 1.0f - numerator / denominator;
            if (record->state == 0)
                goto interpolate;
            if (record->state == 1) {
                first = IntToFloat(record->initialCount);
                second = IntToFloat(record->initialCount);
                curve = Square(fraction);
                record->count = FloatToInt(first - second * curve);
                if (record->kind != 2) {
interpolate:
                    record->color = FastTweenColor(record->colorStart, record->colorEnd, fraction);
                    record->spin = record->spinStart + (record->spinEnd - record->spinStart) * fraction;
                    record->offset = record->offsetStart + (record->offsetEnd - record->offsetStart) * fraction;
                    record->size = record->sizeStart + (record->sizeEnd - record->sizeStart) * fraction;
                    vec_scale_to_length(&displacement, &record->direction, record->scale * EaseOutQuad(fraction));
                } else {
                    vec_scale_to_length(&displacement, &record->direction, record->scale);
                }
            }
            ComputeViewDirection(*(char **)(owner + 0x30) + 0x10, &axis, 1);
            vec_scale_to_length(&velocity, &axis, record->offset);
            FastVecAdd(record, record, &velocity);
            if (record->kind != 1)
                FastVecAdd(record, &displacement, record);
            object = *(char **)(record->owner + 0x30);
            data = *(char **)(object + 0x68);
            record->phase = FastAddRotations(record->phase, record->spin);
            if (*(unsigned char *)(object + 0x20) == 2 && *(int *)(data + 0x14) < 38 && record->kind != 2) {
                record->state = 1;
                record->duration = record->remaining = RandomIntRange(30, 45);
                record->sizeStart = record->size;
                record->colorStart = record->color;
                record->offsetStart = record->offset;
                record->initialCount = record->count;
                record->spinStart = record->spin;
            }
            if (FastFloatHelperD(&record->remaining) != 0) {
                if (record->state == 0) {
                    record->state = 1;
                    if (record->kind == 1) {
                        record->duration = 30;
                        record->remaining = 30;
                    } else {
                        record->duration = 55;
                        record->remaining = 55;
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
