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
extern void vec_clear_128(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int FastTweenColor(int, int, float);
extern float math_square(float);
extern float math_ease_out_quad(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float FastAddRotations(float, float);
extern int math_random_int_range(int, int);
extern int math_fast_float_d(void *);
extern void cam_compute_view_direction(void *, void *, int);

/* Updates every glow particle owned by one object: it fades the colour and size, moves the particle with the object, and frees it when it has run out. */
void part_update_owned_effect(char *owner)
{
    Vector displacement, axis, velocity;
    Effect *record;
    char *object, *data;
    float numerator, denominator, fraction, first, second, curve;
    int i;

    i = 0;
    vec_clear_128(&displacement);
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
                curve = math_square(fraction);
                record->count = FloatToInt(first - second * curve);
                if (record->kind != 2) {
interpolate:
                    record->color = FastTweenColor(record->colorStart, record->colorEnd, fraction);
                    record->spin = record->spinStart + (record->spinEnd - record->spinStart) * fraction;
                    record->offset = record->offsetStart + (record->offsetEnd - record->offsetStart) * fraction;
                    record->size = record->sizeStart + (record->sizeEnd - record->sizeStart) * fraction;
                    vec_scale_to_length(&displacement, &record->direction, record->scale * math_ease_out_quad(fraction));
                } else {
                    vec_scale_to_length(&displacement, &record->direction, record->scale);
                }
            }
            cam_compute_view_direction(*(char **)(owner + 0x30) + 0x10, &axis, 1);
            vec_scale_to_length(&velocity, &axis, record->offset);
            FastVecAdd(record, record, &velocity);
            if (record->kind != 1)
                FastVecAdd(record, &displacement, record);
            object = *(char **)(record->owner + 0x30);
            data = *(char **)(object + 0x68);
            record->phase = FastAddRotations(record->phase, record->spin);
            if (*(unsigned char *)(object + 0x20) == 2 && *(int *)(data + 0x14) < 38 && record->kind != 2) {
                record->state = 1;
                record->duration = record->remaining = math_random_int_range(30, 45);
                record->sizeStart = record->size;
                record->colorStart = record->color;
                record->offsetStart = record->offset;
                record->initialCount = record->count;
                record->spinStart = record->spin;
            }
            if (math_fast_float_d(&record->remaining) != 0) {
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
