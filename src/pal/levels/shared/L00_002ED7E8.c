#include "include_asm.h"
#include "names.h"

/* func_PAL_L00_002ED7E8, the PAL copy of func_L00_002EC248: the same C, where the gravity
   scale 0.00027777778f becomes 0.00040000002f and the two lifetimes are rescaled to 50 Hz
   in float, (scale * 10 * 5 + 2) / 6, written as (scale * 50 + 2) * (1 / 6). */

typedef struct { float x,y,z,w; } BurstVector;
extern void vec_random_direction(void *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_local_offset_to_world(void *, void *, float, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern void vec_clear_128(void *);
extern int FastTweenColor(int, int, float);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

void func_PAL_L00_002ED7E8(char *object, void *positionOffset, void *velocityOffset,
                     int count, int palette, float positionSpread, float velocitySpread,
                     float width, float gravity, float duration)
{
    BurstVector position, velocity, endpoint;
    int start, end, i;
    int first, middle, last;
    int texture = 0x1003C;
    float scale, small;
    gravity *= 0.00040000002f;
    palette &= 0xFF;
    for (i = 0; i < count; i++) {
        vec_random_direction(&position, 0.0f, positionSpread);
        FastVecAdd(&position, &position, positionOffset);
        vec_local_offset_to_world(object, &position, position.x, position.y, position.z);
        vec_random_direction(&velocity, 0.0f, velocitySpread);
        FastVecAdd(&velocity, &velocity, velocityOffset);
        matrix_mul_vec3(&velocity, &velocity, object + 0xC0);
        scale = duration * math_random_float_range(0.5f, 1.5f);
        small = (scale * 50.0f + 2.0f) * 0.16666667f;
        first = FloatToInt(small);
        middle = FloatToInt((scale * 200.0f + 2.0f) * 0.16666667f);
        last = FloatToInt(small);
        velocity.w = width * math_random_float_range(0.1f, 0.4f);
        vec_clear_128(&endpoint);
        endpoint.z = -gravity * (float)(first + middle + last);
        FastVecAdd(&endpoint, &endpoint, &velocity);
        switch (palette) {
        case 1:
            start = FastTweenColor(0x80102040, 0x801010A0, math_random_float_range(0.0f, 1.0f));
            end = FastTweenColor(0x00102040, 0x001010A0, math_random_float_range(0.0f, 1.0f));
            break;
        case 3:
            start = FastTweenColor(0x80201608, 0x80402510, math_random_float_range(0.0f, 1.0f));
            end = FastTweenColor(0x00201608, 0x00402510, math_random_float_range(0.0f, 1.0f));
            break;
        case 2:
            start = FastTweenColor(0x80104010, 0x8020A020, math_random_float_range(0.0f, 1.0f));
            end = FastTweenColor(0x00104010, 0x0020A020, math_random_float_range(0.0f, 1.0f));
            break;
        case 0:
        default:
            start = FastTweenColor(0x80004080, 0x80408080, math_random_float_range(0.0f, 1.0f));
            end = FastTweenColor(0x00004080, 0x00408080, math_random_float_range(0.0f, 1.0f));
            break;
        }
        part_spawn_trail(&position, &velocity, &endpoint, start, end,
                     first, middle, last, texture);
    }
}
